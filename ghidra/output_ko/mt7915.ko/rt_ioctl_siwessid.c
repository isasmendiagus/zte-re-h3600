// module: mt7915.ko
// function: rt_ioctl_siwessid @ 0x6e6cc
// size: 352 bytes
//

int rt_ioctl_siwessid(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_28 [4];
  uint local_24;
  undefined4 local_20;
  int local_1c;
  
  uVar1 = RtmpOsGetNetDevPriv();
  iVar2 = RTMP_COM_IoctlHandle(uVar1,0,0x5011,0,0,0);
  if (iVar2 != 0) {
    if (2 < DebugLevel) {
      printk("INFO::Network is down!\n");
      return -100;
    }
    return -100;
  }
  local_24 = (uint)*(ushort *)(param_3 + 4);
  if ((*(short *)(param_3 + 6) == 0) || (local_24 < 0x22)) {
    local_28[0] = (undefined1)*(short *)(param_3 + 6);
    local_1c = 0;
    local_20 = param_4;
    iVar2 = DetermineCallerInterface(param_1,uVar1);
    if (iVar2 != 0) {
      return -0xe;
    }
    uVar3 = RtmpDevPrivFlagsGet(param_1);
    RTMP_STA_IoctlHandle(uVar1,0,0xa00f,0,local_28,0,uVar3);
    if (local_1c == 30000) {
      return -0x16;
    }
    if (local_1c == 0x7531) {
      return -0x5f;
    }
    if (local_1c == 0x7532) {
      return -0xe;
    }
    if (local_1c != 0x7534) {
      if (local_1c == 0x7535) {
        return -0xc;
      }
      if (local_1c != 0x7536) {
        if (local_1c != 0x7537) {
          return local_1c;
        }
        return -0x6b;
      }
      return -0xb;
    }
  }
  return -7;
}

