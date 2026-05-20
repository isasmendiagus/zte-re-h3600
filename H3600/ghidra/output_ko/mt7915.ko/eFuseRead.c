// module: mt7915.ko
// function: eFuseRead @ 0x1d2410
// size: 88 bytes
//

undefined4 eFuseRead(undefined4 param_1,int param_2,int param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  if (param_4 != 0) {
    iVar3 = 0;
    do {
      uVar1 = param_2 + iVar3;
      iVar2 = param_3 + iVar3;
      iVar3 = iVar3 + 2;
      eFuseReadRegisters(param_1,uVar1 & 0xffff,2,iVar2);
    } while (iVar3 < param_4);
    return 0;
  }
  return 0;
}

