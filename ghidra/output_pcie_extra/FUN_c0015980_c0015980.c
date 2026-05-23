// FUN_c0015980 @ c0015980

void FUN_c0015980(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(undefined4 *)(param_1 + 0x900) = param_6;
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(undefined4 *)(param_1 + 0x90c) = param_2;
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(undefined4 *)(param_1 + 0x910) = 0;
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(undefined4 *)(param_1 + 0x914) = param_3;
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(undefined4 *)(param_1 + 0x918) = param_4;
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(undefined4 *)(param_1 + 0x91c) = 0;
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(undefined4 *)(param_1 + 0x904) = param_5;
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  *(undefined4 *)(param_1 + 0x908) = 0x80000000;
  return;
}

