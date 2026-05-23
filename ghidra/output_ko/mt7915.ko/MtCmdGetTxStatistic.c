// module: mt7915.ko
// function: MtCmdGetTxStatistic @ 0x1b5a78
// size: 324 bytes
//

int MtCmdGetTxStatistic(undefined4 param_1,undefined4 param_2,undefined1 param_3,int param_4,
                       undefined4 param_5)

{
  int iVar1;
  undefined4 local_54;
  undefined1 local_50;
  undefined1 local_4f;
  byte local_4e;
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
  os_zero_mem(&local_54,0xc);
  if (2 < DebugLevel) {
    printk("%s:u4Field=0x%8x, Wcid=%d\n","MtCmdGetTxStatistic",param_2,param_4);
  }
  iVar1 = AndesAllocCmdMsg(param_1,0xc);
  if (iVar1 == 0) {
    iVar1 = 3;
  }
  else {
    local_44 = CONCAT31(local_44._1_3_,7);
    local_3c = param_5;
    local_48 = CONCAT13(0x30,CONCAT12(0xed,(undefined2)local_48));
    local_44 = CONCAT22(0x44,(undefined2)local_44);
    local_34 = local_48;
    uStack_30 = local_44;
    uStack_2c = local_40;
    uStack_28 = param_5;
    local_24 = MtCmdGetTxStatisticRsp;
    AndesInitCmdMsg(iVar1,local_48,local_44,local_40,param_5,MtCmdGetTxStatisticRsp);
    local_4e = (byte)((uint)(param_4 << 0x16) >> 0x1e);
    local_50 = (undefined1)param_4;
    local_54 = param_2;
    local_4f = param_3;
    AndesAppendCmdMsg(iVar1,&local_54,0xc);
    iVar1 = chip_cmd_tx(param_1,iVar1);
    if (iVar1 == 0) {
      return 0;
    }
  }
  if (0 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdGetTxStatistic",iVar1);
  }
  return iVar1;
}

