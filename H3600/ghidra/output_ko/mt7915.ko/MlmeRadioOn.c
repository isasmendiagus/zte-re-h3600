// module: mt7915.ko
// function: MlmeRadioOn @ 0x12ca4c
// size: 48 bytes
//

void MlmeRadioOn(undefined4 param_1,int *param_2)

{
  if (param_2 == (int *)0x0) {
    return;
  }
  *(undefined1 *)(param_2 + 0x2b0) = 1;
  MTRadioOn();
  _clear_bit(0,*(int *)(*param_2 + 0x240) + 0x50);
  return;
}

