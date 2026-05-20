// module: mt7915.ko
// function: MtCmdMultipleMibRegAccessRead @ 0x1b0668
// size: 288 bytes
//

undefined4
MtCmdMultipleMibRegAccessRead(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_58;
  undefined4 local_54;
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
  iVar1 = AndesAllocCmdMsg(param_1,param_4 << 4);
  if (iVar1 == 0) {
    uVar3 = 3;
  }
  else {
    local_44 = CONCAT22((short)(param_4 << 4) + 0x14,(undefined2)local_44);
    local_48 = CONCAT13(0x5a,CONCAT12(0xed,(undefined2)local_48));
    local_44 = CONCAT31(local_44._1_3_,7);
    local_34 = local_48;
    uStack_30 = local_44;
    uStack_2c = local_40;
    local_24 = CmdMultipleMibRegAccessReadCb;
    local_3c = param_3;
    iStack_28 = param_3;
    AndesInitCmdMsg(iVar1,local_48,local_44,local_40,param_3,CmdMultipleMibRegAccessReadCb);
    if (param_4 != 0) {
      do {
        os_zero_mem(&local_58,0x10);
        local_54 = *(undefined4 *)(param_3 + iVar2 * 0x10);
        iVar2 = iVar2 + 1;
        local_58 = param_2;
        AndesAppendCmdMsg(iVar1,&local_58,0x10);
      } while (iVar2 != param_4);
    }
    uVar3 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdMultipleMibRegAccessRead",uVar3);
  }
  return uVar3;
}

