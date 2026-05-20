// module: mt7915.ko
// function: CmdRaFixRateUpdateWoSta @ 0x1d9810
// size: 264 bytes
//

undefined4
CmdRaFixRateUpdateWoSta
          (undefined4 param_1,int param_2,void *param_3,undefined1 param_4,undefined1 param_5)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_39 [9];
  byte local_30;
  undefined1 local_2f;
  undefined1 local_2e;
  undefined1 local_2d;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  os_move_mem(auStack_39,param_3,9);
  local_2d = (undefined1)param_2;
  local_2e = param_5;
  local_30 = (byte)((uint)(param_2 << 0x16) >> 0x1e);
  local_2f = param_4;
  iVar1 = AndesAllocCmdMsg(param_1,0xd);
  if (iVar1 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    local_28 = CONCAT31(local_28._1_3_,8);
    local_2c = CONCAT13(0x91,CONCAT12(0xed,(undefined2)local_2c));
    local_28 = CONCAT22(0xffff,(undefined2)local_28);
    AndesInitCmdMsg(iVar1,local_2c,local_28,local_24,local_20,local_1c);
    AndesAppendCmdMsg(iVar1,auStack_39,0xd);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (0 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdRaFixRateUpdateWoSta",uVar2);
  }
  return uVar2;
}

