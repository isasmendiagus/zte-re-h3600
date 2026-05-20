// module: mt7915.ko
// function: set_vow_rx_repeater_wmm_backoff @ 0x4579c
// size: 228 bytes
//

undefined4 set_vow_rx_repeater_wmm_backoff(int param_1,char *param_2)

{
  int iVar1;
  uint local_18;
  uint local_14 [2];
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  iVar1 = sscanf(param_2,"%u-%u",&local_18,local_14);
  if (((iVar1 != 0) && (local_18 < 4)) && (local_14[0] < 0x100000)) {
    *(short *)(param_1 + (local_18 + 0x53cc04) * 2 + 4) = (short)local_14[0];
    iVar1 = vow_set_backoff_time(param_1,4);
    if (DebugLevel < 0) {
      if (iVar1 == 0) {
        return 1;
      }
    }
    else {
      printk("%s: set ac %d, val = %u.\n","set_vow_rx_repeater_wmm_backoff",local_18,local_14[0]);
      if (iVar1 == 0) {
        return 1;
      }
      if (-1 < DebugLevel) {
        printk("%s: set command failed.\n","set_vow_rx_repeater_wmm_backoff");
      }
    }
  }
  return 0;
}

