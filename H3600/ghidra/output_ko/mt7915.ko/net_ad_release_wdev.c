// module: mt7915.ko
// function: net_ad_release_wdev @ 0x25bccc
// size: 208 bytes
//

undefined4 net_ad_release_wdev(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    return 0x606;
  }
  iVar3 = *(int *)(param_2 + 0x24);
  if (iVar3 == 0) goto LAB_0025bd84;
  iVar2 = wifi_sys_linkdown(iVar3);
  if (iVar2 == 1) {
    iVar2 = wdev_do_close(iVar3);
    if (((iVar2 != 1) || (iVar3 = wdev_deinit(iVar1,iVar3), iVar3 != 1)) ||
       (iVar3 = *(int *)(param_2 + 0x28), iVar3 == 0)) goto LAB_0025bd84;
    iVar2 = wifi_sys_linkdown(iVar3);
    if (iVar2 == 1) {
      iVar2 = wdev_do_close(iVar3);
      if ((iVar2 == 1) && (iVar1 = wdev_deinit(iVar1,iVar3), iVar1 == 1)) {
        return 0;
      }
      goto LAB_0025bd84;
    }
  }
  printk("%s: linkdown failed!\n","net_ad_release_wdev");
LAB_0025bd84:
  printk("%s: releases wdev failed!\n","net_ad_release_wdev");
  return 0x603;
}

