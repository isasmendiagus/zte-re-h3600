// module: mt7915.ko
// function: CmdPfmuMemAlloc @ 0x1b1e80
// size: 296 bytes
//

undefined4 CmdPfmuMemAlloc(undefined4 param_1,undefined1 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_4c;
  undefined1 local_4b;
  undefined1 local_4a;
  byte local_49;
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
  local_3c = 0;
  if (3 < DebugLevel) {
    printk("%s: u2WlanId = %d\n","CmdPfmuMemAlloc");
  }
  iVar1 = AndesAllocCmdMsg(param_1,4);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_48 = CONCAT13(0x1e,CONCAT12(0xed,(undefined2)local_48));
    local_44 = CONCAT31(local_44._1_3_,8);
    local_44 = CONCAT22(0xffff,(undefined2)local_44);
    local_4a = (undefined1)param_3;
    local_34 = local_48;
    uStack_30 = local_44;
    uStack_2c = local_40;
    uStack_28 = local_3c;
    local_24 = EventExtCmdResult;
    local_49 = (byte)((uint)(param_3 << 0x16) >> 0x1e);
    local_4c = 3;
    local_4b = param_2;
    AndesInitCmdMsg(iVar1,local_48,local_44,local_40,local_3c,EventExtCmdResult);
    AndesAppendCmdMsg(iVar1,&local_4c,4);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdPfmuMemAlloc",uVar2);
  }
  return uVar2;
}

