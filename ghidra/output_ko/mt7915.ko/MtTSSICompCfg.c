// module: mt7915.ko
// function: MtTSSICompCfg @ 0x1bc4a4
// size: 276 bytes
//

undefined4 MtTSSICompCfg(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_3c;
  undefined1 local_3b;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 local_14;
  
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar1 = AndesAllocCmdMsg(param_1,4);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_38 = CONCAT13(0x58,CONCAT12(0xed,(undefined2)local_38));
    local_34 = CONCAT31(local_34._1_3_,8);
    local_34 = CONCAT22(0xffff,(undefined2)local_34);
    local_24 = local_38;
    uStack_20 = local_34;
    uStack_1c = local_30;
    uStack_18 = local_2c;
    local_14 = local_28;
    AndesInitCmdMsg(iVar1,local_38,local_34,local_30,local_2c,local_28);
    __memzero(&local_3c,4);
    local_3b = 4;
    local_3c = 0xb;
    AndesAppendCmdMsg(iVar1,&local_3c,4);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtTSSICompCfg",uVar2);
  }
  return uVar2;
}

