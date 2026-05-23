// module: mt7915.ko
// function: HcSetGreenAPActiveByBand @ 0xa8fa4
// size: 36 bytes
//

void HcSetGreenAPActiveByBand(int param_1,int param_2,undefined1 param_3)

{
  if (*(int *)(param_1 + 0xa797a0) != 0) {
    *(undefined1 *)(*(int *)(*(int *)(param_1 + 0xa797a0) + param_2 * 0x1c + 4) + 0xc) = param_3;
  }
  return;
}

