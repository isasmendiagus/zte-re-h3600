// module: mt7915.ko
// function: rt28xx_ap_ioctl @ 0x4a210
// size: 2772 bytes
//

int rt28xx_ap_ioctl(undefined4 **param_1,undefined4 ***param_2,int param_3)

{
  ushort uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 ***pppuVar4;
  undefined4 **ppuVar5;
  undefined4 **ppuVar6;
  uint uVar7;
  undefined4 **ppuVar8;
  undefined4 ***local_78;
  int **local_74;
  int **local_6c;
  int *local_68;
  int local_64;
  uint local_60;
  int *local_5c;
  int *piStack_58;
  int *piStack_54;
  int *piStack_50;
  int *local_4c;
  ushort local_48;
  undefined2 local_46;
  int *local_44;
  undefined4 local_40;
  undefined4 local_3c;
  int *local_38;
  uint local_34;
  undefined4 local_30;
  int *local_2c;
  undefined4 local_28;
  int local_24;
  
  iVar3 = RtmpOsGetNetDevPriv();
  if (iVar3 == 0) {
    return -100;
  }
  piStack_54 = (int *)param_2[2];
  piStack_58 = (int *)param_2[1];
  piStack_50 = (int *)param_2[3];
  local_5c = (int *)*param_2;
  local_4c = (int *)param_2[4];
  uVar1 = *(ushort *)(param_2 + 5);
  local_24 = 0;
  local_48 = uVar1;
  local_44 = (int *)param_1;
  local_40 = RtmpOsGetNetDevWdev(param_1);
  local_3c = RtmpDevPrivFlagsGet(param_1);
  local_34 = (uint)*(ushort *)(param_2 + 5);
  if (local_34 == 0) {
    local_38 = (int *)0x0;
  }
  else {
    local_38 = (int *)param_2[4];
  }
  local_30 = 0x8be2;
  local_28 = 0;
  local_2c = (int *)param_1;
  if (param_3 == 0x8b0d) {
LAB_0004a748:
    ppuVar6 = param_2[4];
    if (ppuVar6 == (undefined4 **)0x0) goto switchD_0004a88c_caseD_2;
    ppuVar5 = *(undefined4 ***)(((uint)&local_78 & 0xffffe000) + 8);
    ppuVar8 = ppuVar5;
    if (ppuVar6 < (undefined4 **)0xfffffe50 && ppuVar6 + 0x6c <= ppuVar5) {
      ppuVar8 = (undefined4 **)0x0;
    }
    if (ppuVar8 != (undefined4 **)0x0) goto switchD_0004a88c_caseD_2;
    if (local_48 < 0x12) {
      local_24 = 0x7534;
      goto LAB_0004a344;
    }
    if (ppuVar6 < (undefined4 **)0xfffffe50 && ppuVar6 + 0x6c <= ppuVar5) {
      ppuVar5 = (undefined4 **)0x0;
    }
    *(undefined2 *)(param_2 + 5) = 0x12;
    if (ppuVar5 == (undefined4 **)0x0) {
      iVar3 = __copy_to_user(ppuVar6,&ap_privtab,0x1b0);
      if (iVar3 == 0) goto switchD_0004a88c_caseD_2;
LAB_0004a660:
      local_24 = 0x7532;
      goto LAB_0004a344;
    }
    goto LAB_0004a410;
  }
  local_78 = (undefined4 ***)&local_44;
  local_74 = (int **)0x0;
  pppuVar4 = (undefined4 ***)RTMP_AP_IoctlHandle(iVar3,0,0x22,0);
  uVar2 = local_28;
  if (pppuVar4 != (undefined4 ***)0x0) goto LAB_0004a32c;
  if (param_3 == 0x8b01) {
    if (2 < DebugLevel) {
      printk("IOCTL::SIOCGIWNAME\n");
    }
    local_78 = param_2 + 4;
    local_74 = (int **)0x0;
    RTMP_COM_IoctlHandle(iVar3,0,0x5043,0);
    return 0;
  }
  if (param_3 == 0x8be9) {
    local_78 = pppuVar4;
    local_74 = (int **)pppuVar4;
    RTMP_AP_IoctlHandle(iVar3,&local_5c,5,0);
    goto switchD_0004a88c_caseD_2;
  }
  if (param_3 < 0x8bea) {
    if (param_3 == 0x8b1b) {
      *(undefined2 *)((int)param_2 + 0x16) = 1;
      local_6c = (int **)RtmpDevPrivFlagsGet(param_1);
      local_78 = &local_6c;
      local_68 = (int *)uVar2;
      local_74 = (int **)pppuVar4;
      RTMP_AP_IoctlHandle(iVar3,&local_5c,0x25,0);
      ppuVar6 = param_2[4];
      *(short *)(param_2 + 5) = (short)local_60;
      if (ppuVar6 != (undefined4 **)0x0 && local_64 != 0) {
        local_60 = local_60 & 0xffff;
        uVar7 = *(uint *)(((uint)&local_78 & 0xffffe000) + 8);
        if (!CARRY4((uint)ppuVar6,local_60) && (int)ppuVar6 + local_60 <= uVar7) {
          uVar7 = 0;
        }
        if (uVar7 == 0) {
          local_60 = __copy_to_user();
        }
        if (local_60 != 0) goto LAB_0004a660;
      }
    }
    else if (param_3 < 0x8b1c) {
      if (param_3 == 0x8b0b) {
        local_6c = (int **)pppuVar4;
        os_alloc_mem(0,&local_6c,0x238);
        if ((undefined4 ***)local_6c == (undefined4 ***)0x0) {
          if (-1 < DebugLevel) {
            printk("%s: Allocate memory fail!!!\n","rt28xx_ap_ioctl");
          }
        }
        else {
          __memzero(local_6c,0x238);
          *(undefined1 *)(local_6c + 0xb) = 100;
          *(undefined1 *)((int)local_6c + 0x119) = 0xe;
          *(undefined1 *)((int)local_6c + 0x2d) = 0;
          *(undefined1 *)((int)local_6c + 0x2e) = 0;
          *(undefined1 *)(local_6c + 0x46) = 0x16;
          ppuVar6 = *(undefined4 ***)(((uint)&local_78 & 0xffffe000) + 8);
          if (local_4c < (undefined4 **)0xfffffdc8 && local_4c + 0x8e <= ppuVar6) {
            ppuVar6 = (undefined4 **)0x0;
          }
          if (ppuVar6 == (undefined4 **)0x0) {
            __copy_to_user(local_4c,local_6c,0x238);
          }
          os_free_mem(local_6c);
        }
      }
      else if (param_3 < 0x8b0c) {
        if (param_3 == 0x8b05) {
          local_78 = &local_6c;
          local_74 = (int **)local_28;
          RTMP_COM_IoctlHandle(iVar3,0,0x5042,0);
          *(undefined2 *)(param_2 + 5) = 0;
          *(undefined1 *)((int)param_2 + 0x16) = 0;
          param_2[4] = local_6c;
        }
        else if (param_3 == 0x8b07) {
          iVar3 = RtmpDevPrivFlagsGet(param_1);
          if (iVar3 == 0x400) {
            ppuVar6 = (undefined4 **)0x2;
          }
          else {
            ppuVar6 = (undefined4 **)0x3;
          }
          param_2[4] = ppuVar6;
        }
        else {
          if (param_3 != 0x8927) goto LAB_0004a4fc;
          if (2 < DebugLevel) {
            printk("IOCTLIOCTLIOCTL::SIOCGIFHWADDR\n");
          }
          local_78 = (undefined4 ***)0x0;
          local_74 = (int **)0x0;
          RTMP_AP_IoctlHandle(iVar3,&local_5c,0x24);
        }
      }
      else if (param_3 == 0x8b15) {
        *(undefined2 *)(param_2 + 4) = 1;
        local_74 = (int **)RtmpDevPrivFlagsGet(param_1);
        local_78 = (undefined4 ***)((int)param_2 + 0x12);
        RTMP_AP_IoctlHandle(iVar3,&local_5c,0x23,0);
      }
      else if (param_3 != 0x8b1a) {
        if (param_3 == 0x8b0d) goto LAB_0004a748;
        goto LAB_0004a4fc;
      }
    }
    else if (param_3 == 0x8be3) {
      local_78 = pppuVar4;
      local_74 = (int **)pppuVar4;
      RTMP_AP_IoctlHandle(iVar3,&local_5c,10,0);
    }
    else if (param_3 < 0x8be4) {
      if (param_3 == 0x8be1) goto LAB_0004abb0;
      if (param_3 < 0x8be2) {
        if (param_3 != 0x8b21) goto LAB_0004a4fc;
        local_6c = (int **)RtmpDevPrivFlagsGet(param_1);
        local_78 = &local_6c;
        local_74 = (int **)0x0;
        RTMP_COM_IoctlHandle(iVar3,0,0x5044,0);
        *(undefined1 *)((int)param_2 + 0x15) = 0;
        param_2[4] = (undefined4 **)local_68;
      }
      else {
        local_78 = *(undefined4 ****)(((uint)&local_78 & 0xffffe000) + 8);
        if (!CARRY4((uint)param_2[4],(uint)*(ushort *)(param_2 + 5)) &&
            (undefined4 ***)((int)param_2[4] + (uint)*(ushort *)(param_2 + 5)) <= local_78) {
          local_78 = (undefined4 ***)0x0;
        }
        if (local_78 == (undefined4 ***)0x0) {
          local_74 = (int **)local_78;
          local_24 = RTMP_AP_IoctlHandle(iVar3,&local_5c,0xe);
          goto LAB_0004a32c;
        }
      }
    }
    else if (param_3 == 0x8be7) {
      local_78 = (undefined4 ***)0x0;
      local_74 = (int **)0x0;
      RTMP_AP_IoctlHandle(iVar3,&local_5c,9);
    }
    else if (param_3 < 0x8be8) {
      if (param_3 != 0x8be5) goto LAB_0004a4fc;
      local_78 = (undefined4 ***)0x0;
      local_74 = (int **)0x0;
      RTMP_AP_IoctlHandle(iVar3,&local_5c,0xb);
    }
    else {
      local_74 = (int **)0x0;
      local_78 = param_2;
      RTMP_COM_IoctlHandle(iVar3,&local_5c,0x10);
    }
    goto switchD_0004a88c_caseD_2;
  }
  if (param_3 == 0x8bf5) {
    local_46 = *(undefined2 *)((int)param_2 + 0x16);
    RTMPAR9IoctlGetMacTableNew(iVar3,&local_5c);
    goto switchD_0004a88c_caseD_2;
  }
  if (0x8bf5 < param_3) {
    if (param_3 == 0x8bf9) {
      local_78 = pppuVar4;
      local_74 = (int **)pppuVar4;
      RTMP_AP_IoctlHandle(iVar3,&local_5c,1,0);
    }
    else if (param_3 < 0x8bfa) {
      if (param_3 == 0x8bf7) {
        local_78 = (undefined4 ***)0x0;
        local_74 = (int **)0x0;
        RTMP_AP_IoctlHandle(iVar3,&local_5c,6);
      }
      else if (param_3 < 0x8bf8) {
        local_78 = (undefined4 ***)0x0;
        local_74 = (int **)0x0;
        RTMP_AP_IoctlHandle(iVar3,&local_5c,8);
      }
      else {
        local_78 = *(undefined4 ****)(((uint)&local_78 & 0xffffe000) + 8);
        if (!CARRY4((uint)param_2[4],(uint)*(ushort *)(param_2 + 5)) &&
            (undefined4 ***)((int)param_2[4] + (uint)*(ushort *)(param_2 + 5)) <= local_78) {
          local_78 = (undefined4 ***)0x0;
        }
        if (local_78 == (undefined4 ***)0x0) {
          local_74 = (int **)local_78;
          RTMP_AP_IoctlHandle(iVar3,&local_5c,0x32);
        }
      }
    }
    else if (param_3 == 0x8bfd) {
      local_78 = *(undefined4 ****)(((uint)&local_78 & 0xffffe000) + 8);
      if (!CARRY4((uint)param_2[4],(uint)*(ushort *)(param_2 + 5)) &&
          (undefined4 ***)((int)param_2[4] + (uint)*(ushort *)(param_2 + 5)) <= local_78) {
        local_78 = (undefined4 ***)0x0;
      }
      if (local_78 == (undefined4 ***)0x0) {
        local_74 = (int **)local_78;
        local_24 = RTMP_AP_IoctlHandle(iVar3,&local_5c,0x29);
        goto LAB_0004a32c;
      }
    }
    else if (param_3 < 0x8bfe) {
      if (param_3 != 0x8bfb) {
LAB_0004a4fc:
        local_24 = 0x7531;
        goto LAB_0004a344;
      }
      local_78 = (undefined4 ***)0x0;
      local_74 = (int **)0x0;
      RTMP_AP_IoctlHandle(iVar3,&local_5c,0xd,0x67d);
    }
    else if (param_3 == 0x8bff) {
      local_78 = (undefined4 ***)0x0;
      local_74 = (int **)0x0;
      RTMP_AP_IoctlHandle(iVar3,&local_5c,0x13);
    }
    else {
      if (param_3 != 0x8c03) goto LAB_0004a4fc;
      local_78 = *(undefined4 ****)(((uint)&local_78 & 0xffffe000) + 8);
      if (!CARRY4((uint)param_2[4],(uint)*(ushort *)(param_2 + 5)) &&
          (undefined4 ***)((int)param_2[4] + (uint)*(ushort *)(param_2 + 5)) <= local_78) {
        local_78 = (undefined4 ***)0x0;
      }
      if (local_78 == (undefined4 ***)0x0) {
        local_74 = (int **)local_78;
        local_24 = RTMP_AP_IoctlHandle(iVar3,&local_5c,0x2e);
        goto LAB_0004a32c;
      }
    }
    goto switchD_0004a88c_caseD_2;
  }
  if (param_3 == 0x8bf1) {
    local_78 = *(undefined4 ****)(((uint)&local_78 & 0xffffe000) + 8);
    if (!CARRY4((uint)param_2[4],(uint)*(ushort *)(param_2 + 5)) &&
        (undefined4 ***)((int)param_2[4] + (uint)*(ushort *)(param_2 + 5)) <= local_78) {
      local_78 = (undefined4 ***)0x0;
    }
    if (local_78 == (undefined4 ***)0x0) {
      local_74 = (int **)local_78;
      local_24 = RTMP_AP_IoctlHandle(iVar3,&local_5c,0xf);
      goto LAB_0004a32c;
    }
    goto switchD_0004a88c_caseD_2;
  }
  if (param_3 < 0x8bf2) {
    if (param_3 == 0x8bee) {
LAB_0004abb0:
      local_78 = (undefined4 ***)param_2[4];
      local_74 = (int **)0x0;
      local_24 = RTMP_AP_IoctlHandle(iVar3,&local_5c,0xd,*(undefined2 *)((int)param_2 + 0x16));
      goto LAB_0004a32c;
    }
    if (param_3 == 0x8bef) {
      local_78 = (undefined4 ***)0x0;
      local_74 = (int **)0x0;
      RTMP_AP_IoctlHandle(iVar3,&local_5c,2);
    }
    else {
      if (param_3 != 0x8bed) goto LAB_0004a4fc;
      local_78 = (undefined4 ***)0x0;
      local_74 = (int **)0x0;
      RTMP_AP_IoctlHandle(iVar3,&local_5c,3);
    }
    goto switchD_0004a88c_caseD_2;
  }
  if (param_3 == 0x8bf3) {
    local_78 = (undefined4 ***)0x0;
    local_74 = (int **)0x0;
    RTMP_AP_IoctlHandle(iVar3,&local_5c,0xc);
    goto switchD_0004a88c_caseD_2;
  }
  if (param_3 < 0x8bf4) {
    local_78 = (undefined4 ***)0x0;
    local_74 = (int **)0x0;
    RTMP_AP_IoctlHandle(iVar3,&local_5c,0x1b);
    goto switchD_0004a88c_caseD_2;
  }
  switch(*(undefined2 *)((int)param_2 + 0x16)) {
  case 1:
  case 0xc:
    local_78 = (undefined4 ***)0x0;
    local_74 = (int **)0x0;
    local_24 = RTMP_AP_IoctlHandle(iVar3,&local_5c,0x2a);
    break;
  default:
    goto switchD_0004a88c_caseD_2;
  case 5:
    local_78 = (undefined4 ***)0x0;
    local_74 = (int **)0x0;
    RTMP_AP_IoctlHandle(iVar3,&local_5c,0x2b);
    goto switchD_0004a88c_caseD_2;
  case 6:
    local_78 = (undefined4 ***)0x0;
    local_74 = (int **)0x0;
    RTMP_AP_IoctlHandle(iVar3,&local_5c,0x2c);
    goto switchD_0004a88c_caseD_2;
  case 7:
    local_78 = *(undefined4 ****)(((uint)&local_78 & 0xffffe000) + 8);
    if (!CARRY4((uint)param_2[4],(uint)*(ushort *)(param_2 + 5)) &&
        (undefined4 ***)((int)param_2[4] + (uint)*(ushort *)(param_2 + 5)) <= local_78) {
      local_78 = (undefined4 ***)0x0;
    }
    if (local_78 == (undefined4 ***)0x0) {
      local_74 = (int **)local_78;
      local_24 = RTMP_AP_IoctlHandle(iVar3,&local_5c,4);
      break;
    }
    goto switchD_0004a88c_caseD_2;
  case 9:
    local_78 = (undefined4 ***)0x0;
    local_74 = (int **)0x0;
    local_24 = RTMP_AP_IoctlHandle(iVar3,&local_5c,0x2f);
    break;
  case 0xb:
    local_24 = RTMPAPPrivIoctlGetFactoryStatistics(iVar3,&local_5c);
    break;
  case 0xd:
    local_78 = (undefined4 ***)0x0;
    local_74 = (int **)0x0;
    local_24 = RTMP_AP_IoctlHandle(iVar3,&local_5c,0x2d);
    break;
  case 0x10:
    local_78 = (undefined4 ***)0x0;
    local_74 = (int **)0x0;
    local_24 = RTMP_AP_IoctlHandle(iVar3,&local_5c,0x33);
    break;
  case 0x11:
    local_78 = (undefined4 ***)0x0;
    local_74 = (int **)0x0;
    local_24 = RTMP_AP_IoctlHandle(iVar3,&local_5c,0x30);
  }
LAB_0004a32c:
  if (local_24 == 0) {
switchD_0004a88c_caseD_2:
    if (uVar1 != local_48) {
      *(ushort *)(param_2 + 5) = local_48;
      return 0;
    }
    local_24 = 0;
  }
  else if (local_24 == 30000) {
    local_24 = -0x16;
  }
  else {
LAB_0004a344:
    if (local_24 == 0x7531) {
      local_24 = -0x5f;
    }
    else if (local_24 == 0x7532) {
LAB_0004a410:
      local_24 = -0xe;
    }
    else if (local_24 == 0x7534) {
      local_24 = -7;
    }
    else if (local_24 == 0x7535) {
      local_24 = -0xc;
    }
    else if (local_24 == 0x7536) {
      local_24 = -0xb;
    }
    else if (local_24 == 0x7537) {
      local_24 = -0x6b;
    }
  }
  return local_24;
}

