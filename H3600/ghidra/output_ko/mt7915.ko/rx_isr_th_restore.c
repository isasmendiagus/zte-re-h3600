// module: mt7915.ko
// function: rx_isr_th_restore @ 0x15de40
// size: 24 bytes
//

void rx_isr_th_restore(int param_1)

{
  if (*(char *)(param_1 + 0xa7c544) == '\0') {
    return;
  }
  FUN_00156824();
  return;
}

