// module: mt7915.ko
// function: eFuseReadPhysical @ 0x1d23c4
// size: 76 bytes
//

void eFuseReadPhysical(undefined4 param_1,ushort *param_2,undefined4 param_3,int param_4)

{
  ushort uVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  uVar1 = param_2[1];
  uVar2 = *param_2;
  if (uVar1 == 0) {
    return;
  }
  iVar5 = 0;
  do {
    uVar3 = (uint)uVar2 + iVar5;
    iVar4 = param_4 + iVar5;
    iVar5 = iVar5 + 2;
    EfusePhysicalReadRegisters(param_1,uVar3 & 0xffff,2,iVar4);
  } while (iVar5 < (int)(uint)uVar1);
  return;
}

