// module: mt7915.ko
// function: rt_ioctl_siwauth @ 0x6c304
// size: 844 bytes
//

undefined4 rt_ioctl_siwauth(undefined4 param_1,undefined4 param_2,uint *param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_20;
  uint local_1c;
  
  uVar1 = RtmpOsGetNetDevPriv();
  iVar2 = RTMP_COM_IoctlHandle(uVar1,0,0x5011,0,0,0);
  if (iVar2 == 0) {
    local_1c = *param_3;
    switch(*(ushort *)((int)param_3 + 6) & 0xfff) {
    case 0:
      local_20 = 0x10;
      if (local_1c == 2) {
        local_1c = 0x11;
      }
      else if (local_1c == 4) {
        local_1c = 0x12;
      }
      if (2 < DebugLevel) {
        printk("%s::IW_AUTH_WPA_VERSION - param->value = %d!\n","rt_ioctl_siwauth");
      }
      break;
    case 1:
      local_20 = 0x20;
      if (local_1c == 1) {
        local_1c = 0x21;
      }
      else if (local_1c == 2) {
        local_1c = 0x22;
      }
      else if (local_1c == 0x10) {
        local_1c = 0x23;
      }
      else if (local_1c == 4) {
        local_1c = 0x24;
      }
      else if (local_1c == 8) {
        local_1c = 0x25;
      }
      if (2 < DebugLevel) {
        printk("%s::IW_AUTH_CIPHER_PAIRWISE - param->value = %d!\n","rt_ioctl_siwauth");
      }
      break;
    case 2:
      local_20 = 0x30;
      if (local_1c == 1) {
        local_1c = 0x31;
      }
      else if (local_1c == 2) {
        local_1c = 0x32;
      }
      else if (local_1c == 0x10) {
        local_1c = 0x33;
      }
      else if (local_1c == 4) {
        local_1c = 0x34;
      }
      else if (local_1c == 8) {
        local_1c = 0x35;
      }
      if (2 < DebugLevel) {
        printk("%s::IW_AUTH_CIPHER_GROUP - param->value = %d!\n","rt_ioctl_siwauth");
      }
      break;
    case 3:
      local_20 = 0x40;
      if (local_1c == 1) {
        local_1c = 0x41;
      }
      if (2 < DebugLevel) {
        printk("%s::IW_AUTH_KEY_MGMT - param->value = %d!\n","rt_ioctl_siwauth");
      }
      break;
    default:
      return 0xffffffa1;
    case 5:
      local_20 = 0x70;
      if (2 < DebugLevel) {
        printk("%s::IW_AUTH_DROP_UNENCRYPTED - param->value = %d!\n","rt_ioctl_siwauth");
      }
      break;
    case 6:
      local_20 = 0x80;
      if ((local_1c & 2) == 0) {
        if ((local_1c & 1) == 0) {
          if ((local_1c & 4) != 0) {
            local_1c = 0x83;
          }
        }
        else {
          local_1c = 0x82;
        }
      }
      else {
        local_1c = 0x81;
      }
      if (2 < DebugLevel) {
        printk("%s::IW_AUTH_80211_AUTH_ALG - param->value = %d!\n","rt_ioctl_siwauth");
      }
      break;
    case 7:
      local_20 = 0x90;
      if (2 < DebugLevel) {
        printk("%s::IW_AUTH_WPA_ENABLED - Driver supports WPA!(param->value = %d)\n",
               "rt_ioctl_siwauth");
      }
      break;
    case 8:
      local_20 = 0x50;
      break;
    case 10:
      local_20 = 0x60;
      if (2 < DebugLevel) {
        printk("%s::IW_AUTH_PRIVACY_INVOKED - param->value = %d!\n","rt_ioctl_siwauth");
      }
    }
    uVar3 = RtmpDevPrivFlagsGet(param_1);
    RTMP_STA_IoctlHandle(uVar1,0,0xa01a,0,&local_20,0,uVar3);
    return 0;
  }
  if (2 < DebugLevel) {
    printk("INFO::Network is down!\n");
  }
  return 0xffffff9c;
}

