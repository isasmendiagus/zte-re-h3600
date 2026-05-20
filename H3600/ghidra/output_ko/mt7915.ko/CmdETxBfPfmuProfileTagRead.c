// module: mt7915.ko
// function: CmdETxBfPfmuProfileTagRead @ 0x1b21c8
// size: 420 bytes
//

undefined4 CmdETxBfPfmuProfileTagRead(int *param_1,undefined4 param_2,undefined4 param_3)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_4c;
  undefined1 local_4b;
  undefined1 local_4a;
  undefined1 local_49;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 local_24;
  
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  iVar4 = param_1[0x29deee];
  get_wdev_by_ioctl_idx_and_iftype
            (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  uVar1 = HcGetBandByWdev();
  iVar2 = AndesAllocCmdMsg(param_1,4);
  if (iVar2 == 0) {
    uVar3 = 3;
  }
  else {
    os_zero_mem(&local_4c,4);
    local_4b = (undefined1)param_2;
    local_4a = (undefined1)param_3;
    local_4c = 5;
    if (((param_1[0x28eb05] & 1U) != 0) ||
       ((param_1[0x29deed] == 1 && ((*(uint *)(param_1[0x29deee] + 0x4e0) & 1) != 0)))) {
      uVar1 = (uint)*(byte *)(iVar4 + 0x4cc);
    }
    local_49 = (undefined1)uVar1;
    if (2 < DebugLevel) {
      printk("%s: PFMU ID = %d, BFer: %x, Band:%d\n","CmdETxBfPfmuProfileTagRead",param_2,param_3,
             uVar1);
    }
    local_48 = CONCAT13(0x1e,CONCAT12(0xed,(undefined2)local_48));
    local_44 = CONCAT31(local_44._1_3_,8);
    local_44 = CONCAT22(0xffff,(undefined2)local_44);
    local_34 = local_48;
    uStack_30 = local_44;
    uStack_2c = local_40;
    uStack_28 = local_3c;
    local_24 = local_38;
    AndesInitCmdMsg(iVar2,local_48,local_44,local_40,local_3c,local_38);
    AndesAppendCmdMsg(iVar2,&local_4c,4);
    uVar3 = chip_cmd_tx(param_1,iVar2);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdETxBfPfmuProfileTagRead",uVar3);
  }
  return uVar3;
}

