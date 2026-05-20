// module: mt7915.ko
// function: os_usec_delay @ 0x142a60
// size: 4 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void os_usec_delay(uint param_1)

{
  uint uVar1;
  
  if (param_1 / 0x32 == 0) {
    if (param_1 == 0) {
      return;
    }
  }
  else {
    uVar1 = 0;
    do {
      uVar1 = uVar1 + 1;
      (*_memcpy)(&DAT_0051eb7c);
    } while (uVar1 != param_1 / 0x32);
    if (param_1 % 0x32 == 0) {
      return;
    }
  }
                    /* WARNING: Could not recover jumptable at 0x0024325c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_dump_stack)();
  return;
}

