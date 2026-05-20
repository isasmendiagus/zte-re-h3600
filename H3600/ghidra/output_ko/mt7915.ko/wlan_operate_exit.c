// module: mt7915.ko
// function: wlan_operate_exit @ 0x106cb0
// size: 100 bytes
//

void wlan_operate_exit(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0xb14);
  if (iVar1 != 0) {
    phy_oper_exit(iVar1);
    ht_oper_exit(iVar1 + 8);
    vht_oper_exit(iVar1 + 0x52);
    he_oper_exit(iVar1 + 0x5c);
    ht_op_status_exit(iVar1 + 0x20);
    return;
  }
  if (DebugLevel < 3) {
    return;
  }
  printk("%s : Can\'t find wlan operate for wdev.\n","wlan_operate_exit");
  return;
}

