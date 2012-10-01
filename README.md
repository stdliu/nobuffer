nobuffer
========

Nobuffer is a program to help turn output stream buffering off.

Introduction
------------

Nobuffer not only remove output buffers of stdout and stderr, but also remove fopen returned file stream's buffer.
Furthermore it disables setbuf to prevent program set a user buffer after fopen.

Idea and part of the code from [checkinstall](http://checkinstall.izto.org)/installwatch.

*NOTE: only tested under Linux with glibc 2.5.*

Examples
---------

Run the following code in shell:

	while date; do sleep 1; done | grep . | cat

You can not immediately see the output of the date.
With nobuffer, to turn grep's stdout stream's buffer off, you will see the output immediately:

	while date; do sleep 1; done | nobuffer grep . | cat
