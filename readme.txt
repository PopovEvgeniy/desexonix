                              Desexonix

                 Sexonix image extractor by Popov Evgeniy Alekseyevich         

                             Version 0.5.1

System requirement

52 kilobytes free space on storage media.
100 kilobytes of free RAM.

Description and usage

This program let you extract an images from Sexonix game. It store in Sexonix.pic file.
Extracted images will saved in Truevision TGA format(256 colors with indexed palette).
This program takes a target file name as command line argument.

License

This program distributed under GNU GENERAL PUBLIC LICENSE.

Exit codes

0 - Operation successfully complete.
1 - Can't open input file.
2 - Can't create output file.
4 - Can't allocate memory.

Third-party code

Some code is based on XXX Games tools sources by CTPAX-X team(http://www.ctpax-x.org/?goto=files&show=21).
It relicensed with permission from the author.

Source code

The program source code was compiled under Open Watcom.
But you can do it under any modern C compiler.
Source code can be compiled for wide range operation systems, but you need create makefile or build script by yourself.
I provide only two things: compiled binary file for Windows and makefile for Linux.

Install and uninstall under Linux

Follow this steps:

1.Extract content of source code archive.
2.Open terminal and go to source code directory.
3.
Run as root for install: make install
Run as root for uninstall: make uninstall

Contact

You can send me a letter to tuzik87@inbox.ru.

Version history

0.1 - Initial version.
0.2 - Target file size checking was added.
0.3 - 0.4.2 - Small changes.
0.4.3 - Small bug was fixed.
0.4.4 - Small changes.
0.4.5 - Small bug was fixed.
0.4.6 - 0.5.1 - Small changes.