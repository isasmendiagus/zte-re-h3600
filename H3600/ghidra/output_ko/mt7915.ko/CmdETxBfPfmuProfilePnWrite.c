// module: mt7915.ko
// function: CmdETxBfPfmuProfilePnWrite @ 0x1b2eb0
// size: 484 bytes
//

undefined4
CmdETxBfPfmuProfilePnWrite(int *param_1,undefined4 param_2,undefined4 param_3,void *param_4)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_4c;
  undefined1 local_4b;
  undefined1 local_4a;
  undefined1 local_49;
  undefined1 auStack_48 [36];
  
  get_wdev_by_ioctl_idx_and_iftype
            (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  uVar1 = HcGetBandByWdev();
  iVar4 = param_1[0x29deee];
  iVar2 = AndesAllocCmdMsg(param_1,0x24);
  if (iVar2 == 0) {
    uVar3 = 3;
  }
  else {
    os_zero_mem(&local_4c,0x24);
    local_4b = (undefined1)param_2;
    local_4a = (undefined1)param_3;
    local_4c = 10;
    if (((param_1[0x28eb05] & 1U) != 0) ||
       ((param_1[0x29deed] == 1 && ((*(uint *)(param_1[0x29deee] + 0x4e0) & 1) != 0)))) {
      uVar1 = (uint)*(byte *)(iVar4 + 0x4cc);
    }
    local_49 = (undefined1)uVar1;
    if (2 < DebugLevel) {
      printk("%s: PFMU ID = %d, Band:%d\n","CmdETxBfPfmuProfilePnWrite",param_2,uVar1);
    }
    switch(param_3) {
    case 0:
    case 1:
    case 2:
      os_move_mem(auStack_48,param_4,0x14);
      break;
    case 3:
      os_move_mem(auStack_48,param_4,8);
      break;
    default:
      return 1;
    }
    AndesInitCmdMsg(iVar2,0x1eed0000,0xffff0008,0,0,EventExtCmdResult);
    AndesAppendCmdMsg(iVar2,&local_4c,0x24);
    uVar3 = chip_cmd_tx(param_1,iVar2);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdETxBfPfmuProfilePnWrite",uVar3);
  }
  return uVar3;
}

