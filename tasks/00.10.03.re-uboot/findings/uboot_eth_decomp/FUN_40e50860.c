// FUN_40e50860 @ 40e50860

undefined4 FUN_40e50860(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int in_r12;
  int iVar5;
  int iVar6;
  
  if (9 < *(uint *)(in_r12 + 0x48)) {
    *(uint *)(in_r12 + 0x48) = *(uint *)(in_r12 + 0x48) - (*(uint *)(iRam40e50924 + 0x68) & 0xffff);
  }
  iVar1 = iRam40e50920;
  if (*(uint *)(in_r12 + 0x48) < 0x400) {
    iVar5 = *(int *)(iRam40e50920 + 0x54);
    iVar6 = *(int *)(iRam40e50920 + 0x58);
    *(uint *)(iRam40e50920 + 0x54) = iVar5 + 1U;
    iVar4 = iVar6 + iVar5 * 0x10;
    if (0x3ff < iVar5 + 1U) {
      *(undefined4 *)(iVar1 + 0x54) = 0;
    }
    if (iVar4 != 0) {
      *(undefined4 *)(iVar6 + iVar5 * 0x10) = 0x80;
      *(undefined4 *)(iVar4 + 4) = 0x10000;
      *(undefined4 *)(iVar4 + 8) = 0x1000000;
      *(undefined4 *)(iVar4 + 0xc) = 2;
      FUN_40e50730();
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
    *(uint *)(iRam40e50920 + 0x48) = *(uint *)(in_r12 + 0x48) - (uVar2 & 0xffff);
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
