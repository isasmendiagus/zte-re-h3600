// module: plat-zxylzb_9128S.ko
// function: warn_slowpath_null @ 0x2f0b0
// size: 1 bytes
//

/* WARNING: Control flow encountered bad instruction data */

void warn_slowpath_null(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

