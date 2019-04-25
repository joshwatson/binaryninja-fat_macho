# Fat Mach-O BinaryView for Binary Ninja

This Binary Ninja plugin extends the Mach-O BinaryView to support Fat Mach-O files.

# Supported Platforms
I haven't tested this on anything but MacOS, but there is no reason why it shouldn't be buildable on both Linux and Windows as well. If you do build it on one of those systems, and make changes to the Makefile, I would definitely appreciate it if you filed a PR to update the repo!

# Building
## Requirements
* `libbinaryninja.a` built from [binaryninja-api](https://github.com/vector35/binaryninja-api)
* Binary Ninja (note: support for this plugin is currently only on the development channel; it does not work on stable yet)

## Building
1. Update the first two variables in `Makefile` to reflect the locations of your `libbinaryninja.a` and `binaryninjaapi.h`

```make
# Path to prebuilt libbinaryninjaapi.a
BINJA_API_A := ~/Documents/Repos/binaryninja-api/bin/libbinaryninjaapi.a

# Path to binaryninjaapi.h and json
INC := -I/Users/user/Documents/Repos/binaryninja-api/
```

2. Run the following:
```sh
make
make install
```

This will copy `libfat_macho.dylib` into your Binary Ninja plugins directory.

# Usage
Open a Fat Mach-O binary. If any of the contained architectures are supported, one of them will be displayed immediately.

You can choose a different contained Mach-O using the bottom right menu:
[!img](images/menu.png)

# Acknowledgements
Thanks to @melomac for [adding support for arm and ppc](https://github.com/joshwatson/binaryninja-fat_macho/pull/2)!
