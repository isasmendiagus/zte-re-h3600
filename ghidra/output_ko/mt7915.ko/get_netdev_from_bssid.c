// module: mt7915.ko
// function: get_netdev_from_bssid @ 0x13c9a0
// size: 88 bytes
//

int get_netdev_from_bssid(int param_1,uint param_2)

{
  int iVar1;
  
  if ((param_2 < 0x68) && (iVar1 = **(int **)(param_1 + param_2 * 4 + 0xc), iVar1 != 0)) {
    return iVar1;
  }
  if (DebugLevel < 0) {
    return 0;
  }
  printk("%s,dev_p=NULL,caller:%pS\n","get_netdev_from_bssid");
  return 0;
}

