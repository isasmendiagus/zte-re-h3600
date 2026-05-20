// module: mt7915.ko
// function: MtCmdSetTxPowerCtrl @ 0x1b08dc
// size: 380 bytes
//

undefined4
MtCmdSetTxPowerCtrl(int param_1,undefined4 param_2,undefined4 param_3,undefined1 param_4,
                   undefined4 param_5)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_68;
  undefined1 local_67;
  undefined1 local_66;
  undefined1 local_65;
  undefined1 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 local_3c;
  
  local_60 = 0;
  local_5c = 0;
  local_58 = 0;
  local_54 = 0;
  local_50 = 0;
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (0 < DebugLevel) {
    printk("%s: BandIdx: %d, Power: %d, AntIdx: %d\n","MtCmdSetTxPowerCtrl",param_5,param_3,param_2)
    ;
  }
  iVar2 = AndesAllocCmdMsg(param_1,8);
  if (iVar2 == 0) {
    uVar3 = 3;
  }
  else {
    os_zero_mem(&local_68);
    if (*(char *)(iVar1 + 0x210) == '\0') {
      local_68 = 0x10;
    }
    else {
      local_68 = 0xf;
    }
    local_5c = CONCAT31(local_5c._1_3_,8);
    local_60 = CONCAT13(0x58,CONCAT12(0xed,(undefined2)local_60));
    local_5c = CONCAT22(0xffff,(undefined2)local_5c);
    local_66 = (undefined1)param_3;
    local_67 = (undefined1)param_5;
    local_65 = (undefined1)param_2;
    local_4c = local_60;
    uStack_48 = local_5c;
    uStack_44 = local_58;
    uStack_40 = local_54;
    local_3c = local_50;
    local_64 = param_4;
    AndesInitCmdMsg(iVar2,local_60,local_5c,local_58,local_54,local_50);
    AndesAppendCmdMsg(iVar2,&local_68,8);
    uVar3 = chip_cmd_tx(param_1,iVar2);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdSetTxPowerCtrl",uVar3);
  }
  return uVar3;
}

