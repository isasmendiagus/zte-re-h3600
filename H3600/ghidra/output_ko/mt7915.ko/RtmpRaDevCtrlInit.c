// module: mt7915.ko
// function: RtmpRaDevCtrlInit @ 0x13c9fc
// size: 444 bytes
//

undefined4 RtmpRaDevCtrlInit(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  
  iVar1 = DebugLevel;
  *(undefined1 *)(param_1 + 0x286285) = 0;
  *(undefined4 *)(param_1 + 0x286280) = param_2;
  if (iVar1 < 3) {
    *(bool *)(param_1 + 0x286285) = iVar1 < 3;
  }
  else {
    printk("STA Driver version-%s\n","7.1.0.1");
    iVar1 = DebugLevel;
    *(undefined1 *)(param_1 + 0x286285) = 1;
    if ((2 < iVar1) && (printk("AP Driver version-%s\n","7.1.0.1"), 2 < DebugLevel)) {
      printk("pAd->infType=%d\n",*(undefined4 *)(param_1 + 0x286280));
    }
  }
  *(undefined1 *)(param_1 + 0x286294) = 3;
  *(undefined4 *)(param_1 + 0xa7cc00) = 0xffffffff;
  *(int *)(param_1 + 0x285d60) = param_1 + 0x285d60;
  *(undefined4 *)(param_1 + 0x285d58) = 0;
  *(undefined4 *)(param_1 + 0x285d5c) = 1;
  *(int *)(param_1 + 0x285d64) = param_1 + 0x285d60;
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  __memzero(iVar1,0x230);
  iVar2 = RtmpChipOpsHook(param_1);
  if (iVar2 == 0) {
    ChipOpsMCUHook(param_1,*(undefined4 *)(iVar1 + 0x3c));
    get_dev_config_idx(param_1);
    hdev_resource_init(*(undefined4 *)(param_1 + 0xa797a0));
    mt_wlan_hook_init();
    uVar3 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
    if ((uVar3 & 8) != 0) {
      uVar3 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
      if (uVar3 < 0x80) {
        *(uint *)(param_1 + 0xa39f8c) = *(uint *)(param_1 + 0xa39f8c) | 8;
      }
      else if (1 < DebugLevel) {
        uVar4 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
        printk("%s(): MCS_LUT not used becasue MacTb size(%d) > 128!\n","RtmpRaDevCtrlInit",uVar4);
      }
    }
    *(undefined1 *)(param_1 + 0xa7d171) = 6;
    *(undefined1 *)(param_1 + 0xa7d195) = 6;
    return 0;
  }
  if (-1 < DebugLevel) {
    printk("chip ops hook error\n");
  }
  return 0;
}

