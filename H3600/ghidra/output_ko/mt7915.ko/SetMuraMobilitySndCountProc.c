// module: mt7915.ko
// function: SetMuraMobilitySndCountProc @ 0x96d3c
// size: 380 bytes
//

undefined4 SetMuraMobilitySndCountProc(int param_1,int param_2)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_24 = 0;
  uVar3 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_28 = 0;
  local_2c = 0x11;
  if (uVar3 == 0x7626 || (uVar3 == 0x7663 || uVar3 == 0x7615)) {
    if (param_2 != 0) {
      uVar1 = simple_strtol(param_2,0,10);
      iVar2 = AndesAllocCmdMsg(param_1,8);
      if (iVar2 != 0) {
        local_24 = CONCAT13(0x55,CONCAT12(0xed,(undefined2)local_24));
        local_20 = CONCAT31(local_20._1_3_,10);
        local_28 = CONCAT31(local_28._1_3_,uVar1);
        AndesInitCmdMsg(iVar2,local_24,local_20,local_1c,local_18,local_14);
        AndesAppendCmdMsg(iVar2,&local_2c,4);
        AndesAppendCmdMsg(iVar2,&local_28,4);
        AndesSendCmdMsg(param_1,iVar2);
        return 1;
      }
      if (3 < DebugLevel) {
        printk("%s:(Ret = %d_\n","SetMuraMobilitySndCountProc",0);
      }
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s: Not Supported (Ret = %d_\n","SetMuraMobilitySndCountProc",0);
  }
  return 0;
}

