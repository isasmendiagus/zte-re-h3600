// module: wlan_debug_module.ko
// function: sprintf @ 0x68060
// size: 1 bytes
//

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int sprintf(char *__s,char *__format,...)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

