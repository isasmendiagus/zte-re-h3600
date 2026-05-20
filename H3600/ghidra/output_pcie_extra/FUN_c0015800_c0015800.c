// FUN_c0015800 @ c0015800

void FUN_c0015800(void)

{
  DataSynchronizationBarrier(0xe);
  if (DAT_c066d2b8 != (code *)0x0) {
    (*DAT_c066d2b8)();
  }
  uRamf0400044 = 1;
  return;
}

