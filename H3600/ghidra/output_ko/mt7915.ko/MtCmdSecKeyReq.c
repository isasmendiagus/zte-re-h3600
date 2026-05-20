// module: mt7915.ko
// function: MtCmdSecKeyReq @ 0x1b078c
// size: 332 bytes
//

undefined4
MtCmdSecKeyReq(undefined4 param_1,undefined1 param_2,undefined1 param_3,void *param_4,
              undefined1 param_5,undefined1 param_6,byte param_7,undefined1 param_8,void *param_9)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_68 [2];
  undefined1 local_66;
  undefined1 auStack_64 [7];
  undefined1 local_5d;
  undefined1 local_5c;
  byte local_5b;
  undefined1 local_5a;
  undefined1 auStack_48 [36];
  
  iVar1 = AndesAllocCmdMsg(param_1,0x40);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    AndesInitCmdMsg(iVar1,0x10ed0000,0xc0009,0,0,CmdSecKeyRsp);
    os_zero_mem(local_68,0x40);
    local_68[0] = param_2;
    local_66 = param_3;
    os_move_mem(auStack_64,param_4,6);
    local_5d = param_5;
    local_5c = param_6;
    local_5b = param_7;
    os_move_mem(auStack_48,param_9,(uint)param_7);
    local_5a = param_8;
    AndesAppendCmdMsg(iVar1,local_68,0x40);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdSecKeyReq",uVar2);
  }
  return uVar2;
}

