// module: mt7915.ko
// function: CmdETxBfPfmuProfileDataRead @ 0x1b255c
// size: 436 bytes
//

undefined4
CmdETxBfPfmuProfileDataRead(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_58;
  undefined1 local_57;
  undefined1 local_56;
  undefined1 local_55;
  undefined2 local_52;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 local_2c;
  
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  get_wdev_by_ioctl_idx_and_iftype
            (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  uVar1 = HcGetBandByWdev();
  iVar4 = param_1[0x29deee];
  iVar2 = AndesAllocCmdMsg(param_1,8);
  if (iVar2 == 0) {
    uVar3 = 3;
  }
  else {
    os_zero_mem(&local_58);
    local_57 = (undefined1)param_2;
    local_56 = (undefined1)param_3;
    local_52 = (undefined2)param_4;
    local_58 = 7;
    if (((param_1[0x28eb05] & 1U) != 0) ||
       ((param_1[0x29deed] == 1 && ((*(uint *)(param_1[0x29deee] + 0x4e0) & 1) != 0)))) {
      uVar1 = (uint)*(byte *)(iVar4 + 0x4cc);
    }
    local_55 = (undefined1)uVar1;
    if (2 < DebugLevel) {
      printk("%s: PFMU ID = %d, BFer:%x, Subcarrier:%d, Band:%d\n","CmdETxBfPfmuProfileDataRead",
             param_2,param_3,param_4,uVar1);
    }
    local_50 = CONCAT13(0x1e,CONCAT12(0xed,(undefined2)local_50));
    local_4c = CONCAT31(local_4c._1_3_,8);
    local_4c = CONCAT22(0xffff,(undefined2)local_4c);
    local_48 = CONCAT22(local_48._2_2_,500);
    local_3c = local_50;
    uStack_38 = local_4c;
    uStack_34 = local_48;
    uStack_30 = local_44;
    local_2c = local_40;
    AndesInitCmdMsg(iVar2,local_50,local_4c,local_48,local_44,local_40);
    AndesAppendCmdMsg(iVar2,&local_58,8);
    uVar3 = chip_cmd_tx(param_1,iVar2);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdETxBfPfmuProfileDataRead",uVar3);
  }
  return uVar3;
}

