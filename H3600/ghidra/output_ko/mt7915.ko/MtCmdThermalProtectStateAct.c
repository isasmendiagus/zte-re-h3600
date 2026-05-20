// module: mt7915.ko
// function: MtCmdThermalProtectStateAct @ 0x1b56bc
// size: 360 bytes
//

undefined4
MtCmdThermalProtectStateAct
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
          undefined1 param_5)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_58;
  undefined1 local_57;
  undefined1 local_56;
  undefined1 local_55;
  undefined1 local_54;
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
  if ((0 < DebugLevel) &&
     (printk("%s: band_idx: %d, protect_type: %d\n","MtCmdThermalProtectStateAct",param_2,param_3),
     0 < DebugLevel)) {
    printk("%s: trig_type: %d, state: %d\n","MtCmdThermalProtectStateAct",param_4,param_5);
  }
  iVar1 = AndesAllocCmdMsg(param_1,8);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    os_zero_mem(&local_58);
    local_50 = CONCAT13(0x23,CONCAT12(0xed,(undefined2)local_50));
    local_4c = CONCAT31(local_4c._1_3_,8);
    local_4c = CONCAT22(0xffff,(undefined2)local_4c);
    local_57 = (undefined1)param_2;
    local_56 = (undefined1)param_3;
    local_55 = (undefined1)param_4;
    local_3c = local_50;
    uStack_38 = local_4c;
    uStack_34 = local_48;
    uStack_30 = local_44;
    local_2c = local_40;
    local_58 = 7;
    local_54 = param_5;
    AndesInitCmdMsg(iVar1,local_50,local_4c,local_48,local_44,local_40);
    AndesAppendCmdMsg(iVar1,&local_58,8);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdThermalProtectStateAct",uVar2);
  }
  return uVar2;
}

