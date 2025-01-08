# SyncKing

### what is this?
this is the firmware for a looper device. It's written to be run on the electrosmith [https://electro-smith.com/products/daisy-seed](daisy-seed) module.

### how to build
this uses the normal daisy bulid system, which is basically just a makefile that pulls in "libdaisy" which handles all the STM32 setup and basic stuff.
you will need libdaisy in the directory above this one in the heirarchy. After that just hit make.

If you add new files you will need to add them to the makefile if they aren't under the devices audio or screens header. all files in those directories are picked up automatically.
