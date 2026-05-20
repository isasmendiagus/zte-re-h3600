// module: mt7915.ko
// function: set_vow_rx_non_qos_backoff @ 0x455e4
// size: 208 bytes
//

undefined4 set_vow_rx_non_qos_backoff(int param_1,char *param_2)

{
  int iVar1;
  uint local_14 [2];
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  iVar1 = sscanf(param_2,"%u",local_14);
  if ((iVar1 != 0) && (local_14[0] < 0x100000)) {
    *(short *)(param_1 + 0xa79814) = (short)local_14[0];
    iVar1 = vow_set_backoff_time(param_1,6);
    if (DebugLevel < 0) {
      if (iVar1 == 0) {
        return 1;
      }
    }
    else {
      printk("%s: set %u.\n","set_vow_rx_non_qos_backoff",local_14[0]);
      if (iVar1 == 0) {
        return 1;
      }
      if (-1 < DebugLevel) {
        printk("%s: set command failed.\n","set_vow_rx_non_qos_backoff");
      }
    }
  }
  return 0;
}

