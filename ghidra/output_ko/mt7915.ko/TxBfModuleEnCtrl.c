// module: mt7915.ko
// function: TxBfModuleEnCtrl @ 0x887cc
// size: 504 bytes
//

uint TxBfModuleEnCtrl(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  bool bVar9;
  undefined1 local_30;
  undefined1 local_2f;
  
  iVar3 = *(int *)(param_1 + 0xa797a0);
  if (*(byte *)(iVar3 + 0x32d8) < 2) {
    if (0 < DebugLevel) {
      printk("%s:It\'s not DBDC mode\n","TxBfModuleEnCtrl");
      return 0;
    }
    return 0;
  }
  os_zero_mem(&local_30,8);
  iVar1 = hc_get_chip_cap(iVar3);
  uVar6 = *(byte *)(iVar1 + 0x96) & 4;
  iVar2 = DebugLevel;
  if ((*(byte *)(iVar1 + 0x96) & 4) == 0) {
    uVar5 = uVar6;
    uVar7 = uVar6;
    uVar8 = uVar6;
    if (*(char *)(iVar3 + 0x32d8) != '\0') {
      do {
        if (*(char *)(uVar5 * 0x354 + iVar3 + 0x16a6) != '\0') {
          local_30 = (undefined1)uVar5;
          uVar8 = uVar8 + 1 & 0xff;
          uVar7 = 1;
        }
        if (0 < iVar2) {
          printk("%s:i = %d, pRadioCtrl->IsBfBand = %d\n","TxBfModuleEnCtrl",uVar5);
          iVar2 = DebugLevel;
        }
        uVar5 = uVar5 + 1 & 0xff;
      } while (uVar5 < *(byte *)(iVar3 + 0x32d8));
      uVar4 = 1;
      if (1 < uVar8) {
        if (-1 < iVar2) {
          printk("%s:Error - isBfBfBandNum > hardware capability\n","TxBfModuleEnCtrl");
          return uVar6;
        }
        return 0;
      }
      goto LAB_0008886c;
    }
    uVar4 = 1;
  }
  else {
    if (*(byte *)(iVar3 + 0x32d8) != 0) {
      bVar9 = *(char *)(iVar3 + 0x16a6) != '\0';
      if (bVar9) {
        local_30 = 0;
      }
      uVar7 = (uint)bVar9;
      if ((1 < *(byte *)(iVar3 + 0x32d8)) && (*(char *)(iVar3 + 0x19fa) != '\0')) {
        uVar7 = uVar7 | 2;
        local_2f = 0;
      }
      uVar4 = 2;
      goto LAB_0008886c;
    }
    uVar4 = 2;
  }
  uVar7 = 0;
LAB_0008886c:
  if (0 < iVar2) {
    printk("%s:u1BfNum = %d, u1BfBitmap = %d, u1BfSelBand[0] = %d\n","TxBfModuleEnCtrl",uVar4,uVar7,
           local_30);
  }
  AsicTxBfModuleEnCtrl(param_1,uVar4,uVar7,&local_30);
  return 1;
}

