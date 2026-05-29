// FUN_40e50854 @ 40e50854

undefined4 FUN_40e50854(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar5 = iRam40e50920;
  if (9 < *(uint *)(iRam40e50920 + 0x48)) {
    *(uint *)(iRam40e50920 + 0x48) =
         *(uint *)(iRam40e50920 + 0x48) - (*(uint *)(iRam40e50924 + 0x68) & 0xffff);
  }
  iVar1 = iRam40e50920;
  if (*(uint *)(iVar5 + 0x48) < 0x400) {
    iVar4 = *(int *)(iRam40e50920 + 0x54);
    iVar6 = *(int *)(iRam40e50920 + 0x58);
    *(uint *)(iRam40e50920 + 0x54) = iVar4 + 1U;
    iVar5 = iVar6 + iVar4 * 0x10;
    if (0x3ff < iVar4 + 1U) {
      *(undefined4 *)(iVar1 + 0x54) = 0;
    }
    if (iVar5 != 0) {
      *(undefined4 *)(iVar6 + iVar4 * 0x10) = 0x80;
      *(undefined4 *)(iVar5 + 4) = 0x10000;
      *(undefined4 *)(iVar5 + 8) = 0x1000000;
      *(undefined4 *)(iVar5 + 0xc) = 2;
      FUN_40e50730(param_2,param_3);
      return 0;
    }
  }
  else {
    uVar2 = *(uint *)(iRam40e50924 + 0x68);
    uVar3 = uVar2;
    if (0x3ffffff < uVar2) {
      uVar3 = *(uint *)(iRam40e50920 + 0x4c);
    }
    if (uVar2 < 0x4000000) {
      iVar4 = *(int *)(iRam40e50920 + 0x50);
    }
    else {
      iVar4 = uVar3 + 1;
    }
    *(uint *)(iRam40e50920 + 0x48) = *(uint *)(iVar5 + 0x48) - (uVar2 & 0xffff);
    if (uVar2 < 0x4000000) {
      *(int *)(iVar1 + 0x50) = iVar4 + 1;
    }
    else {
      *(int *)(iVar1 + 0x4c) = iVar4;
    }
  }
  FUN_40e2a1b4(uRam40e50928);
  return 0xffffffff;
}
