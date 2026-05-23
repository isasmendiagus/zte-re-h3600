// module: mt7915.ko
// function: IsHcGreenAPActiveByBand @ 0xa8fc8
// size: 36 bytes
//

undefined1 IsHcGreenAPActiveByBand(int param_1,int param_2)

{
  undefined1 uVar1;
  
  uVar1 = 0;
  if (*(int *)(param_1 + 0xa797a0) != 0) {
    uVar1 = *(undefined1 *)(*(int *)(*(int *)(param_1 + 0xa797a0) + param_2 * 0x1c + 4) + 0xc);
  }
  return uVar1;
}

