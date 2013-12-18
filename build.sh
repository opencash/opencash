#!/bin/bash

#set -x

is_ios_simulator_ar_avail()
{
  XCODE_IPHONE_SIMULATOR_DIR=/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform
  IPHONE_SIMULATOR_AR=${XCODE_IPHONE_SIMULATOR_DIR}/Developer/usr/bin/ar
  return $(test -d "$XCODE_IPHONE_SIMULATOR_DIR" -a -e "$IPHONE_SIMULATOR_AR")
}

platform="all"
configuration="Debug"
make_targets="all"

if [ "x$1" = "x-h" -o "x$1" = "x--help" ]
then
  echo "Usage: $(basename $0) [all|host|ios-device|ios-simulator|ios-universal|osx-ios-universal|android] [Debug|Release] [make_target_1 [make_target_2 [...]]]"
  exit
fi

if [ $# -ge 1 ]
then
  platform=$1
  shift
fi

if [ $# -ge 1 ]
then
  configuration=$1
  shift
fi

if [ $# -ge 1 ]
then
  make_targets="$@"
fi

if [ $platform = "all" ]
then
  platforms="host ios-device ios-simulator ios-universal osx-ios-universal android"
elif [ $platform = "ios-universal" ]
then
  platforms="ios-device ios-simulator ios-universal"
elif [ $platform = "osx-ios-universal" ]
then
  platforms="host ios-device ios-simulator ios-universal osx-ios-universal"
else
  platforms=$platform
fi

parent_pwd=$(pwd)

for p in $platforms; do
  echo "==> building platform '$p'"
  p_build_dir="$parent_pwd/build/$p/$configuration"
  p_out_dir="$p_build_dir/out"
  p_out_lib_dir="$p_out_dir/lib"
  p_out_lib_static_filename="$p_out_lib_dir/libopencash-static.a"

  mkdir -p "$p_build_dir"
  cd "$p_build_dir"

  if [ $p = "ios-simulator" ] && ! is_ios_simulator_ar_avail
  then
    echo "======"
    echo "Warning:"
    echo "\`ar\` not found for iPhoneSimulator at"
    echo "${IPHONE_SIMULATOR_AR}"
    echo
    echo "This is probably a bug with Xcode 5 and the build might"
    echo "fail on \`ar\` not being found. You can fix it with the"
    echo "following command:"
    echo
    echo "sudo ln -s ../../Toolchains/XcodeDefault.xctoolchain/usr/bin/ar $IPHONE_SIMULATOR_AR"
    echo "======"
  fi

  if [ $p = "android" ]
  then
    if [ "x$ANDROID_STANDALONE_TOOLCHAIN" = "x" -a ! -d /opt/android-toolchain ]
    then
      echo "\$ANDROID_STANDALONE_TOOLCHAIN is not set and /opt/android-toolchain"
      echo "does not exist (or is not a directory). You must either set"
      echo "\$ANDROID_STANDALONE_TOOLCHAIN to the path of your Android"
      echo "standalone toolchain, or symlink it from /opt/android-toolchain"
      echo
      echo "You can generate a standalone toolchain using the script"
      echo "build/tool/make-standalone-toolchain.sh provided with the NDK."
      echo "You must use a clang-based toolchain. Please refer to NDK docs"
      echo "for more info."
      echo
      echo "Exiting."
      exit 1
    fi

    # Set PATH. Value set in $ANDROID_STANDALONE_TOOLCHAIN
    # overrides /opt/android-toolchain
    PATH_OLD=$PATH
    [ -d /opt/android-toolchain ] && PATH=/opt/android-toolchain/bin:$PATH
    [ "x$ANDROID_STANDALONE_TOOLCHAIN" != "x" ] && PATH=$ANDROID_STANDALONE_TOOLCHAIN/bin:$PATH
  fi

  if [ $p = "ios-universal" ]
  then
    rm -rf "$p_out_dir"
    mkdir -p "$p_out_dir"
    cp -r "$parent_pwd/build/ios-device/$configuration/out/include" "$p_out_dir/include"
    mkdir -p "$p_out_lib_dir"
    lipo -create \
      "$parent_pwd/build/ios-device/$configuration/out/lib/libopencash-static.a" \
      "$parent_pwd/build/ios-simulator/$configuration/out/lib/libopencash-static.a" \
      -output "$p_out_lib_static_filename" >/dev/null

  elif [ $p = "osx-ios-universal" ]
  then
    rm -rf "$p_out_dir"
    mkdir -p "$p_out_dir"
    cp -r "$parent_pwd/build/ios-device/$configuration/out/include" "$p_out_dir/include"
    mkdir -p "$p_out_lib_dir"
    lipo -create \
      "$parent_pwd/build/host/$configuration/out/lib/libopencash-static.a" \
      "$parent_pwd/build/ios-universal/$configuration/out/lib/libopencash-static.a" \
      -output "$p_out_lib_static_filename" >/dev/null

  else
    [ $configuration = "Debug" ] && cmake_debug_arg="-DOC_DEBUG=ON"
    cmake $cmake_debug_arg -DOC_TESTS=ON -DOC_STATIC=ON -DOC_PLATFORM=$p "$parent_pwd" &&
      make $make_targets

    # create the aggregated static library
    if [ $p = "android" ]
    then
      tmp_file=$(mktemp -t ar)
      echo "CREATE $p_out_lib_static_filename" >> $tmp_file
      echo "ADDLIB $p_out_lib_dir/libPocoFoundation.a" >> $tmp_file
      echo "ADDLIB $p_out_lib_dir/libodb.a" >> $tmp_file
      echo "ADDLIB $p_out_lib_dir/libodb-sqlite.a" >> $tmp_file
      echo "ADDLIB $p_out_lib_dir/libsqlite3.a" >> $tmp_file
      echo "ADDLIB $p_out_lib_dir/libopencash.a" >> $tmp_file
      echo "SAVE" >> $tmp_file
      echo "END" >> $tmp_file
      arm-linux-androideabi-ar -M < $tmp_file
      rm -rf $tmp_file
    else
      rm -rf "$p_out_lib_static_filename" &&
      libtool -static -o "${p_out_lib_static_filename}.tmp" "${p_out_lib_dir}"/*.a >/dev/null &&
      mv "${p_out_lib_static_filename}.tmp" "${p_out_lib_static_filename}"
    fi
  fi

  if [ "x$PATH_OLD" != "x" ]
  then
    PATH=$PATH_OLD
    unset PATH_OLD
  fi

  echo "<== done platform '$p'"
  cd "$parent_pwd"
done

echo "done."
