// module: mt7915.ko
// function: SetMuraDisableCN3CN4Proc @ 0x97790
// size: 364 bytes
//

bool SetMuraDisableCN3CN4Proc(int param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  bool bVar4;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  bVar4 = false;
  uVar3 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_30 = 0;
  local_34 = 9;
  if (uVar3 == 0x7626 || (uVar3 == 0x7663 || uVar3 == 0x7615)) {
    iVar2 = AndesAllocCmdMsg(param_1,8);
    bVar4 = iVar2 != 0;
    if (bVar4) {
      uVar1 = simple_strtol(param_2,0,10);
      local_28 = CONCAT31(local_28._1_3_,10);
      local_2c = CONCAT13(0x55,CONCAT12(0xed,(undefined2)local_2c));
      local_30 = CONCAT31(local_30._1_3_,uVar1);
      AndesInitCmdMsg(iVar2,local_2c,local_28,local_24,local_20,local_1c);
      AndesAppendCmdMsg(iVar2,&local_34,4);
      AndesAppendCmdMsg(iVar2,&local_30,4);
      AndesSendCmdMsg(param_1,iVar2);
    }
    if (3 < DebugLevel) {
      printk("%s:(Ret = %d_\n","SetMuraDisableCN3CN4Proc",bVar4);
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s: Not Supported (Ret = %d_\n","SetMuraDisableCN3CN4Proc",0);
    bVar4 = false;
  }
  return bVar4;
}

