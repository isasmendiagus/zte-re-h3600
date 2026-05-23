// module: mt7915.ko
// function: rt28xx_sta_ioctl @ 0x6f54c
// size: 2004 bytes
//

uint rt28xx_sta_ioctl(undefined4 param_1,uint *param_2,int param_3)

{
  undefined2 uVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined4 uVar7;
  uint uVar8;
  uint uVar9;
  uint *local_78;
  uint *local_74;
  undefined4 local_70;
  uint local_64;
  undefined1 *local_60;
  undefined1 auStack_5c [16];
  uint local_4c;
  ushort local_48;
  undefined1 auStack_41 [37];
  
  iVar2 = RtmpOsGetNetDevPriv();
  if (iVar2 == 0) {
    return 0xffffff9c;
  }
  if (param_2 == (uint *)0x0) {
    if (3 < DebugLevel) {
      printk("INFO::wrqin is null!\n");
      return 0;
    }
    return 0;
  }
  local_4c = param_2[4];
  uVar5 = param_2[5];
  local_48 = (ushort)uVar5;
  puVar3 = (uint *)DetermineCallerInterface(param_1,iVar2);
  if (puVar3 != (uint *)0x0) {
    return 0xfffffff2;
  }
  local_78 = puVar3;
  local_74 = puVar3;
  iVar4 = RTMP_COM_IoctlHandle(iVar2,0,0x5011,0);
  if (iVar4 != 0) {
    uVar8 = param_2[4];
    if (uVar8 == 0) {
      return 0;
    }
    if (param_3 != 0x8be2) {
      if (DebugLevel < 3) {
        return 0xffffff9c;
      }
      printk("INFO::Network is down!\n");
      return 0xffffff9c;
    }
LAB_0006fb60:
    uVar6 = *(uint *)(((uint)&local_78 & 0xffffe000) + 8);
    if (!CARRY4(uVar8,(uint)(ushort)param_2[5]) && uVar8 + (ushort)param_2[5] <= uVar6) {
      uVar6 = 0;
    }
    if (uVar6 == 0) {
      uVar5 = rt_ioctl_setparam(param_1,0,0);
      return uVar5;
    }
    goto LAB_0006f6f4;
  }
  if (param_3 == 0x8b20) {
    rt_ioctl_siwrate(param_1,0,param_2 + 4,0);
    goto LAB_0006f6f4;
  }
  if (param_3 < 0x8b21) {
    if (0x8b09 < param_3) {
      if (param_3 == 0x8b15) {
        rt_ioctl_giwap(param_1,0,param_2 + 4,(int)param_2 + 0x12);
        goto LAB_0006f6f4;
      }
      if (param_3 < 0x8b16) {
        if (param_3 == 0x8b0d) {
          uVar8 = param_2[4];
          if (uVar8 == 0) goto LAB_0006f6f4;
          uVar9 = *(uint *)(((uint)&local_78 & 0xffffe000) + 8);
          uVar6 = uVar9;
          if (uVar8 < 0xfffffa30 && uVar8 + 0x5d0 <= uVar9) {
            uVar6 = 0;
          }
          if (uVar6 != 0) goto LAB_0006f6f4;
          if (local_48 < 0x3e) {
            uVar8 = 0xfffffff9;
          }
          else {
            if (uVar8 < 0xfffffa30 && uVar8 + 0x5d0 <= uVar9) {
              uVar9 = 0;
            }
            *(undefined2 *)(param_2 + 5) = 0x3e;
            if (uVar9 != 0) {
              return 0xfffffff2;
            }
            iVar2 = __copy_to_user(uVar8,&privtab,0x5d0);
            if (iVar2 == 0) goto LAB_0006f6f4;
            uVar8 = 0xfffffff2;
          }
          goto LAB_0006f848;
        }
        if (param_3 == 0x8b14) {
          rt_ioctl_siwap(param_1,0,param_2 + 4,(int)param_2 + 0x12);
          goto LAB_0006f6f4;
        }
        if (param_3 == 0x8b0b) goto LAB_0006f8e8;
      }
      else {
        if (param_3 == 0x8b1b) {
          rt_ioctl_giwessid(param_1,0,param_2 + 4,param_2[4]);
          goto LAB_0006f6f4;
        }
        if (param_3 < 0x8b1c) {
          if (param_3 == 0x8b1a) {
            rt_ioctl_siwessid(param_1,0,param_2 + 4,param_2[4]);
            goto LAB_0006f6f4;
          }
        }
        else {
          if (param_3 == 0x8b1c) goto LAB_0006f6f4;
          if (param_3 == 0x8b1d) {
            local_64 = 0x21;
            local_60 = auStack_41;
            local_70 = RtmpDevPrivFlagsGet(param_1);
            local_78 = &local_64;
            local_74 = (uint *)0x0;
            RTMP_STA_IoctlHandle(iVar2,0,0xa012,0);
            uVar6 = param_2[4];
            uVar8 = local_64 & 0xffff;
            *(short *)(param_2 + 5) = (short)local_64;
            uVar9 = *(uint *)(((uint)&local_78 & 0xffffe000) + 8);
            if (!CARRY4(uVar6,uVar8) && uVar6 + uVar8 <= uVar9) {
              uVar9 = 0;
            }
            if (uVar9 == 0) {
              uVar8 = __copy_to_user(uVar6,auStack_41);
            }
            goto LAB_0006f830;
          }
        }
      }
      goto LAB_0006f8d4;
    }
    if (param_3 < 0x8b08) {
      if (param_3 < 0x8b04) {
        if (0x8b01 < param_3) goto LAB_0006f8e8;
        if (param_3 == 0x8946) goto LAB_0006f6f4;
        if (param_3 == 0x8b01) {
          return 0xffffffa1;
        }
        if (param_3 == 0x8927) {
          if (2 < DebugLevel) {
            printk("IOCTL::SIOCGIFHWADDR\n");
          }
          local_70 = RtmpDevPrivFlagsGet(param_1);
          local_78 = param_2 + 4;
          local_74 = (uint *)0x0;
          RTMP_STA_IoctlHandle(iVar2,0,0xa023,0);
          goto LAB_0006f6f4;
        }
      }
      else {
        if (param_3 == 0x8b05) {
          rt_ioctl_giwfreq(param_1,0,param_2 + 4,0);
          goto LAB_0006f6f4;
        }
        if (param_3 < 0x8b05) {
          rt_ioctl_siwfreq(param_1,0,param_2 + 4,0);
          goto LAB_0006f6f4;
        }
        if (param_3 == 0x8b06) {
          rt_ioctl_siwmode(param_1,0,param_2 + 4,0);
          goto LAB_0006f6f4;
        }
        if (param_3 == 0x8b07) {
          rt_ioctl_giwmode(param_1,0,param_2 + 4,0);
          goto LAB_0006f6f4;
        }
      }
      goto LAB_0006f8d4;
    }
  }
  else {
    if (param_3 < 0x8b2e) {
      if (param_3 < 0x8b2c) {
        if (param_3 == 0x8b25) {
          rt_ioctl_giwfrag(param_1,0,param_2 + 4,0);
          goto LAB_0006f6f4;
        }
        if (param_3 < 0x8b26) {
          if (param_3 == 0x8b22) {
            rt_ioctl_siwrts(param_1,0,param_2 + 4,0);
            goto LAB_0006f6f4;
          }
          if (param_3 < 0x8b22) {
            rt_ioctl_giwrate(param_1,0,param_2 + 4,0);
            goto LAB_0006f6f4;
          }
          if (param_3 == 0x8b23) {
            rt_ioctl_giwrts(param_1,0,param_2 + 4,0);
            goto LAB_0006f6f4;
          }
          if (param_3 == 0x8b24) {
            rt_ioctl_siwfrag(param_1,0,param_2 + 4,0);
            goto LAB_0006f6f4;
          }
          goto LAB_0006f8d4;
        }
        if (param_3 == 0x8b2a) {
          rt_ioctl_siwencode(param_1,0,param_2 + 4,param_2[4]);
          goto LAB_0006f6f4;
        }
        if (0x8b2a < param_3) {
          rt_ioctl_giwencode(param_1,0,param_2 + 4,param_2[4]);
          goto LAB_0006f6f4;
        }
      }
      goto LAB_0006f8e8;
    }
    if (param_3 == 0x8be8) {
      local_78 = param_2;
      local_74 = puVar3;
      RTMP_COM_IoctlHandle(iVar2,auStack_5c,0x10,0);
      goto LAB_0006f6f4;
    }
    if (param_3 < 0x8be9) {
      if (param_3 == 0x8be2) {
        uVar8 = param_2[4];
        goto LAB_0006fb60;
      }
      if (0x8be2 < param_3) {
        if (param_3 == 0x8be5) {
          local_70 = RtmpDevPrivFlagsGet(param_1);
          uVar7 = 0xb;
        }
        else {
          if (param_3 != 0x8be7) goto LAB_0006f8d4;
          local_70 = RtmpDevPrivFlagsGet(param_1);
          uVar7 = 9;
        }
LAB_0006f768:
        local_78 = (uint *)0x0;
        local_74 = (uint *)0x0;
        RTMP_STA_IoctlHandle(iVar2,auStack_5c,uVar7,0);
LAB_0006f6f4:
        if ((ushort)uVar5 != local_48) {
          *(ushort *)(param_2 + 5) = local_48;
          return 0;
        }
        return 0;
      }
      if (param_3 == 0x8be1) goto LAB_0006fba8;
    }
    else {
      if (param_3 == 0x8bee) {
LAB_0006fba8:
        uVar1 = *(undefined2 *)((int)param_2 + 0x16);
        local_70 = RtmpDevPrivFlagsGet(param_1);
        local_78 = (uint *)0x0;
        local_74 = (uint *)0x0;
        uVar8 = RTMP_STA_IoctlHandle(iVar2,auStack_5c,0xd,uVar1);
LAB_0006f830:
        if (uVar8 == 0) goto LAB_0006f6f4;
        if (uVar8 == 30000) {
          return 0xffffffea;
        }
        goto LAB_0006f848;
      }
      if (param_3 < 0x8bef) {
        if (param_3 == 0x8bed) {
          local_70 = RtmpDevPrivFlagsGet(param_1);
          uVar7 = 0xa002;
          goto LAB_0006f768;
        }
      }
      else {
        if (param_3 == 0x8bf2) {
          uVar8 = *(uint *)(((uint)&local_78 & 0xffffe000) + 8);
          if (!CARRY4(param_2[4],(uint)(ushort)param_2[5]) &&
              param_2[4] + (uint)(ushort)param_2[5] <= uVar8) {
            uVar8 = 0;
          }
          if (uVar8 == 0) {
            uVar5 = rt_ioctl_showparam(param_1,0,0);
            return uVar5;
          }
          goto LAB_0006f6f4;
        }
        if (param_3 == 0x8bf3) {
          local_70 = RtmpDevPrivFlagsGet(param_1);
          uVar7 = 0xc;
          goto LAB_0006f768;
        }
      }
    }
LAB_0006f8d4:
    if (-1 < DebugLevel) {
      printk("IOCTL::unknown IOCTL\'s cmd = 0x%08x\n",param_3);
      uVar8 = 0xffffffa1;
      goto LAB_0006f848;
    }
  }
LAB_0006f8e8:
  uVar8 = 0xffffffa1;
LAB_0006f848:
  if (uVar8 == 0x7531) {
    return 0xffffffa1;
  }
  if (uVar8 == 0x7532) {
    return 0xfffffff2;
  }
  if (uVar8 == 0x7534) {
    return 0xfffffff9;
  }
  if (uVar8 != 0x7535) {
    if (uVar8 == 0x7536) {
      return 0xfffffff5;
    }
    if (uVar8 == 0x7537) {
      return 0xffffff95;
    }
    return uVar8;
  }
  return 0xfffffff4;
}

