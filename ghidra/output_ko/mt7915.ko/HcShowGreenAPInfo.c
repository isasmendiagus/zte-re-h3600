// module: mt7915.ko
// function: HcShowGreenAPInfo @ 0xa96ec
// size: 4 bytes
//

void HcShowGreenAPInfo(int param_1)

{
  undefined1 uVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  int *piVar9;
  undefined4 auStack_24 [2];
  
  iVar5 = 0;
  auStack_24[0] = 0;
  uVar2 = HcGetAmountOfBand();
  if (param_1 != -0x36da94) {
    piVar9 = (int *)(param_1 + 8);
    iVar4 = DebugLevel;
    do {
      piVar9 = piVar9 + 1;
      iVar7 = *piVar9;
      if ((iVar7 != 0) && (2 < iVar4)) {
        uVar3 = HcGetBandByWdev(iVar7);
        printk("\tband(%d), wdev[%d], type(0x%x), up(%d)\n",uVar3,iVar5,
               *(undefined4 *)(iVar7 + 0x14),*(undefined1 *)(iVar7 + 0x28));
        iVar4 = DebugLevel;
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 != 0x68);
    if (2 < iVar4) {
      uVar1 = (&DAT_0036da94)[param_1];
      uVar3 = FUN_00083b10(param_1);
      printk("\tGREENAP::greenap_cap(%d), greenap_allow(%d), dbdc_mode(%d)\n",uVar1,uVar3,
             *(undefined1 *)(param_1 + 0x79504d));
    }
    if (uVar2 != 0) {
      uVar6 = 0;
      uVar8 = 0;
      do {
        uVar3 = 0x820f5020;
        if (uVar6 != 0) {
          uVar3 = 0x820f5120;
        }
        mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar3,auStack_24);
        if (2 < DebugLevel) {
          uVar3 = IsHcGreenAPActiveByBand(param_1,uVar8);
          printk("\tGREENAP::band_idx(%d), greenap_active(%d)\n",uVar6,uVar3);
        }
        uVar6 = uVar6 + 1;
        uVar8 = uVar6 & 0xff;
      } while (uVar8 < uVar2);
    }
  }
  return;
}

