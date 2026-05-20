// module: mt7915.ko
// function: set_vow_rx_wmm_backoff @ 0x454d8
// size: 264 bytes
//

undefined4 set_vow_rx_wmm_backoff(int param_1,char *param_2)

{
  uint uVar1;
  int iVar2;
  uint local_1c;
  uint local_18;
  uint local_14 [2];
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  uVar1 = sscanf(param_2,"%u-%u-%u",&local_1c,&local_18,local_14);
  if ((((2 < uVar1) && (local_1c < 4)) && (local_18 < 4)) && (local_14[0] < 0x10000)) {
    *(short *)(param_1 + (local_18 + local_1c * 4 + 0x53cbf0) * 2 + 4) = (short)local_14[0];
    iVar2 = vow_set_backoff_time(param_1,local_1c & 0xff);
    if (DebugLevel < 0) {
      if (iVar2 == 0) {
        return 1;
      }
    }
    else {
      printk("%s: wmm %d ac %d set %u.\n","set_vow_rx_wmm_backoff",local_1c,local_18,local_14[0]);
      if (iVar2 == 0) {
        return 1;
      }
      if (-1 < DebugLevel) {
        printk("%s: set command failed.\n","set_vow_rx_wmm_backoff");
      }
    }
  }
  return 0;
}

