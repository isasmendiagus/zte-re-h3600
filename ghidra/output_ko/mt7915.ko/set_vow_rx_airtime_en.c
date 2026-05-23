// module: mt7915.ko
// function: set_vow_rx_airtime_en @ 0x45260
// size: 204 bytes
//

undefined4 set_vow_rx_airtime_en(int param_1,char *param_2)

{
  int iVar1;
  undefined4 local_14 [2];
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  iVar1 = sscanf(param_2,"%u",local_14);
  if (iVar1 != 0) {
    *(char *)(param_1 + 0xa79826) = (char)local_14[0];
    iVar1 = vow_set_rx_airtime(param_1,1,1);
    if (DebugLevel < 0) {
      if (iVar1 == 0) {
        return 1;
      }
    }
    else {
      printk("%s: set %u.\n","set_vow_rx_airtime_en",local_14[0]);
      if (iVar1 == 0) {
        return 1;
      }
      if (-1 < DebugLevel) {
        printk("%s: set command failed.\n","set_vow_rx_airtime_en");
      }
    }
  }
  return 0;
}

