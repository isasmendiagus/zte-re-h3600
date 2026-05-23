// module: mt7915.ko
// function: MtCmdThermalProtectAdmitDuty @ 0x1b4ee0
// size: 288 bytes
//

undefined4
MtCmdThermalProtectAdmitDuty
          (undefined4 param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
          undefined1 param_5,undefined1 param_6)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 uStack_5c;
  undefined1 local_5b;
  undefined1 local_4d;
  undefined1 local_4c;
  undefined1 local_4b;
  undefined1 local_4a;
  undefined1 local_49;
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
  local_3c = 0;
  iVar1 = AndesAllocCmdMsg(param_1,0x14);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_48 = CONCAT13(0x23,CONCAT12(0xed,(undefined2)local_48));
    local_44 = CONCAT31(local_44._1_3_,0xf);
    local_44 = CONCAT22(8,(undefined2)local_44);
    local_34 = local_48;
    uStack_30 = local_44;
    uStack_2c = local_40;
    uStack_28 = local_3c;
    local_24 = EventExtCmdResult;
    AndesInitCmdMsg(iVar1,local_48,local_44,local_40,local_3c,EventExtCmdResult);
    os_zero_mem(&uStack_5c,0x14);
    local_4d = 1;
    local_4a = param_5;
    local_49 = param_6;
    local_5b = param_2;
    local_4c = param_3;
    local_4b = param_4;
    AndesAppendCmdMsg(iVar1,&uStack_5c,0x14);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdThermalProtectAdmitDuty",uVar2);
  }
  return uVar2;
}

