// module: mt7915.ko
// function: set_muru_data @ 0x178688
// size: 444 bytes
//

void set_muru_data(undefined4 param_1,int param_2)

{
  char cVar1;
  int iVar2;
  char cVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  cVar3 = '\0';
  local_2c = 0;
  local_38 = 0x15;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  if (param_2 != 0) {
    cVar1 = delimitcnt(param_2,&_LC251);
    if ((byte)(cVar1 + 1U) < 3) {
      iVar2 = rstrtok(param_2,&_LC251);
      if (iVar2 == 0) {
        uVar4 = 0;
        uVar5 = 0;
      }
      else {
        uVar5 = 0;
        uVar4 = 0;
        do {
          if (cVar3 == '\0') {
            uVar4 = os_str_tol(iVar2,0,0x10);
          }
          else if (cVar3 == '\x01') {
            uVar5 = os_str_tol(iVar2,0,0x10);
          }
          cVar3 = cVar3 + '\x01';
          iVar2 = rstrtok(0,&_LC251);
        } while (iVar2 != 0);
      }
      if (-1 < DebugLevel) {
        printk("Address = 0x%08X Value = %d\n",uVar4,uVar5);
      }
      os_zero_mem(&local_34,8);
      local_34 = uVar4;
      local_30 = uVar5;
      iVar2 = AndesAllocCmdMsg(param_1,0xc);
      if (iVar2 != 0) {
        local_2c = CONCAT13(0x9f,CONCAT12(0xed,(undefined2)local_2c));
        local_28 = CONCAT31(local_28._1_3_,10);
        AndesInitCmdMsg(iVar2,local_2c,local_28,local_24,local_20,local_1c);
        AndesAppendCmdMsg(iVar2,&local_38,4);
        AndesAppendCmdMsg(iVar2,&local_34,8);
        AndesSendCmdMsg(param_1,iVar2);
        return;
      }
    }
    else if (-1 < DebugLevel) {
      printk("Num of Input Parameters Wrong\n");
    }
  }
  return;
}

