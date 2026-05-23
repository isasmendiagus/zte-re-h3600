// module: mt7915.ko
// function: ShowL1profile @ 0x14f0d4
// size: 228 bytes
//

undefined4 ShowL1profile(int param_1)

{
  char *pcVar1;
  undefined4 uVar2;
  
  if (0 < DebugLevel) {
    printk("===== L1 profile settings =====\n");
    if (0 < DebugLevel) {
      uVar2 = get_dev_l2profile(param_1);
      printk("%s = %s\n",s_profile_path_0033ae50,uVar2);
      if (0 < DebugLevel) {
        pcVar1 = "Get_System_CapNode_Info" + param_1 + 4;
        pcVar1[0] = '\0';
        pcVar1[1] = '\0';
        pcVar1[2] = '\0';
        pcVar1[3] = '\0';
        printk("%s = 0x%x\n",s_EEPROM_offset_0033aea0,DAT_0033aa18);
        if (0 < DebugLevel) {
          pcVar1 = "Get_System_CapNode_Info" + param_1 + 4;
          pcVar1[0] = '\0';
          pcVar1[1] = '\0';
          pcVar1[2] = '\0';
          pcVar1[3] = '\0';
          printk("%s = 0x%x\n",s_EEPROM_size_0033aec8,DAT_0033aa1c);
          if (0 < DebugLevel) {
            uVar2 = get_dev_name_prefix(param_1,0x100);
            printk("%s = %s\n",s_main_ifname_0033aef0,uVar2);
          }
        }
      }
    }
  }
  return 1;
}

