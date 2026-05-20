// module: mt7915.ko
// function: MtCmdGetTxPower @ 0x1b0a5c
// size: 364 bytes
//

undefined4
MtCmdGetTxPower(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_54;
  undefined1 local_53;
  undefined1 local_52;
  undefined1 local_51;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  code *local_2c;
  
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (0 < DebugLevel) {
    printk("%s: u1CenterCh: %d, u1BandIdx: %d, u1AntIdx: %d\n","MtCmdGetTxPower",param_3,param_2,
           param_4);
  }
  iVar2 = AndesAllocCmdMsg(param_1,4);
  if (iVar2 == 0) {
    uVar3 = 3;
  }
  else {
    os_zero_mem(&local_54,4);
    if (*(char *)(iVar1 + 0x210) == '\0') {
      local_54 = 0x11;
    }
    else {
      local_54 = 0x10;
    }
    local_4c = CONCAT22(4,(undefined2)local_4c);
    local_44 = param_5;
    local_50 = CONCAT13(0x58,CONCAT12(0xed,(undefined2)local_50));
    local_4c = CONCAT31(local_4c._1_3_,7);
    local_53 = (undefined1)param_2;
    local_52 = (undefined1)param_4;
    local_51 = (undefined1)param_3;
    local_3c = local_50;
    uStack_38 = local_4c;
    uStack_34 = local_48;
    uStack_30 = param_5;
    local_2c = MtCmdGetTxPowerRsp;
    AndesInitCmdMsg(iVar2,local_50,local_4c,local_48,param_5,MtCmdGetTxPowerRsp);
    AndesAppendCmdMsg(iVar2,&local_54,4);
    uVar3 = chip_cmd_tx(param_1,iVar2);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdGetTxPower",uVar3);
  }
  return uVar3;
}

