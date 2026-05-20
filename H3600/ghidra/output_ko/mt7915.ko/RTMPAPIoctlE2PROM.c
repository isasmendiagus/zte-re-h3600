// module: mt7915.ko
// function: RTMPAPIoctlE2PROM @ 0x3a230
// size: 1684 bytes
//

void RTMPAPIoctlE2PROM(int param_1,int param_2)

{
  int iVar1;
  byte *__s;
  char *pcVar2;
  size_t sVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  byte *pbVar7;
  byte *pbVar8;
  char *__s_00;
  char *__s_01;
  char *__s_02;
  byte *pbVar9;
  char *local_68;
  undefined4 local_64;
  ushort local_5a;
  int local_58;
  char *local_54;
  uint local_50;
  uint local_4c;
  byte local_48;
  byte local_47;
  byte abStack_39 [21];
  
  local_50 = 0;
  local_4c = 0;
  os_alloc_mem(0,&local_58,0x410c);
  if (local_58 == 0) {
    return;
  }
  __s_00 = (char *)(local_58 + 3U & 0xfffffffc);
  __s_01 = __s_00 + 0x4000;
  __memzero(__s_00);
  __memzero(__s_01,0x100);
  uVar4 = (uint)*(ushort *)(param_2 + 0x14);
  if (1 < uVar4) {
    if (0xfe < uVar4) {
      uVar4 = 0xff;
    }
    uVar6 = *(uint *)(((uint)&local_68 & 0xffffe000) + 8);
    if (!CARRY4(*(uint *)(param_2 + 0x10),uVar4) && *(uint *)(param_2 + 0x10) + uVar4 <= uVar6) {
      uVar6 = 0;
    }
    if (uVar6 == 0) {
      iVar1 = __copy_from_user(__s_01);
      if (iVar1 == 0) {
        __s_00[0] = '\n';
        __s_00[1] = '\0';
        local_54 = __s_01;
LAB_0003a328:
        do {
          __s = (byte *)strsep(&local_54,",");
          if (__s == (byte *)0x0) goto LAB_0003a6ec;
          if (*__s != 0) {
            pcVar2 = strchr((char *)__s,0x3d);
            if (pcVar2 != (char *)0x0) {
              __s_02 = pcVar2 + 1;
              *pcVar2 = '\0';
              if ((__s_02 != (char *)0x0) && (pcVar2[1] != '\0')) {
                local_64 = 0;
                local_68 = __s_02;
                sVar3 = strlen(__s_02);
                if (sVar3 < 0x10) {
                  memmove(abStack_39 + 1,local_68,sVar3);
                  sVar3 = strlen(local_68);
                  abStack_39[sVar3 + 1] = (byte)local_64;
                }
                else {
                  if (3 < DebugLevel) {
                    printk("over fixed-size string temp2 by copying value, strlen(value)=%d\n",sVar3
                          );
                  }
                  memmove(abStack_39 + 1,local_68,0x10);
                  sVar3 = strlen((char *)(abStack_39 + 1));
                  abStack_39[sVar3] = 0;
                }
                pbVar8 = abStack_39 + 1;
                local_68 = (char *)strlen((char *)__s);
                if (((char *)0x4 < local_68) || (sVar3 = strlen((char *)pbVar8), 8 < sVar3))
                goto LAB_0003a6ec;
                pbVar9 = __s + (int)local_68;
                pbVar7 = pbVar9;
                while (pbVar7 != __s) {
                  pbVar7 = pbVar7 + -1;
                  if (0x36 < *pbVar7 - 0x30) goto LAB_0003a2d4;
                }
                if (sVar3 != 0) {
                  if (0x36 < abStack_39[sVar3] - 0x30) break;
                  pbVar7 = pbVar8 + (sVar3 - 1);
                  while (pbVar7 != pbVar8) {
                    pbVar7 = pbVar7 + -1;
                    if (0x36 < *pbVar7 - 0x30) goto LAB_0003a2d4;
                  }
                }
                if (local_68 == (char *)0x0) {
LAB_0003a48c:
                  pbVar7 = __s + (3 - (int)local_68);
                  do {
                    pbVar9 = pbVar7 + -1;
                    *pbVar7 = 0x30;
                    pbVar7 = pbVar9;
                  } while (pbVar9 != __s + -1);
                }
                else {
                  pbVar7 = __s + 4;
                  do {
                    pbVar9 = pbVar9 + -1;
                    pbVar7 = pbVar7 + -1;
                    *pbVar7 = *pbVar9;
                  } while (pbVar9 != __s);
                  if (local_68 != (char *)0x4) goto LAB_0003a48c;
                }
                __s[4] = 0;
                sVar3 = strlen((char *)pbVar8);
                iVar1 = sVar3 - 1;
                if (-1 < iVar1) {
                  iVar5 = iVar1 + (4 - sVar3);
                  if (-1 < iVar5) {
                    pbVar9 = pbVar8 + sVar3;
                    pbVar7 = pbVar8 + iVar5;
                    do {
                      iVar1 = iVar1 + -1;
                      pbVar9 = pbVar9 + -1;
                      *pbVar7 = *pbVar9;
                      if (iVar1 == -1) break;
                      pbVar7 = pbVar7 + -1;
                    } while (-1 < (int)((4 - sVar3) + iVar1));
                  }
                }
                if ((int)sVar3 < 4) {
                  pbVar7 = pbVar8 + (4 - sVar3);
                  do {
                    pbVar7 = pbVar7 + -1;
                    *pbVar7 = 0x30;
                  } while (pbVar7 != pbVar8);
                }
                abStack_39[5] = 0;
                AtoH(__s,&local_48,2);
                uVar6 = (uint)local_48;
                uVar4 = (uint)local_47;
                AtoH(pbVar8,&local_48,2);
                uVar4 = uVar4 + uVar6 * 0x100 & 0xffff;
                local_5a = (ushort)local_47 + (ushort)local_48 * 0x100;
                iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
                if (*(code **)(iVar1 + 0xc) != (code *)0x0) {
                  (**(code **)(iVar1 + 0xc))(param_1,uVar4,local_5a);
                }
                sVar3 = strlen(__s_00);
                sprintf(__s_00 + sVar3,"[0x%02X]:%02X  ",uVar4,(uint)local_5a);
                goto LAB_0003a328;
              }
            }
            pcVar2 = strchr((char *)__s,0x3a);
            if (pcVar2 != (char *)0x0) {
              if ("cp_support_is_enabled"[param_1 + 4] == '\x02') {
                uVar4 = get_dev_eeprom_size(param_1);
              }
              else {
                uVar4 = 0x400;
              }
              sscanf(__s_01,"%4x:%4x",&local_50,&local_4c);
              if (local_4c < uVar4 && (local_50 < local_4c && local_4c + local_50 != 0)) {
                if (0x400 < local_4c - local_50) {
                  if (0 < DebugLevel) {
                    printk("Maximum display %d bytes, display 0x%x to 0x%x\n",0x400,local_50,
                           local_50 + 0x400);
                  }
                  local_4c = local_50 + 0x400;
                }
                goto LAB_0003a62c;
              }
              goto LAB_0003a6ec;
            }
            sVar3 = strlen((char *)__s);
            if (4 < sVar3) goto LAB_0003a6ec;
            pbVar7 = __s + sVar3;
            pbVar8 = pbVar7;
            while (pbVar8 != __s) {
              pbVar8 = pbVar8 + -1;
              if (0x36 < *pbVar8 - 0x30) goto LAB_0003a2d4;
            }
            if (sVar3 == 0) {
LAB_0003a7a8:
              pbVar8 = __s + (3 - sVar3);
              do {
                pbVar7 = pbVar8 + -1;
                *pbVar8 = 0x30;
                pbVar8 = pbVar7;
              } while (pbVar7 != __s + -1);
            }
            else {
              pbVar8 = __s + 4;
              do {
                pbVar7 = pbVar7 + -1;
                pbVar8 = pbVar8 + -1;
                *pbVar8 = *pbVar7;
              } while (__s != pbVar7);
              if (sVar3 != 4) goto LAB_0003a7a8;
            }
            __s[4] = 0;
            sVar3 = strlen((char *)__s);
            if (sVar3 == 4) {
              AtoH(__s,&local_48,2);
              uVar4 = (uint)local_47 + (uint)local_48 * 0x100 & 0xffff;
              if (uVar4 == 0xffff) goto LAB_0003a6ec;
              chip_eeprom_read16(param_1,uVar4,&local_5a);
              sVar3 = strlen(__s_00);
              sprintf(__s_00 + sVar3,"[0x%04X]:0x%04X  ",uVar4,(uint)local_5a);
            }
          }
        } while( true );
      }
    }
    else {
      __memzero(__s_01,uVar4);
    }
    goto LAB_0003a2d4;
  }
LAB_0003a62c:
  __s_00[0] = '\n';
  __s_00[1] = '\0';
  if (local_4c + local_50 == 0) {
    local_4c = 0xe000;
    uVar4 = 0;
    local_50 = 0;
LAB_0003a678:
    do {
      sVar3 = strlen(__s_00);
      if (0x3fff < sVar3 + 0x11) goto LAB_0003a72c;
      chip_eeprom_read16(param_1,uVar4,&local_5a);
      sVar3 = strlen(__s_00);
      sprintf(__s_00 + sVar3,"[0x%04X]:%04X  ",uVar4,(uint)local_5a);
      if ((uVar4 & 6) == 6) {
        sVar3 = strlen(__s_00);
        (__s_00 + sVar3)[0] = '\n';
        (__s_00 + sVar3)[1] = '\0';
      }
      uVar4 = uVar4 + 2 & 0xffff;
    } while (uVar4 < local_4c);
  }
  else {
    uVar4 = local_50 & 0xffff;
    if (uVar4 < local_4c) goto LAB_0003a678;
  }
LAB_0003a6ec:
  sVar3 = strlen(__s_00);
  if (sVar3 == 1) {
    builtin_strncpy(__s_00 + 1,"===>Error command format!",0x1a);
  }
LAB_0003a72c:
  AP_E2PROM_IOCTL_PostCtrl(param_2,__s_00);
LAB_0003a2d4:
  os_free_mem(local_58);
  if ((*(short *)(param_2 + 0x16) != 0x525) && (2 < DebugLevel)) {
    printk("<==RTMPIoctlE2PROM\n");
  }
  return;
}

