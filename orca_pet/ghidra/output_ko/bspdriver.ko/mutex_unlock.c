// module: bspdriver.ko
// function: mutex_unlock @ 0x12030
// size: 1 bytes
//

/* WARNING: Control flow encountered bad instruction data */

void mutex_unlock(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

