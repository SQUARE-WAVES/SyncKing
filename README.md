# SyncKing

### what is this?
this is the firmware for a looper device. It's written to be run on the electrosmith [https://electro-smith.com/products/daisy-seed](daisy-seed) module.

### how to build
this uses the normal daisy bulid system, which is basically just a makefile that pulls in "libdaisy" which handles all the STM32 setup and basic stuff.
you will need libdaisy in the directory above this one in the heirarchy. After that just hit make.

If you add new files you will need to add them to the makefile if they aren't under the devices audio or screens header. all files in those directories are picked up automatically.

### current hardware
right now this project is at the prototype stage, it's based around my daisy protoyping board, with 4 encoders. The io is expanded with 2 mcp23017 i2c io expanders running 8 leds and 8 buttons a piece. This is technically a problem as the mcp23017 has an issue it's i2c interface that supposedly causes problems if you use all 8 pins on either register as inputs, but I haven't encountered that yet. Moving out of the prototype stage I will probably shift to mcp23018s or some other IO expander.
