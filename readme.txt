                              Desexonix

                 Sexonix image extractor by Popov Evgeniy Alekseyevich         

                             Version 0.5.6

System requirement

52 kilobytes free space on storage media.
100 kilobytes of free RAM.

Description and usage

This program let you extract images from Sexonix game. It stores in Sexonix.pic file.
Extracted images will save in Truevision TGA format(256 colors with indexed palette).
This program takes a target file name as command line argument.

License

This program distributed under GNU GENERAL PUBLIC LICENSE.

Exit codes

0 - Operation successfully complete.
1 - Can't open input file.
2 - Can't create output file.
3 - Invalid target file size.
4 - Can't allocate memory.

Third-party code

Some code taken from XXX Games tools by CTPAX-X team(http://www.ctpax-x.org/?goto=files&show=21).
It re-licensed with permission from the author.

Source code

The program source code compiled under Open Watcom.
But you can do it under any modern C compiler.
Source code can be compiled for wide range operating systems, but you need to create makefile or build script by yourself.
I provide only two things: compiled the binary file for Windows and makefile for Linux.

Install and uninstall under Linux

Follow these steps:

1.Extract content of source code archive.
2.Open terminal and go to source code directory.
3.
Run as root for install: make install
Run as root for uninstall: make uninstall

Contact

You can send me a letter to tuzik87@inbox.ru.

Version history

0.1 - Initial version.
0.2 - Target file size checking added.
0.3 - 0.4.2 - Small changes.
0.4.3 - Small bug fixed.
0.4.4 - Small changes.
0.4.5 - Small bug fixed.
0.4.6 - 0.5.3 - Small changes.
0.5.3.1 - 0.5.3.2 - Makefile updated.
0.5.4 - 0.5.6 - Small changes.