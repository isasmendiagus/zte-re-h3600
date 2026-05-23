// module: mt7915.ko
// function: vow_set_sta_DWRR_max_time @ 0x40a08
// size: 156 bytes
//

undefined4 vow_set_sta_DWRR_max_time(int param_1)

{
  undefined4 uVar1;
  undefined4 local_24 [3];
  uint local_18;
  
  __memzero(local_24,0x14);
  local_24[0] = 0x10;
  local_18 = (uint)*(byte *)(param_1 + 0xa7a2f2);
  if (2 < DebugLevel) {
    printk("%s:(sta_max_wait_time = 0x%x)\n","vow_set_sta_DWRR_max_time");
  }
  uVar1 = MtCmdSetVoWDRRCtrl(param_1,local_24);
  if (2 < DebugLevel) {
    printk("%s:(ret = %d), sizeof %zu\n","vow_set_sta_DWRR_max_time",uVar1,0x14);
  }
  return uVar1;
}

