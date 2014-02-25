# OpenCash

A free open-source accounting software (early stage).

## How to build OpenCash (quick'n'dirty)

1. Build `libopencash` for all platforms:
       ```
cd libopencash
./build.sh all Debug
       ```

2. Open the Xcode workspace:
       ```
open opencash-xcode/OpenCash.xcworkspace
       ```

3. Manually trigger build for targets `OpenCash.framework`, `OpenCash-OSX` and `OpenCash-iOS`

### Project structure

```
.
├── LICENSE.txt      # OpenCash's license (GPLv2)
├── README.md        # This current file
├── libopencash      # Shared core in C++
├── opencash-android # Android app built on top of libopencash (NDK)
├── opencash-cocoa   # Cocoa framework around libopencash
├── opencash-ios     # iOS app built on top of opencash-cocoa
├── opencash-osx     # Mac app built on top of opencash-cocoa
└── opencash-xcode   # Xcode project to build opencash-coca, opencash-ios
                     #   and opencash-osx
```

### References to external repositories

This project uses [`git subtree`](https://github.com/git/git/blob/master/contrib/subtree/git-subtree.txt) to pull in external repos. Currently the following externals are set up:

| Directory     | Origin |
|---------------|--------|
| `libopencash` | https://github.com/opencash/libopencash.git |
| `opencash-android` | https://github.com/opencash/opencash-android.git |
| `opencash-cocoa` | https://github.com/opencash/opencash-cocoa.git |
| `opencash-osx` | https://github.com/opencash/opencash-osx.git |
| `opencash-ios` | https://github.com/opencash/opencash-ios.git |
| `opencash-xcode` | https://github.com/opencash/opencash-xcode.git |

How to use `git subtree` on the example of `libopencash`:

```
git remote add -f libopencash https://github.com/opencash/libopencash.git
git subtree push -P libopencash libopencash master
git subtree pull -P libopencash libopencash

# to push all external repos
for p in libopencash opencash-android opencash-cocoa opencash-ios opencash-osx opencash-xcode; do git subtree push -P $p $p master; done
```


[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/opencash/opencash/trend.png)](https://bitdeli.com/free "Bitdeli Badge")
