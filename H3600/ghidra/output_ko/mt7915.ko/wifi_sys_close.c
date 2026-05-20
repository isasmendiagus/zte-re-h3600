// module: mt7915.ko
// function: wifi_sys_close @ 0x105048
// size: 224 bytes
//

undefined4 wifi_sys_close(int param_1)

{
  int iVar1;
  int local_224 [3];
  undefined1 auStack_218 [528];
  
  os_zero_mem(local_224 + 2,0x214);
  if (0 < DebugLevel) {
    printk("%s(), wdev idx = %d\n","wifi_sys_close",*(undefined1 *)(param_1 + 0xc));
  }
  iVar1 = wlan_operate_get_state(param_1);
  if (iVar1 != 1) {
    return 1;
  }
  wlan_operate_set_state(param_1,0);
  UpdateDot11hForWdev(*(undefined4 *)(param_1 + 8),param_1,0);
  if (*(int *)(param_1 + 0x14) != 8) {
    FUN_00104318(*(undefined4 *)(param_1 + 8),param_1,0,auStack_218);
  }
  local_224[1] = 0;
  local_224[0] = param_1;
  local_224[2] = param_1;
  mt_notify_call_chain(*(int *)(param_1 + 8) + 0xa7bef8,1,local_224);
  HW_WIFISYS_CLOSE(*(undefined4 *)(param_1 + 8),local_224 + 2);
  return 1;
}

