// module: mt7915.ko
// function: show_e2pinfo_proc @ 0x128530
// size: 332 bytes
//

undefined4 show_e2pinfo_proc(int param_1)

{
  int iVar1;
  byte bVar2;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (((0 < DebugLevel) &&
      (printk("Default eeprom mode from profile: %s\n",
              (&PTR_DAT_00298c50)[(byte)"cp_support_is_enabled"[param_1 + 4]]), 0 < DebugLevel)) &&
     (printk("Current mode: %s\n",(&PTR_DAT_00298c50)[(byte)"cp_support_is_enabled"[param_1 + 5]]),
     0 < DebugLevel)) {
    printk("E2p source: %s\n",
           *(undefined4 *)(&DAT_00298c64 + (uint)(byte)"cp_support_is_enabled"[param_1 + 6] * 4));
  }
  bVar2 = "cp_support_is_enabled"[param_1 + 6];
  if (((bVar2 & 1) == 0) && (*(code **)(iVar1 + 0x94) != (code *)0x0)) {
    iVar1 = (**(code **)(iVar1 + 0x94))(param_1);
    if (iVar1 == 0) {
      if (0 < DebugLevel) {
        printk("ical data merge: No\n");
      }
    }
    else if (0 < DebugLevel) {
      printk("ical data merge: YES\n");
      bVar2 = "cp_support_is_enabled"[param_1 + 6];
      goto LAB_001285a0;
    }
    bVar2 = "cp_support_is_enabled"[param_1 + 6];
  }
LAB_001285a0:
  if ((((bVar2 & 8) != 0) && (param_1 != -0x296d3b)) && (0 < DebugLevel)) {
    printk("Bin file Source: %s\n");
  }
  return 1;
}

