// module: mt7915.ko
// function: MtCmdGetThermalSensorResult @ 0x1b5828
// size: 312 bytes
//

undefined4
MtCmdGetThermalSensorResult
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_50;
  undefined1 local_4f;
  undefined1 local_4e;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  code *local_24;
  
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  if (2 < DebugLevel) {
    printk("%s: ActionIdx: %d, uBandIdx: %d\n","MtCmdGetThermalSensorResult",param_2,param_3);
  }
  iVar1 = AndesAllocCmdMsg(param_1,8);
  if (iVar1 != 0) {
    os_zero_mem(&local_50);
    local_44 = CONCAT22(8,(undefined2)local_44);
    local_48 = CONCAT13(0x2c,CONCAT12(0xed,(undefined2)local_48));
    local_44 = CONCAT31(local_44._1_3_,7);
    local_4f = (undefined1)param_2;
    local_4e = (undefined1)param_3;
    local_50 = 0;
    local_34 = local_48;
    uStack_30 = local_44;
    uStack_2c = local_40;
    local_24 = MtCmdThemalSensorRsp;
    local_3c = param_4;
    uStack_28 = param_4;
    AndesInitCmdMsg(iVar1,local_48,local_44,local_40,param_4,MtCmdThemalSensorRsp);
    AndesAppendCmdMsg(iVar1,&local_50,8);
    uVar2 = chip_cmd_tx(param_1,iVar1);
    return uVar2;
  }
  if (-1 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdGetThermalSensorResult",3);
  }
  return 3;
}

