// module: mt7915.ko
// function: MtCmdSetDpdFlatnessCal_7915 @ 0x1b9008
// size: 276 bytes
//

undefined4 MtCmdSetDpdFlatnessCal_7915(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int local_44;
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
  
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  iVar1 = DpdFlatnessCalInfoAlloc_7915(param_1,&local_44,param_2,param_3);
  if ((iVar1 == 0) || (iVar2 = AndesAllocCmdMsg(param_1,iVar1), iVar2 == 0)) {
    uVar3 = 3;
  }
  else {
    local_3c = CONCAT22((short)iVar1,(undefined2)local_3c);
    local_40 = CONCAT13(0xac,CONCAT12(0xed,(undefined2)local_40));
    local_3c = CONCAT31(local_3c._1_3_,10);
    local_2c = local_40;
    uStack_28 = local_3c;
    uStack_24 = local_38;
    uStack_20 = local_34;
    local_1c = local_30;
    AndesInitCmdMsg(iVar2,local_40,local_3c,local_38,local_34,local_30);
    AndesAppendCmdMsg(iVar2,local_44,iVar1);
    uVar3 = chip_cmd_tx(param_1,iVar2);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdSetDpdFlatnessCal_7915",uVar3);
  }
  if (local_44 != 0) {
    os_free_mem();
  }
  return uVar3;
}

