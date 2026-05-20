// module: mt7915.ko
// function: rt_ioctl_giwauth @ 0x6c680
// size: 352 bytes
//

undefined4 rt_ioctl_giwauth(undefined4 param_1,undefined4 param_2,int *param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  ushort uVar3;
  int iVar4;
  undefined4 local_20;
  int local_1c;
  
  uVar1 = RtmpOsGetNetDevPriv();
  local_1c = RTMP_COM_IoctlHandle(uVar1,0,0x5011,0,0,0);
  if (local_1c == 0) {
    uVar3 = *(ushort *)((int)param_3 + 6) & 0xfff;
    if (uVar3 == 6) {
      local_20 = 0x80;
    }
    else if (uVar3 == 7) {
      local_20 = 0x90;
    }
    else {
      if (uVar3 != 5) {
        return 0xffffffa1;
      }
      local_20 = 0x70;
    }
    uVar2 = RtmpDevPrivFlagsGet(param_1);
    RTMP_STA_IoctlHandle(uVar1,0,0xa01b,0,&local_20,0,uVar2);
    uVar3 = *(ushort *)((int)param_3 + 6) & 0xfff;
    if (uVar3 == 6) {
      if (local_1c == 0) {
        iVar4 = 2;
      }
      else {
        iVar4 = 1;
      }
      *param_3 = iVar4;
    }
    else if ((uVar3 == 7) || (uVar3 == 5)) {
      *param_3 = local_1c;
    }
    uVar1 = 0;
    if (2 < DebugLevel) {
      printk("rt_ioctl_giwauth::param->value = %d!\n",*param_3);
    }
  }
  else if (DebugLevel < 3) {
    uVar1 = 0xffffff9c;
  }
  else {
    uVar1 = 0xffffff9c;
    printk("INFO::Network is down!\n");
  }
  return uVar1;
}

