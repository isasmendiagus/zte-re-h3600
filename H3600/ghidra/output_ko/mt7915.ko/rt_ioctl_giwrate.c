// module: mt7915.ko
// function: rt_ioctl_giwrate @ 0x6cc28
// size: 184 bytes
//

undefined4 rt_ioctl_giwrate(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_1c [2];
  
  uVar1 = RtmpOsGetNetDevPriv();
  iVar2 = RTMP_COM_IoctlHandle(uVar1,0,0x5011,0,0,0);
  if (iVar2 != 0) {
    if (2 < DebugLevel) {
      printk("INFO::Network is down!\n");
    }
    return 0xffffff9c;
  }
  uVar3 = RtmpDevPrivFlagsGet(param_1);
  RTMP_STA_IoctlHandle(uVar1,0,0xa022,0,local_1c,0,uVar3);
  *(undefined1 *)((int)param_3 + 5) = 0;
  *param_3 = local_1c[0];
  return 0;
}

