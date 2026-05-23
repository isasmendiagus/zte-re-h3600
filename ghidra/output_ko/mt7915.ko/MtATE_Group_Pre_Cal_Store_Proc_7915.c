// module: mt7915.ko
// function: MtATE_Group_Pre_Cal_Store_Proc_7915 @ 0x28b228
// size: 480 bytes
//

undefined4 MtATE_Group_Pre_Cal_Store_Proc_7915(int param_1,int param_2)

{
  char *pcVar1;
  undefined4 uVar2;
  ushort local_22 [3];
  
  local_22[0] = 0;
  if (("cp_support_is_enabled"[param_1 + 4] - 2U & 0xfd) != 0) {
    if (-1 < DebugLevel) {
      printk("%s: Currently not in FLASH or BIN MODE,return.\n",
             "MtATE_Group_Pre_Cal_Store_Proc_7915");
    }
    return 0;
  }
  "RTMPSetSTAPassPhrase"[param_1 + 3] = '\x01';
  if (param_2 == 0) {
    pcVar1 = "RTMPSetSTAPassPhrase" + param_1 + 0xc;
    pcVar1[0] = '\0';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    RTMPZeroMemory(*(undefined4 *)("RTMPSetSTAPassPhrase" + param_1 + 4),0x10);
    RTMPZeroMemory(*(undefined4 *)("RTMPSetSTAPassPhrase" + param_1 + 8),0xc410);
    if ("cp_support_is_enabled"[param_1 + 4] == '\x02') {
      rtmp_ee_flash_read(param_1,0x62,local_22);
      local_22[0] = local_22[0] & 0xfffe;
      rtmp_ee_flash_write(param_1,0x62);
    }
  }
  else if (param_2 == 1) {
    MtATE_Dump_Group_PreCal_7915();
  }
  else if (param_2 == 2) {
    uVar2 = *(undefined4 *)("RTMPSetSTAPassPhrase" + param_1 + 4);
    pcVar1 = "RTMPSetSTAPassPhrase" + param_1 + 0xc;
    pcVar1[0] = '\0';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    RTMPZeroMemory(uVar2,0x10);
    RTMPZeroMemory(*(undefined4 *)("RTMPSetSTAPassPhrase" + param_1 + 8),0xc410);
    MtCmdDoCalibration(param_1,1,0x20000000,0);
    if ("cp_support_is_enabled"[param_1 + 4] == '\x02') {
      rtmp_ee_flash_read(param_1,0x62,local_22);
      local_22[0] = local_22[0] | 1;
      rtmp_ee_flash_write(param_1,0x62);
    }
  }
  else {
    if (DebugLevel < 0) goto LAB_0028b2ac;
    printk("%s: Should not be here !\n","MtATE_Group_Pre_Cal_Store_Proc_7915");
  }
  if (-1 < DebugLevel) {
    printk("%s: op=%d, 0x%2x=%d\n","MtATE_Group_Pre_Cal_Store_Proc_7915",param_2,0x62,local_22[0]);
  }
LAB_0028b2ac:
  "RTMPSetSTAPassPhrase"[param_1 + 3] = '\0';
  return 1;
}

