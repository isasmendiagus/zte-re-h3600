// module: mt7915.ko
// function: SetMuraTestAlgorithmProc @ 0x94ff0
// size: 360 bytes
//

bool SetMuraTestAlgorithmProc(int param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  bool bVar3;
  undefined2 local_32;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  bVar3 = false;
  uVar2 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  local_30 = 6;
  local_32 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  if (uVar2 == 0x7626 || (uVar2 == 0x7663 || uVar2 == 0x7615)) {
    iVar1 = AndesAllocCmdMsg();
    bVar3 = iVar1 != 0;
    if (bVar3) {
      local_32 = os_str_tol(param_2,0,10);
      local_28 = CONCAT31(local_28._1_3_,10);
      local_2c = CONCAT13(0x55,CONCAT12(0xed,(undefined2)local_2c));
      AndesInitCmdMsg(iVar1,local_2c,local_28,local_24,local_20,local_1c);
      AndesAppendCmdMsg(iVar1,&local_30,4);
      AndesAppendCmdMsg(iVar1,&local_32,2);
      AndesSendCmdMsg(param_1,iVar1);
    }
    if (-1 < DebugLevel) {
      printk("%s:(Ret = %d_\n","SetMuraTestAlgorithmProc",bVar3);
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s: Not Supported (Ret = %d_\n","SetMuraTestAlgorithmProc",0);
    bVar3 = false;
  }
  return bVar3;
}

