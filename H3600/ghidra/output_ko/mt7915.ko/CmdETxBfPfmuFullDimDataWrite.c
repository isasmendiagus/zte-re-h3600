// module: mt7915.ko
// function: CmdETxBfPfmuFullDimDataWrite @ 0x1b29a8
// size: 428 bytes
//

undefined4
CmdETxBfPfmuFullDimDataWrite
          (int *param_1,undefined1 param_2,undefined2 param_3,undefined1 param_4,void *param_5,
          byte param_6)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined1 local_130;
  undefined1 local_12f;
  undefined2 local_12e;
  undefined1 local_12c;
  undefined1 local_12b;
  undefined1 auStack_128 [260];
  
  get_wdev_by_ioctl_idx_and_iftype
            (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  uVar1 = HcGetBandByWdev();
  iVar3 = param_1[0x29deee];
  if (param_5 == (void *)0x0) {
    uVar4 = 2;
  }
  else {
    iVar5 = param_6 + 8;
    iVar2 = AndesAllocCmdMsg(param_1,iVar5);
    if (iVar2 == 0) {
      uVar4 = 3;
    }
    else {
      os_zero_mem(&local_130,iVar5);
      local_130 = 0x1e;
      if (((param_1[0x28eb05] & 1U) != 0) ||
         ((param_1[0x29deed] == 1 && ((*(uint *)(param_1[0x29deee] + 0x4e0) & 1) != 0)))) {
        uVar1 = *(undefined1 *)(iVar3 + 0x4cc);
      }
      local_12f = param_2;
      local_12e = param_3;
      local_12c = uVar1;
      local_12b = param_4;
      os_move_mem(auStack_128,param_5,(uint)param_6);
      AndesInitCmdMsg(iVar2,0x1eed0000,0xffff0008,0,0,EventExtCmdResult);
      AndesAppendCmdMsg(iVar2,&local_130,iVar5);
      uVar4 = chip_cmd_tx(param_1,iVar2);
    }
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdETxBfPfmuFullDimDataWrite",uVar4);
  }
  return uVar4;
}

