// module: tm.ko
// function: printk @ 0xdf070
// size: 1 bytes
//

/* WARNING: Control flow encountered bad instruction data */

void printk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

