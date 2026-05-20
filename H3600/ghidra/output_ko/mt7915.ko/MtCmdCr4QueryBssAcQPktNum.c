// module: mt7915.ko
// function: MtCmdCr4QueryBssAcQPktNum @ 0x1ba194
// size: 288 bytes
//

undefined4 MtCmdCr4QueryBssAcQPktNum(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 local_1c;
  
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  if (3 < DebugLevel) {
    printk(":%s: u4bssbitmap(0x%08X)\n","MtCmdCr4QueryBssAcQPktNum",param_2);
  }
  iVar1 = AndesAllocCmdMsg(param_1,0xc);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_40 = CONCAT13(local_40._3_1_,0xc40002);
    local_2c = local_40;
    uStack_28 = local_3c;
    uStack_24 = local_38;
    uStack_20 = local_34;
    local_1c = local_30;
    AndesInitCmdMsg(iVar1,local_40,local_3c,local_38,local_34,local_30);
    os_zero_mem(&local_4c,0xc);
    local_44 = 0;
    local_4c = 0x12;
    local_48 = param_2;
    AndesAppendCmdMsg(iVar1,&local_4c,0xc);
    uVar2 = chip_cmd_tx(param_1,iVar1);
    if (3 < DebugLevel) {
      printk("%s: (ret = %d)\n","MtCmdCr4QueryBssAcQPktNum",uVar2);
    }
  }
  return uVar2;
}

