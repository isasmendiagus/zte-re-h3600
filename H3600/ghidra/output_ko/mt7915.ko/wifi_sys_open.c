// module: mt7915.ko
// function: wifi_sys_open @ 0x104f5c
// size: 232 bytes
//

undefined4 wifi_sys_open(int param_1)

{
  int iVar1;
  int local_21c;
  undefined1 auStack_218 [528];
  
  os_zero_mem(&local_21c,0x214);
  if (0 < DebugLevel) {
    printk("%s(), wdev idx = %d\n","wifi_sys_open",*(undefined1 *)(param_1 + 0xc));
  }
  iVar1 = is_testmode_wdev(*(undefined4 *)(param_1 + 0x14));
  if (iVar1 != 0) {
    wlan_config_set_ht_bw(param_1,0);
    wlan_config_set_ext_cha(param_1,0);
  }
  if ((*(char *)(param_1 + 0xaa8) == '\0') && (iVar1 = wlan_operate_get_state(param_1), iVar1 == 0))
  {
    wlan_operate_set_state(param_1,1);
    wdev_attr_update(*(undefined4 *)(param_1 + 8),param_1);
    wdev_fsm_init(param_1);
    FUN_00104318(*(undefined4 *)(param_1 + 8),param_1,1,auStack_218);
    local_21c = param_1;
    HW_WIFISYS_OPEN(*(undefined4 *)(param_1 + 8),&local_21c);
    return 1;
  }
  return 1;
}

