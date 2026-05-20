// module: mt7915.ko
// function: MtCmdPwrLimitTblUpdate @ 0x150980
// size: 400 bytes
//

undefined4
MtCmdPwrLimitTblUpdate
          (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined1 param_5,
          undefined1 param_6)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_e4;
  undefined1 local_e3;
  undefined1 local_e2;
  undefined1 auStack_e1 [189];
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (2 < DebugLevel) {
    printk("%s: u1Type: %d, u1BandIdx: %d, u1ChannelBand: %d, u1ControlChannel: %d, u1CentralChannel: %d\n"
           ,"MtCmdPwrLimitTblUpdate",param_3,param_2,param_4,param_5,param_6);
  }
  iVar2 = AndesAllocCmdMsg(param_1,0xbc);
  if (iVar2 == 0) {
    uVar3 = 3;
  }
  else {
    os_zero_mem(&local_e4,0xbc);
    local_e3 = (undefined1)param_3;
    local_e2 = (undefined1)param_2;
    if (*(char *)(iVar1 + 0x210) == '\x01') {
      local_e4 = 4;
      MtPwrFillLimitParam(param_1,param_4,param_5,param_6,auStack_e1,param_3);
    }
    AndesInitCmdMsg(iVar2,0x58ed0000,0xffff0008,0,0,0);
    AndesAppendCmdMsg(iVar2,&local_e4,0xbc);
    uVar3 = chip_cmd_tx(param_1,iVar2);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdPwrLimitTblUpdate",uVar3);
  }
  return uVar3;
}

