DCPU-VV
=======

[![Build Status](https://travis-ci.org/vieux/dcpu-vv.png?branch=master)](undefined)

dcpu-vv is a dcpu-16 emulator *written in C*

You can found dcpu-16 full specs on [0x10c.com](http://0x10c.com/doc/dcpu-16.txt "http://0x10c.com/doc/dcpu-16.txt")

One of the particularity of dcpu-vv is the capacity to emulate multiple dcpu16 at the same time, using *ncurses* to render the screens


For new it is able to run programs like this: http://0x10co.de/2j83h

SCREENSHOTS
===========

![ENvOS & Color Test](https://raw.github.com/vieux/dcpu-vv/master/screenshots/EnvOS_color.png "dcpu-vv running ENvOS & color test at the same time")
![Matrix test](https://raw.github.com/vieux/dcpu-vv/master/screenshots/matrix.png "dcpu-vv running a matrix test")
![Color Test](https://raw.github.com/vieux/dcpu-vv/master/screenshots/color_test.png "dcpu-vv running a color test")


FEATURES
========

DONE
----

### Specifications
0x10c.com v1.1 specifications compliant
It supports both hex and binary files

### Output
basic output rendering (no blink, no highlight)
border at 0x8280

### Input
keyboard works if there is one DCPU-16

### Misc
.core files generation upon crash

TO DO
-----

### Specifications
Lets wait 1.2 specs

### Input
Handle keyboard for multiple DCPU (for exemple press F1 to cycle between DCPU)

### Misc
add a -step option (step by step)
