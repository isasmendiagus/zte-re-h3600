// module: mt7915.ko
// function: rt_private_get_statistics @ 0x6d1bc
// size: 244 bytes
//

undefined4
rt_private_get_statistics(undefined4 param_1,undefined4 param_2,int param_3,char *param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  size_t sVar4;
  
  uVar1 = RtmpOsGetNetDevPriv();
  iVar2 = RTMP_COM_IoctlHandle(uVar1,0,0x5011,0,0,0);
  if (iVar2 == 0) {
    if (param_4 == (char *)0x0) {
      *(undefined2 *)(param_3 + 4) = 0;
      uVar1 = 0xfffffffb;
    }
    else {
      __memzero(param_4,0x7ff);
      uVar3 = RtmpDevPrivFlagsGet(param_1);
      RTMP_STA_IoctlHandle(uVar1,0,40999,0,param_4,0x7ff,uVar3);
      sVar4 = strlen(param_4);
      iVar2 = DebugLevel;
      *(short *)(param_3 + 4) = (short)sVar4 + 1;
      uVar1 = 0;
      if (2 < iVar2) {
        printk("<== rt_private_get_statistics, wrq->length = %d\n");
      }
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

