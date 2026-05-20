// module: mt7915.ko
// function: MtCmdEfuseFreeBlockCount @ 0x1acbc0
// size: 616 bytes
//

undefined4 MtCmdEfuseFreeBlockCount(int param_1,undefined1 *param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_4c;
  undefined1 local_4b;
  undefined1 local_4a;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  code *local_38;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  code *local_24;
  
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_38 = (code *)0x0;
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7663 ||
      (*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) {
    cVar1 = param_2[1];
    iVar2 = AndesAllocCmdMsg(param_1,4);
    if (iVar2 == 0) {
LAB_001acd5c:
      uVar3 = 3;
      goto LAB_001accbc;
    }
    if (cVar1 == '\0') goto LAB_001acce0;
    if (cVar1 == '\x01') {
      local_48._0_3_ = CONCAT12(0xed,(undefined2)local_48);
      local_48 = CONCAT13(0x4f,(undefined3)local_48);
      local_44 = CONCAT31(local_44._1_3_,7);
      local_44 = CONCAT22(4,(undefined2)local_44);
      local_34 = local_48;
      uStack_30 = local_44;
      uStack_2c = local_40;
      local_24 = CmdEfuseFreeBlockCountCb;
      local_3c = param_3;
      uStack_28 = param_3;
      AndesInitCmdMsg(iVar2,local_48,local_44,local_40,param_3,CmdEfuseFreeBlockCountCb);
      os_zero_mem(&local_4c,4);
      local_4b = param_2[1];
      local_4a = param_2[2];
      if (0 < DebugLevel) {
        printk("%s:\tVersion = %x  DieIndex:%d\n","MtCmdEfuseFreeBlockCount");
      }
    }
    else {
      local_44._1_3_ = local_44._1_3_ & 0xff;
      local_3c = 0;
      local_48._0_3_ = CONCAT12(0xed,(undefined2)local_48);
      local_48 = CONCAT13(0x4f,(undefined3)local_48);
      local_44 = CONCAT31(local_44._1_3_,7);
      local_34 = local_48;
      uStack_30 = local_44;
      uStack_2c = local_40;
      uStack_28 = 0;
      local_24 = (code *)0x0;
      AndesInitCmdMsg(iVar2,local_48,local_44,local_40,0,0);
      os_zero_mem(&local_4c,4);
    }
  }
  else {
    iVar2 = AndesAllocCmdMsg(param_1,4);
    if (iVar2 == 0) goto LAB_001acd5c;
LAB_001acce0:
    local_48._0_3_ = CONCAT12(0xed,(undefined2)local_48);
    local_48 = CONCAT13(0x4f,(undefined3)local_48);
    local_44 = CONCAT31(local_44._1_3_,7);
    local_44 = CONCAT22(8,(undefined2)local_44);
    local_34 = local_48;
    uStack_30 = local_44;
    uStack_2c = local_40;
    local_24 = local_38;
    local_3c = param_3;
    uStack_28 = param_3;
    AndesInitCmdMsg(iVar2,local_48,local_44,local_40,param_3,local_38);
    os_zero_mem(&local_4c,4);
    local_4c = *param_2;
  }
  AndesAppendCmdMsg(iVar2,&local_4c,4);
  uVar3 = chip_cmd_tx(param_1,iVar2);
LAB_001accbc:
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdEfuseFreeBlockCount",uVar3);
  }
  return uVar3;
}

