// module: mt7915.ko
// function: trigger_timer_callback @ 0x206d68
// size: 244 bytes
//

void trigger_timer_callback(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_11;
  
  uVar2 = *(undefined4 *)(param_2 + 8);
  local_11 = 0;
  if (2 < DebugLevel) {
    printk("%s: enter\n","trigger_timer_callback");
  }
  FUN_00206840(param_2);
  if (*(char *)(param_2 + 0xa3f) != '\0') {
    if (2 < DebugLevel) {
      printk("%s: trigger BSS color change procedure\n","trigger_timer_callback");
    }
    *(undefined1 *)(param_2 + 0xa3c) = 1;
    FUN_00206598(uVar2,param_2 + 0x98c,param_2 + 0xa3c);
    wlan_operate_set_he_bss_color(param_2,*(undefined1 *)(param_2 + 0xa3d),1);
    iVar1 = FUN_002067d0(param_2,&local_11);
    if (iVar1 == 0) {
      *(undefined1 *)(param_2 + 0xa46) = 0;
      return;
    }
    *(undefined1 *)(param_2 + 0xa3e) = local_11;
    wlan_operate_set_he_bss_next_color(param_2,local_11,*(undefined1 *)(param_2 + 0xa44));
    UpdateBeaconHandler(uVar2,param_2,2);
  }
  *(undefined1 *)(param_2 + 0xa46) = 0;
  return;
}

