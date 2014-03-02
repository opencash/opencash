#### EARLY STAGE

Please note that `opencash-cli` (and more broadly, OpenCash) is in a very early
stage of development. The current focus lies on getting infrastructure set up
and cross-platform issues sorted out. The actual functionality is still very
limited.

_This project is not usable yet!_

[![Build Status](https://travis-ci.org/opencash/opencash-cli.png?branch=master)](https://travis-ci.org/opencash/opencash-cli)

# What is `opencash-cli`?

`opencash-cli` is the command line app of OpenCash, a free open-source
accounting software (early stage).

## How to build `opencash-cli` (quick'n'dirty)

Run the following in the current folder (`-q` for less verbosity):

```
> ./gradlew -q clean build test
```

The output binaries are located in `./build/binaries/`. The executables are
linked statically and don't required other dependencies.

More information on the build system with:

```
> ./gradlew describe
```

## License

[GNU General Public License v2
(GPL-2.0)](https://tldrlegal.com/license/gnu-general-public-license-v2)
