// module: mt7915.ko
// function: SetMuraPeriodicSndProc @ 0x94e9c
// size: 336 bytes
//

bool SetMuraPeriodicSndProc(int param_1)

{
  int iVar1;
  uint uVar2;
  bool bVar3;
  undefined2 local_2a;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  bVar3 = false;
  uVar2 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  local_28 = 0;
  local_2a = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  if (uVar2 == 0x7626 || (uVar2 == 0x7663 || uVar2 == 0x7615)) {
    iVar1 = AndesAllocCmdMsg(param_1,6);
    bVar3 = iVar1 != 0;
    if (bVar3) {
      local_24 = CONCAT13(0x55,CONCAT12(0xed,(undefined2)local_24));
      local_20 = CONCAT31(local_20._1_3_,10);
      AndesInitCmdMsg(iVar1,local_24,local_20,local_1c,local_18,local_14);
      AndesAppendCmdMsg(iVar1,&local_28,4);
      AndesAppendCmdMsg(iVar1,&local_2a,2);
      AndesSendCmdMsg(param_1,iVar1);
    }
    if (3 < DebugLevel) {
      printk("%s:(Ret = %d_\n","SetMuraPeriodicSndProc",bVar3);
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s: Not Supported (Ret = %d_\n","SetMuraPeriodicSndProc",0);
    bVar3 = false;
  }
  return bVar3;
}

