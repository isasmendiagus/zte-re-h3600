// module: mt7915.ko
// function: WscTimeOutProcess @ 0x1e9e38
// size: 924 bytes
//

void WscTimeOutProcess(int param_1,int *param_2,int param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  int iVar2;
  char cVar3;
  byte local_29 [5];
  
  cVar3 = *(char *)(param_1 + 0x286285);
  if (cVar3 == '\x01') {
    iVar2 = 0;
  }
  else if (cVar3 == '\0') {
    iVar2 = 2;
  }
  else {
    iVar2 = 0xff;
  }
  if (param_3 == 0x19) {
    param_4[4] = 4;
  }
  else if (param_3 == 10) {
    param_4[4] = 0;
  }
  else {
    if (param_3 == 0x10) {
      param_4[4] = 3;
      if (param_2 != (int *)0x0 && iVar2 == 0) {
        iVar2 = *param_2;
        if (iVar2 == 0x20001) {
          WscSendEapFail(param_1,param_4,1);
          iVar2 = *param_2;
        }
        if (iVar2 == 2) {
          WscApCliLinkDown(param_1,param_4);
        }
        *(undefined1 *)(param_4 + 0x9f2) = 0;
        *(undefined1 *)((int)param_4 + 0x1c53) = 0;
        return;
      }
      *(undefined1 *)(param_4 + 0x9f2) = 0;
      *(undefined1 *)((int)param_4 + 0x1c53) = 0;
      if (iVar2 != 2) {
        return;
      }
      FUN_001e0304(param_1,param_4[0xa7b]);
      return;
    }
    if (param_3 == 0x1a) {
      param_4[4] = 0;
      *param_4 = 0;
      param_4[3] = 0x22;
      complete(param_4 + 0xb18);
    }
    else {
      if (param_4[0xa88] == 2 && cVar3 == '\x01') {
        uVar1 = 0;
      }
      else {
        uVar1 = 3;
      }
      param_4[4] = uVar1;
      if (param_3 == 0x17) {
        *(undefined1 *)(param_4 + 0xa79) = 0;
      }
    }
  }
  *(undefined1 *)((int)param_4 + 0x1c53) = 0;
  __memzero((int)param_4 + 0x1c55,6);
  *(undefined1 *)(param_4 + 0x9f2) = 0;
  if (param_4[1] == 1) {
    uVar1 = 0;
  }
  else {
    uVar1 = 4;
  }
  if (iVar2 == 0) {
    cVar3 = *(char *)(param_4 + 2);
    if ((cVar3 == '\x01') && (param_3 - 0x18U < 2)) {
      *(undefined1 *)(param_4 + 0xa79) = 0;
      *(undefined1 *)(param_4 + 2) = 2;
      WscBuildBeaconIE(param_1,2,0,uVar1,*(undefined2 *)((int)param_4 + 10),
                       *(byte *)(param_4 + 0x715) & 0xf,0,0,0);
      WscBuildProbeRespIE(param_1,3,*(undefined1 *)(param_4 + 2),0,uVar1,
                          *(undefined2 *)((int)param_4 + 10),*(undefined1 *)(param_4 + 0x715),0,0,0)
      ;
      *(undefined1 *)(param_1 + 0x794b18) = *(undefined1 *)(param_4 + 0x715);
      WscWriteConfToPortCfg(param_1,param_4,param_4 + 0x726,0);
      local_29[0] = *(byte *)(param_4 + 0x715) & 0xf;
      RTEnqueueInternalCmd(param_1,5,local_29,1);
      RtmpOsTaskWakeUp(param_1 + 0x794ae8);
    }
    else {
      if ((param_2 != (int *)0x0) && (*param_2 == 0x20001)) {
        *(undefined1 *)(param_2 + 0x349) = 0;
        WscSendEapFail(param_1,param_4,1);
        cVar3 = *(char *)(param_4 + 2);
      }
      WscBuildBeaconIE(param_1,cVar3,0,uVar1,*(undefined2 *)((int)param_4 + 10),
                       *(byte *)(param_4 + 0x715) & 0xf,0,0,0);
      WscBuildProbeRespIE(param_1,3,*(undefined1 *)(param_4 + 2),0,uVar1,
                          *(undefined2 *)((int)param_4 + 10),*(undefined1 *)(param_4 + 0x715),0,0,0)
      ;
    }
    if ((param_2 != (int *)0x0) && (*param_2 == 2)) {
      WscApCliLinkDown(param_1,param_4);
    }
  }
  else if (iVar2 == 2) {
    FUN_001e0304(param_1,param_4[0xa7b]);
  }
  if (2 < DebugLevel) {
    printk("WscTimeOutProcess\n");
  }
  return;
}

