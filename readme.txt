                              Desexonix

                 Sexonix image extractor by Popov Evgeniy Alekseyevich

                             Version 0.6.7

System requirements

68 kilobytes of free space on storage media.
100 kilobytes of free RAM.

Description and usage

This program lets you extract the images from the Sexonix game. It is stored in the Sexonix.pic file.
The extracted images will be saved in Truevision TGA format (256 colors with an indexed palette).
This program takes a target file name as the command-line argument.

License

This program is distributed under the GNU GENERAL PUBLIC LICENSE.

Exit codes

0: The operation was successfully completed.
1: Can't open the input file.
2: Can't create the output file.
3: The target file length is invalid.
4: Can't allocate memory.

Third-party code

Some code was taken from XXX Games tools by the CTPAX-X team (http://www.ctpax-x.org/?goto=files&show=21).
It was relicensed with the permission of the author.

Source code

The code was compiled under Open Watcom.
You can compile it with any modern C compiler.
The source code can be compiled for a wide range of operating systems, but you need to create a makefile or a build script by yourself.
I provide only two things: the binary file for Windows and the makefile for Linux.

Install and uninstall under Linux

Follow these steps:

1. Extract the content of the source code archive.
2. Open a terminal and go to the source code directory.
3.
Run as root to install: make install
Run as root to uninstall: make uninstall

Version history

0.1: Initial version.
0.2: The target file size checking has been added.
0.3-0.4.2: The small changes.
0.4.3: A small bug has been fixed.
0.4.4: The small changes.
0.4.5: A small bug has been fixed.
0.4.6-0.5.3: The small changes.
0.5.3.1-0.5.3.2: The makefile has been updated.
0.5.4-0.5.9: The small changes.
0.6: The unused code has been removed.
0.6.1-0.6.2: The small changes.
0.6.3: Visual C++ support has improved.
0.6.3.1-0.6.3.2: The documentation has been updated.
0.6.4: The small changes.
0.6.4.1-0.6.4.2: The documentation has been updated.
0.6.5: The source code was recompiled under Tiny C Compiler.
0.6.5.1: The makefile has been updated.
0.6.6: The small changes.
0.6.6.1: The documentation has been updated.
0.6.7: The small changes.