// module: mt7915.ko
// function: rt_ioctl_giwencodeext @ 0x6cfb8
// size: 516 bytes
//

int rt_ioctl_giwencodeext(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  bool bVar4;
  void *local_3c;
  ushort local_38;
  uint local_34;
  int local_30;
  int local_2c;
  ushort local_26;
  int local_24;
  
  uVar1 = RtmpOsGetNetDevPriv();
  if (2 < DebugLevel) {
    printk("===> rt_ioctl_giwencodeext\n");
  }
  iVar2 = RTMP_COM_IoctlHandle(uVar1,0,0x5011,0,0,0);
  if (iVar2 != 0) {
    if (2 < DebugLevel) {
      printk("INFO::Network is down!\n");
      return -100;
    }
    return -100;
  }
  iVar2 = *(ushort *)(param_3 + 4) - 0x28;
  if (-1 < iVar2) {
    __memzero(param_4,0x28);
    __memzero(&local_3c,0x1c);
    local_34 = (uint)*(byte *)(param_3 + 6);
    local_30 = iVar2;
    uVar3 = RtmpDevPrivFlagsGet(param_1);
    iVar2 = RTMP_STA_IoctlHandle(uVar1,0,0xa01d,0,&local_3c,0,uVar3);
    if (iVar2 == 0) {
      *(short *)(param_3 + 6) = (short)local_34;
      *(ushort *)(param_4 + 0x26) = local_38;
      if (local_2c == 1) {
        *(undefined2 *)(param_4 + 0x24) = 0;
      }
      else if (local_2c == 2) {
        *(undefined2 *)(param_4 + 0x24) = 1;
      }
      else if (local_2c == 3) {
        *(undefined2 *)(param_4 + 0x24) = 2;
      }
      else if (local_2c == 4) {
        *(undefined2 *)(param_4 + 0x24) = 3;
      }
      bVar4 = (local_26 & 1) != 0;
      if (bVar4) {
        local_26 = *(ushort *)(param_3 + 6);
      }
      if (bVar4) {
        *(ushort *)(param_3 + 6) = ~((ushort)~(ushort)(((uint)local_26 << 0x11) >> 0x10) >> 1);
        local_38 = *(ushort *)(param_4 + 0x26);
      }
      if (local_38 == 0) {
        return 0;
      }
      if (local_3c == (void *)0x0) {
        return 0;
      }
      memcpy((void *)(param_4 + 0x28),local_3c,(uint)local_38);
      return 0;
    }
    *(undefined2 *)(param_4 + 0x26) = 0;
    if (local_24 != 30000) {
      if (local_24 == 0x7531) {
        return -0x5f;
      }
      if (local_24 == 0x7532) {
        return -0xe;
      }
      if (local_24 == 0x7534) {
        return -7;
      }
      if (local_24 != 0x7535) {
        if (local_24 == 0x7536) {
          return -0xb;
        }
        if (local_24 != 0x7537) {
          return local_24;
        }
        return -0x6b;
      }
      return -0xc;
    }
  }
  return -0x16;
}

