// module: mt7915.ko
// function: virtual_if_up_handler @ 0x245fc4
// size: 196 bytes
//

undefined4 virtual_if_up_handler(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = RtmpOsGetNetDevPriv();
  if (iVar1 != 0) {
    iVar2 = wdev_search_by_netdev(iVar1,param_1);
    if (iVar2 != 0) {
      wdev_if_up_down(iVar1,iVar2,1);
      iVar3 = greenap_check_when_if_down_up(iVar1);
      if ((((iVar3 != 0) && (iVar1 = VIRTUAL_IF_NUM(iVar1), iVar1 != 0)) &&
          (iVar1 = wdev_do_open(iVar2), iVar1 != 1)) && (2 < DebugLevel)) {
        printk("%s() inf_up (idx %d) fail!!!\n","virtual_if_up_handler",*(undefined1 *)(iVar2 + 0xc)
              );
      }
      return 0;
    }
    if (-1 < DebugLevel) {
      printk("%s() wdev fail!!!\n","virtual_if_up_handler");
    }
  }
  return 0xffffffff;
}

