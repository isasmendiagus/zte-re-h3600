// FUN_c0016a5c @ c0016a5c

void FUN_c0016a5c(int param_1)

{
  undefined4 uVar1;
  
  FUN_c001605c();
  FUN_c00169c8(param_1);
  FUN_c0016840(param_1);
  FUN_c00168a4(param_1);
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(undefined4 *)(*(int *)(&DAT_c069ea20 + param_1 * 0x38) + 4) = 0x146;
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(undefined4 *)(*(int *)(&DAT_c069ea20 + param_1 * 0x38) + 0xc) = 0x10008;
  uVar1 = 0x21002000;
  if (param_1 == 0) {
    uVar1 = 0x11001000;
  }
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(undefined4 *)(*(int *)(&DAT_c069ea20 + param_1 * 0x38) + 0x20) = uVar1;
  return;
}

