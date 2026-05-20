// module: mt7915.ko
// function: CmdMultipleMibRegAccessReadCb @ 0x1ab3b8
// size: 76 bytes
//

void CmdMultipleMibRegAccessReadCb(int param_1,int param_2,int param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  
  uVar1 = param_3 - 0x14U >> 4;
  if (uVar1 == 0) {
    return;
  }
  iVar4 = param_2 + 0x14;
  puVar2 = *(undefined4 **)(param_1 + 0xc);
  do {
    iVar5 = iVar4 + 0x10;
    *puVar2 = *(undefined4 *)(iVar4 + 4);
    uVar3 = *(undefined4 *)(iVar4 + 0xc);
    puVar2[2] = *(undefined4 *)(iVar4 + 8);
    puVar2[3] = uVar3;
    iVar4 = iVar5;
    puVar2 = puVar2 + 4;
  } while (iVar5 != param_2 + uVar1 * 0x10 + 0x14);
  return;
}

