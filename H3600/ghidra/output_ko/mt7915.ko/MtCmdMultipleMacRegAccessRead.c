// module: mt7915.ko
// function: MtCmdMultipleMacRegAccessRead @ 0x1b0100
// size: 292 bytes
//

undefined4 MtCmdMultipleMacRegAccessRead(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  int local_3c;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  int iStack_28;
  code *local_24;
  
  iVar2 = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  iVar1 = AndesAllocCmdMsg(param_1,param_3 * 0xc);
  if (iVar1 == 0) {
    uVar3 = 3;
  }
  else {
    local_44 = CONCAT22((short)(param_3 * 0xc) + 0x14,(undefined2)local_44);
    local_48 = CONCAT13(0xe,CONCAT12(0xed,(undefined2)local_48));
    local_44 = CONCAT31(local_44._1_3_,7);
    local_34 = local_48;
    uStack_30 = local_44;
    uStack_2c = local_40;
    local_24 = CmdMultipleMacRegAccessReadCb;
    local_3c = param_2;
    iStack_28 = param_2;
    AndesInitCmdMsg(iVar1,local_48,local_44,local_40,param_2,CmdMultipleMacRegAccessReadCb);
    if (param_3 != 0) {
      do {
        os_zero_mem(&local_54,0xc);
        local_50 = *(undefined4 *)(param_2 + iVar2 * 8);
        iVar2 = iVar2 + 1;
        local_54 = 0;
        AndesAppendCmdMsg(iVar1,&local_54,0xc);
      } while (iVar2 != param_3);
    }
    uVar3 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdMultipleMacRegAccessRead",uVar3);
  }
  return uVar3;
}

