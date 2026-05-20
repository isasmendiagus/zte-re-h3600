// module: mt7915.ko
// function: rt_ioctl_siwencode @ 0x6eecc
// size: 420 bytes
//

int rt_ioctl_siwencode(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  ushort uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  bool bVar5;
  undefined4 local_34;
  undefined2 local_30;
  int local_2c;
  ushort local_1e;
  int local_1c;
  
  uVar2 = RtmpOsGetNetDevPriv();
  iVar3 = RTMP_COM_IoctlHandle(uVar2,0,0x5011,0,0,0);
  if (iVar3 == 0) {
    uVar1 = *(ushort *)(param_3 + 6);
    local_30 = *(undefined2 *)(param_3 + 4);
    bVar5 = (uVar1 & 0x8000) == 0;
    if (bVar5) {
      local_1e = 0;
    }
    local_2c = (uVar1 & 0xff) - 1;
    if (!bVar5) {
      local_1e = 1;
    }
    if ((uVar1 & 0x4000) != 0) {
      local_1e = local_1e | 4;
    }
    if ((uVar1 & 0x2000) != 0) {
      local_1e = local_1e | 8;
    }
    if ((uVar1 & 0x800) != 0) {
      local_1e = local_1e | 0x10;
    }
    if ((uVar1 & 0xf000) != 0) {
      local_1e = local_1e | 0x20;
    }
    local_1c = 0;
    local_34 = param_4;
    iVar3 = DetermineCallerInterface(param_1,uVar2);
    if (iVar3 != 0) {
      return -0xe;
    }
    uVar4 = RtmpDevPrivFlagsGet(param_1);
    RTMP_STA_IoctlHandle(uVar2,0,0xa017,0,&local_34,0,uVar4);
    if (local_1c == 30000) {
      local_1c = -0x16;
    }
    else if (local_1c == 0x7531) {
      local_1c = -0x5f;
    }
    else {
      if (local_1c == 0x7532) {
        return -0xe;
      }
      if (local_1c == 0x7534) {
        local_1c = -7;
      }
      else if (local_1c == 0x7535) {
        local_1c = -0xc;
      }
      else if (local_1c == 0x7536) {
        local_1c = -0xb;
      }
      else if (local_1c == 0x7537) {
        local_1c = -0x6b;
      }
    }
  }
  else if (DebugLevel < 3) {
    local_1c = -100;
  }
  else {
    printk("INFO::Network is down!\n");
    local_1c = -100;
  }
  return local_1c;
}

