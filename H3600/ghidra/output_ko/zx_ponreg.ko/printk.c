// module: zx_ponreg.ko
// function: printk @ 0x11008
// size: 1 bytes
//

/* WARNING: Control flow encountered bad instruction data */

void printk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

