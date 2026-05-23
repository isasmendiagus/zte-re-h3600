// module: mt7915.ko
// function: ZeroWaitDfsCmdHandler @ 0x237af4
// size: 580 bytes
//

undefined4 ZeroWaitDfsCmdHandler(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint local_118 [3];
  undefined1 local_10c;
  byte local_10b;
  undefined2 local_10a;
  ushort local_108;
  
  if (param_2 == 0) {
    return 1;
  }
  uVar2 = (uint)*(ushort *)(param_2 + 0x14);
  uVar3 = *(uint *)(((uint)local_118 & 0xffffe000) + 8);
  if (!CARRY4(*(uint *)(param_2 + 0x10),uVar2) && *(uint *)(param_2 + 0x10) + uVar2 <= uVar3) {
    uVar3 = 0;
  }
  if (uVar3 == 0) {
    iVar1 = __copy_from_user(&local_10c);
    if (iVar1 != 0) {
      return 0xfffffff2;
    }
  }
  else if (uVar2 != 0) {
    __memzero(&local_10c,uVar2);
    return 0xfffffff2;
  }
  switch(local_10c) {
  case 1:
    FUN_002371f0(param_1,&local_10c);
    return 0;
  case 2:
    uVar2 = (uint)local_10b;
    uVar3 = (uint)local_10a._1_1_;
    if (0 < DebugLevel) {
      local_118[0] = uVar3;
      printk(&_LC146,"ZeroWaitDfsMonitorChUpdate",uVar2,(undefined1)local_10a);
    }
    if (uVar2 < 2) {
      local_118[0] = uVar2;
      DfsDedicatedInBandSetChannel(param_1,(undefined1)local_10a,uVar3,(undefined1)local_108);
      return 0;
    }
    if (uVar2 == 2) {
      DfsDedicatedOutBandSetChannel(param_1,(undefined1)local_10a,uVar3,2);
      return 0;
    }
    break;
  case 3:
    if (0 < DebugLevel) {
      local_118[0] = (uint)local_108;
      printk(&_LC179,"ZeroWaitDfsSetNopToChList",local_10b,(undefined1)local_10a);
    }
    ZeroWait_DFS_set_NOP_to_Channel_List(param_1,local_10b,(undefined1)local_10a,(uint)local_108);
    return 0;
  case 4:
    if (0 < DebugLevel) {
      printk(&_LC180,"ZeroWaitDfsPreAssignNextTarget",4,local_10b);
    }
    *(byte *)(param_1 + 0x7953f2) = local_10b;
    *(undefined1 *)(param_1 + 0x7953f1) = 4;
    *(undefined2 *)(param_1 + 0x7953f4) = local_10a;
    return 0;
  case 5:
    if ((0 < DebugLevel) && (printk(&_LC181,"ZeroWaitShowTargetInfo",5), 0 < DebugLevel)) {
      FUN_0022fc0c(param_1);
      return 0;
    }
  }
  return 0;
}

