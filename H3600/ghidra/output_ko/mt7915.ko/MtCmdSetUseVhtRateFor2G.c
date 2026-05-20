// module: mt7915.ko
// function: MtCmdSetUseVhtRateFor2G @ 0x1bd34c
// size: 300 bytes
//

undefined4 MtCmdSetUseVhtRateFor2G(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_44 [4];
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
  iVar1 = AndesAllocCmdMsg(param_1,4);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    os_zero_mem(local_44,4);
    local_44[0] = *(undefined1 *)(param_1 + 0x795060);
    if (2 < DebugLevel) {
      printk("%s: Use VHT Rate for 2G = %d\n","MtCmdSetUseVhtRateFor2G");
    }
    local_40 = CONCAT13(0x90,CONCAT12(0xed,(undefined2)local_40));
    local_3c = CONCAT31(local_3c._1_3_,8);
    local_3c = CONCAT22(0xffff,(undefined2)local_3c);
    local_2c = local_40;
    uStack_28 = local_3c;
    uStack_24 = local_38;
    uStack_20 = local_34;
    local_1c = local_30;
    AndesInitCmdMsg(iVar1,local_40,local_3c,local_38,local_34,local_30);
    AndesAppendCmdMsg(iVar1,local_44,4);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdSetUseVhtRateFor2G",uVar2);
  }
  return uVar2;
}

