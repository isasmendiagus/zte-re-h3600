// module: mt7915.ko
// function: MtCmdGetRssi @ 0x1534e0
// size: 284 bytes
//

undefined4 MtCmdGetRssi(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_30 [2];
  undefined2 local_2e;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  code *local_1c;
  
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  if (3 < DebugLevel) {
    printk("%s: wcid: %d\n","MtCmdGetRssi",param_2);
  }
  iVar1 = AndesAllocCmdMsg(param_1,4);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    os_zero_mem(local_30,4);
    local_1c = phy_stat_rssi_rsp_handle;
    local_2c = CONCAT13(0xad,CONCAT12(0xed,(undefined2)local_2c));
    local_28 = CONCAT31(local_28._1_3_,0xf);
    local_28 = CONCAT22(8,(undefined2)local_28);
    local_30[0] = 2;
    local_2e = (undefined2)param_2;
    local_20 = param_3;
    AndesInitCmdMsg(iVar1,local_2c,local_28,local_24,param_3,phy_stat_rssi_rsp_handle);
    AndesAppendCmdMsg(iVar1,local_30,4);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdGetRssi",uVar2);
  }
  return uVar2;
}

