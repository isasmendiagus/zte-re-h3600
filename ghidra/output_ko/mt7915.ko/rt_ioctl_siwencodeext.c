// module: mt7915.ko
// function: rt_ioctl_siwencodeext @ 0x6c7e0
// size: 384 bytes
//

undefined4 rt_ioctl_siwencodeext(undefined4 param_1,undefined4 param_2,int param_3,uint *param_4)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  uint *local_34;
  undefined2 local_30;
  int local_2c;
  undefined4 local_24;
  ushort local_20;
  ushort local_1e;
  
  sVar1 = (short)param_4[9];
  uVar2 = RtmpOsGetNetDevPriv();
  iVar3 = RTMP_COM_IoctlHandle(uVar2,0,0x5011,0,0,0);
  if (iVar3 != 0) {
    if (2 < DebugLevel) {
      printk("INFO::Network is down!\n");
    }
    return 0xffffff9c;
  }
  local_30 = *(undefined2 *)((int)param_4 + 0x26);
  local_34 = param_4 + 10;
  local_2c = (*(ushort *)(param_3 + 6) & 0xff) - 1;
  if (sVar1 == 0) {
    local_24 = 1;
  }
  else if (sVar1 == 1) {
    local_24 = 2;
  }
  else if (sVar1 == 2) {
    local_24 = 3;
  }
  else {
    if (sVar1 != 3) {
      if (DebugLevel < 2) {
        return 0xffffffa1;
      }
      printk("Warning: Security type is not supported. (alg = %d)\n",sVar1);
      return 0xffffffa1;
    }
    local_24 = 4;
  }
  local_20 = (ushort)((*param_4 & 8) != 0);
  if ((*param_4 & 4) != 0) {
    local_20 = local_20 | 2;
  }
  local_1e = (ushort)((*(ushort *)(param_3 + 6) & 0x8000) != 0);
  uVar4 = RtmpDevPrivFlagsGet(param_1);
  iVar3 = RTMP_STA_IoctlHandle(uVar2,0,0xa01c,0,&local_34,0,uVar4);
  uVar2 = 0;
  if (iVar3 != 0) {
    uVar2 = 0xffffffea;
  }
  return uVar2;
}

