// module: switch.ko
// function: strncpy @ 0x2c1a0
// size: 1 bytes
//

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * strncpy(char *__dest,char *__src,size_t __n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

