// module: mt7915.ko
// function: MtCmdMemDump @ 0x1b7860
// size: 328 bytes
//

void MtCmdMemDump(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 *local_34;
  undefined4 local_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 *puStack_20;
  code *local_1c;
  
  local_48 = (undefined4 *)0x0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  os_zero_mem(&local_44,4);
  local_44 = param_3;
  os_alloc_mem(param_1,&local_48,0x44);
  if (local_48 == (undefined4 *)0x0) {
    uVar2 = 3;
  }
  else {
    iVar1 = AndesAllocCmdMsg(param_1,0x44);
    if (iVar1 == 0) {
      uVar2 = 3;
    }
    else {
      local_34 = &local_44;
      local_40 = CONCAT13(0x57,CONCAT12(0xed,(undefined2)local_40));
      local_3c = CONCAT22(0x44,(undefined2)local_3c);
      local_3c = CONCAT31(local_3c._1_3_,0xd);
      local_2c = local_40;
      uStack_28 = local_3c;
      uStack_24 = local_38;
      local_1c = CmdMemDumpRsp;
      puStack_20 = local_34;
      AndesInitCmdMsg(iVar1,local_40,local_3c,local_38,local_34,CmdMemDumpRsp);
      os_zero_mem(local_48,0x44);
      *local_48 = param_2;
      AndesAppendCmdMsg(iVar1,local_48,0x44);
      uVar2 = chip_cmd_tx(param_1,iVar1);
    }
    if (local_48 != (undefined4 *)0x0) {
      os_free_mem();
    }
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdMemDump",uVar2);
  }
  return;
}

