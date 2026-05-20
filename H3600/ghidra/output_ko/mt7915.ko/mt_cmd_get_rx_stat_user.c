// module: mt7915.ko
// function: mt_cmd_get_rx_stat_user @ 0x1beafc
// size: 260 bytes
//

undefined4 mt_cmd_get_rx_stat_user(undefined4 param_1,undefined2 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_4c [2];
  undefined2 local_4a;
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
  os_zero_mem(local_4c,4);
  iVar1 = AndesAllocCmdMsg(param_1,4);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_44 = CONCAT31(local_44._1_3_,5);
    local_48 = CONCAT13(0xa4,CONCAT12(0xed,(undefined2)local_48));
    local_44 = CONCAT22(4,(undefined2)local_44);
    local_4c[0] = 5;
    local_34 = local_48;
    uStack_30 = local_44;
    uStack_2c = local_40;
    local_24 = mt_cmd_get_rx_stat_user_rsp;
    local_4a = param_2;
    local_3c = param_3;
    uStack_28 = param_3;
    AndesInitCmdMsg(iVar1,local_48,local_44,local_40,param_3,mt_cmd_get_rx_stat_user_rsp);
    AndesAppendCmdMsg(iVar1,local_4c,4);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","mt_cmd_get_rx_stat_user",uVar2);
  }
  return uVar2;
}

