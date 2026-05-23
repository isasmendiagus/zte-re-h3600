// module: mt7915.ko
// function: l1set_profile_path @ 0x14eac0
// size: 308 bytes
//

undefined4 l1set_profile_path(int param_1,undefined4 param_2,char *param_3,undefined4 param_4)

{
  char *pcVar1;
  char *pcVar2;
  size_t sVar3;
  int iVar4;
  
  pcVar1 = "Get_System_CapNode_Info" + param_1 + 4;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  pcVar1 = strchr(param_3,0x3b);
  if (pcVar1 != (char *)0x0) {
    if (2 < DebugLevel) {
      printk("DBDC format of profile path!\n");
    }
    *pcVar1 = '\0';
    update_mtb_value(param_1,0,param_2,param_3,param_4);
    pcVar2 = strchr(pcVar1 + 1,0x3b);
    if (pcVar2 != (char *)0x0) {
      *pcVar2 = '\0';
    }
    update_mtb_value(param_1,1,param_2,pcVar1 + 1,param_4);
  }
  sVar3 = strlen(param_3);
  iVar4 = strcmp(s__etc_Wireless_RT2860_RT2860_dat_0033a9e6,param_3);
  if (iVar4 == 0 || 0x31 < (sVar3 & 0xff)) {
    if (2 < DebugLevel) {
      printk("profile remain %s\n",s__etc_Wireless_RT2860_RT2860_dat_0033a9e6);
    }
    return 0;
  }
  if (2 < DebugLevel) {
    printk("profile update from %s to %s\n",s__etc_Wireless_RT2860_RT2860_dat_0033a9e6,param_3);
  }
  strcpy(s__etc_Wireless_RT2860_RT2860_dat_0033a9e6,param_3);
  return 0;
}

