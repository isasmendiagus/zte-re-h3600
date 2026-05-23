// module: mt7915.ko
// function: rt_private_set_wsc_string_item @ 0x6cce0
// size: 292 bytes
//

int rt_private_set_wsc_string_item
              (undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  uint local_28;
  undefined4 local_24;
  uint local_20;
  
  uVar1 = RtmpOsGetNetDevPriv();
  iVar2 = RTMP_COM_IoctlHandle(uVar1,0,0x5011,0,0,0);
  if (iVar2 == 0) {
    local_28 = (uint)*(ushort *)(param_3 + 6);
    local_20 = (uint)*(ushort *)(param_3 + 4);
    local_24 = param_4;
    uVar3 = RtmpDevPrivFlagsGet(param_1);
    iVar2 = RTMP_STA_IoctlHandle(uVar1,0,0xa026,0,&local_28,0,uVar3);
    if (iVar2 == 30000) {
      iVar2 = -0x16;
    }
    else if (iVar2 == 0x7531) {
      iVar2 = -0x5f;
    }
    else if (iVar2 == 0x7532) {
      iVar2 = -0xe;
    }
    else if (iVar2 == 0x7534) {
      iVar2 = -7;
    }
    else if (iVar2 == 0x7535) {
      iVar2 = -0xc;
    }
    else if (iVar2 == 0x7536) {
      iVar2 = -0xb;
    }
    else if (iVar2 == 0x7537) {
      iVar2 = -0x6b;
    }
  }
  else if (DebugLevel < 3) {
    iVar2 = -100;
  }
  else {
    printk("INFO::Network is down!\n");
    iVar2 = -100;
  }
  return iVar2;
}

