// module: mt7915.ko
// function: mt_cmd_get_rx_stat @ 0x1be7e0
// size: 260 bytes
//

undefined4 mt_cmd_get_rx_stat(undefined4 param_1,undefined1 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_44;
  undefined1 local_43;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  code *local_1c;
  
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  os_zero_mem(&local_44,4);
  iVar1 = AndesAllocCmdMsg(param_1,4);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_40 = CONCAT13(0xa4,CONCAT12(0xed,(undefined2)local_40));
    local_3c = CONCAT31(local_3c._1_3_,5);
    local_3c = CONCAT22(0x54,(undefined2)local_3c);
    local_44 = 0;
    local_2c = local_40;
    uStack_28 = local_3c;
    uStack_24 = local_38;
    local_1c = mt_cmd_get_rx_stat_rsp;
    local_43 = param_2;
    local_34 = param_3;
    uStack_20 = param_3;
    AndesInitCmdMsg(iVar1,local_40,local_3c,local_38,param_3,mt_cmd_get_rx_stat_rsp);
    AndesAppendCmdMsg(iVar1,&local_44,4);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","mt_cmd_get_rx_stat",uVar2);
  }
  return uVar2;
}

