// module: mt7915.ko
// function: GetMuraPFIDStatProc @ 0x95568
// size: 544 bytes
//

undefined4 GetMuraPFIDStatProc(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 *local_4c;
  code *local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  uVar2 = 0;
  uVar3 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  local_60 = 0;
  local_58 = 0;
  local_54 = 0;
  local_50 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_5c = 10;
  if (uVar3 == 0x7626 || (uVar3 == 0x7663 || uVar3 == 0x7615)) {
    if (param_2 == 0) {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("%s: Argument is NULL\n","GetMuraPFIDStatProc");
      uVar2 = 0;
    }
    else {
      local_60 = simple_strtol(param_2);
      iVar1 = AndesAllocCmdMsg(param_1,0x3c);
      if (iVar1 == 0) {
        if (DebugLevel < 0) {
          return 0;
        }
        printk("%s: Msg allocation failed\n","GetMuraPFIDStatProc");
        uVar2 = 0;
      }
      else {
        local_4c = &local_44;
        local_48 = MuraEventDispatcher;
        local_58 = CONCAT13(0x55,CONCAT12(0xed,(undefined2)local_58));
        local_54 = CONCAT31(local_54._1_3_,5);
        uVar2 = 1;
        local_54 = CONCAT22(0x34,(undefined2)local_54);
        AndesInitCmdMsg(iVar1,local_58,local_54,local_50,local_4c,MuraEventDispatcher);
        AndesAppendCmdMsg(iVar1,&local_5c,4);
        AndesAppendCmdMsg(iVar1,&local_60,4);
        AndesSendCmdMsg(param_1,iVar1);
      }
    }
    if (3 < DebugLevel) {
      printk("%s:(Ret = %d\n","GetMuraPFIDStatProc",uVar2);
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s: Not Supported (Ret = %d_\n","GetMuraPFIDStatProc",0);
    uVar2 = 0;
  }
  return uVar2;
}

