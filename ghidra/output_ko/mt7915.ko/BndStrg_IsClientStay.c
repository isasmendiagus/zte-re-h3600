// module: mt7915.ko
// function: BndStrg_IsClientStay @ 0x9d8f0
// size: 804 bytes
//

undefined4 BndStrg_IsClientStay(undefined4 param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  uint uVar4;
  undefined1 local_68 [2];
  undefined1 local_66;
  undefined1 local_64;
  undefined1 local_61;
  undefined4 local_5c;
  undefined2 local_58;
  
  iVar1 = RTMPAvgRssi(param_1,param_3 + 0x108);
  if (*(char *)((int)param_2 + 0x106e) == '\x02') {
    uVar4 = 0;
    piVar2 = (int *)(param_3 + 5000);
    do {
      piVar2 = piVar2 + 1;
      uVar4 = uVar4 + *piVar2;
    } while (piVar2 != (int *)(param_3 + 0x13a8));
    uVar4 = uVar4 >> 3;
    if ((param_2[4] & 0x100) == 0) {
      return 1;
    }
  }
  else {
    if (((uint)(*(char *)((int)param_2 + 0x106e) == '\x01') & (uint)param_2[4] >> 3) == 0) {
      return 1;
    }
    if (2 < DebugLevel) {
      printk("\n 5G IsClientStay %02x:%02x:%02x:%02x:%02x:%02x Rssi=%d, RssiLow=%d RssiLowCnt=%d\n",
             *(undefined1 *)(param_3 + 0xec),*(undefined1 *)(param_3 + 0xed),
             *(undefined1 *)(param_3 + 0xee),*(undefined1 *)(param_3 + 0xef),
             *(undefined1 *)(param_3 + 0xf0),*(undefined1 *)(param_3 + 0xf1),iVar1,
             (int)*(char *)((int)param_2 + 0x1023),*(undefined4 *)(param_3 + 300));
    }
    if (iVar1 < *(char *)((int)param_2 + 0x1023)) {
      uVar4 = *(int *)(param_3 + 300) + 1;
      *(uint *)(param_3 + 300) = uVar4;
      if ((uint)param_2[0x422] <= uVar4) {
        *(undefined4 *)(param_3 + 300) = 0;
        local_5c = *(undefined4 *)(param_3 + 0xec);
        local_64 = *(undefined1 *)((int)param_2 + 0x106e);
        local_58 = *(undefined2 *)(param_3 + 0xf0);
        local_61 = (undefined1)iVar1;
        local_68[0] = 0x22;
        RtmpOSWrielessEventSend(*param_2,1,0x950,0,local_68,0x40);
        if (DebugLevel < 3) {
          return 0;
        }
        printk("\n %02x:%02x:%02x:%02x:%02x:%02x kick out bandsteering DetectInterval=%d\n",
               *(undefined1 *)(param_3 + 0xec),*(undefined1 *)(param_3 + 0xed),
               *(undefined1 *)(param_3 + 0xee),*(undefined1 *)(param_3 + 0xef),
               *(undefined1 *)(param_3 + 0xf0),*(undefined1 *)(param_3 + 0xf1),param_2[0x422]);
        return 0;
      }
    }
    else {
      *(undefined4 *)(param_3 + 300) = 0;
    }
    if ((param_2[4] & 0x100) == 0) {
      return 1;
    }
    if (*(char *)((int)param_2 + 0x106e) != '\x02') {
      return 1;
    }
    uVar4 = 0;
  }
  if (2 < DebugLevel) {
    printk("\n 2GIsClientStay %02x:%02x:%02x:%02x:%02x:%02x Rssi=%d, RssiHigh=%d RssiHighCnt=%d ulAveTxRxkbps=%d\n"
           ,*(undefined1 *)(param_3 + 0xec),*(undefined1 *)(param_3 + 0xed),
           *(undefined1 *)(param_3 + 0xee),*(undefined1 *)(param_3 + 0xef),
           *(undefined1 *)(param_3 + 0xf0),*(undefined1 *)(param_3 + 0xf1),iVar1,
           (int)*(char *)(param_2 + 0x409),*(undefined4 *)(param_3 + 0x130),uVar4);
  }
  if (*(char *)(param_2 + 0x409) < iVar1) {
    uVar3 = *(int *)(param_3 + 0x130) + 1;
    *(uint *)(param_3 + 0x130) = uVar3;
    if (((uint)param_2[0x422] <= uVar3) && (uVar4 < (uint)param_2[0x424] || param_2[0x424] == 0)) {
      *(undefined4 *)(param_3 + 0x130) = 0;
      local_5c = *(undefined4 *)(param_3 + 0xec);
      local_58 = *(undefined2 *)(param_3 + 0xf0);
      local_68[0] = 0x1c;
      local_66 = 0x80;
      RtmpOSWrielessEventSend(*param_2,1,0x950,0,local_68,0x40);
      if (2 < DebugLevel) {
        printk("\n%02x:%02x:%02x:%02x:%02x:%02x send CHECK_IF_TO_5G to bandsteering DetectInterval=%d ulAveTxRxkbps=%d\n"
               ,*(undefined1 *)(param_3 + 0xec),*(undefined1 *)(param_3 + 0xed),
               *(undefined1 *)(param_3 + 0xee),*(undefined1 *)(param_3 + 0xef),
               *(undefined1 *)(param_3 + 0xf0),*(undefined1 *)(param_3 + 0xf1),param_2[0x422],uVar4)
        ;
      }
    }
    return 1;
  }
  *(undefined4 *)(param_3 + 0x130) = 0;
  return 1;
}

