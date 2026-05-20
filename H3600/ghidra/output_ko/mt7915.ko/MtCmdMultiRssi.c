// module: mt7915.ko
// function: MtCmdMultiRssi @ 0x153600
// size: 272 bytes
//

undefined4 MtCmdMultiRssi(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 local_40;
  undefined1 local_3f;
  undefined2 local_3e;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  int local_30;
  code *local_2c;
  
  iVar2 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  iVar1 = AndesAllocCmdMsg(param_1,param_3 << 2);
  if (iVar1 == 0) {
    uVar3 = 3;
  }
  else {
    local_2c = phy_stat_multi_rssi_rsp_handle;
    local_3c = CONCAT13(0xad,CONCAT12(0xed,(undefined2)local_3c));
    local_38 = CONCAT31(local_38._1_3_,0xf);
    local_38 = CONCAT22((short)(param_3 << 3),(undefined2)local_38);
    local_30 = param_2;
    AndesInitCmdMsg(iVar1,local_3c,local_38,local_34,param_2,phy_stat_multi_rssi_rsp_handle);
    iVar4 = iVar2;
    if (param_3 != 0) {
      do {
        local_3e = *(undefined2 *)(param_2 + iVar2);
        iVar4 = iVar4 + 1;
        local_40 = 2;
        local_3f = 0;
        iVar2 = iVar2 + 6;
        AndesAppendCmdMsg(iVar1,&local_40,4);
      } while (iVar4 != param_3);
    }
    uVar3 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdMultiRssi",uVar3);
  }
  return uVar3;
}

