========
nobuffer
========
------------------------------------------------
Run command with no output stream buffering.
------------------------------------------------

SYNOPOSIS
=========
| nobuffer [OPTION] command [command arguments]

DESCRIPTION
===========
Run command with no output stream buffering.
Nobuffer not only remove output buffers of stdout and stderr, but also remove fopen returned file stream's buffer.
Furthermore it disables setbuf to prevent program set a user buffer after fopen.

Options:

-e, --export
  Print export expression and exit.

-p [install_dir], --prefix [install_dir]
  Set install prefix dir.

-h, --help
  Print help message.

EXAMPLES
========

``$ while date; do sleep 1; done | nobuffer grep . | cat``

``$ tail -f logfile | nobuffer sed 's/replace/replace_with/' > /tmp/fifo``

Or run ``eval $(nobuffer -e)`` first and run your commmand without nobuffer prefixed.

``$ eval $(nobuffer -e)``

``$ while date; do sleep 1; done | grep . | cat``


CAVEATS
=======
Only tested under Linux with glibc 2.5.

AUTHOR
======
Writen by Liu Bin <stdliu@gamil.com>, idea and part of the code from the installwatch.

SEE ALSO
========
stdbuf(1), unbuffer(1)
