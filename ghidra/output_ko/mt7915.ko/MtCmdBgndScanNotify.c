// module: mt7915.ko
// function: MtCmdBgndScanNotify @ 0x1b9f0c
// size: 344 bytes
//

undefined4 MtCmdBgndScanNotify(undefined4 param_1,uint param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined1 local_4c;
  undefined1 local_4b;
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
  uVar3 = (param_2 << 0x10) >> 0x18;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  if (2 < DebugLevel) {
    printk("%s: NotifyFunc = %d, BgndScanStatus = %d\n","MtCmdBgndScanNotify",param_2 & 0xff,uVar3);
  }
  iVar1 = AndesAllocCmdMsg(param_1,4);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_48 = CONCAT13(0x4d,CONCAT12(0xed,(undefined2)local_48));
    local_44 = CONCAT31(local_44._1_3_,0xf);
    local_44 = CONCAT22(8,(undefined2)local_44);
    local_34 = local_48;
    uStack_30 = local_44;
    uStack_2c = local_40;
    uStack_28 = local_3c;
    local_24 = EventExtCmdResult;
    AndesInitCmdMsg(iVar1,local_48,local_44,local_40,local_3c,EventExtCmdResult);
    os_zero_mem(&local_4c,4);
    local_4c = (undefined1)param_2;
    local_4b = (undefined1)(param_2 >> 8);
    if (2 < DebugLevel) {
      printk("%s: ucNotifyFunc = %d, ucBgndScanStatus = %d\n","MtCmdBgndScanNotify",param_2 & 0xff,
             uVar3);
    }
    AndesAppendCmdMsg(iVar1,&local_4c,4);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdBgndScanNotify",uVar2);
  }
  return uVar2;
}

