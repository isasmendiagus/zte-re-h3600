// module: mt7915.ko
// function: rt_ioctl_giwessid @ 0x6e82c
// size: 320 bytes
//

int rt_ioctl_giwessid(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 auStack_28 [4];
  undefined2 local_24;
  undefined4 local_20;
  int local_1c;
  
  iVar1 = RtmpOsGetNetDevPriv();
  if (iVar1 != 0) {
    local_1c = RTMP_COM_IoctlHandle(iVar1,0,0x5011,0,0,0);
    if (local_1c == 0) {
      *(undefined2 *)(param_3 + 6) = 1;
      local_20 = param_4;
      iVar2 = DetermineCallerInterface(param_1,iVar1);
      if (iVar2 == 0) {
        uVar3 = RtmpDevPrivFlagsGet(param_1);
        RTMP_STA_IoctlHandle(iVar1,0,0xa010,0,auStack_28,0,uVar3);
        *(undefined2 *)(param_3 + 4) = local_24;
        if (local_1c == 30000) {
          return -0x16;
        }
        if (local_1c == 0x7531) {
          return -0x5f;
        }
        if (local_1c != 0x7532) {
          if (local_1c == 0x7534) {
            return -7;
          }
          if (local_1c == 0x7535) {
            return -0xc;
          }
          if (local_1c == 0x7536) {
            return -0xb;
          }
          if (local_1c != 0x7537) {
            return local_1c;
          }
          return -0x6b;
        }
      }
      return -0xe;
    }
    if (2 < DebugLevel) {
      printk("INFO::Network is down!\n");
    }
  }
  return -100;
}

