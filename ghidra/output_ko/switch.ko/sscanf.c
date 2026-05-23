// module: switch.ko
// function: sscanf @ 0x2c1c8
// size: 1 bytes
//

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int sscanf(char *__s,char *__format,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

