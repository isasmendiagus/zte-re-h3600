// module: mt7915.ko
// function: mt_cmd_get_rdd_ipi_hist @ 0x1be6dc
// size: 256 bytes
//

undefined4 mt_cmd_get_rdd_ipi_hist(undefined4 param_1,undefined1 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_54 [20];
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
  os_zero_mem(local_54,0x14);
  iVar1 = AndesAllocCmdMsg(param_1,0x14);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_40 = CONCAT13(0xa3,CONCAT12(0xed,(undefined2)local_40));
    local_3c = CONCAT31(local_3c._1_3_,7);
    local_3c = CONCAT22(0x34,(undefined2)local_3c);
    local_2c = local_40;
    uStack_28 = local_3c;
    uStack_24 = local_38;
    local_1c = mt_cmd_get_rdd_ipi_hist_rsp;
    local_34 = param_3;
    uStack_20 = param_3;
    AndesInitCmdMsg(iVar1,local_40,local_3c,local_38,param_3,mt_cmd_get_rdd_ipi_hist_rsp);
    local_54[0] = param_2;
    AndesAppendCmdMsg(iVar1,local_54,0x14);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","mt_cmd_get_rdd_ipi_hist",uVar2);
  }
  return uVar2;
}

