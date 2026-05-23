// module: mt7915.ko
// function: MtCmdMultipleRfRegAccessWrite @ 0x1b0528
// size: 316 bytes
//

undefined4 MtCmdMultipleRfRegAccessWrite(undefined4 param_1,byte *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  byte *pbVar4;
  uint local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  code *local_38;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  code *local_24;
  
  iVar2 = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  iVar1 = AndesAllocCmdMsg(param_1,param_3 * 0xc);
  if (iVar1 == 0) {
    uVar3 = 3;
  }
  else {
    local_38 = CmdMultipleRfRegAccessWriteCb;
    local_48 = CONCAT13(0xe,CONCAT12(0xed,(undefined2)local_48));
    local_44 = CONCAT31(local_44._1_3_,0xf);
    local_44 = CONCAT22(0x20,(undefined2)local_44);
    local_34 = local_48;
    uStack_30 = local_44;
    uStack_2c = local_40;
    uStack_28 = local_3c;
    local_24 = CmdMultipleRfRegAccessWriteCb;
    AndesInitCmdMsg(iVar1,local_48,local_44,local_40,local_3c,CmdMultipleRfRegAccessWriteCb);
    pbVar4 = param_2;
    if (param_3 != 0) {
      do {
        os_zero_mem(&local_54,0xc);
        local_50 = *(undefined4 *)(pbVar4 + 4);
        local_4c = *(undefined4 *)(pbVar4 + 8);
        iVar2 = iVar2 + 1;
        local_54 = (uint)*param_2 << 8 | 1;
        AndesAppendCmdMsg(iVar1,&local_54);
        pbVar4 = pbVar4 + 0xc;
      } while (iVar2 != param_3);
    }
    uVar3 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdMultipleRfRegAccessWrite",uVar3);
  }
  return uVar3;
}

