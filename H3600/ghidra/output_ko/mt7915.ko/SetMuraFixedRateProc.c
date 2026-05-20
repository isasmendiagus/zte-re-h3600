// module: mt7915.ko
// function: SetMuraFixedRateProc @ 0x9578c
// size: 364 bytes
//

bool SetMuraFixedRateProc(int param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  bool bVar3;
  undefined1 local_31;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  bVar3 = false;
  local_30 = 4;
  uVar2 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  local_31 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  if (uVar2 == 0x7626 || (uVar2 == 0x7663 || uVar2 == 0x7615)) {
    local_31 = os_str_tol(param_2,0,10);
    iVar1 = AndesAllocCmdMsg(param_1,5);
    bVar3 = iVar1 != 0;
    if (bVar3) {
      local_2c = CONCAT13(0x55,CONCAT12(0xed,(undefined2)local_2c));
      local_28 = CONCAT31(local_28._1_3_,10);
      AndesInitCmdMsg(iVar1,local_2c,local_28,local_24,local_20,local_1c);
      AndesAppendCmdMsg(iVar1,&local_30,4);
      AndesAppendCmdMsg(iVar1,&local_31,1);
      AndesSendCmdMsg(param_1,iVar1);
    }
    if (3 < DebugLevel) {
      printk("%s:(Ret = %d_\n","SetMuraFixedRateProc",bVar3);
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s: Not Supported (Ret = %d_\n","SetMuraFixedRateProc",0);
    bVar3 = false;
  }
  return bVar3;
}

