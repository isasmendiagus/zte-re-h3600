// module: mt7915.ko
// function: MtCmdEfuseAccessCheck @ 0x1acf90
// size: 312 bytes
//

undefined4 MtCmdEfuseAccessCheck(undefined4 param_1,uint param_2,void *param_3)

{
  int iVar1;
  undefined4 uVar2;
  uint local_5c;
  undefined1 auStack_58 [16];
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
  if (3 < DebugLevel) {
    printk("%s: offset = %x\n","MtCmdEfuseAccessCheck",param_2);
  }
  iVar1 = AndesAllocCmdMsg(param_1,0x14);
  if (iVar1 == 0) {
    uVar2 = 3;
  }
  else {
    local_48 = CONCAT13(0x72,CONCAT12(0xed,(undefined2)local_48));
    local_44 = CONCAT22(0x14,(undefined2)local_44);
    local_44 = CONCAT31(local_44._1_3_,7);
    local_34 = local_48;
    uStack_30 = local_44;
    uStack_2c = local_40;
    uStack_28 = local_3c;
    local_24 = local_38;
    AndesInitCmdMsg(iVar1,local_48,local_44,local_40,local_3c,local_38);
    os_zero_mem(&local_5c,0x14);
    local_5c = param_2 & 0xfffffff0;
    os_move_mem(auStack_58,param_3,0x10);
    AndesAppendCmdMsg(iVar1,&local_5c,0x14);
    uVar2 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdEfuseAccessCheck",uVar2);
  }
  return uVar2;
}

