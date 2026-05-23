// module: mt7915.ko
// function: WPAParseEapolKeyData @ 0x11d85c
// size: 2028 bytes
//

undefined4
WPAParseEapolKeyData
          (undefined4 param_1,char *param_2,uint param_3,uint param_4,byte param_5,char param_6,
          int *param_7)

{
  byte *pbVar1;
  bool bVar2;
  undefined4 uVar3;
  char *pcVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  void *__dest;
  uint uVar10;
  char *pcVar11;
  char *__s1;
  uint local_120;
  char *local_118;
  char *local_114;
  uint local_110;
  byte local_f8;
  undefined1 uStack_f7;
  undefined1 auStack_f6 [6];
  undefined1 auStack_f0 [32];
  undefined1 auStack_d0 [32];
  int local_b0 [3];
  undefined2 local_a4;
  undefined1 local_a2;
  undefined1 local_a1;
  undefined1 auStack_a0 [81];
  undefined1 auStack_4f [32];
  byte local_2f;
  undefined1 auStack_2e [10];
  
  uVar8 = (uint)param_5;
  uVar10 = 0;
  local_f8 = 0;
  __memzero(auStack_f0,0x20);
  if (uVar8 - 2 < 2) {
    uVar9 = (uint)*(byte *)(param_7 + 0x276);
    if (uVar9 < 3) {
      local_110 = 0;
      local_118 = (char *)0x0;
      local_114 = (char *)0x0;
    }
    else {
      local_118 = (char *)0x0;
      local_114 = (char *)0x0;
      local_110 = 0;
      pcVar11 = (char *)((int)param_7 + 0x9d9);
      do {
        if (*pcVar11 == '0') {
          uVar6 = (uint)(byte)pcVar11[1];
          uVar5 = uVar6 + 2;
          uVar10 = uVar5 & 0xff;
          local_114 = pcVar11;
        }
        else if (*pcVar11 == -0x23) {
          iVar7 = memcmp(pcVar11 + 2,&WPA_OUI,4);
          uVar6 = (uint)(byte)pcVar11[1];
          if (iVar7 == 0) {
            local_110 = uVar6 + 2 & 0xff;
            local_118 = pcVar11;
          }
          uVar5 = uVar6 + 2;
        }
        else {
          uVar6 = (uint)(byte)pcVar11[1];
          uVar5 = uVar6 + 2;
        }
        pcVar11 = pcVar11 + uVar5;
        uVar9 = uVar9 + (0xfffe - uVar6) & 0xff;
      } while (2 < uVar9);
      if (local_118 != (char *)0x0) {
        hex_dump("WPA IE:",local_118,local_110);
      }
      if (local_114 != (char *)0x0) {
        hex_dump("RSN IE:",local_114,uVar10);
      }
    }
    pcVar11 = local_118;
    if (param_3 < 3) {
LAB_0011dca0:
      if (-1 < DebugLevel) {
        printk("RSN_IE Different in msg %d of 4-way handshake!\n",uVar8);
      }
      hex_dump("Receive RSN_IE ",param_2,param_3);
      hex_dump("Desired RSN_IE ",(char *)((int)param_7 + 0x9d9),(char)param_7[0x276]);
      return 0;
    }
    uVar9 = 0;
    bVar2 = false;
    uVar10 = param_3;
    __s1 = param_2;
    do {
      if (*__s1 == '0') {
        if ((local_114 != (char *)0x0 && param_6 != '\0') && (*local_114 == '0')) {
          uVar6 = (uint)(byte)__s1[1];
          local_118 = (char *)(uVar6 + 2);
          if ((byte)local_114[1] + 2 <= local_118) {
            iVar7 = memcmp(__s1,local_114,(byte)local_114[1] + 2);
            if (iVar7 == 0) {
              if (DebugLevel < 3) goto LAB_0011dbc8;
              pcVar4 = "%s ==> RSN IE matched, Length(%d)\n";
              goto LAB_0011df04;
            }
            goto LAB_0011dbd0;
          }
        }
        if (-1 < DebugLevel) {
          printk("%s ==> RSN IE Lens mis-matched\n","RTMPCheckRSNIE");
        }
LAB_0011dc40:
        uVar6 = (uint)(byte)__s1[1];
        local_118 = (char *)(uVar6 + 2);
      }
      else {
        if ((*__s1 != -0x23) || (iVar7 = memcmp(__s1 + 2,&WPA_OUI,4), iVar7 != 0)) break;
        if (param_6 != '\0') {
LAB_0011dc34:
          if (-1 < DebugLevel) {
            printk("%s ==> WPA/WPAPSK IE mis-matched\n","RTMPCheckRSNIE");
          }
          goto LAB_0011dc40;
        }
        uVar6 = (uint)(byte)__s1[1];
        local_118 = (char *)(uVar6 + 2);
        if ((pcVar11 == (char *)0x0 || (char *)local_110 != local_118) ||
           (iVar7 = memcmp(__s1,pcVar11,(byte)pcVar11[1] + 2), iVar7 != 0)) goto LAB_0011dc34;
        if (DebugLevel < 3) {
LAB_0011dbc8:
          bVar2 = true;
        }
        else {
          pcVar4 = "%s ==> WPA/WPAPSK IE matched, Length(%d)\n";
LAB_0011df04:
          printk(pcVar4,"RTMPCheckRSNIE",local_118);
          uVar6 = (uint)(byte)__s1[1];
          bVar2 = true;
          local_118 = (char *)(uVar6 + 2);
        }
      }
LAB_0011dbd0:
      __s1 = __s1 + (int)local_118;
      uVar10 = uVar10 + (0xfffe - uVar6) & 0xff;
      uVar9 = uVar6 + (uVar9 + 2 & 0xff) & 0xff;
    } while (2 < uVar10);
    if (!bVar2) goto LAB_0011dca0;
    if (param_6 == '\0' || uVar8 != 3) {
      return 1;
    }
    param_2 = param_2 + uVar9;
    param_3 = param_3 - uVar9 & 0xff;
    if (2 < DebugLevel) {
      printk("RTMPParseEapolKeyData ==> WPA2/WPA2PSK RSN IE matched in Msg 3, Length(%d)\n",uVar9);
      goto LAB_0011d8a4;
    }
  }
  else {
LAB_0011d8a4:
    if (2 < DebugLevel) {
      printk("RTMPParseEapolKeyData ==> KeyDataLength %d without RSN_IE\n",param_3);
    }
    if (param_6 == '\0') {
      if (uVar8 == 5) {
        if (0x20 < param_3) {
          if (DebugLevel < 0) {
            return 0;
          }
          printk("ERROR: GTK Key length is invalid (%d)\n",param_3);
          return 0;
        }
        memcpy(auStack_f0,param_2,param_3);
        if (2 < DebugLevel) {
          printk("GTK without KDE, DefaultKeyID=%d, KeyLen=%d\n",param_4,param_3);
        }
        uVar8 = param_3;
        local_120 = param_4;
        if (3 < param_4) {
          if (DebugLevel < 0) {
            return 0;
          }
          uVar3 = GetEapolMsgType(5);
          printk("ERROR: GTK Key index(%d) is invalid in %s %s\n",param_4,&_LC100,uVar3);
          return 0;
        }
      }
      else {
        local_120 = 0;
        uVar8 = 0;
      }
      goto LAB_0011d9c8;
    }
  }
  if ((uVar8 - 3 & 0xfd) == 0) {
    uVar10 = (uint)(byte)param_2[1];
    local_120 = 0;
    uVar8 = local_120;
    if ((int)(uVar10 + 2) <= (int)param_3) {
      uVar9 = 0;
      do {
        if ((*param_2 == -0x23) && (iVar7 = memcmp(param_2 + 2,&OUI_WPA2_CIPHER,3), iVar7 == 0)) {
          if (param_2[5] == '\x01') {
            uVar8 = uVar10 - 6 & 0xff;
            local_120 = (byte)param_2[6] & 3;
            if (0x1b < uVar10 - 0xb) {
              if (DebugLevel < 0) {
                return 0;
              }
              printk("ERROR: GTK Key length is invalid (%d)\n",uVar8);
              return 0;
            }
            memcpy(auStack_f0,param_2 + 8,uVar8);
            if (2 < DebugLevel) {
              printk("GTK in KDE format ,DefaultKeyID=%d, KeyLen=%d\n",local_120,uVar8);
            }
          }
          else if ((param_2[5] == '\t') &&
                  (iVar7 = PMF_ExtractIGTKKDE(param_2 + 6,uVar10 - 4,auStack_d0,&local_f8,auStack_f6
                                              ,&uStack_f7), iVar7 == 0)) {
            if (DebugLevel < 0) {
              return 0;
            }
            printk("PMF_ExtractIGTKKDE: %s FAIL\n","WPAParseEapolKeyData");
            return 0;
          }
        }
        pbVar1 = (byte *)(param_2 + 1);
        param_2 = param_2 + *pbVar1 + 2;
        uVar9 = uVar9 + *pbVar1 + 2 & 0xff;
        uVar10 = (uint)(byte)param_2[1];
      } while ((int)(uVar9 + 2 + uVar10) <= (int)param_3);
    }
  }
  else {
    local_120 = 0;
    uVar8 = 0;
  }
LAB_0011d9c8:
  iVar7 = *param_7;
  if (iVar7 == 2) {
    memset(local_b0,0,0x88);
    __dest = (void *)((int)param_7 + 0x3c9);
    memcpy(__dest,auStack_f0,uVar8);
    *(undefined1 *)(param_7 + 0xea) = (undefined1)local_120;
    os_zero_mem(local_b0,0x88);
    local_b0[1] = 1;
    local_a1 = (undefined1)param_7[0xea];
    local_b0[2] = param_7[0xe9];
    local_a4 = *(undefined2 *)(param_7[2] + 0x9a0);
    local_a2 = 0;
    local_b0[0] = iVar7;
    os_move_mem(auStack_2e,param_7 + 0x3b,6);
    os_move_mem(auStack_a0,__dest,0x20);
    if (local_f8 != 0) {
      local_b0[2] = local_b0[2] | *(uint *)((int)param_7 + 0x563);
      os_move_mem(auStack_4f,auStack_d0,(uint)local_f8);
      local_2f = local_f8;
    }
    if ((*(char *)((int)param_7 + 0x91e) == (char)param_7[0xea]) &&
       (iVar7 = memcmp((void *)((int)param_7 + 0x91f),__dest,0x20), iVar7 == 0)) {
      if (-1 < DebugLevel) {
        printk("!!!%s : the Group reinstall attack, skip install key (%d)\n","WPAParseEapolKeyData",
               (short)param_7[0x38]);
      }
    }
    else {
      WPAInstallKey(param_1,local_b0,0,1);
      *(char *)((int)param_7 + 0x91e) = (char)param_7[0xea];
      os_move_mem((void *)((int)param_7 + 0x91f),__dest,0x20);
      *(undefined1 *)(param_7 + 0x519) = 1;
    }
  }
  return 1;
}

