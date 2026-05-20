// module: mt7915.ko
// function: net_ad_close_inf @ 0x25abc0
// size: 88 bytes
//

undefined4 net_ad_close_inf(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 8);
  printk("%s --->\n","net_ad_close_inf",param_3,param_4,param_4);
  if ((iVar2 == 0) || (iVar2 = wifi_sys_close(param_1), iVar2 != 1)) {
    uVar1 = 0;
  }
  else {
    printk("%s <---\n","net_ad_close_inf");
    uVar1 = 1;
  }
  return uVar1;
}

