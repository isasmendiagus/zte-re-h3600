// compatible: zte,zx279128-smp
// function: FUN_c0014894 @ 0xc0014894
// found via struct field ptr -> 0xc0014894
// total struct-refs for compat: 2
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_c0014894(void)

{
  int iVar1;
  
  iVar1 = _DAT_c06ae8b8;
  (*DAT_c066b2b0)();
  if (*(int *)(iVar1 + 0x100) != 0) {
    if (DAT_c066b2c0 == (code *)0x0) {
      *(undefined4 *)(iVar1 + 0x100) = 0;
      DataSynchronizationBarrier(0xe);
      return;
    }
    (*DAT_c066b2c0)(0,0x100);
  }
  DataSynchronizationBarrier(0xe);
  return;
}

