// module: mt7915.ko
// function: sta_rec_update_muru_info @ 0x1c2de8
// size: 644 bytes
//

undefined4 sta_rec_update_muru_info(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined2 local_3c;
  undefined2 local_3a;
  undefined1 local_38;
  undefined1 local_37;
  undefined1 local_36;
  undefined1 local_35;
  undefined1 local_30;
  byte local_2f;
  byte local_2e;
  byte local_2d;
  undefined1 local_2c;
  undefined1 local_2b;
  undefined1 local_2a;
  undefined1 local_28;
  byte local_27;
  byte local_26;
  undefined1 local_25;
  undefined1 local_24;
  byte local_20;
  byte local_1f;
  byte local_1c;
  byte local_1b;
  
  iVar2 = *(int *)(param_3 + 0x9c);
  os_zero_mem(&local_3c,0x24);
  if (iVar2 == 0) {
    return 0xffffffff;
  }
  uVar3 = *(undefined4 *)(iVar2 + 8);
  local_3c = 0x12;
  local_3a = 0x24;
  local_38 = wlan_config_get_mu_dl_ofdma(uVar3);
  local_37 = wlan_config_get_mu_ul_ofdma(uVar3);
  local_36 = wlan_config_get_mu_dl_mimo(uVar3);
  local_35 = wlan_config_get_mu_ul_mimo(uVar3);
  local_30 = *(undefined1 *)(iVar2 + 0x9d);
  local_28 = *(undefined1 *)(iVar2 + 0x9b);
  iVar1 = *(int *)(iVar2 + 0x7c);
  local_2f = (byte)((uint)(iVar1 << 0xf) >> 0x1f);
  local_2e = (byte)((uint)(iVar1 << 0xe) >> 0x1f);
  local_2d = (byte)((uint)(iVar1 << 0xd) >> 0x1f);
  local_1f = (byte)((uint)(iVar1 << 0x13) >> 0x1f);
  local_1c = (byte)((uint)(iVar1 << 0x1a) >> 0x1f);
  local_1b = (byte)((uint)(iVar1 << 0x19) >> 0x1f);
  local_27 = (byte)((uint)(*(int *)(iVar2 + 0x78) << 0x17) >> 0x1f);
  local_26 = (byte)((uint)(*(int *)(iVar2 + 0x78) << 0x13) >> 0x1f);
  local_20 = (byte)(((uint)*(byte *)(iVar2 + 0xd16) << 0x1b) >> 0x1f);
  local_2c = 0;
  local_2b = 0;
  local_2a = 0;
  local_25 = 0;
  local_24 = 0;
  if (DebugLevel < 3) goto LAB_001c2ee0;
  printk("fgDlOfdmaEn = 0x%02X, fgUlOfdmaEn = 0x%02X\n",local_38,local_37);
  if (DebugLevel < 3) {
LAB_001c2f98:
    if (2 < DebugLevel) {
      printk("u1RxSUNonCompSigB = 0x%02X\n",local_2a);
      if (DebugLevel < 3) goto LAB_001c2ee0;
      printk("u1TrigFrmPad = 0x%02X, u1MuCascading = 0x%02X\n",local_28,local_27);
      goto LAB_001c2fdc;
    }
  }
  else {
    printk("fgDlMimoEn = 0x%02X, fgUlMimoEn= 0x%02X\n",local_36,local_35);
    if (DebugLevel < 3) goto LAB_001c2ee0;
    printk("u1PhyPunRx = 0x%02X, u120MIn40M2G = 0x%02X\n",local_30,local_2f);
    if (2 < DebugLevel) {
      printk("u120MIn160M = 0x%02X, u180MIn160M= 0x%02X\n",local_2e,local_2d);
      if (DebugLevel < 3) goto LAB_001c2ee0;
      printk("u1Lt16SigB = 0x%02X, u1RxSUCompSigB = 0x%02X\n",local_2c,local_2b);
      goto LAB_001c2f98;
    }
LAB_001c2fdc:
    if ((DebugLevel < 3) ||
       (printk("u1UoRa = 0x%02X, u12x996Tone= 0x%02X\n",local_26,local_25), DebugLevel < 3))
    goto LAB_001c2ee0;
    printk("u1RxTrgFrmBy11ac = 0x%02X\n",local_24);
  }
  if ((2 < DebugLevel) &&
     (printk("fgVhtMuBfee = 0x%02X, fgParBWDlMimo = 0x%02X\n",local_20,local_1f), 2 < DebugLevel)) {
    printk("fgFullUlMimo = 0x%02X, fgParUlMimo = 0x%02X\n",local_1c,local_1b);
  }
LAB_001c2ee0:
  AndesAppendCmdMsg(param_2,&local_3c,0x24);
  return 0;
}

