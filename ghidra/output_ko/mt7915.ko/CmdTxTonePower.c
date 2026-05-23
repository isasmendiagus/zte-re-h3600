// module: mt7915.ko
// function: CmdTxTonePower @ 0x1c4e08
// size: 352 bytes
//

undefined4 CmdTxTonePower(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_70 [4];
  undefined4 local_6c;
  undefined1 local_68;
  undefined1 local_67;
  
  iVar1 = AndesAllocCmdMsg(param_1,0x58);
  if (iVar1 == 0) {
    uVar2 = 3;
    goto LAB_001c4efc;
  }
  if (2 < DebugLevel) {
    printk("%s, type:%d, dec:%d\n","CmdTxTonePower",param_2,param_3);
  }
  AndesInitCmdMsg(iVar1,0x4ed0000,0x8000f,0,0,EventExtCmdResult);
  os_zero_mem(local_70,0x58);
  local_70[0] = 1;
  iVar3 = *(int *)(param_1 + 0xa3ac20);
  if (iVar3 == 1) {
LAB_001c4ed4:
    local_68 = (undefined1)iVar3;
  }
  else {
    if (iVar3 != 0) {
      if (iVar3 != 2) {
        iVar3 = iVar3 + -1;
      }
      goto LAB_001c4ed4;
    }
    local_68 = 0;
  }
  local_67 = (undefined1)param_3;
  local_6c = param_2;
  AndesAppendCmdMsg(iVar1,local_70,0x58);
  uVar2 = AndesSendCmdMsg(param_1,iVar1);
LAB_001c4efc:
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","CmdTxTonePower",uVar2);
  }
  return uVar2;
}

