// module: mt7915.ko
// function: rt_ioctl_siwnickn @ 0x6e96c
// size: 224 bytes
//

undefined4 rt_ioctl_siwnickn(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  undefined2 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  
  uVar2 = RtmpOsGetNetDevPriv();
  iVar3 = RTMP_COM_IoctlHandle(uVar2,0,0x5011,0,0,0);
  if (iVar3 == 0) {
    if (*(ushort *)(param_3 + 4) < 0x21) {
      iVar3 = DetermineCallerInterface(param_1,uVar2);
      if (iVar3 == 0) {
        uVar1 = *(undefined2 *)(param_3 + 4);
        uVar4 = RtmpDevPrivFlagsGet(param_1);
        RTMP_STA_IoctlHandle(uVar2,0,0xa011,0,param_4,uVar1,uVar4);
        return 0;
      }
      uVar2 = 0xfffffff2;
    }
    else {
      uVar2 = 0xffffffea;
    }
  }
  else if (DebugLevel < 3) {
    uVar2 = 0xffffff9c;
  }
  else {
    uVar2 = 0xffffff9c;
    printk("INFO::Network is down!\n");
  }
  return uVar2;
}

