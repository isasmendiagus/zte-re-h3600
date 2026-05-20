// module: mt7915.ko
// function: CmdETxBfStaRecRead @ 0x1b3b70
// size: 292 bytes
//

undefined4 CmdETxBfStaRecRead(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_50;
  undefined1 local_4f;
  byte local_4e;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 local_24;
  
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  if (2 < DebugLevel) {
    printk("%s: WLAN ID = %d\n","CmdETxBfStaRecRead",param_2);
  }
  iVar1 = AndesAllocCmdMsg(param_1,8);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_48 = CONCAT13(0x1e,CONCAT12(0xed,(undefined2)local_48));
    local_44 = CONCAT31(local_44._1_3_,8);
    local_44 = CONCAT22(0xffff,(undefined2)local_44);
    local_4f = (undefined1)param_2;
    local_50 = 0xd;
    local_4e = (byte)((uint)(param_2 << 0x16) >> 0x1e);
    local_34 = local_48;
    uStack_30 = local_44;
    uStack_2c = local_40;
    uStack_28 = local_3c;
    local_24 = local_38;
    AndesInitCmdMsg(iVar1,local_48,local_44,local_40,local_3c,local_38);
    AndesAppendCmdMsg(iVar1,&local_50,8);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (2 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdETxBfStaRecRead",uVar2);
  }
  return uVar2;
}

