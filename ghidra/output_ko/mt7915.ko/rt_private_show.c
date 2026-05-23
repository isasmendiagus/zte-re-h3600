// module: mt7915.ko
// function: rt_private_show @ 0x6f29c
// size: 204 bytes
//

undefined4 rt_private_show(undefined4 param_1,undefined4 param_2,undefined4 *param_3,int param_4)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int local_44 [3];
  undefined1 auStack_38 [16];
  undefined4 local_28;
  undefined2 local_24;
  
  uVar1 = *(undefined2 *)((int)param_3 + 6);
  iVar2 = RtmpOsGetNetDevPriv();
  if (iVar2 == 0) {
    uVar4 = 0xffffff9c;
  }
  else {
    iVar3 = DetermineCallerInterface(param_1,iVar2);
    if (iVar3 == 0) {
      if (param_4 == 0) {
        *(undefined2 *)(param_3 + 1) = 0;
        uVar4 = 0xfffffffb;
      }
      else {
        __memzero(param_4,0x7ff);
        local_28 = *param_3;
        local_24 = *(undefined2 *)(param_3 + 1);
        local_44[1] = 0x7ff;
        local_44[0] = param_4;
        local_44[2] = RtmpDevPrivFlagsGet(param_1);
        uVar4 = RtmpDevPrivFlagsGet(param_1);
        RTMP_STA_IoctlHandle(iVar2,auStack_38,0xf,uVar1,local_44,0,uVar4);
        *(undefined2 *)(param_3 + 1) = local_24;
        uVar4 = 0;
      }
    }
    else {
      uVar4 = 0xfffffff2;
    }
  }
  return uVar4;
}

