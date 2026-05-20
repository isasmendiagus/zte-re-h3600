// module: mt7915.ko
// function: BigInteger_GetByteValue @ 0x1fb5e8
// size: 88 bytes
//

uint BigInteger_GetByteValue(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  if (param_2 == 0) {
    iVar2 = 0;
    iVar3 = 0;
  }
  else {
    uVar1 = param_2 - 1 >> 2;
    if ((*(uint *)(param_1 + 0x14) < uVar1) || (*(uint *)(param_1 + 0x18) < param_2)) {
      return 0;
    }
    iVar3 = uVar1 << 2;
    iVar2 = (param_2 - 1 & 3) << 3;
  }
  return *(uint *)(*(int *)(param_1 + 0xc) + iVar3) >> iVar2 & 0xff;
}

