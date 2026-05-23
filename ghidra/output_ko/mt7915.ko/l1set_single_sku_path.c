// module: mt7915.ko
// function: l1set_single_sku_path @ 0x14ed1c
// size: 140 bytes
//

undefined4 l1set_single_sku_path(int param_1,undefined4 param_2,char *param_3)

{
  char *pcVar1;
  int iVar2;
  
  pcVar1 = "Get_System_CapNode_Info" + param_1 + 4;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  iVar2 = strcmp(s__etc_wireless_mediatek_mt7615e_s_0033aaf4,param_3);
  if (iVar2 == 0) {
    if (2 < DebugLevel) {
      printk("profile remain %s\n",s__etc_wireless_mediatek_mt7615e_s_0033aaf4);
    }
  }
  else {
    if (2 < DebugLevel) {
      printk("sku path update from %s to %s\n",s__etc_wireless_mediatek_mt7615e_s_0033aaf4,param_3);
    }
    strncpy(s__etc_wireless_mediatek_mt7615e_s_0033aaf4,param_3,0x31);
  }
  return 0;
}

