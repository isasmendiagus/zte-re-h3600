// module: mt7915.ko
// function: BigInteger_BitsOfBI @ 0x1fb554
// size: 80 bytes
//

void BigInteger_BitsOfBI(int param_1,int *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  if (param_1 == 0) {
    return;
  }
  uVar2 = *(uint *)(*(int *)(param_1 + 0xc) + (*(int *)(param_1 + 0x14) + 0x3fffffff) * 4);
  uVar3 = 0;
  if (-1 < (int)uVar2) {
    do {
      uVar2 = uVar2 << 1;
      uVar3 = uVar3 + 1;
      uVar1 = ~uVar2 >> 0x1f;
      if (0x1f < uVar3) {
        uVar1 = 0;
      }
    } while (uVar1 != 0);
  }
  *param_2 = *(int *)(param_1 + 0x14) * 0x20 - uVar3;
  return;
}

