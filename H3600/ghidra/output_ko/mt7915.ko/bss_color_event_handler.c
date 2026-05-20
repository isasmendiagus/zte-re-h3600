// module: mt7915.ko
// function: bss_color_event_handler @ 0x206b44
// size: 168 bytes
//

void bss_color_event_handler(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)(param_1 + 8);
  if (2 < DebugLevel) {
    printk("%s: start to use the new BSS color\n","bss_color_event_handler");
  }
  *(undefined1 *)(param_1 + 0xa3c) = 0;
  *(undefined1 *)(param_1 + 0xa3d) = *(undefined1 *)(param_1 + 0xa3e);
  *(undefined1 *)(param_1 + 0xa3e) = 0;
  *(undefined1 *)(param_1 + 0xa3f) = 0;
  FUN_00206598(uVar1,param_1 + 0x98c,param_1 + 0xa3c);
  wlan_operate_set_he_bss_color
            (param_1,*(undefined1 *)(param_1 + 0xa3d),*(undefined1 *)(param_1 + 0xa3c));
  wlan_operate_set_he_bss_next_color(param_1,*(undefined1 *)(param_1 + 0xa3e),0);
  UpdateBeaconHandler(uVar1,param_1,2);
  return;
}

