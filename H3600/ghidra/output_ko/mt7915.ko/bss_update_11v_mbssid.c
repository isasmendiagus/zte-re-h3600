// module: mt7915.ko
// function: bss_update_11v_mbssid @ 0x1c23dc
// size: 140 bytes
//

void bss_update_11v_mbssid(undefined4 param_1,int param_2,undefined4 param_3)

{
  undefined4 local_18;
  undefined4 local_14;
  
  local_18 = 0;
  local_14 = 0;
  os_zero_mem(&local_18,8);
  local_14 = CONCAT22(local_14._2_2_,*(undefined2 *)(param_2 + 0x104));
  local_18 = 0x80010;
  if (2 < DebugLevel) {
    printk("%s:ucMaxBSSIDIndicator(%d),ucMBSSIDIndex(%d)\n","bss_update_11v_mbssid",
           *(undefined1 *)(param_2 + 0x104));
  }
  AndesAppendCmdMsg(param_3,&local_18,8);
  return;
}

