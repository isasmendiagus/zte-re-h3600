// module: mt7915.ko
// function: rt_private_set_wsc_u32_item @ 0x6ce04
// size: 280 bytes
//

int rt_private_set_wsc_u32_item(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 local_20;
  int local_1c;
  
  uVar1 = RtmpOsGetNetDevPriv();
  local_1c = RTMP_COM_IoctlHandle(uVar1,0,0x5011,0,0,0);
  if (local_1c == 0) {
    local_20 = param_3;
    uVar2 = RtmpDevPrivFlagsGet(param_1);
    RTMP_STA_IoctlHandle(uVar1,0,0xa025,0,&local_20,0,uVar2);
    if (local_1c == 30000) {
      local_1c = -0x16;
    }
    else if (local_1c == 0x7531) {
      local_1c = -0x5f;
    }
    else if (local_1c == 0x7532) {
      local_1c = -0xe;
    }
    else if (local_1c == 0x7534) {
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
  else if (DebugLevel < 3) {
    local_1c = -100;
  }
  else {
    printk("INFO::Network is down!\n");
    local_1c = -100;
  }
  return local_1c;
}

