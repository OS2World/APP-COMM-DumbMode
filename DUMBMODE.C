/*

  DUMBMODE.C

  Simple program to set comm port mode before invoking BinkleyTerm under
  OS/2 2.0 with Gary Rosema's com16550.sys

  Communications parameters for COM1 are set to 19200 baud,
  8 data bits, no parity, and 1 stop bit.

  Usage is:  dumbmode

  Released to the public domain by John Tarbox (FidoNet 1:150/130.0)
*/

#define INCL_BASE
#define INCL_DOSDEVIOCTL
#include <os2.h>

#include <string.h>
#include <stdio.h>

#define PARITY_NONE 0
#define PARITY_ODD 1
#define PARITY_EVEN 2

#define ONE_STOP_BIT 0
#define ONEANDAHALF_STOP_BITS 1
#define TWO_STOP_BITS 2

#define COMPORT 1

int DisplayDCB (void);

DCBINFO usDCB;
unsigned chandle;			       /* handle for COM port */

int main(int argc, char *argv[])
{
  USHORT usBaudRate = 19200;
  USHORT usBaudRateOld;
  LINECONTROL lc;
  unsigned action;
  unsigned openflag = 0x01;
  unsigned openmode = 0x12;
  PSZ pszCOMPORT;

  pszCOMPORT = argv[1];
  /* open com port */
  if (DosOpen(pszCOMPORT, &chandle, &action, 0L, 0, openflag, openmode, 0L))
      puts("\nCan't open COM device.\n");

  if (DosDevIOCtl(&usBaudRateOld, 0L, ASYNC_GETBAUDRATE, 1, chandle))
      puts("\nCan't get baud rate.");

  if (DosDevIOCtl(&lc, 0L, ASYNC_GETLINECTRL, 1, chandle))
      puts("\nCan't get line control info.");

  printf( "Old baud : %u:%c,%u,%u\n\r",
       usBaudRateOld, lc.bParity, lc.bDataBits, lc.bStopBits );

  DisplayDCB();

  if (DosDevIOCtl(NULL, &usBaudRate, ASYNC_SETBAUDRATE, 1, chandle))
      puts("\nCan't set baud rate.");

  lc.bDataBits = 8;
  lc.bParity   = PARITY_NONE;
  lc.bStopBits = ONE_STOP_BIT;

  if (DosDevIOCtl(NULL, &lc, ASYNC_SETLINECTRL, 1, chandle))
      puts("\nCan't configure COM port.");

  usDCB.fbCtlHndShake = 8;
  usDCB.fbFlowReplace = 128;
  usDCB.fbTimeout     = 3;

  if (DosDevIOCtl(0L, &usDCB, ASYNC_SETDCBINFO, 1, chandle))
      puts("\nCan't set DCB info.");

  puts("\nComm port set...");
  DisplayDCB();
  puts("\nTerminating...");

  return 0;

} /* main */

int DisplayDCB()
{
  if (DosDevIOCtl(&usDCB, 0L, ASYNC_GETDCBINFO, 1, chandle))
       {
	  puts("\nCan't get dcb info.");
	  return 99;
       }

    puts( "DCB info : \n\r" );

    printf("  Write timeout   : %u\n\r", usDCB.usWriteTimeout);
    printf("  Read  timeout   : %u\n\r", usDCB.usReadTimeout);
    printf("  Handshake       : %u\n\r", usDCB.fbCtlHndShake);
    printf("  Flow replace    : %u\n\r", usDCB.fbFlowReplace);
    printf("  Timeout         : %u\n\r", usDCB.fbTimeout);
    printf("  Error repl. char: %u\n\r", usDCB.bErrorReplacementChar);
    printf("  Break repl. char: %u\n\r", usDCB.bBreakReplacementChar);
    printf("  Xon char        : %u\n\r", usDCB.bXONChar);
    printf("  Xoff char       : %u\n\r", usDCB.bXOFFChar);

  return 0;
}
