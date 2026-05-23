// module: mt7915.ko
// function: CmdETxBfPfmuProfileTagWrite @ 0x1b2370
// size: 488 bytes
//

undefined4
CmdETxBfPfmuProfileTagWrite
          (int *param_1,void *param_2,void *param_3,size_t param_4,byte param_5,undefined1 param_6)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_6c;
  undefined1 local_6b;
  undefined1 local_6a;
  undefined1 local_69;
  undefined1 auStack_68 [68];
  
  get_wdev_by_ioctl_idx_and_iftype
            (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  uVar1 = HcGetBandByWdev();
  iVar4 = param_1[0x29deee];
  iVar2 = AndesAllocCmdMsg(param_1,0x44);
  if (iVar2 == 0) {
    uVar3 = 3;
  }
  else {
    os_zero_mem(&local_6c,0x44);
    local_6c = 6;
    local_6b = param_6;
    local_6a = 1;
    if (((param_1[0x28eb05] & 1U) != 0) ||
       ((param_1[0x29deed] == 1 && ((*(uint *)(param_1[0x29deee] + 0x4e0) & 1) != 0)))) {
      uVar1 = (uint)*(byte *)(iVar4 + 0x4cc);
    }
    local_69 = (undefined1)uVar1;
    if (2 < DebugLevel) {
      printk("%s: PFMU ID = %d, Band:%d\n","CmdETxBfPfmuProfileTagWrite",param_6,uVar1);
    }
    os_move_mem(auStack_68,param_2,param_4);
    os_move_mem(auStack_68 + param_4,param_3,(uint)param_5);
    AndesInitCmdMsg(iVar2,0x1eed0000,0xffff0008,0,0,EventExtCmdResult);
    AndesAppendCmdMsg(iVar2,&local_6c,0x44);
    uVar3 = chip_cmd_tx(param_1,iVar2);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdETxBfPfmuProfileTagWrite",uVar3);
  }
  return uVar3;
}

