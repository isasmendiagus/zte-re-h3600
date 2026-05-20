// module: mt7915.ko
// function: Set_Channel_Proc @ 0xd96f0
// size: 404 bytes
//

undefined4 Set_Channel_Proc(int *param_1,undefined4 param_2)

{
  undefined1 uVar1;
  char cVar2;
  char cVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  
  iVar6 = *param_1;
  uVar1 = *(undefined1 *)(iVar6 + 0x3c);
  iVar4 = get_wdev_by_ioctl_idx_and_iftype(param_1,uVar1,*(undefined4 *)(iVar6 + 0x38));
  cVar3 = os_str_tol(param_2,0,10);
  if (iVar4 == 0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: wdev == NULL! if_type %d, if_idx = %d\n","Set_Channel_Proc",
           *(undefined4 *)(iVar6 + 0x38),uVar1);
    return 0;
  }
  cVar2 = *(char *)(iVar4 + 0x1a);
  if (cVar2 != cVar3) {
    DfsDedicatedExamineSetNewCh(param_1,iVar4,cVar3);
    DedicatedZeroWaitStop(param_1,1);
    DfsOutBandCacReset(param_1);
    *(undefined1 *)(param_1 + 0xdae11) = 1;
    uVar5 = rtmp_set_channel(param_1,iVar4,cVar3);
    if ((char)param_1[0xdae0c] == '\x01') {
      iVar4 = wait_for_completion_timeout(param_1 + 0xdae0d,500);
      if (iVar4 == 0) {
        if (0 < DebugLevel) {
          printk("%s() wait channel setting timeout.\n","Set_Channel_Proc");
        }
        *(undefined1 *)(param_1 + 0xdae0c) = 0;
      }
      else if (0 < DebugLevel) {
        printk("%s() wait channel setting success.\n","Set_Channel_Proc");
      }
    }
    *(undefined1 *)(param_1 + 0xdae11) = 0;
    return uVar5;
  }
  if (DebugLevel < 3) {
    return 1;
  }
  printk("%s() old_channel = %d Channel =%d return\n","Set_Channel_Proc",cVar2,cVar2);
  return 1;
}

