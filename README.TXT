  Simple program to set comm port mode before invoking BinkleyTerm under
  OS/2 2.0 with Gary Rosema's com16550.sys

  Communications parameters for comm ports are set to 19200 baud,
  8 data bits, no parity, and 1 stop bit.

  Usage is:  dumbmode COM[n] <n=1 or 2>

Original (dumbmode.org) released to the public domain
by John Tarbox (FidoNet 1:150/130.0)

Modified version (accepts comm port parameter) ported by David Troendle
(FidoNet 1:396/5.0) and released to the public domain

Why?

Some systems can only use a 16550x chip on COM2.  This version has been tested
for both COM1 and COM2, it MAY work with COM3 or COM4, but the word is still
out.  All original files are retained in the DUMBMODE.LZH archive...

Jim Sterrett (1:396/51.0)