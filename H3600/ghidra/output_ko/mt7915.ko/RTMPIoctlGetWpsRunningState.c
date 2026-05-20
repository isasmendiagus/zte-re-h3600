// module: mt7915.ko
// function: RTMPIoctlGetWpsRunningState @ 0x15f9e4
// size: 308 bytes
//

void RTMPIoctlGetWpsRunningState(int *param_1,int param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined1 auStack_18 [4];
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  if (((*(int *)(*param_1 + 0x38) - 0x100U & 0xfffffeff) == 0) &&
     (uVar3 = *(uint *)(*param_1 + 0x3c) & 0xff, uVar3 < *(byte *)((int)param_1 + 0x2b7242))) {
    iVar2 = HcGetBandByWdev(param_1 + uVar3 * 0x160d + 0xadc92);
    cVar1 = *(char *)((int)&g_WPSLEDStatus + iVar2);
    if (cVar1 == '\b') {
      local_14[0] = 1;
    }
    else if (cVar1 == '\t') {
      local_14[0] = 2;
    }
    else if (cVar1 == '\n') {
      local_14[0] = 3;
    }
    else if (cVar1 == '\v') {
      local_14[0] = 4;
    }
    else if (cVar1 == '\f') {
      local_14[0] = 5;
    }
    else {
      local_14[0] = 0;
    }
    uVar3 = *(uint *)(param_2 + 0x10);
    *(undefined2 *)(param_2 + 0x14) = 4;
    uVar4 = *(uint *)(((uint)auStack_18 & 0xffffe000) + 8);
    if (uVar3 < 0xfffffffc && uVar3 + 4 <= uVar4) {
      uVar4 = 0;
    }
    if (((uVar4 != 0) || (iVar2 = __copy_to_user(uVar3,local_14), iVar2 != 0)) && (2 < DebugLevel))
    {
      printk("%s: copy_to_user() fail\n","RTMPIoctlGetWpsRunningState");
    }
  }
  return;
}

