// module: mt7915.ko
// function: DetermineCallerInterface @ 0x6d318
// size: 116 bytes
//

undefined4 DetermineCallerInterface(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_14 = 0;
  local_28 = param_1;
  local_24 = RtmpOsGetNetDevWdev();
  local_20 = RtmpDevPrivFlagsGet(param_1);
  local_18 = 0;
  local_1c = param_1;
  uVar1 = RtmpDevPrivFlagsGet(param_1);
  iVar2 = RTMP_STA_IoctlHandle(param_2,0,0x22,0,&local_28,0,uVar1);
  uVar1 = 0;
  if (iVar2 != 0) {
    uVar1 = 0xfffffff2;
  }
  return uVar1;
}

