// module: mt7915.ko
// function: RTMP_STA_IoctlHandle @ 0x66938
// size: 2100 bytes
//

uint RTMP_STA_IoctlHandle
               (int *param_1,undefined4 param_2,int param_3,uint param_4,uint *param_5,uint param_6)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  uint *puVar4;
  undefined *puVar5;
  uint *puVar6;
  int iVar7;
  bool bVar8;
  
  iVar7 = *(int *)(*param_1 + 0x3c);
  iVar1 = iVar7 * 0x2137b0;
  puVar5 = (undefined *)((int)param_1 + (int)(&DAT_0036db58 + iVar1));
  if (puVar5 == (undefined *)0x0) {
    printk(&_LC379,0x261b);
    dump_stack();
    return 0;
  }
  if (param_3 == 0xa010) {
    uVar2 = RtmpIoctl_rt_ioctl_giwessid(param_1,param_5,param_6);
    return uVar2;
  }
  if (param_3 < 0xa011) {
    if (param_3 == 0xa003) {
      StaSiteSurvey(param_1,param_5,param_6 & 0xff,puVar5);
      return 0;
    }
    if (param_3 < 0xa004) {
      if (param_3 == 0xf) {
        RTMPIoctlShow(param_1,param_2,param_4,param_5,param_6);
        return 0;
      }
      if (param_3 < 0x10) {
        if (param_3 == 0xb) {
          RTMPIoctlMAC();
          return 0;
        }
        if (param_3 < 0xc) {
          if (param_3 == 9) {
            RTMPIoctlE2PROM(param_1,param_2);
            return 0;
          }
          if (param_3 == 10) {
            return 0;
          }
        }
        else {
          if (param_3 == 0xc) {
            return 0;
          }
          if (param_3 == 0xd) {
            if ((param_4 & 0x8000) != 0) {
              uVar2 = RTMPSetInformation(param_1,param_2,param_4,puVar5);
              return uVar2;
            }
            uVar2 = RTMPQueryInformation();
            return uVar2;
          }
        }
      }
      else {
        if (param_3 == 0x22) {
          uVar2 = RTMP_STA_IoctlPrepare(param_1,param_5);
          param_5[5] = uVar2;
          return (uint)(uVar2 != 0);
        }
        if (param_3 < 0x23) {
          if (param_3 == 0x11) {
            RTMP_MapChannelID2KHZ(param_6 & 0xff,param_5);
            return 0;
          }
          if (param_3 == 0x12) {
            RTMP_MapKHZ2ChannelID(param_6,param_5);
            return 0;
          }
        }
        else {
          if (param_3 == 0xa001) {
            uVar2 = RTMPSTAPrivIoctlShow(param_1,*param_5,param_5[1]);
            return uVar2;
          }
          if (0xa001 < param_3) {
            RTMPIoctlGetSiteSurvey(param_1,param_2);
            return 0;
          }
          if (param_3 == 0xa000) {
            uVar2 = RTMPSTAPrivIoctlSet(param_1,*param_5,param_5[1]);
            return uVar2;
          }
        }
      }
    }
    else {
      if (param_3 == 0xa009) {
        uVar2 = RtmpIoctl_rt_ioctl_siwmode(param_1,param_5,param_6);
        return uVar2;
      }
      if (param_3 < 0xa00a) {
        if (param_3 == 0xa006) {
          puVar4 = (uint *)get_scan_tab_by_wdev(param_1,puVar5);
          param_5[1] = *puVar4;
          if (*param_5 == 0) {
            return 0;
          }
          if (*puVar4 != 0) {
            puVar6 = puVar4 + 2;
            uVar2 = 0;
            do {
              iVar1 = uVar2 * 9;
              uVar2 = uVar2 + 1;
              FUN_00059bdc(param_5[2] + iVar1,puVar6);
              puVar6 = puVar6 + 0x2bd;
              if (*param_5 <= uVar2) {
                return 0;
              }
            } while (uVar2 < *puVar4);
            return 0;
          }
          return 0;
        }
        if (param_3 < 0xa007) {
          if (param_3 == 0xa004) {
            if (((param_1[0x28e7e1] & 0x4000U) == 0) && (cRam00000bb4 == '\0')) {
              return 0;
            }
            *(undefined1 *)((int)param_1 + iVar7 * 0x2137b0 + 0x580ccd) = 1;
            return 1;
          }
          if (param_3 == 0xa005) {
            puVar3 = (undefined4 *)get_scan_tab_by_wdev(param_1,puVar5);
            bVar8 = -1 < DebugLevel;
            *(undefined1 *)((int)param_1 + iVar7 * 0x2137b0 + 0x580ccd) = 0;
            if (bVar8) {
              printk("===>rt_ioctl_giwscan. %d(%d) BSS returned, data->length = %ld\n",*puVar3,
                     *puVar3,param_6);
              return 0;
            }
            return 0;
          }
        }
        else {
          if (param_3 == 0xa007) {
            uVar2 = RtmpIoctl_rt_ioctl_siwfreq(param_1,param_5,param_6);
            return uVar2;
          }
          if (param_3 == 0xa008) {
            uVar2 = RtmpIoctl_rt_ioctl_giwfreq(param_1,param_5,param_6);
            return uVar2;
          }
        }
      }
      else {
        if (param_3 == 0xa00c) {
          uVar2 = RtmpIoctl_rt_ioctl_giwap(param_1,param_5,param_6);
          return uVar2;
        }
        if (0xa00c < param_3) {
          if (param_3 == 0xa00e) {
            uVar2 = RtmpIoctl_rt_ioctl_giwscan(param_1,param_5,param_6);
            return uVar2;
          }
          if (param_3 < 0xa00f) {
            uVar2 = RtmpIoctl_rt_ioctl_siwscan(param_1,param_5,param_6);
            return uVar2;
          }
          uVar2 = RtmpIoctl_rt_ioctl_siwessid(param_1,param_5,param_6);
          return uVar2;
        }
        if (param_3 == 0xa00a) {
          uVar2 = RtmpIoctl_rt_ioctl_giwmode(param_1,param_5,param_6);
          return uVar2;
        }
        if (param_3 == 0xa00b) {
          uVar2 = RtmpIoctl_rt_ioctl_siwap(param_1,param_5,param_6);
          return uVar2;
        }
      }
    }
  }
  else {
    if (param_3 == 0xa01d) {
      uVar2 = RtmpIoctl_rt_ioctl_giwencodeext(param_1,param_5,param_6);
      return uVar2;
    }
    if (param_3 < 0xa01e) {
      if (param_3 == 0xa016) {
        uVar2 = RtmpIoctl_rt_ioctl_giwfrag(param_1,param_5,param_6);
        return uVar2;
      }
      if (param_3 < 0xa017) {
        if (param_3 == 0xa013) {
          uVar2 = RtmpIoctl_rt_ioctl_siwrts(param_1,param_5,param_6);
          return uVar2;
        }
        if (param_3 < 0xa014) {
          if (param_3 == 0xa011) {
            __memzero((void *)((int)param_1 + 0x794abb),0x21);
            memcpy((void *)((int)param_1 + 0x794abb),param_5,param_6);
            return 0;
          }
          if (param_3 == 0xa012) {
            uVar2 = RtmpIoctl_rt_ioctl_giwnickn(param_1,param_5,param_6);
            return uVar2;
          }
        }
        else {
          if (param_3 == 0xa014) {
            uVar2 = RtmpIoctl_rt_ioctl_giwrts(param_1,param_5,param_6);
            return uVar2;
          }
          if (param_3 == 0xa015) {
            uVar2 = RtmpIoctl_rt_ioctl_siwfrag(param_1,param_5,param_6);
            return uVar2;
          }
        }
      }
      else {
        if (param_3 == 0xa019) {
          uVar2 = RtmpIoctl_rt_ioctl_siwmlme(param_1,param_5,param_6);
          return uVar2;
        }
        if (0xa019 < param_3) {
          if (param_3 == 0xa01b) {
            uVar2 = RtmpIoctl_rt_ioctl_giwauth(param_1,param_5,param_6);
            return uVar2;
          }
          if (param_3 < 0xa01c) {
            uVar2 = RtmpIoctl_rt_ioctl_siwauth(param_1,param_5,param_6);
            return uVar2;
          }
          uVar2 = RtmpIoctl_rt_ioctl_siwencodeext(param_1,param_5,param_6,puVar5);
          return uVar2;
        }
        if (param_3 == 0xa017) {
          uVar2 = RtmpIoctl_rt_ioctl_siwencode(param_1,param_5,param_6);
          return uVar2;
        }
        if (param_3 == 0xa018) {
          uVar2 = RtmpIoctl_rt_ioctl_giwencode(param_1,param_5,param_6);
          return uVar2;
        }
      }
    }
    else {
      if (param_3 == 0xa023) {
        *param_5 = *(uint *)((int)param_1 + (int)(&DAT_0036db70 + iVar1 + 3));
        *(undefined2 *)(param_5 + 1) =
             *(undefined2 *)((int)param_1 + (int)(&DAT_0036db70 + iVar1 + 7));
        return 0;
      }
      if (param_3 < 0xa024) {
        if (param_3 == 0xa020) {
          uVar2 = RtmpIoctl_rt_ioctl_siwpmksa(param_1,param_5,param_6);
          return uVar2;
        }
        if (param_3 < 0xa021) {
          if (param_3 == 0xa01e) {
            return 0;
          }
          if (param_3 == 0xa01f) {
            uVar2 = RtmpIoctl_rt_ioctl_giwgenie(param_1,param_5,param_6);
            return uVar2;
          }
        }
        else {
          if (param_3 == 0xa021) {
            uVar2 = RtmpIoctl_rt_ioctl_siwrate(param_1,param_5,param_6,puVar5);
            return uVar2;
          }
          if (param_3 == 0xa022) {
            uVar2 = RtmpIoctl_rt_ioctl_giwrate(param_1,param_5,param_6,puVar5);
            return uVar2;
          }
        }
      }
      else {
        if (param_3 == 0xa026) {
          uVar2 = RtmpIoctl_rt_private_set_wsc_string_item(param_1,param_5,param_6);
          return uVar2;
        }
        if (param_3 < 40999) {
          if (param_3 == 0xa024) {
            *(char *)param_5 = (char)param_1[iVar7 * 0x84dec + 0x160349];
            return 0;
          }
          if (param_3 == 0xa025) {
            uVar2 = RtmpIoctl_rt_private_set_wsc_u32_item(param_1,param_5,param_6);
            return uVar2;
          }
        }
        else {
          if (param_3 == 41000) {
            MSTA_Init(param_1,param_5);
            return 0;
          }
          if (param_3 < 41000) {
            uVar2 = RtmpIoctl_rt_private_get_statistics(param_1,param_5,param_6);
            return uVar2;
          }
          if (param_3 == 0xa02a) {
            MSTA_Remove(param_1);
            return 0;
          }
        }
      }
    }
  }
  uVar2 = RTMP_COM_IoctlHandle(param_1,param_2,param_3,param_4);
  return uVar2;
}

