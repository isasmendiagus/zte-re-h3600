// module: mt7915.ko
// function: mt_ate_release_wdev @ 0x282280
// size: 324 bytes
//

int mt_ate_release_wdev(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = net_ad_wrap_service();
  iVar2 = *(int *)(param_2 * 0xd18 + iVar2 + 0x504);
  if (iVar2 == 0) {
LAB_002822f0:
    if (-1 < DebugLevel) {
      printk("%s: Invalid wdev\n","mt_ate_release_wdev");
      cVar1 = -1;
      goto LAB_002822d8;
    }
  }
  else {
    if (3 < DebugLevel) {
      printk("%s: wdev_idx=%d\n","mt_ate_release_wdev",*(undefined1 *)(iVar2 + 0xc),DebugLevel,
             param_4);
    }
    iVar3 = wifi_sys_linkdown(iVar2);
    if (iVar3 == 1) {
      iVar3 = wdev_do_close(iVar2);
      if (iVar3 == 1) {
        wdev_deinit(param_1,iVar2);
        iVar2 = net_ad_wrap_service(param_1);
        iVar2 = *(int *)(param_2 * 0xd18 + iVar2 + 0x508);
        if (iVar2 != 0) {
          if (3 < DebugLevel) {
            printk("%s: wdev_idx=%d\n","mt_ate_release_wdev",*(undefined1 *)(param_1 + 0xa3ad58));
          }
          iVar3 = wifi_sys_linkdown(iVar2);
          if (iVar3 != 1) goto LAB_002822c8;
          iVar3 = wdev_do_close(iVar2);
          if (iVar3 == 1) {
            wdev_deinit(param_1,iVar2);
            cVar1 = '\0';
            goto LAB_002822d8;
          }
        }
      }
      goto LAB_002822f0;
    }
LAB_002822c8:
    if (-1 < DebugLevel) {
      printk("%s(): linkdown fail!\n","mt_ate_release_wdev");
      goto LAB_002822f0;
    }
  }
  cVar1 = -1;
LAB_002822d8:
  return (int)cVar1;
}

