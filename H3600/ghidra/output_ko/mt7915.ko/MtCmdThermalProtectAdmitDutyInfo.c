// module: mt7915.ko
// function: MtCmdThermalProtectAdmitDutyInfo @ 0x1b4de4
// size: 248 bytes
//

undefined4 MtCmdThermalProtectAdmitDutyInfo(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_4c [20];
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 local_14;
  
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  iVar1 = AndesAllocCmdMsg(param_1,0x14);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_38 = CONCAT13(0x23,CONCAT12(0xed,(undefined2)local_38));
    local_34 = CONCAT31(local_34._1_3_,8);
    local_34 = CONCAT22(0xffff,(undefined2)local_34);
    local_24 = local_38;
    uStack_20 = local_34;
    uStack_1c = local_30;
    uStack_18 = local_2c;
    local_14 = local_28;
    AndesInitCmdMsg(iVar1,local_38,local_34,local_30,local_2c,local_28);
    os_zero_mem(local_4c,0x14);
    local_4c[0] = 1;
    AndesAppendCmdMsg(iVar1,local_4c,0x14);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdThermalProtectAdmitDutyInfo",uVar2);
  }
  return uVar2;
}

