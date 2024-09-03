                              Desexonix

                 Sexonix image extractor by Popov Evgeniy Alekseyevich         

                             Version 0.6.3.2

System requirement

70 kilobytes of free space on storage media.
100 kilobytes of free RAM.

Description and usage

This program lets you extract images from the Sexonix game. It is stored in the Sexonix.pic file.
Extracted images will be saved in Truevision TGA format (256 colors with an indexed palette).
This program takes a target file name as a command-line argument.

License

This program is distributed under GNU GENERAL PUBLIC LICENSE.

Exit codes

0 — Operation successfully completed.
1 — Can't open input file.
2 — Can't create output file.
3 — Invalid target file size.
4 — Can't allocate memory.

Third—party code

Some code was taken from XXX Games tools by the CTPAX-X team (http://www.ctpax-x.org/?goto=files&show=21).
It was re-licensed with permission from the author.

Source code

The code was compiled under Open Watcom.
You can compile it with any modern C compiler.
Source code can be compiled for a wide range of operating systems, but you need to create a makefile or build a script by yourself.
I provide only two things: the binary file for Windows and the makefile for Linux.

Install and uninstall under Linux

Follow these steps:

1. Extract the content of the source code archive.
2. Open a terminal and go to the source code directory.
3.
Run as root to install: make install
Run as root to uninstall: make uninstall

Contact

You can send me a letter to tuzik87@inbox.ru.

Version history

0.1 — Initial version.
0.2 — Target file size checking added.
0.3 — 0.4.2 — Small changes.
0.4.3 — Small bug fixed.
0.4.4 — Small changes.
0.4.5 — Small bug fixed.
0.4.6 — 0.5.3 — Small changes.
0.5.3.1 — 0.5.3.2 — Makefile updated.
0.5.4 — 0.5.9 — Small changes.
0.6 — Unused code removed.
0.6.1 — 0.6.2 — Small changes.
0.6.3 — Visual C++ support improved.
0.6.3.1 — 0.6.3.2 — Documentation updated.