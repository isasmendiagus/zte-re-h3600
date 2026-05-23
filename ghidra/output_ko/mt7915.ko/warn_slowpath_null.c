// module: mt7915.ko
// function: warn_slowpath_null @ 0x5f715c
// size: 1 bytes
//

/* WARNING: Control flow encountered bad instruction data */

void warn_slowpath_null(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}

