// module: mt7915.ko
// function: virtual_if_down_handler @ 0x24610c
// size: 168 bytes
//

undefined4
virtual_if_down_handler(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = RtmpOsGetNetDevPriv();
  if (iVar1 != 0) {
    iVar2 = wdev_search_by_netdev(iVar1,param_1);
    if (iVar2 != 0) {
      iVar3 = wdev_do_close();
      if ((iVar3 != 1) && (2 < DebugLevel)) {
        printk("%s() inf_down (idx %d) fail!!!\n","virtual_if_down_handler",
               *(undefined1 *)(iVar2 + 0xc),DebugLevel,param_4);
      }
      wdev_if_up_down(iVar1,iVar2,0);
      greenap_check_when_if_down_up(iVar1);
      return 0;
    }
    if (-1 < DebugLevel) {
      printk("%s() wdev fail!!!\n","virtual_if_down_handler");
    }
  }
  return 0xffffffff;
}

