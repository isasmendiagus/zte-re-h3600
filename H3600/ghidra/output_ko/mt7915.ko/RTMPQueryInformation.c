// module: mt7915.ko
// function: RTMPQueryInformation @ 0x5da78
// size: 12524 bytes
//

/* WARNING: Type propagation algorithm not settling */

uint RTMPQueryInformation(int *param_1,uint param_2,int param_3,int param_4)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  ushort uVar7;
  short sVar8;
  undefined1 uVar9;
  char cVar10;
  char cVar11;
  uint *puVar12;
  undefined4 uVar13;
  int iVar14;
  uint uVar15;
  uint extraout_r1;
  uint extraout_r1_00;
  uint extraout_r1_01;
  uint extraout_r1_02;
  undefined4 extraout_r1_03;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  uint *puVar20;
  uint *puVar21;
  int *piVar22;
  int iVar23;
  undefined8 uVar24;
  uint local_a8;
  uint local_a4;
  uint local_a0;
  uint local_9c;
  uint *local_94;
  uint local_90;
  uint local_8c;
  int local_88;
  int *local_84;
  int local_80;
  uint *local_7c;
  undefined4 *local_78;
  uint *local_74;
  uint *local_70;
  int local_6c;
  undefined4 local_68;
  uint local_64;
  uint local_60;
  undefined4 local_5c;
  uint *local_58;
  uint *local_54;
  undefined4 local_50;
  int *local_4c;
  char *local_48;
  undefined4 local_44;
  undefined4 local_40;
  
  iVar23 = *(int *)(*param_1 + 0x3c);
  local_78 = (undefined4 *)0x0;
  local_74 = (uint *)0x0;
  local_70 = (uint *)0x0;
  local_6c = 0;
  local_64 = 0;
  local_60 = 0;
  local_5c = 0;
  local_58 = (uint *)0x0;
  local_54 = (uint *)0x0;
  local_50 = 0;
  puVar12 = (uint *)get_scan_tab_by_wdev(param_1,param_4);
  uVar13 = HcGetBandByWdev(param_4);
  iVar14 = hc_get_channel_ctrl(param_1[0x29e5e8],uVar13);
  if (param_3 == 0x60d) {
LAB_0005fd58:
    uVar15 = *(uint *)(param_2 + 0x10);
    uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
    if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
      uVar16 = 0;
    }
    local_64 = (uint)(char)param_1[iVar23 * 0x84dec + 0x160348];
    *(undefined2 *)(param_2 + 0x14) = 4;
    if (uVar16 != 0) {
      return 4;
    }
    uVar15 = __copy_to_user(uVar15,&local_64);
    return uVar15;
  }
  if (param_3 < 0x60e) {
    if (param_3 == 0x511) {
      local_68 = SecAuthModeNewToOld(param_1[iVar23 * 0x84dec + 0xdb6e1]);
      uVar15 = *(uint *)(param_2 + 0x10);
      *(undefined2 *)(param_2 + 0x14) = 4;
      uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
      if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
        uVar16 = 0;
      }
      if (uVar16 == 0) {
        uVar15 = __copy_to_user(uVar15,&local_68);
      }
      else {
        uVar15 = 4;
      }
      if (2 < DebugLevel) {
        printk("Query::OID_802_11_AUTHENTICATION_MODE(=%d)\n",local_68);
        return uVar15;
      }
      return uVar15;
    }
    if (0x511 < param_3) {
      if (param_3 == 0x523) {
        cVar10 = RTMPMaxRssi(param_1,(int)(char)param_1[iVar23 * 0x84dec + 0x160349],
                             (int)*(char *)((int)param_1 + iVar23 * 0x2137b0 + 0x580d25),
                             (int)*(char *)((int)param_1 + iVar23 * 0x2137b0 + 0x580d26));
        cVar11 = RTMPMinSnr(param_1,(int)(char)param_1[iVar23 * 0x84dec + 0x16034d],
                            (int)*(char *)((int)param_1 + iVar23 * 0x2137b0 + 0x580d35));
        iVar14 = *(int *)(param_2 + 0x10);
        *(undefined2 *)(param_2 + 0x14) = 1;
        local_4c = (int *)CONCAT31(local_4c._1_3_,cVar10 - cVar11);
        uVar15 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
        if (iVar14 != -1 && iVar14 + 1U <= uVar15) {
          uVar15 = 0;
        }
        if (uVar15 == 0) {
          uVar15 = __copy_to_user(iVar14,&local_4c);
        }
        else {
          uVar15 = 1;
        }
        if (2 < DebugLevel) {
          printk("Query::RT_OID_802_11_QUERY_NOISE_LEVEL (=%d)\n",(uint)local_4c & 0xff);
          return uVar15;
        }
        return uVar15;
      }
      if (param_3 < 0x524) {
        if (param_3 == 0x515) {
          local_4c = (int *)wlan_operate_get_frag_thld(param_4);
          iVar14 = param_1[0x1e541a];
          *(undefined2 *)(param_2 + 0x14) = 4;
          if ((char)iVar14 == '\x01') {
            local_4c = (int *)0x0;
          }
          uVar15 = *(uint *)(param_2 + 0x10);
          uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
          if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
            uVar16 = 0;
          }
          if (uVar16 == 0) {
            uVar15 = __copy_to_user(uVar15,&local_4c);
          }
          else {
            uVar15 = 4;
          }
          if (2 < DebugLevel) {
            printk("Query::OID_802_11_FRAGMENTATION_THRESHOLD(=%d)\n",local_4c);
            return uVar15;
          }
          return uVar15;
        }
        if (param_3 < 0x516) {
          if (param_3 == 0x512) {
            local_4c = (int *)(uint)*(byte *)(param_1 + iVar23 * 0x84dec + 0xdc6ee);
            if (((local_4c != (int *)0x0) && (local_4c != (int *)0x1)) && (local_4c != (int *)0x3))
            {
              local_4c = (int *)0x2;
            }
            uVar15 = *(uint *)(param_2 + 0x10);
            *(undefined2 *)(param_2 + 0x14) = 4;
            uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
            if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
              uVar16 = 0;
            }
            if (uVar16 == 0) {
              uVar15 = __copy_to_user(uVar15,&local_4c);
            }
            else {
              uVar15 = 4;
            }
            if (2 < DebugLevel) {
              printk("Query::OID_802_11_INFRASTRUCTURE_MODE(=%d)\n",local_4c);
              return uVar15;
            }
            return uVar15;
          }
          if (param_3 == 0x514) {
            local_4c = (int *)wlan_operate_get_rts_len_thld(param_4);
            uVar15 = *(uint *)(param_2 + 0x10);
            *(undefined2 *)(param_2 + 0x14) = 4;
            uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
            if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
              uVar16 = 0;
            }
            if (uVar16 == 0) {
              uVar15 = __copy_to_user(uVar15,&local_4c);
            }
            else {
              uVar15 = 4;
            }
            if (2 < DebugLevel) {
              printk("Query::OID_802_11_RTS_THRESHOLD(=%d)\n",local_4c);
              return uVar15;
            }
            return uVar15;
          }
        }
        else {
          if (param_3 == 0x517) {
            uVar15 = *(uint *)(param_2 + 0x10);
            *(undefined2 *)(param_2 + 0x14) = 4;
            uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
            if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
              uVar16 = 0;
            }
            if (uVar16 == 0) {
              uVar15 = __copy_to_user(uVar15,(int)param_1 + 0x794cd7,4);
            }
            else {
              uVar15 = 4;
            }
            if (2 < DebugLevel) {
              printk("Query::OID_802_11_TX_POWER_LEVEL %x\n",
                     *(undefined1 *)((int)param_1 + 0x794cd7));
              return uVar15;
            }
            return uVar15;
          }
          if (param_3 < 0x517) {
            uVar15 = *(uint *)(param_2 + 0x10);
            uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
            if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
              uVar16 = 0;
            }
            local_4c = (int *)param_1[iVar23 * 0x84dec + 0x160001];
            *(undefined2 *)(param_2 + 0x14) = 4;
            if (uVar16 == 0) {
              uVar15 = __copy_to_user(uVar15,&local_4c);
            }
            else {
              uVar15 = 4;
            }
            if (2 < DebugLevel) {
              printk("Query::OID_802_11_POWER_MODE(=%d)\n",local_4c);
              return uVar15;
            }
            return uVar15;
          }
          if (param_3 == 0x521) {
            os_alloc_mem(param_1,&local_78,0x20);
            if (local_78 != (undefined4 *)0x0) {
              *local_78 = 0x20;
              local_78[1] = (uint)*(ushort *)(param_1 + 0x1e5314);
              local_78[2] = (uint)*(ushort *)((int)param_1 + iVar23 * 0x2137b0 + 0x371c0a);
              RTMP_MapChannelID2KHZ(*(undefined1 *)(param_4 + 0x1a),local_78 + 3);
              uVar16 = *(uint *)(param_2 + 0x10);
              *(undefined2 *)(param_2 + 0x14) = 0x20;
              uVar18 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
              uVar17 = uVar16 + 0x20;
              uVar15 = uVar17;
              if (uVar16 < 0xffffffe0) {
                uVar15 = uVar17 - (uVar18 + 1);
              }
              if (uVar16 < 0xffffffe0 && uVar17 <= uVar18) {
                uVar18 = 0;
              }
              if (uVar18 == 0) {
                uVar24 = __copy_to_user(uVar16,local_78,0x20);
              }
              else {
                uVar24 = CONCAT44(uVar15,0x20);
              }
              uVar13 = (undefined4)((ulonglong)uVar24 >> 0x20);
              if (2 < DebugLevel) {
                printk("Query::OID_802_11_CONFIGURATION(BeaconPeriod=%d,AtimW=%d,Channel=%d)\n",
                       local_78[1],local_78[2],*(undefined1 *)(param_4 + 0x1a));
                uVar13 = extraout_r1_03;
              }
              os_free_mem(local_78,uVar13);
              return (uint)uVar24;
            }
            if (DebugLevel < 3) {
              return 0xfffffff2;
            }
            printk("Query::OID_802_11_CONFIGURATION(mem alloc failed)\n");
            return 0xfffffff2;
          }
        }
LAB_0005fae4:
        if (DebugLevel < 3) {
          return 0xffffffa1;
        }
        printk("Query::unknown IOCTL\'s subcmd = 0x%08x\n",param_3);
        return 0xffffffa1;
      }
      if (param_3 != 0x609) {
        if (0x609 < param_3) {
          if (param_3 == 0x60b) {
            uVar15 = *(uint *)(param_2 + 0x10);
            iVar14 = param_1[0x1e52b9];
            *(undefined2 *)(param_2 + 0x14) = 4;
            local_4c = (int *)(uint)(iVar14 == 1);
            uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
            if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
              uVar16 = 0;
            }
            if (uVar16 != 0) {
              return 4;
            }
            uVar15 = __copy_to_user(uVar15,&local_4c);
            return uVar15;
          }
          if (0x60b < param_3) {
            os_alloc_mem(param_1,&local_74,0x14);
            puVar12 = local_74;
            if (local_74 == (uint *)0x0) {
              if (DebugLevel < 3) {
                return 0xfffffff2;
              }
              printk("Query::RT_OID_802_11_QUERY_LINK_STATUS(mem alloc failed)\n");
              return 0xfffffff2;
            }
            *local_74 = (uint)*(ushort *)(RateIdTo500Kbps + (uint)*(byte *)(param_1 + 0x1e5334) * 2)
            ;
            local_74[1] = param_1[iVar23 * 0x84dec + 0x15ffee];
            local_74[3] = param_1[0x28e795];
            local_74[2] = param_1[0x28e794];
            uVar15 = wlan_operate_get_cen_ch_1
                               ((undefined *)
                                ((int)param_1 + (int)(&DAT_0036db58 + iVar23 * 0x2137b0)));
            puVar12[4] = uVar15;
            *(undefined2 *)(param_2 + 0x14) = 0x14;
            uVar16 = *(uint *)(param_2 + 0x10);
            uVar15 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
            if (uVar16 < 0xffffffec && uVar16 + 0x14 <= uVar15) {
              uVar15 = 0;
            }
            if (uVar15 == 0) {
              uVar15 = __copy_to_user(uVar16);
            }
            else {
              uVar15 = 0x14;
            }
            os_free_mem(local_74);
            if (2 < DebugLevel) {
              printk("Query::RT_OID_802_11_QUERY_LINK_STATUS\n");
              return uVar15;
            }
            return uVar15;
          }
          uVar15 = *(uint *)(param_2 + 0x10);
          *(undefined2 *)(param_2 + 0x14) = 6;
          uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
          if (uVar15 < 0xfffffffa && uVar15 + 6 <= uVar16) {
            uVar16 = 0;
          }
          if (uVar16 != 0) {
            return 6;
          }
          uVar15 = __copy_to_user(uVar15,param_4 + 0x1b);
          return uVar15;
        }
        if (param_3 == 0x607) {
          uVar15 = *(uint *)(param_2 + 0x10);
          *(undefined2 *)(param_2 + 0x14) = 0x21;
          uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
          if (uVar15 < 0xffffffdf && uVar15 + 0x21 <= uVar16) {
            uVar16 = 0;
          }
          if (uVar16 != 0) {
            return 0x21;
          }
          uVar15 = __copy_to_user(uVar15,(int)param_1 + 0x794abb,0x21);
          return uVar15;
        }
        if (0x607 < param_3) {
          if (2 < DebugLevel) {
            printk("Query::RT_OID_VERSION_INFO\n");
          }
          uVar15 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
          uVar16 = *(uint *)(param_2 + 0x10);
          local_4c = (int *)0x2e312e37;
          if (uVar16 < 0xfffffff8 && uVar16 + 8 <= uVar15) {
            uVar15 = 0;
          }
          *(undefined2 *)(param_2 + 0x14) = 8;
          local_48 = "er fail!!\n";
          if (uVar15 == 0) {
            iVar14 = __copy_to_user(uVar16,&local_4c);
            if (iVar14 != 0) {
              return 0xfffffff2;
            }
            return 0;
          }
          return 0xfffffff2;
        }
        if (param_3 == 0x524) {
          uVar15 = *(uint *)(param_2 + 0x10);
          *(undefined2 *)(param_2 + 0x14) = 4;
          uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
          if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
            uVar16 = 0;
          }
          if (uVar16 == 0) {
            uVar15 = __copy_to_user(uVar15,param_1 + 0x28e7e9);
          }
          else {
            uVar15 = 4;
          }
          if (2 < DebugLevel) {
            printk("Query::RT_OID_802_11_EXTRA_INFO (=%ld)\n",param_1[0x28e7e9]);
            return uVar15;
          }
          return uVar15;
        }
        goto LAB_0005fae4;
      }
      if (2 < DebugLevel) {
        printk("Query::OID_802_11_BSSID_LIST (%d BSS returned)\n",*puVar12);
      }
      *(undefined1 *)((int)param_1 + iVar23 * 0x2137b0 + 0x580ccd) = 0;
      if (*puVar12 == 0) {
        os_alloc_mem(param_1,&local_58,0x104);
        if (local_58 == (uint *)0x0) {
          return 0xfffffff4;
        }
        iVar14 = 0x104;
      }
      else {
        iVar14 = 4;
        uVar15 = 0;
        do {
          uVar16 = uVar15 + 1 & 0xff;
          iVar14 = iVar14 + (ushort)puVar12[uVar15 * 0x2bd + 0x3d] + 0x80;
          uVar15 = uVar16;
        } while (uVar16 < *puVar12);
        iVar14 = iVar14 + 0x100;
        os_alloc_mem(param_1,&local_58,iVar14);
        if (local_58 == (uint *)0x0) {
          return 0xfffffff4;
        }
        if (iVar14 == 0) goto LAB_0005ee14;
      }
      local_7c = local_58;
      __memzero(local_58,iVar14);
LAB_0005ee14:
      *local_58 = *puVar12;
      local_7c = local_58;
      if (*puVar12 == 0) {
        uVar16 = 4;
        uVar15 = param_2;
      }
      else {
        local_88 = iVar23 * 0x85;
        local_94 = (uint *)(param_1 + 0xa5800);
        local_90 = 0;
        uVar16 = 4;
        puVar21 = local_58 + 1;
        local_8c = param_2;
        local_84 = param_1;
        local_80 = param_4;
        do {
          uVar17 = local_90;
          iVar14 = local_90 * 0xaf4;
          memmove(puVar21 + 1,(void *)((int)puVar12 + iVar14 + 0xe),6);
          if ((*(char *)((int)puVar12 + iVar14 + 0x8d) == '\x01') &&
             (*(char *)((int)local_84 + local_88 * 0x3ff0 + 0x57ffc1) == '\0')) {
            if (((*(uint *)(local_80 + 0x2c) & 0x12cf8) == 0) ||
               (*(char *)(local_80 + 0x888) == '\x01')) {
              *(undefined1 *)(puVar21 + 3) = 0;
              *(undefined1 *)((int)puVar21 + 0xd) = 0;
              *(undefined1 *)((int)puVar21 + 0xe) = 0;
              *(undefined1 *)((int)puVar21 + 0xf) = 0;
            }
            else {
              puVar21[3] = (uint)(byte)puVar12[uVar17 * 0x2bd + 0x27];
              memmove(puVar21 + 4,(void *)((int)puVar12 + iVar14 + 0x9d),
                      (uint)(byte)puVar12[uVar17 * 0x2bd + 0x27]);
            }
          }
          else {
            puVar21[3] = (uint)(byte)puVar12[uVar17 * 0x2bd + 0x27];
            memmove(puVar21 + 4,(void *)((int)puVar12 + uVar17 * 0xaf4 + 0x9d),
                    (uint)(byte)puVar12[uVar17 * 0x2bd + 0x27]);
          }
          iVar14 = uVar17 * 0xaf4;
          iVar23 = uVar17 * 0xaf4;
          puVar21[0xc] = (uint)(byte)puVar12[uVar17 * 0x2bd + 0x23];
          puVar21[0xd] = (int)*(char *)((int)puVar12 + iVar14 + 0x79) -
                         (int)*(char *)((int)local_94 + 0xe62);
          *(undefined1 *)((int)puVar21 + 0xb) = *(undefined1 *)((int)puVar12 + iVar14 + 0x8b);
          uVar15 = NetworkTypeInUseSanity(puVar12 + uVar17 * 0x2bd + 2);
          *(undefined1 *)((int)puVar21 + 0x3d) = 0;
          *(undefined1 *)((int)puVar21 + 0x3e) = 0;
          *(undefined1 *)((int)puVar21 + 0x3f) = 0;
          *(undefined1 *)(puVar21 + 0xf) = 0x20;
          puVar21[0xe] = uVar15;
          puVar21[0x10] = (uint)(ushort)puVar12[uVar17 * 0x2bd + 8];
          puVar21[0x11] = (uint)*(ushort *)((int)puVar12 + iVar14 + 0x1e);
          RTMP_MapChannelID2KHZ((char)puVar12[uVar17 * 0x2bd + 5],puVar21 + 0x12);
          uVar15 = puVar12[uVar17 * 0x2bd + 7];
          *(undefined1 *)((int)puVar21 + 0x5d) = 0;
          *(undefined1 *)((int)puVar21 + 0x5e) = 0;
          if ((char)uVar15 == '\x01') {
            *(undefined1 *)(puVar21 + 0x17) = 1;
          }
          else {
            *(undefined1 *)(puVar21 + 0x17) = 0;
          }
          *(undefined1 *)((int)puVar21 + 0x5f) = 0;
          memmove(puVar21 + 0x18,(void *)((int)puVar12 + iVar23 + 0x22),
                  (uint)*(byte *)((int)puVar12 + iVar23 + 0x2e));
          memmove((void *)((int)puVar21 + *(byte *)((int)puVar12 + iVar23 + 0x2e) + 0x60),
                  (void *)((int)puVar12 + iVar23 + 0x2f),
                  (uint)*(byte *)((int)puVar12 + iVar23 + 0x3b));
          uVar7 = (ushort)puVar12[uVar17 * 0x2bd + 0x3d];
          if (uVar7 == 0) {
            uVar9 = (undefined1)uVar7;
            *(undefined1 *)((int)puVar21 + 0x71) = uVar9;
            *(undefined1 *)((int)puVar21 + 0x72) = uVar9;
            *(undefined1 *)((int)puVar21 + 0x73) = uVar9;
            *(undefined1 *)(puVar21 + 0x1c) = 0xc;
            memmove(puVar21 + 0x1d,(void *)((int)puVar12 + iVar23 + 0xda),0xc);
            puVar20 = puVar21 + 0x20;
            uVar15 = (ushort)puVar12[uVar17 * 0x2bd + 0x3d] + 0x80;
          }
          else {
            puVar21[0x1c] = uVar7 + 0xc;
            memmove(puVar21 + 0x1d,(void *)((int)puVar12 + iVar23 + 0xda),0xc);
            memmove(puVar21 + 0x20,(void *)((int)puVar12 + iVar23 + 0xf6),
                    (uint)(ushort)puVar12[uVar17 * 0x2bd + 0x3d]);
            uVar15 = (ushort)puVar12[uVar17 * 0x2bd + 0x3d] + 0x80;
            puVar20 = (uint *)((int)puVar21 + uVar15);
          }
          *puVar21 = uVar15;
          uVar18 = RtmpOsWirelessExtVerGet();
          uVar15 = local_8c;
          if ((uVar18 < 0x11) && ((uint)*(ushort *)(local_8c + 0x14) <= uVar16 + *puVar21)) {
            *local_7c = local_90;
            break;
          }
          uVar16 = uVar16 + *puVar21 & 0xffff;
          local_90 = uVar17 + 1 & 0xff;
          puVar21 = puVar20;
        } while (local_90 < *puVar12);
      }
      uVar17 = RtmpOsWirelessExtVerGet();
      if ((0x10 < uVar17) && (*(ushort *)(uVar15 + 0x14) < uVar16)) {
        os_free_mem(local_7c);
        return 0xfffffff9;
      }
      *(short *)(uVar15 + 0x14) = (short)uVar16;
      uVar17 = *(uint *)(uVar15 + 0x10);
      uVar19 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
      uVar18 = uVar17 + uVar16;
      uVar15 = uVar18;
      if (!CARRY4(uVar17,uVar16)) {
        uVar15 = uVar18 - (uVar19 + 1);
      }
      uVar24 = CONCAT44(uVar15,uVar16);
      if (!CARRY4(uVar17,uVar16) && uVar18 <= uVar19) {
        uVar19 = 0;
      }
      if (uVar19 == 0) {
        uVar24 = __copy_to_user(uVar17,local_7c);
      }
      os_free_mem(local_7c,(int)((ulonglong)uVar24 >> 0x20));
      return (uint)uVar24;
    }
    if (param_3 == 0x507) {
      if (2 < DebugLevel) {
        printk("Query::RT_OID_802_11_COUNTRY_REGION\n");
      }
      *(undefined2 *)(param_2 + 0x14) = 4;
      uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
      uVar15 = *(uint *)(param_2 + 0x10);
      if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
        uVar16 = 0;
      }
      local_64 = (uint)*(ushort *)(param_1 + 0x1e5311);
      if (uVar16 != 0) {
        return 0xfffffff2;
      }
      iVar14 = __copy_to_user(uVar15,&local_64);
      goto joined_r0x00060134;
    }
    if (param_3 < 0x508) {
      if (param_3 == 0x107) {
        uVar15 = *(uint *)(param_2 + 0x10);
        uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
        cVar10 = *(char *)((int)param_1 + 0x296e62);
        if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
          uVar16 = 0;
        }
        iVar14 = param_1[iVar23 * 0x84dec + 0x160348];
        *(undefined2 *)(param_2 + 0x14) = 4;
        local_64 = (int)(char)iVar14 - (int)cVar10;
        if (uVar16 == 0) {
          uVar15 = __copy_to_user(uVar15,&local_64);
        }
        else {
          uVar15 = 4;
        }
        if (2 < DebugLevel) {
          printk("Query::OID_802_11_RSSI_TRIGGER(=%ld)\n",local_64);
          return uVar15;
        }
        return uVar15;
      }
      if (param_3 < 0x108) {
        if (param_3 == 0x103) {
          uVar15 = *(uint *)(param_2 + 0x10);
          if ((*(byte *)((int)param_1 + 0x296e6e) & 0xfffffffb) - 9 < 2 ||
              (*(byte *)((int)param_1 + 0x296e6e) - 2 & 0xfd) == 0) {
            local_4c = (int *)0x3;
            uVar18 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
            uVar13 = 0x10;
            local_40 = 2;
            uVar17 = uVar15 + 0x10;
            uVar16 = uVar17;
            if (uVar15 < 0xfffffff0) {
              uVar16 = uVar17 - (uVar18 + 1);
            }
            if (uVar15 < 0xfffffff0 && uVar17 <= uVar18) {
              uVar18 = 0;
            }
            *(undefined2 *)(param_2 + 0x14) = 0x10;
          }
          else {
            local_4c = (int *)0x2;
            uVar18 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
            uVar13 = 0xc;
            uVar17 = uVar15 + 0xc;
            uVar16 = uVar17;
            if (uVar15 < 0xfffffff4) {
              uVar16 = uVar17 - (uVar18 + 1);
            }
            if (uVar15 < 0xfffffff4 && uVar17 <= uVar18) {
              uVar18 = 0;
            }
            *(undefined2 *)(param_2 + 0x14) = 0xc;
          }
          uVar24 = CONCAT44(uVar16,uVar13);
          local_48 = (char *)0x1;
          local_44 = 3;
          if (uVar18 == 0) {
            local_44 = 3;
            local_48 = (char *)0x1;
            uVar24 = __copy_to_user(uVar15,&local_4c);
          }
          if (2 < DebugLevel) {
            printk("Query::OID_802_11_NETWORK_TYPES_SUPPORTED\n",(int)((ulonglong)uVar24 >> 0x20));
            return (uint)uVar24;
          }
          return (uint)uVar24;
        }
        if (param_3 == 0x104) {
          *(undefined2 *)(param_2 + 0x14) = 4;
          if (*(ushort *)(param_4 + 0x18) == 1) {
            local_64 = 2;
          }
          else if ((*(ushort *)(param_4 + 0x18) & 0xfffd) == 4) {
            local_64 = 3;
          }
          else {
            local_64 = 1;
          }
          uVar15 = *(uint *)(param_2 + 0x10);
          uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
          if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
            uVar16 = 0;
          }
          if (uVar16 != 0) {
            return 4;
          }
          uVar15 = __copy_to_user(uVar15,&local_64,4);
          return uVar15;
        }
      }
      else {
        if (param_3 == 0x109) {
          uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
          uVar15 = *(uint *)(param_2 + 0x10);
          if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
            uVar16 = 0;
          }
          local_64 = (uint)*(char *)((int)param_1 + iVar23 * 0x2137b0 + 0x580d21);
          *(undefined2 *)(param_2 + 0x14) = 4;
          if (uVar16 != 0) {
            return 4;
          }
          uVar15 = __copy_to_user(uVar15,&local_64,4);
          return uVar15;
        }
        if (param_3 < 0x109) goto LAB_0005fd58;
        if (param_3 == 0x10a) {
          uVar15 = *(uint *)(param_2 + 0x10);
          uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
          if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
            uVar16 = 0;
          }
          local_64 = (uint)*(char *)((int)param_1 + iVar23 * 0x2137b0 + 0x580d22);
          *(undefined2 *)(param_2 + 0x14) = 4;
          if (uVar16 != 0) {
            return 4;
          }
          uVar15 = __copy_to_user(uVar15,&local_64);
          return uVar15;
        }
      }
      goto LAB_0005fae4;
    }
    if (param_3 == 0x50c) {
      local_64 = (uint)*(ushort *)(param_4 + 0x18);
      uVar15 = *(uint *)(param_2 + 0x10);
      *(undefined2 *)(param_2 + 0x14) = 4;
      uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
      if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
        uVar16 = 0;
      }
      if (uVar16 == 0) {
        uVar15 = __copy_to_user(uVar15,&local_64);
      }
      else {
        uVar15 = 4;
      }
      if (2 < DebugLevel) {
        printk("Query::RT_OID_802_11_PHY_MODE (=%ld)\n",local_64);
        return uVar15;
      }
      return uVar15;
    }
    if (param_3 < 0x50d) {
      if (param_3 == 0x50a) {
        if (((param_1[iVar23 * 0x84dec + 0x15ffef] & 1U) == 0) && ((param_1[0x1e5449] & 2U) == 0)) {
          if (DebugLevel < 3) {
            return 0xffffff95;
          }
          printk("Query::OID_802_11_BSSID(=EMPTY)\n");
          return 0xffffff95;
        }
        uVar15 = *(uint *)(param_2 + 0x10);
        uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
        if (uVar15 < 0xfffffffa && uVar15 + 6 <= uVar16) {
          uVar16 = 0;
        }
        if (uVar16 != 0) {
          return 6;
        }
        uVar15 = __copy_to_user(uVar15,param_1 + iVar23 * 0x84dec + 0x15ffe0,6);
        return uVar15;
      }
      if (0x50a < param_3) {
        iVar14 = *(int *)(param_2 + 0x10);
        uVar15 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
        if (iVar14 != -1 && iVar14 + 1U <= uVar15) {
          uVar15 = 0;
        }
        iVar23 = param_1[iVar23 * 0x84dec + 0x160324];
        *(undefined2 *)(param_2 + 0x14) = 1;
        if (uVar15 != 0) {
          param_2 = 1;
        }
        local_4c = (int *)CONCAT31(local_4c._1_3_,(char)iVar23);
        if (uVar15 == 0) {
          param_2 = __copy_to_user(iVar14,&local_4c);
        }
        if (2 < DebugLevel) {
          printk("Query::RT_OID_802_11_QUERY_RADIO (=%d)\n",(uint)local_4c & 0xff);
          return param_2;
        }
        return param_2;
      }
      if (param_3 == 0x509) {
        __memzero(&local_4c,0x24);
        __memzero(&local_48,0x20);
        local_4c = (int *)(uint)*(byte *)((int)param_1 + iVar23 * 0x2137b0 + 0x57ff7e);
        memcpy(&local_48,(void *)((int)param_1 + iVar23 * 0x2137b0 + 0x57ff5e),(size_t)local_4c);
        uVar15 = *(uint *)(param_2 + 0x10);
        *(undefined2 *)(param_2 + 0x14) = 0x24;
        uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
        if (uVar15 < 0xffffffdc && uVar15 + 0x24 <= uVar16) {
          uVar16 = 0;
        }
        if (uVar16 == 0) {
          uVar15 = __copy_to_user(uVar15,&local_4c);
        }
        else {
          uVar15 = 0x24;
        }
        if (2 < DebugLevel) {
          printk("Query::OID_802_11_SSID (Len=%d, ssid=%s)\n",local_4c,&local_48);
          return uVar15;
        }
        return uVar15;
      }
      goto LAB_0005fae4;
    }
    if (param_3 == 0x50f) {
      uVar15 = *(uint *)(param_2 + 0x10);
      local_4c = (int *)param_1[0x1e5419];
      uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
      *(undefined2 *)(param_2 + 0x14) = 4;
      if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
        uVar16 = 0;
      }
      if (uVar16 == 0) {
        uVar15 = __copy_to_user(uVar15,&local_4c,4);
      }
      else {
        uVar15 = 4;
      }
      if (2 < DebugLevel) {
        printk("Query::RT_OID_802_11_PREAMBLE(=%d)\n",local_4c);
        return uVar15;
      }
      return uVar15;
    }
    if (0x50f < param_3) {
      local_68 = SecEncryModeNewToOld(param_1[iVar23 * 0x84dec + 0xdb733]);
      uVar15 = *(uint *)(param_2 + 0x10);
      *(undefined2 *)(param_2 + 0x14) = 4;
      uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
      if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
        uVar16 = 0;
      }
      if (uVar16 == 0) {
        uVar15 = __copy_to_user(uVar15,&local_4c);
      }
      else {
        uVar15 = 4;
      }
      if (2 < DebugLevel) {
        printk("Query::OID_802_11_WEP_STATUS(=%d)\n",local_4c);
        return uVar15;
      }
      return uVar15;
    }
    if (param_3 != 0x50d) goto LAB_0005fae4;
    os_alloc_mem(param_1,&local_70,0x20);
    if (local_70 != (uint *)0x0) {
      if (2 < DebugLevel) {
        printk("Query::RT_OID_802_11_STA_CONFIG\n");
      }
      *local_70 = (uint)*(byte *)((int)param_1 + 0x795071);
      local_70[1] = 0;
      local_70[2] = param_1[0x1e541b];
      local_70[3] = (uint)*(byte *)(param_1 + 0x1e541c);
      cVar10 = *(char *)((int)param_1 + iVar23 * 0x2137b0 + 0x580c91);
      local_70[6] = 0;
      local_70[5] = (uint)(cVar10 == '\x01');
      local_70[7] = param_1[0x28e7ea];
      uVar15 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
      if (*(uint *)(param_2 + 0x10) < 0xffffffe0 && *(uint *)(param_2 + 0x10) + 0x20 <= uVar15) {
        uVar15 = 0;
      }
      *(undefined2 *)(param_2 + 0x14) = 0x20;
      if (uVar15 == 0) {
        uVar15 = __copy_to_user();
      }
      else {
        uVar15 = 0x20;
      }
      os_free_mem(local_70);
      return uVar15;
    }
    if (DebugLevel < 3) {
      return 0xfffffff2;
    }
    goto LAB_0005ffac;
  }
  if (param_3 == 0x63e) {
    iVar14 = *(int *)(param_2 + 0x10);
    *(undefined2 *)(param_2 + 0x14) = 1;
    uVar15 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
    if (iVar14 != -1 && iVar14 + 1U <= uVar15) {
      uVar15 = 0;
    }
    if (uVar15 == 0) {
      uVar15 = __copy_to_user(iVar14,param_4 + 0x8d4);
    }
    else {
      uVar15 = 1;
    }
    if (2 < DebugLevel) {
      printk("Query::RT_OID_802_11_QUERY_WMM (=%d)\n",*(undefined1 *)(param_4 + 0x8d4));
      return uVar15;
    }
    return uVar15;
  }
  if (param_3 < 0x63f) {
    if (param_3 == 0x614) {
      uVar15 = *(uint *)(param_2 + 0x10);
      *(undefined2 *)(param_2 + 0x14) = 4;
      uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
      if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
        uVar16 = 0;
      }
      if (uVar16 == 0) {
        __copy_to_user(uVar15,param_1 + 0x1e5336);
      }
      if (DebugLevel < 3) {
        uVar15 = *(uint *)(param_2 + 0x10);
        uVar16 = (uint)*(ushort *)(param_2 + 0x14);
        uVar17 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
        if (!CARRY4(uVar15,uVar16) && uVar15 + uVar16 <= uVar17) {
          uVar17 = 0;
        }
        if (uVar17 != 0) {
          return uVar16;
        }
      }
      else {
        printk("Query::RT_OID_802_11_TX_POWER_LEVEL_1 (BAND0) (=%d)\n",(char)param_1[0x1e5336]);
        uVar15 = *(uint *)(param_2 + 0x10);
        uVar16 = (uint)*(ushort *)(param_2 + 0x14);
        uVar17 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
        if (!CARRY4(uVar15,uVar16) && uVar15 + uVar16 <= uVar17) {
          uVar17 = 0;
        }
        if (uVar17 != 0) goto LAB_00060428;
      }
      uVar16 = __copy_to_user(uVar15,(int)param_1 + 0x794cd9);
LAB_00060428:
      if (2 < DebugLevel) {
        printk("Query::RT_OID_802_11_TX_POWER_LEVEL_1 (BAND1) (=%d)\n",
               *(undefined1 *)((int)param_1 + 0x794cd9));
      }
      return uVar16;
    }
    if (param_3 < 0x615) {
      if (param_3 == 0x610) {
        local_64 = param_1[0x28e6fd];
        uVar15 = *(uint *)(param_2 + 0x10);
        uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
        if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
          uVar16 = 0;
        }
        *(undefined2 *)(param_2 + 0x14) = 4;
        if (uVar16 != 0) {
          return 4;
        }
        uVar15 = __copy_to_user(uVar15,&local_64);
        return uVar15;
      }
      if (0x610 < param_3) {
        if (param_3 == 0x612) {
          uVar15 = *(uint *)(param_2 + 0x10);
          *(undefined2 *)(param_2 + 0x14) = 4;
          uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
          if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
            uVar16 = 0;
          }
          if (uVar16 != 0) {
            return 4;
          }
          uVar15 = __copy_to_user(uVar15,param_1 + 0xa5b2e,4);
          return uVar15;
        }
        if (0x612 < param_3) {
          local_64 = param_1[0x28e7e6];
          uVar15 = *(uint *)(param_2 + 0x10);
          uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
          if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
            uVar16 = 0;
          }
          *(undefined2 *)(param_2 + 0x14) = 4;
          if (uVar16 == 0) {
            uVar15 = __copy_to_user(uVar15,&local_64);
          }
          else {
            uVar15 = 4;
          }
          if (2 < DebugLevel) {
            printk("Query::RT_OID_802_11_QUERY_LAST_RX_RATE (=%ld)\n",local_64);
            return uVar15;
          }
          return uVar15;
        }
        uVar15 = *(uint *)(param_2 + 0x10);
        *(undefined2 *)(param_2 + 0x14) = 4;
        uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
        if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
          uVar16 = 0;
        }
        if (uVar16 != 0) {
          return 4;
        }
        uVar15 = __copy_to_user(uVar15,param_1 + 0xa5b2d);
        return uVar15;
      }
      if (param_3 == 0x60e) {
        os_alloc_mem(param_1,&local_6c,0xc0);
        if (local_6c != 0) {
          if (2 < DebugLevel) {
            printk("Query::OID_802_11_STATISTICS\n");
          }
          NICUpdateRawCountersNew(param_1);
          local_94 = (uint *)(param_1 + 0x28e700);
          uVar15 = *local_94;
          iVar14 = param_1[0x28e701];
          uVar16 = param_1[0x28e706];
          iVar23 = param_1[0x28e707];
          if ((int)(iVar14 - (iVar23 + (uint)(uVar15 < uVar16))) < 0 !=
              (SBORROW4(iVar14,iVar23) != SBORROW4(iVar14 - iVar23,(uint)(uVar15 < uVar16)))) {
            *local_94 = uVar16;
            param_1[0x28e701] = iVar23;
            iVar14 = iVar23;
            uVar15 = uVar16;
          }
          uVar16 = param_1[0x28e702];
          iVar23 = param_1[0x28e703];
          *(uint *)(local_6c + 8) = uVar16 + uVar15;
          *(uint *)(local_6c + 0xc) = iVar23 + iVar14 + (uint)CARRY4(uVar16,uVar15);
          iVar14 = param_1[0x28e703];
          local_90 = 0xa39c30;
          *(int *)(local_6c + 0x10) = param_1[0x28e702];
          *(int *)(local_6c + 0x14) = iVar14;
          iVar14 = param_1[0x28e705];
          *(int *)(local_6c + 0x18) = param_1[0x28e704];
          *(int *)(local_6c + 0x1c) = iVar14;
          iVar14 = param_1[0x28e707];
          *(int *)(local_6c + 0x20) = param_1[0x28e706];
          *(int *)(local_6c + 0x24) = iVar14;
          iVar14 = param_1[0x28e709];
          *(int *)(local_6c + 0x28) = param_1[0x28e708];
          *(int *)(local_6c + 0x2c) = iVar14;
          iVar14 = param_1[0x28e70b];
          *(int *)(local_6c + 0x30) = param_1[0x28e70a];
          *(int *)(local_6c + 0x34) = iVar14;
          iVar14 = param_1[0x28e70d];
          *(int *)(local_6c + 0x38) = param_1[0x28e70c];
          *(int *)(local_6c + 0x3c) = iVar14;
          iVar14 = param_1[0x28e70f];
          *(int *)(local_6c + 0x40) = param_1[0x28e70e];
          *(int *)(local_6c + 0x44) = iVar14;
          iVar14 = param_1[0x28e711];
          *(int *)(local_6c + 0x48) = param_1[0x28e710];
          *(int *)(local_6c + 0x4c) = iVar14;
          iVar14 = param_1[0x28e713];
          *(int *)(local_6c + 0x50) = param_1[0x28e712];
          *(int *)(local_6c + 0x54) = iVar14;
          iVar14 = param_1[0x28e715];
          *(int *)(local_6c + 0x58) = param_1[0x28e714];
          *(int *)(local_6c + 0x5c) = iVar14;
          iVar14 = param_1[0x28e79d];
          *(int *)(local_6c + 0x60) = param_1[0x28e79c];
          *(int *)(local_6c + 100) = iVar14;
          iVar14 = param_1[0x28e701];
          *(uint *)(local_6c + 0x68) = *local_94;
          *(int *)(local_6c + 0x6c) = iVar14;
          iVar14 = param_1[0x28e71b];
          *(int *)(local_6c + 0x70) = param_1[0x28e71a];
          *(int *)(local_6c + 0x74) = iVar14;
          uVar15 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
          if (*(uint *)(param_2 + 0x10) < 0xffffff40 && *(uint *)(param_2 + 0x10) + 0xc0 <= uVar15)
          {
            uVar15 = 0;
          }
          *(undefined2 *)(param_2 + 0x14) = 0xc0;
          if (uVar15 == 0) {
            uVar15 = __copy_to_user();
          }
          else {
            uVar15 = 0xc0;
          }
          os_free_mem(local_6c);
          return uVar15;
        }
        if (DebugLevel < 3) {
          return 0xfffffff2;
        }
        printk("Query::OID_802_11_STATISTICS(mem alloc failed)\n");
        return 0xfffffff2;
      }
      if (param_3 == 0x60f) {
        local_64 = param_1[0x28e6fa];
        uVar15 = *(uint *)(param_2 + 0x10);
        uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
        if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
          uVar16 = 0;
        }
        *(undefined2 *)(param_2 + 0x14) = 4;
        if (uVar16 != 0) {
          return 4;
        }
        uVar15 = __copy_to_user(uVar15,&local_64);
        return uVar15;
      }
      goto LAB_0005fae4;
    }
    if (param_3 == 0x632) {
      local_64 = param_1[0x28e7e7];
      uVar15 = *(uint *)(param_2 + 0x10);
      uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
      if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
        uVar16 = 0;
      }
      *(undefined2 *)(param_2 + 0x14) = 4;
      if (uVar16 == 0) {
        uVar15 = __copy_to_user(uVar15,&local_64);
      }
      else {
        uVar15 = 4;
      }
      if (2 < DebugLevel) {
        printk("Query::RT_OID_802_11_QUERY_LAST_TX_RATE (=%lx)\n",local_64);
        return uVar15;
      }
      return uVar15;
    }
    if (param_3 < 0x633) {
      if (param_3 == 0x630) {
        if ((char)param_1[iVar23 * 0x84dec + 0xdb918] == '\0') {
          return 0xfffffff2;
        }
        local_64 = ConvertToSnr(param_1);
        uVar15 = *(uint *)(param_2 + 0x10);
        *(undefined2 *)(param_2 + 0x14) = 4;
        uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
        if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
          uVar16 = 0;
        }
        if (uVar16 == 0) {
          uVar15 = __copy_to_user(uVar15,&local_64);
        }
        else {
          uVar15 = 4;
        }
        if (2 < DebugLevel) {
          printk("Query::RT_OID_802_11_SNR_0(0x=%lx)\n",local_64);
          return uVar15;
        }
        return uVar15;
      }
      if (0x630 < param_3) {
        if (((*(byte *)(param_1 + 0xa5b73) & 0xf) < 2) ||
           (*(char *)((int)param_1 + iVar23 * 0x2137b0 + 0x36e461) == '\0')) {
          uVar15 = 0xfffffff2;
        }
        else {
          local_64 = ConvertToSnr(param_1);
          uVar15 = *(uint *)(param_2 + 0x10);
          *(undefined2 *)(param_2 + 0x14) = 4;
          uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
          if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
            uVar16 = 0;
          }
          if (uVar16 == 0) {
            uVar15 = __copy_to_user(uVar15,&local_64);
          }
          else {
            uVar15 = 4;
          }
          if (DebugLevel < 3) {
            return uVar15;
          }
          printk("Query::RT_OID_802_11_SNR_1(0x=%lx)\n",local_64);
        }
        if (2 < DebugLevel) {
          printk("Query::RT_OID_802_11_SNR_1(pStaCfg->LastSNR1=%d)\n",
                 *(undefined1 *)((int)param_1 + iVar23 * 0x2137b0 + 0x36e461));
          return uVar15;
        }
        return uVar15;
      }
      if (param_3 == 0x622) {
        *(undefined2 *)(param_2 + 0x14) = 4;
        local_4c = (int *)RtmpOsWirelessExtVerGet();
        uVar15 = *(uint *)(param_2 + 0x10);
        uVar16 = (uint)*(ushort *)(param_2 + 0x14);
        uVar17 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
        if (!CARRY4(uVar15,uVar16) && uVar15 + uVar16 <= uVar17) {
          uVar17 = 0;
        }
        if (uVar17 == 0) {
          uVar15 = __copy_to_user(uVar15,&local_4c);
          return uVar15;
        }
        return uVar16;
      }
      goto LAB_0005fae4;
    }
    if (param_3 == 0x636) {
      bVar1 = *(byte *)(param_1 + 0x1e532a);
      bVar2 = *(byte *)((int)param_1 + 0x794ca7);
      bVar3 = *(byte *)((int)param_1 + 0x794ca9);
      bVar4 = *(byte *)(param_1 + iVar23 * 0x84dec + 0xdb90c);
      uVar15 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
      bVar5 = *(byte *)((int)param_1 + 0x794caa);
      bVar6 = *(byte *)(param_1 + 0x1e5331);
      uVar16 = *(uint *)(param_2 + 0x10);
      *(undefined2 *)(param_2 + 0x14) = 4;
      if (uVar16 < 0xfffffffc && uVar16 + 4 <= uVar15) {
        uVar15 = 0;
      }
      local_60 = (uint)bVar1 << 2 | (uint)bVar2 << 1 | (uint)bVar4 | (uint)bVar3 << 3 |
                 (uint)bVar5 << 4 | (uint)bVar6 << 5;
      if (uVar15 == 0) {
        uVar15 = __copy_to_user(uVar16,&local_60,4);
      }
      else {
        uVar15 = 4;
      }
      if (2 < DebugLevel) {
        local_9c = (uint)*(byte *)(param_1 + 0x1e5331);
        local_a8 = (uint)*(byte *)(param_1 + 0x1e532a);
        local_a4 = (uint)*(byte *)((int)param_1 + 0x794ca9);
        local_a0 = (uint)*(byte *)((int)param_1 + 0x794caa);
        printk("Query::RT_OID_802_11_QUERY_APSD_SETTING (=0x%lx,APSDCap=%d,AC_BE=%d,AC_BK=%d,AC_VI=%d,AC_VO=%d,MAXSPLen=%d)\n"
               ,local_60,(char)param_1[iVar23 * 0x84dec + 0xdb90c],
               *(undefined1 *)((int)param_1 + 0x794ca7));
        return uVar15;
      }
      return uVar15;
    }
    if (param_3 == 0x638) {
      uVar15 = *(uint *)(param_2 + 0x10);
      *(undefined2 *)(param_2 + 0x14) = 4;
      uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
      if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
        uVar16 = 0;
      }
      if (uVar16 == 0) {
        uVar15 = __copy_to_user(uVar15,(int)param_1 + 0x794cc6);
      }
      else {
        uVar15 = 4;
      }
      if (2 < DebugLevel) {
        printk("Query::RT_OID_802_11_QUERY_APSD_PSM (=%d)\n",
               *(undefined1 *)((int)param_1 + 0x794cc6));
        return uVar15;
      }
      return uVar15;
    }
    if (param_3 != 0x633) goto LAB_0005fae4;
    os_alloc_mem(param_1,&local_54,0x10);
    puVar12 = local_54;
    if (local_54 != (uint *)0x0) {
      *local_54 = (uint)*(ushort *)(param_4 + 0x18);
      *(byte *)((int)local_54 + 5) = *(byte *)((int)param_1 + 0xa329d) >> 5;
      *(byte *)(local_54 + 2) = (byte)(((uint)*(ushort *)(param_1 + 0x28ca7) << 0x17) >> 0x1e);
      *(byte *)((int)local_54 + 7) = (byte)(((uint)*(byte *)(param_1 + 0x28ca7) << 0x1a) >> 0x1a);
      *(byte *)((int)local_54 + 10) =
           (byte)(((uint)*(byte *)((int)param_1 + 0xa329d) << 0x1e) >> 0x1f);
      *(byte *)((int)local_54 + 9) =
           (byte)(((uint)*(byte *)((int)param_1 + 0xa329d) << 0x1d) >> 0x1f);
      uVar9 = wlan_operate_get_ext_cha(param_1 + iVar23 * 0x84dec + 0xdb6d6);
      *(undefined1 *)((int)puVar12 + 6) = uVar9;
      *(undefined2 *)(param_2 + 0x14) = 0x10;
      uVar16 = *(uint *)(param_2 + 0x10);
      uVar18 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
      uVar17 = uVar16 + 0x10;
      uVar15 = uVar17;
      if (uVar16 < 0xfffffff0) {
        uVar15 = uVar17 - (uVar18 + 1);
      }
      if (uVar16 < 0xfffffff0 && uVar17 <= uVar18) {
        uVar18 = 0;
      }
      if (uVar18 == 0) {
        uVar24 = __copy_to_user(uVar16,local_54);
        uVar15 = (uint)((ulonglong)uVar24 >> 0x20);
        if ((int)uVar24 == 0) {
          uVar16 = 0;
        }
        else {
          uVar16 = 0xfffffff2;
        }
      }
      else {
        uVar16 = 0xfffffff2;
      }
      if (2 < DebugLevel) {
        local_a8 = (uint)*(byte *)((int)local_54 + 9);
        local_a4 = (uint)*(byte *)((int)local_54 + 6);
        printk("Query::RT_OID_802_11_QUERY_HT_PHYMODE (PhyMode = %d, MCS =%d, BW = %d, STBC = %d, ExtOffset=%d)\n"
               ,*(undefined1 *)((int)local_54 + 5),*(undefined1 *)((int)local_54 + 7),
               (char)local_54[2]);
        uVar15 = extraout_r1;
        if (2 < DebugLevel) {
          printk(" %s(): (.word = %x )\n","RTMPQueryInformation",(short)param_1[0x28ca7]);
          uVar15 = extraout_r1_00;
        }
      }
      os_free_mem(local_54,uVar15);
      return uVar16;
    }
  }
  else {
    if (param_3 == 0x715) {
      local_94 = (uint *)iVar14;
      if (2 < DebugLevel) {
        printk("Query::OID_802_11_GET_CH_LIST\n");
      }
      if ((*(char *)((int)param_1 + 0x2977ee) == '\0') ||
         (os_alloc_mem(param_1,&local_4c,0x3c), local_4c == (int *)0x0)) {
        *(undefined2 *)(param_2 + 0x14) = 0;
        return 0;
      }
      cVar10 = *(char *)((int)local_94 + 0x49c);
      *(char *)((int)local_4c + 0x3b) = cVar10;
      if (cVar10 != '\0') {
        uVar15 = 0;
        do {
          *(undefined1 *)((int)local_4c + uVar15) = *(undefined1 *)((int)local_94 + uVar15 * 0x14);
          uVar15 = uVar15 + 1 & 0xff;
        } while (uVar15 < *(byte *)((int)local_4c + 0x3b));
      }
      *(undefined2 *)(param_2 + 0x14) = 0x3c;
      uVar15 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
      if (*(uint *)(param_2 + 0x10) < 0xffffffc4 && *(uint *)(param_2 + 0x10) + 0x3c <= uVar15) {
        uVar15 = 0;
      }
      if (uVar15 == 0) {
        uVar15 = __copy_to_user();
      }
      else {
        uVar15 = 0x3c;
      }
      if (2 < DebugLevel) {
        printk("Status=%d\n",uVar15);
      }
      if (local_4c != (int *)0x0) {
        os_free_mem();
        return uVar15;
      }
      return uVar15;
    }
    if (0x715 < param_3) {
      if (param_3 == 0x751) {
        uVar15 = *(uint *)(param_2 + 0x10);
        *(undefined2 *)(param_2 + 0x14) = 4;
        uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
        if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
          uVar16 = 0;
        }
        if (uVar16 == 0) {
          iVar14 = __copy_to_user(uVar15,param_4 + 0x12f0);
          if (iVar14 == 0) {
            uVar15 = 0;
          }
          else {
            uVar15 = 0xfffffff2;
          }
        }
        else {
          uVar15 = 0xfffffff2;
        }
        if (2 < DebugLevel) {
          printk("Query::RT_OID_WSC_QUERY_STATUS (=%d)\n",*(undefined4 *)(param_4 + 0x12f0));
          return uVar15;
        }
        return uVar15;
      }
      if (0x751 < param_3) {
        if (param_3 == 0x753) {
          if (2 < DebugLevel) {
            printk("Query::RT_OID_WSC_QUERY_UUID\n");
          }
          uVar15 = *(uint *)(param_2 + 0x10);
          *(undefined2 *)(param_2 + 0x14) = 0x25;
          uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
          if (uVar15 < 0xffffffdb && uVar15 + 0x25 <= uVar16) {
            uVar16 = 0;
          }
          if (uVar16 != 0) {
            return 0xfffffff2;
          }
          iVar14 = __copy_to_user(uVar15,param_4 + 0x3d18);
        }
        else {
          if (param_3 < 0x753) {
            *(undefined2 *)(param_2 + 0x14) = 4;
            local_50 = *(undefined4 *)(param_4 + 0x1300);
            uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
            uVar15 = *(uint *)(param_2 + 0x10);
            if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
              uVar16 = 0;
            }
            if (uVar16 == 0) {
              iVar14 = __copy_to_user(uVar15,&local_50);
              if (iVar14 == 0) {
                uVar15 = 0;
              }
              else {
                uVar15 = 0xfffffff2;
              }
            }
            else {
              uVar15 = 0xfffffff2;
            }
            if (2 < DebugLevel) {
              printk("Query::RT_OID_WSC_PIN_CODE (=%d)\n",local_50);
              return uVar15;
            }
            return uVar15;
          }
          if (param_3 != 0x760) goto LAB_0005fae4;
          if (2 < DebugLevel) {
            printk("Query::RT_OID_WSC_MAC_ADDRESS\n");
          }
          uVar15 = *(uint *)(param_2 + 0x10);
          *(undefined2 *)(param_2 + 0x14) = 6;
          uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
          if (uVar15 < 0xfffffffa && uVar15 + 6 <= uVar16) {
            uVar16 = 0;
          }
          if (uVar16 != 0) {
            return 0xfffffff2;
          }
          iVar14 = __copy_to_user(uVar15,param_4 + 0x1b);
        }
joined_r0x00060134:
        if (iVar14 != 0) {
          return 0xfffffff2;
        }
        return 0;
      }
      if (param_3 != 0x742) {
        if (param_3 != 0x750) {
          if (param_3 == 0x716) {
            if (2 < DebugLevel) {
              printk("Query::OID_802_11_GET_COUNTRY_CODE\n");
            }
            uVar15 = *(uint *)(param_2 + 0x10);
            *(undefined2 *)(param_2 + 0x14) = 2;
            uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
            if (uVar15 < 0xfffffffe && uVar15 + 2 <= uVar16) {
              uVar16 = 0;
            }
            if (uVar16 == 0) {
              uVar15 = __copy_to_user(uVar15,(int)param_1 + 0x794c31);
            }
            else {
              uVar15 = 2;
            }
            if (2 < DebugLevel) {
              printk("Status=%d\n",uVar15);
              return uVar15;
            }
            return uVar15;
          }
          goto LAB_0005fae4;
        }
        *(undefined2 *)(param_2 + 0x14) = 0x3a8;
        os_alloc_mem(param_1,&local_4c,0x3a8);
        if (local_4c == (int *)0x0) {
          if (DebugLevel < 3) {
            return 0xfffffff2;
          }
          printk("RT_OID_802_11_WSC_QUERY_PROFILE fail!\n");
          return 0xfffffff2;
        }
        RTMPZeroMemory(local_4c,0x3a8);
        memmove(local_4c,(void *)(param_4 + 0x2f74),0x3a8);
        if (local_4c[0xb] == 0x10001) {
          *(undefined2 *)(local_4c + 0x1c) = 0;
          __memzero(local_4c + 0xc,0x40);
        }
        uVar15 = *(uint *)(param_2 + 0x10);
        uVar16 = (uint)*(ushort *)(param_2 + 0x14);
        uVar17 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
        if (!CARRY4(uVar15,uVar16) && uVar15 + uVar16 <= uVar17) {
          uVar17 = 0;
        }
        if (uVar17 == 0) {
          uVar16 = __copy_to_user(uVar15,local_4c);
        }
        if (uVar16 != 0) {
          uVar15 = 0xfffffff2;
          goto LAB_0005f590;
        }
        if (DebugLevel < 3) {
LAB_0005f548:
          sVar8 = *(short *)((int)local_4c + 0x2e);
          if (sVar8 != 2) {
LAB_0005f55c:
            iVar14 = DebugLevel;
            if ((sVar8 - 4U & 0xfffb) == 0) {
              if (2 < DebugLevel) {
                printk("PassPhrase Key = %s\n",local_4c + 0xc);
              }
              iVar14 = DebugLevel;
              *(undefined1 *)(local_4c + 0x1e) = 1;
            }
            goto LAB_0005f580;
          }
        }
        else {
          printk("WSC Profile:\n");
          if (2 < DebugLevel) {
            printk("SSID = %s\n",local_4c + 3);
            if (2 < DebugLevel) {
              uVar13 = WscGetAuthTypeStr((short)local_4c[0xb]);
              printk("AuthType = %s\n",uVar13);
              if (2 < DebugLevel) {
                uVar13 = WscGetEncryTypeStr(*(undefined2 *)((int)local_4c + 0x2e));
                printk("EncrpType = %s\n",uVar13);
                goto LAB_00060908;
              }
            }
            goto LAB_0005f548;
          }
LAB_00060908:
          sVar8 = *(short *)((int)local_4c + 0x2e);
          if (sVar8 != 2) goto LAB_0005f55c;
          if ((DebugLevel < 3) || (printk("WEP Key = %s\n",local_4c + 0xc), DebugLevel < 3))
          goto LAB_0005f58c;
          printk("DefaultKey ID = %d\n",(char)local_4c[0x1e]);
          iVar14 = DebugLevel;
LAB_0005f580:
          if (2 < iVar14) {
            uVar15 = 0;
            printk(&_LC52);
            goto LAB_0005f590;
          }
        }
LAB_0005f58c:
        uVar15 = 0;
LAB_0005f590:
        os_free_mem(local_4c);
        if (2 < DebugLevel) {
          printk("Query::RT_OID_802_11_WSC_QUERY_PROFILE\n");
          return uVar15;
        }
        return uVar15;
      }
      *(undefined2 *)(param_2 + 0x14) = 0x3a8;
      os_alloc_mem(param_1,&local_4c);
      if (local_4c == (int *)0x0) {
        if (DebugLevel < 3) {
          return 0xfffffff2;
        }
        printk("RT_OID_WSC_QUERY_DEFAULT_PROFILE fail!\n");
        return 0xfffffff2;
      }
      RTMPZeroMemory(local_4c,0x3a8);
      WscCreateProfileFromCfg(param_1,2,param_4 + 0x12e4,local_4c);
      uVar15 = *(uint *)(param_2 + 0x10);
      uVar16 = (uint)*(ushort *)(param_2 + 0x14);
      uVar17 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
      if (!CARRY4(uVar15,uVar16) && uVar15 + uVar16 <= uVar17) {
        uVar17 = 0;
      }
      if (uVar17 == 0) {
        uVar16 = __copy_to_user(uVar15,local_4c);
      }
      if (uVar16 != 0) {
        uVar15 = 0xfffffff2;
        goto LAB_0005ea80;
      }
      if (DebugLevel < 3) {
LAB_0005ea38:
        sVar8 = *(short *)((int)local_4c + 0x2e);
        if (sVar8 != 2) {
LAB_0005ea4c:
          iVar14 = DebugLevel;
          if ((sVar8 - 4U & 0xfffb) == 0) {
            if (2 < DebugLevel) {
              printk("PassPhrase Key = %s\n",local_4c + 0xc);
            }
            iVar14 = DebugLevel;
            *(undefined1 *)(local_4c + 0x1e) = 1;
          }
          goto LAB_0005ea70;
        }
      }
      else {
        printk("WSC Profile:\n");
        if (2 < DebugLevel) {
          printk("SSID = %s\n",local_4c + 3);
          if (2 < DebugLevel) {
            uVar13 = WscGetAuthTypeStr((short)local_4c[0xb]);
            printk("AuthType = %s\n",uVar13);
            if (2 < DebugLevel) {
              uVar13 = WscGetEncryTypeStr(*(undefined2 *)((int)local_4c + 0x2e));
              printk("EncrpType = %s\n",uVar13);
              goto LAB_00060808;
            }
          }
          goto LAB_0005ea38;
        }
LAB_00060808:
        sVar8 = *(short *)((int)local_4c + 0x2e);
        if (sVar8 != 2) goto LAB_0005ea4c;
        if ((DebugLevel < 3) || (printk("WEP Key = %s\n",local_4c + 0xc), DebugLevel < 3))
        goto LAB_0005ea7c;
        printk("DefaultKey ID = %d\n",(char)local_4c[0x1e]);
        iVar14 = DebugLevel;
LAB_0005ea70:
        if (2 < iVar14) {
          uVar15 = 0;
          printk(&_LC52);
          goto LAB_0005ea80;
        }
      }
LAB_0005ea7c:
      uVar15 = 0;
LAB_0005ea80:
      os_free_mem(local_4c);
      if (2 < DebugLevel) {
        printk("Query::RT_OID_WSC_QUERY_DEFAULT_PROFILE\n");
        return uVar15;
      }
      return uVar15;
    }
    if (param_3 == 0x678) {
      local_5c = 0;
      getRate(param_1[0x28e7e7],&local_5c);
      uVar15 = *(uint *)(param_2 + 0x10);
      *(undefined2 *)(param_2 + 0x14) = 4;
      uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
      if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
        uVar16 = 0;
      }
      if (uVar16 == 0) {
        uVar15 = __copy_to_user(uVar15,&local_5c);
      }
      else {
        uVar15 = 4;
      }
      if (2 < DebugLevel) {
        printk("Query::RT_OID_802_11_QUERY_LAST_TX_RATE (=%ld)\n",local_5c);
        return uVar15;
      }
      return uVar15;
    }
    if (0x678 < param_3) {
      if (param_3 == 0x67c) {
        iVar14 = hc_get_chip_cap(param_1[0x29e5e8]);
        if (*(char *)(iVar14 + 0x96) == '\0') {
          return 0xfffffff2;
        }
        os_alloc_mem(param_1,&local_4c,0xa90);
        if (local_4c == (int *)0x0) {
          return 0xfffffff2;
        }
        *local_4c = 0;
        piVar22 = param_1 + 0x28787;
        iVar14 = 0;
        while( true ) {
          iVar23 = HcGetMaxStaNum(param_1);
          if (iVar23 <= iVar14) break;
          if ((piVar22[-0x3f] == 0x20001) && (*piVar22 == 2)) {
            memmove(local_4c + *local_4c * 9 + 1,piVar22 + 0x2c6,0x24);
            *local_4c = *local_4c + 1;
          }
          piVar22 = piVar22 + 0x530;
          iVar14 = iVar14 + 1;
        }
        uVar16 = *(uint *)(param_2 + 0x10);
        uVar15 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
        if (uVar16 < 0xfffff570 && uVar16 + 0xa90 <= uVar15) {
          uVar15 = 0;
        }
        *(undefined2 *)(param_2 + 0x14) = 0xa90;
        if (uVar15 == 0) {
          uVar15 = __copy_to_user(uVar16);
        }
        else {
          uVar15 = 0xa90;
        }
        os_free_mem(local_4c);
        return uVar15;
      }
      if (param_3 == 0x714) {
        if (DebugLevel < 3) {
          *(undefined2 *)(param_2 + 0x14) = 1;
        }
        else {
          printk("Query::OID_802_11_BUILD_CHANNEL_EX\n");
          iVar14 = DebugLevel;
          *(undefined2 *)(param_2 + 0x14) = 1;
          if (2 < iVar14) {
            printk("Doesn\'t support EXT_BUILD_CHANNEL_LIST.\n");
          }
        }
        iVar14 = *(int *)(param_2 + 0x10);
        local_4c = (int *)((uint)local_4c & 0xffffff00);
        uVar15 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
        if (iVar14 != -1 && iVar14 + 1U <= uVar15) {
          uVar15 = 0;
        }
        if (uVar15 == 0) {
          uVar15 = __copy_to_user(iVar14,&local_4c,1);
        }
        else {
          uVar15 = 1;
        }
        if (2 < DebugLevel) {
          printk("Status=%d\n",uVar15);
          return uVar15;
        }
        return uVar15;
      }
      if (param_3 == 0x679) {
        local_5c = 0;
        getRate(param_1[0x28cc6],&local_5c);
        uVar15 = *(uint *)(param_2 + 0x10);
        *(undefined2 *)(param_2 + 0x14) = 4;
        uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
        if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
          uVar16 = 0;
        }
        if (uVar16 == 0) {
          uVar15 = __copy_to_user(uVar15,&local_5c);
        }
        else {
          uVar15 = 4;
        }
        if (2 < DebugLevel) {
          printk("Query::RT_OID_802_11_QUERY_LAST_RX_RATE (=%ld)\n",local_5c);
          return uVar15;
        }
        return uVar15;
      }
      goto LAB_0005fae4;
    }
    if (param_3 != 0x646) {
      if (param_3 == 0x650) {
        local_64 = (uint)*(ushort *)(param_1 + 0x28ca7);
        uVar15 = *(uint *)(param_2 + 0x10);
        uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
        if (uVar15 < 0xfffffffc && uVar15 + 4 <= uVar16) {
          uVar16 = 0;
        }
        *(undefined2 *)(param_2 + 0x14) = 4;
        if (uVar16 == 0) {
          uVar15 = __copy_to_user(uVar15,&local_64);
        }
        else {
          uVar15 = 4;
        }
        if (2 < DebugLevel) {
          printk("Query::RT_OID_802_11_QUERY_TX_PHYMODE (=%lx)\n",local_64);
          return uVar15;
        }
        return uVar15;
      }
      if (param_3 == 0x645) {
        if (2 < DebugLevel) {
          printk("Query::RT_OID_DRIVER_DEVICE_NAME\n");
        }
        uVar15 = *(uint *)(param_2 + 0x10);
        *(undefined2 *)(param_2 + 0x14) = 0x10;
        uVar16 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
        if (uVar15 < 0xfffffff0 && uVar15 + 0x10 <= uVar16) {
          uVar16 = 0;
        }
        if (uVar16 != 0) {
          return 0xfffffff2;
        }
        iVar14 = __copy_to_user(uVar15,param_1 + iVar23 * 0x84dec + 0x15ffd3);
        goto joined_r0x00060134;
      }
      goto LAB_0005fae4;
    }
    os_alloc_mem(param_1,&local_54,0x10);
    puVar12 = local_54;
    if (local_54 != (uint *)0x0) {
      uVar15 = wmode_2_cfgmode(*(undefined2 *)(param_4 + 0x18));
      puVar21 = local_54;
      *puVar12 = uVar15;
      *(byte *)((int)local_54 + 5) =
           (byte)(((uint)*(byte *)((int)param_1 + 0x794cce) << 0x1f) >> 0x1f);
      uVar9 = wlan_operate_get_ht_bw(param_4);
      puVar12 = local_54;
      *(undefined1 *)(puVar21 + 2) = uVar9;
      *(byte *)((int)local_54 + 7) =
           (byte)(((uint)*(byte *)((int)param_1 + iVar23 * 0x2137b0 + 0x36e406) << 0x19) >> 0x19);
      uVar9 = wlan_config_get_ht_gi(param_4);
      puVar21 = local_54;
      *(undefined1 *)((int)puVar12 + 10) = uVar9;
      uVar9 = wlan_config_get_ht_stbc(param_4);
      *(undefined1 *)((int)puVar21 + 9) = uVar9;
      *(undefined2 *)(param_2 + 0x14) = 0x10;
      uVar16 = *(uint *)(param_2 + 0x10);
      uVar18 = *(uint *)(((uint)&local_a8 & 0xffffe000) + 8);
      uVar17 = uVar16 + 0x10;
      uVar15 = uVar17;
      if (uVar16 < 0xfffffff0) {
        uVar15 = uVar17 - (uVar18 + 1);
      }
      if (uVar16 < 0xfffffff0 && uVar17 <= uVar18) {
        uVar18 = 0;
      }
      if (uVar18 == 0) {
        uVar24 = __copy_to_user(uVar16,local_54);
        uVar15 = (uint)((ulonglong)uVar24 >> 0x20);
        if ((int)uVar24 == 0) {
          uVar16 = 0;
        }
        else {
          uVar16 = 0xfffffff2;
        }
      }
      else {
        uVar16 = 0xfffffff2;
      }
      if (2 < DebugLevel) {
        local_a8 = (uint)*(byte *)((int)local_54 + 9);
        local_a4 = (uint)*(byte *)((int)local_54 + 6);
        printk("Query::RT_OID_802_11_QUERY_HT_PHYMODE (PhyMode = %d, MCS =%d, BW = %d, STBC = %d, ExtOffset=%d)\n"
               ,*(undefined1 *)((int)local_54 + 5),*(undefined1 *)((int)local_54 + 7),
               (char)local_54[2]);
        uVar15 = extraout_r1_01;
        if (2 < DebugLevel) {
          printk("%s(): (.word = %x )\n","RTMPQueryInformation",(short)param_1[0x28ca7]);
          uVar15 = extraout_r1_02;
        }
      }
      os_free_mem(local_54,uVar15);
      return uVar16;
    }
  }
  if (DebugLevel < 3) {
    return 0xfffffff2;
  }
LAB_0005ffac:
  printk("Query::RT_OID_802_11_STA_CONFIG(mem alloc failed)\n");
  return 0xfffffff2;
}

