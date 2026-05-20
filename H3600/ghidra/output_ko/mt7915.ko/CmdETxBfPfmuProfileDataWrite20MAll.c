// module: mt7915.ko
// function: CmdETxBfPfmuProfileDataWrite20MAll @ 0x1b2b58
// size: 432 bytes
//

undefined4 CmdETxBfPfmuProfileDataWrite20MAll(int *param_1,undefined1 param_2,void *param_3)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_224;
  undefined1 local_223;
  undefined1 local_222;
  undefined1 auStack_220 [512];
  
  get_wdev_by_ioctl_idx_and_iftype
            (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  uVar1 = HcGetBandByWdev();
  iVar4 = param_1[0x29deee];
  iVar2 = AndesAllocCmdMsg(param_1,0x204);
  if (iVar2 == 0) {
    uVar3 = 3;
  }
  else {
    os_zero_mem(&local_224,0x204);
    local_224 = 0x11;
    local_223 = param_2;
    os_move_mem(auStack_220,param_3,0x200);
    if (((param_1[0x28eb05] & 1U) != 0) ||
       ((param_1[0x29deed] == 1 && ((*(uint *)(param_1[0x29deee] + 0x4e0) & 1) != 0)))) {
      uVar1 = (uint)*(byte *)(iVar4 + 0x4cc);
    }
    local_222 = (undefined1)uVar1;
    if (2 < DebugLevel) {
      printk("%s: PFMU ID = %d, Band:%d\n","CmdETxBfPfmuProfileDataWrite20MAll",local_223,uVar1);
    }
    AndesInitCmdMsg(iVar2,0x1eed0000,0xffff0008,0,0,EventExtCmdResult);
    AndesAppendCmdMsg(iVar2,&local_224,0x204);
    uVar3 = chip_cmd_tx(param_1,iVar2);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdETxBfPfmuProfileDataWrite20MAll",uVar3);
  }
  return uVar3;
}

