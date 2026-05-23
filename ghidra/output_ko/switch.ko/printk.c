// module: switch.ko
// function: printk @ 0x2c1cc
// size: 1 bytes
//

/* WARNING: Control flow encountered bad instruction data */

void printk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

