// module: mt7915.ko
// function: MtCmdThermoCompCtrl @ 0x1bb7f8
// size: 340 bytes
//

undefined4 MtCmdThermoCompCtrl(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_4c;
  undefined1 local_4b;
  undefined1 local_4a;
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
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (0 < DebugLevel) {
    printk("%s: fgThermoCompEn: %d, BandIdx: %d\n","MtCmdThermoCompCtrl",param_2,param_3);
  }
  iVar2 = AndesAllocCmdMsg(param_1,4);
  if (iVar2 == 0) {
    uVar3 = 3;
  }
  else {
    os_zero_mem(&local_4c,4);
    if (*(char *)(iVar1 + 0x210) == '\0') {
      local_4c = 0xd;
    }
    else {
      local_4c = 0xc;
    }
    local_44 = CONCAT31(local_44._1_3_,8);
    local_48 = CONCAT13(0x58,CONCAT12(0xed,(undefined2)local_48));
    local_44 = CONCAT22(0xffff,(undefined2)local_44);
    local_4b = (undefined1)param_2;
    local_4a = (undefined1)param_3;
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
    printk("%s:(ret = %d)\n","MtCmdThermoCompCtrl",uVar3);
  }
  return uVar3;
}

