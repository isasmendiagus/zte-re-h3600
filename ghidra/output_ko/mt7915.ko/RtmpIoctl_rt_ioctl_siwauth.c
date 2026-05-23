// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_siwauth @ 0x634a4
// size: 1376 bytes
//

undefined4
RtmpIoctl_rt_ioctl_siwauth(int *param_1,uint *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined1 uVar4;
  
  iVar1 = DebugLevel;
  uVar3 = *param_2;
  iVar2 = *(int *)(*param_1 + 0x3c);
  if (uVar3 == 0x60) {
    if (2 < DebugLevel) {
      printk("%s::IW_AUTH_PRIVACY_INVOKED - param->value = %d!\n","RtmpIoctl_rt_ioctl_siwauth",
             param_2[1],DebugLevel,param_4);
    }
  }
  else if (uVar3 < 0x61) {
    if (uVar3 == 0x20) {
      uVar3 = param_2[1];
      if (uVar3 == 0x21) {
        param_1[iVar2 * 0x84dec + 0xdb733] = param_1[iVar2 * 0x84dec + 0xdb733] | 1;
        param_1[iVar2 * 0x84dec + 0x160009] = param_1[iVar2 * 0x84dec + 0x160009] | 1;
      }
      else if (uVar3 - 0x22 < 2) {
        param_1[iVar2 * 0x84dec + 0xdb733] = param_1[iVar2 * 0x84dec + 0xdb733] | 0xe;
        param_1[iVar2 * 0x84dec + 0x160009] = param_1[iVar2 * 0x84dec + 0x160009] | 0xe;
      }
      else if (uVar3 == 0x24) {
        param_1[iVar2 * 0x84dec + 0xdb733] = param_1[iVar2 * 0x84dec + 0xdb733] | 0x10;
        param_1[iVar2 * 0x84dec + 0x160009] = param_1[iVar2 * 0x84dec + 0x160009] | 0x10;
      }
      else if (uVar3 == 0x25) {
        param_1[iVar2 * 0x84dec + 0xdb733] = param_1[iVar2 * 0x84dec + 0xdb733] | 0x20;
        param_1[iVar2 * 0x84dec + 0x160009] = param_1[iVar2 * 0x84dec + 0x160009] | 0x20;
      }
      if (2 < DebugLevel) {
        printk("%s::IW_AUTH_CIPHER_PAIRWISE - param->value = %d!\n","RtmpIoctl_rt_ioctl_siwauth",
               param_2[1],DebugLevel,param_4);
      }
    }
    else if (uVar3 < 0x21) {
      if (uVar3 == 0x10) {
        if (param_2[1] == 0x11) {
          if ((char)param_1[iVar2 * 0x84dec + 0xdc6ee] == '\0') {
            uVar3 = param_1[iVar2 * 0x84dec + 0xdb6e1] | 0x20;
          }
          else {
            uVar3 = param_1[iVar2 * 0x84dec + 0xdb6e1] | 0x10;
          }
          param_1[iVar2 * 0x84dec + 0xdb6e1] = uVar3;
        }
        else if (param_2[1] == 0x12) {
          param_1[iVar2 * 0x84dec + 0xdb6e1] = param_1[iVar2 * 0x84dec + 0xdb6e1] | 0x80;
        }
        if (2 < DebugLevel) {
          printk("%s::IW_AUTH_WPA_VERSION - param->value = %d!\n","RtmpIoctl_rt_ioctl_siwauth",
                 param_2[1],DebugLevel,param_4);
        }
      }
    }
    else if (uVar3 == 0x30) {
      uVar3 = param_2[1];
      if (uVar3 == 0x31) {
        param_1[iVar2 * 0x84dec + 0xdb76b] = param_1[iVar2 * 0x84dec + 0xdb76b] | 1;
      }
      else if (uVar3 == 0x32) {
        param_1[iVar2 * 0x84dec + 0xdb76b] = param_1[iVar2 * 0x84dec + 0xdb76b] | 2;
      }
      else if (uVar3 == 0x33) {
        param_1[iVar2 * 0x84dec + 0xdb76b] = param_1[iVar2 * 0x84dec + 0xdb76b] | 4;
      }
      else if (uVar3 == 0x34) {
        param_1[iVar2 * 0x84dec + 0xdb76b] = param_1[iVar2 * 0x84dec + 0xdb76b] | 0x10;
      }
      else if (uVar3 == 0x35) {
        param_1[iVar2 * 0x84dec + 0xdb76b] = param_1[iVar2 * 0x84dec + 0xdb76b] | 0x20;
      }
      if (2 < DebugLevel) {
        printk("%s::IW_AUTH_CIPHER_GROUP - param->value = %d!\n","RtmpIoctl_rt_ioctl_siwauth",
               param_2[1],DebugLevel,param_4);
      }
    }
    else if (uVar3 == 0x40) {
      if (param_2[1] == 0x41) {
        if ((param_1[iVar2 * 0x84dec + 0xdb6e1] & 0x10U) == 0) {
          if ((param_1[iVar2 * 0x84dec + 0xdb6e1] & 0x80U) != 0) {
            param_1[iVar2 * 0x84dec + 0xdb6e1] = 0x40;
          }
        }
        else {
          param_1[iVar2 * 0x84dec + 0xdb6e1] = 8;
        }
      }
      else if (param_2[1] == 0) {
        *(undefined1 *)(param_1 + iVar2 * 0x84dec + 0xdb8f8) = 1;
      }
      if (2 < DebugLevel) {
        printk("%s::IW_AUTH_KEY_MGMT - param->value = %d!\n","RtmpIoctl_rt_ioctl_siwauth",param_2[1]
               ,DebugLevel,param_4);
      }
    }
  }
  else if (uVar3 == 0x80) {
    uVar3 = param_1[iVar2 * 0x84dec + 0xdb6e1];
    param_1[iVar2 * 0x84dec + 0xdb6e1] = uVar3 | 4;
    if (2 < iVar1) {
      printk("%s::IW_AUTH_80211_AUTH_ALG - param->value = %d!\n","RtmpIoctl_rt_ioctl_siwauth",
             param_2[1],uVar3 | 4,param_4);
    }
  }
  else if (uVar3 < 0x81) {
    if (uVar3 == 0x70) {
      if (param_2[1] == 0) {
        uVar4 = 1;
      }
      else {
        uVar4 = 2;
      }
      *(undefined1 *)(param_1 + iVar2 * 0x84dec + 0xdb8f8) = uVar4;
      if (2 < iVar1) {
        printk("%s::IW_AUTH_DROP_UNENCRYPTED - param->value = %d!\n","RtmpIoctl_rt_ioctl_siwauth",
               param_2[1],iVar1,param_4);
      }
    }
  }
  else if (uVar3 == 0x90) {
    if (2 < DebugLevel) {
      printk("%s::IW_AUTH_WPA_ENABLED - Driver supports WPA!(param->value = %d)\n",
             "RtmpIoctl_rt_ioctl_siwauth",param_2[1],DebugLevel,param_4);
    }
  }
  else if (uVar3 == 0xa0) {
    if (param_2[1] == 1) {
      *(undefined1 *)(param_1 + iVar2 * 0x84dec + 0x1600c4) = 1;
    }
    else {
      *(undefined1 *)(param_1 + iVar2 * 0x84dec + 0x1600c4) = 0;
    }
  }
  return 0;
}

