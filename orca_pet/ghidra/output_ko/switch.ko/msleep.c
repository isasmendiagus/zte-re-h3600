// module: switch.ko
// function: msleep @ 0x2c320
// size: 1 bytes
//

/* WARNING: Control flow encountered bad instruction data */

void msleep(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

