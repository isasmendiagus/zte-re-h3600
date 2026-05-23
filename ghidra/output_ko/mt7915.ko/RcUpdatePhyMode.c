// module: mt7915.ko
// function: RcUpdatePhyMode @ 0xac718
// size: 144 bytes
//

undefined4 RcUpdatePhyMode(int param_1,ushort param_2)

{
  undefined1 uVar1;
  ushort uVar2;
  int iVar3;
  bool bVar4;
  
  uVar2 = param_2 & 0xb1;
  uVar1 = (undefined1)uVar2;
  iVar3 = *(int *)(param_1 + 4);
  if (((uVar2 == 0) || (*(byte *)(iVar3 + 4) < 0xf && (param_2 & 0x4e) == 0)) &&
     (bVar4 = (param_2 & 0x4e) != 0, 0xe < *(byte *)(iVar3 + 4) || !bVar4)) {
    *(ushort *)(iVar3 + 2) = param_2;
    if (bVar4) {
      uVar1 = 1;
    }
    else if (uVar2 != 0) {
      uVar1 = 0x24;
    }
    *(undefined1 *)(iVar3 + 4) = uVar1;
    RcUpdateBandCtrl(*(undefined4 *)(param_1 + 0x18));
    return 0xffffffff;
  }
  *(ushort *)(iVar3 + 2) = param_2 | *(ushort *)(iVar3 + 2);
  return 0;
}

