// module: mt7915.ko
// function: Set_Map_Channel_Proc @ 0xd9888
// size: 320 bytes
//

undefined4 Set_Map_Channel_Proc(int *param_1,undefined4 param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  
  iVar5 = *param_1;
  uVar1 = *(undefined1 *)(iVar5 + 0x3c);
  iVar3 = get_wdev_by_ioctl_idx_and_iftype(param_1,uVar1,*(undefined4 *)(iVar5 + 0x38));
  uVar2 = os_str_tol(param_2,0,10);
  if ((char)param_1[0x29f2ff] == '\0') {
    if (-1 < DebugLevel) {
      printk("MAPQuickChChange feaure not enabled!!");
    }
    uVar4 = Set_Channel_Proc(param_1,param_2);
    return uVar4;
  }
  if (iVar3 != 0) {
    if (-1 < DebugLevel) {
      printk(&_LC211,"Set_Map_Channel_Proc");
    }
    DfsDedicatedExamineSetNewCh(param_1,iVar3,uVar2);
    DedicatedZeroWaitStop(param_1,1);
    *(undefined1 *)(iVar3 + 0x3fe0) = 1;
    uVar4 = rtmp_set_channel(param_1,iVar3,uVar2);
    if (*(int *)(iVar3 + 0x14) != 2) {
      return uVar4;
    }
    *(undefined1 *)(iVar3 + 0x3fe0) = 0;
    return uVar4;
  }
  if (DebugLevel < 0) {
    return 0;
  }
  printk("%s: wdev == NULL! if_type %d, if_idx = %d\n","Set_Map_Channel_Proc",
         *(undefined4 *)(iVar5 + 0x38),uVar1);
  return 0;
}

