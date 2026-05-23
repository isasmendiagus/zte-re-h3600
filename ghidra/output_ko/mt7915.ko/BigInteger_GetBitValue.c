// module: mt7915.ko
// function: BigInteger_GetBitValue @ 0x1fb5a4
// size: 68 bytes
//

uint BigInteger_GetBitValue(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  
  if (param_2 == 0) {
    uVar1 = 0;
    iVar2 = 0;
  }
  else {
    uVar1 = param_2 - 1U >> 5;
    if (*(uint *)(param_1 + 0x14) < uVar1) {
      return 0;
    }
    iVar2 = uVar1 << 2;
    uVar1 = param_2 - 1U & 0x1f;
  }
  return *(uint *)(*(int *)(param_1 + 0xc) + iVar2) >> uVar1 & 1;
}

