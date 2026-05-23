// module: mt7915.ko
// function: PeerBeaconAndProbeRspSanity @ 0x110f50
// size: 4460 bytes
//

undefined4
PeerBeaconAndProbeRspSanity
          (int param_1,int param_2,byte *param_3,uint param_4,byte param_5,undefined4 *param_6,
          ushort *param_7,int param_8,char param_9,char param_10)

{
  byte bVar1;
  char cVar2;
  char cVar3;
  ushort uVar4;
  int iVar5;
  void *pvVar6;
  char *pcVar7;
  byte *pbVar8;
  byte bVar9;
  size_t __n;
  byte bVar10;
  byte bVar11;
  uint uVar12;
  byte *pbVar13;
  byte *__src;
  size_t __n_00;
  uint uVar14;
  uint uVar15;
  int iVar16;
  bool bVar17;
  int local_78;
  size_t local_5c;
  byte *local_4c;
  undefined1 uStack_3a;
  undefined1 local_39;
  void *local_38;
  undefined4 local_34;
  undefined2 local_30;
  
  local_38 = (void *)0x0;
  if (*(int *)(param_2 + 0x14) == 2) {
    local_78 = GetStaCfgByWdev();
  }
  else {
    local_78 = 0;
  }
  os_alloc_mem(0,&local_38,0x200);
  if (local_38 == (void *)0x0) {
    return 0;
  }
  *(undefined1 *)(param_6 + 0xf) = 0xff;
  *(undefined1 *)((int)param_6 + 0xa3) = 0xff;
  *param_7 = 0;
  if (param_10 == '\0') {
    pbVar8 = param_3 + 0x18;
    bVar11 = *param_3;
    iVar16 = 0x24;
    *param_6 = *(undefined4 *)(param_3 + 10);
    bVar11 = bVar11 >> 4;
    *(undefined2 *)(param_6 + 1) = *(undefined2 *)(param_3 + 0xe);
    *(undefined4 *)((int)param_6 + 6) = *(undefined4 *)(param_3 + 0x10);
    *(undefined2 *)((int)param_6 + 10) = *(undefined2 *)(param_3 + 0x14);
    local_4c = param_3;
  }
  else {
    iVar16 = 0xc;
    local_4c = (byte *)0x0;
    bVar11 = 0xff;
    pbVar8 = param_3;
  }
  __src = pbVar8 + 0xc;
  memmove(param_6 + 0x10,pbVar8,8);
  memmove((void *)((int)param_6 + 0x2e),pbVar8 + 8,2);
  memmove(param_6 + 0xd,pbVar8 + 10,2);
  bVar10 = (byte)*(ushort *)(param_6 + 0xd) & 1;
  if ((*(ushort *)(param_6 + 0xd) & 1) != 0) {
    bVar10 = 1;
  }
  *(byte *)((int)param_6 + 0x2d) = bVar10;
  if (bVar11 == 5) {
    txbf_clear_oui();
  }
  __n = (size_t)pbVar8[0xd];
  __n_00 = __n + 2;
  if (param_4 < __n_00 + iVar16) {
    if (0xe < param_5) {
      bVar17 = true;
      iVar16 = hc_radio_query_by_rf(param_1,2,&local_34);
      if (iVar16 == 0) {
        uVar14 = 4;
        bVar10 = 1;
        local_5c = 0;
LAB_00111d10:
        if (((1 < local_34._3_1_ - 1) || (local_78 == 0)) ||
           (bVar11 = *(byte *)(local_78 + 0x4165), bVar11 == 0)) goto LAB_00111c8c;
      }
      else {
        uVar14 = 4;
        bVar10 = 1;
        local_5c = 0;
LAB_00111c8c:
        bVar11 = param_5;
      }
      *(byte *)(param_6 + 0xc) = bVar11;
      goto LAB_0011113c;
    }
    bVar17 = true;
    if (local_38 != (void *)0x0) {
      uVar14 = 0;
      bVar10 = 1;
      goto LAB_00111158;
    }
    bVar10 = 1;
    uVar14 = 0;
  }
  else {
    uVar15 = (uint)*param_7;
    uVar12 = uVar15 + __n + 2;
    if (uVar12 < 0x400) {
      cVar2 = '\0';
      local_5c = 0;
      uVar14 = 0;
      bVar10 = 1;
      do {
        bVar9 = *__src;
        if (bVar9 == 0x32) {
          if (__n < 0xd) {
            memmove((void *)((int)param_6 + 0xba),__src + 2,__n);
            *(byte *)((int)param_6 + 0xb9) = __src[1];
            uVar12 = (uint)__src[1];
            goto LAB_001110e0;
          }
LAB_001110dc:
          uVar12 = (uint)__src[1];
        }
        else {
          if (0x32 < bVar9) {
            if (bVar9 == 0x96) {
              if ((__n == 6) && (iVar5 = memcmp(__src + 2,&CISCO_OUI,3), iVar5 == 0)) {
                *(byte *)(param_6 + 0xf) = __src[6];
              }
            }
            else if (bVar9 < 0x97) {
              if (bVar9 == 0x47) {
                parse_mbssid_subelement(param_1,param_2,__src,param_6);
                uVar12 = (uint)__src[1];
                goto LAB_001110e0;
              }
              if (0x47 < bVar9) {
                if (bVar9 == 0x7f) {
                  if (__n == 0) goto LAB_001110dc;
                  if (10 < __n) {
                    __n = 0xb;
                  }
                  memmove(param_6 + 0x26,__src + 2,__n);
                  uVar12 = (uint)__src[1];
                }
                else {
                  if ((bVar9 != 0x85) || (__n < 0x1c)) goto LAB_001110dc;
                  *(byte *)((int)param_6 + 0x3b) = __src[10];
                  uVar12 = (uint)__src[1];
                }
                goto LAB_001110e0;
              }
              if (bVar9 == 0x3d) {
                if (__n < 0x16) {
                  if (1 < DebugLevel) {
                    printk("%s() - wrong IE_ADD_HT.\n","PeerBeaconAndProbeRspSanity");
                    uVar12 = (uint)__src[1];
                    goto LAB_001110e0;
                  }
                }
                else {
                  memmove((void *)((int)param_6 + 0xf6),__src + 2,0x16);
                  cVar2 = *(char *)((int)param_6 + 0xf6);
                  param_6[0x2a] = param_6[0x2a] | 2;
                  if (local_78 != 0) {
                    uVar4 = *param_7;
                    goto LAB_00111b70;
                  }
                }
              }
              else if (bVar9 == 0x3e) {
                if (__n == 1) {
                  *(byte *)((int)param_6 + 0xa3) = __src[2];
                  uVar12 = (uint)__src[1];
                }
                else {
                  if (DebugLevel < 2) goto LAB_001110dc;
                  printk("%s() - wrong IE_SECONDARY_CH_OFFSET.\n","PeerBeaconAndProbeRspSanity");
                  uVar12 = (uint)__src[1];
                }
                goto LAB_001110e0;
              }
            }
            else if (bVar9 == 0xc4) {
              pbVar8 = __src + 2;
              if ('\0' < (char)__n) {
                bVar9 = __src[3];
                bVar1 = __src[2];
                while( true ) {
                  if (bVar1 == 0xc2) break;
                  uVar12 = __n - (bVar9 + 2 & 0xff);
                  pbVar8 = pbVar8 + (char)(bVar9 + 2);
                  __n = uVar12 & 0xff;
                  if ((char)uVar12 < '\x01') goto LAB_001110dc;
                  bVar9 = pbVar8[1];
                  bVar1 = *pbVar8;
                }
                memmove((void *)((int)param_6 + 0x11f),pbVar8 + 2,3);
              }
            }
            else if (bVar9 < 0xc5) {
              if (bVar9 == 0xbf) {
                if (__n == 0xc) {
                  memmove(param_6 + 0x43,__src + 2,0xc);
                  param_6[0x2a] = param_6[0x2a] | 4;
                }
              }
              else if ((bVar9 == 0xc0) && (__n == 5)) {
                memmove(param_6 + 0x46,__src + 2,5);
                param_6[0x2a] = param_6[0x2a] | 8;
                uVar12 = (uint)__src[1];
                goto LAB_001110e0;
              }
            }
            else {
              if (bVar9 == 0xdd) {
                iVar5 = map_check_zte_ie(__src,&local_39);
                if (iVar5 == 1) {
                  *(undefined1 *)(param_6 + 0x5e) = local_39;
                }
                if (bVar11 == 5) {
                  if (2 < DebugLevel) {
                    printk("%s(): pEid->Octet[0-2] = %x, %x, %x\n","PeerBeaconAndProbeRspSanity",
                           __src[2],__src[3],__src[4]);
                  }
                  iVar5 = memcmp(__src + 2,&METALINK_OUI,3);
                  if (iVar5 == 0) {
                    txbf_set_oui(2);
                  }
                }
                pbVar8 = __src + 2;
                iVar5 = memcmp(pbVar8,&MARVELL_OUI,3);
                if (iVar5 == 0) {
                  *(undefined1 *)((int)param_6 + 0xa5) = 1;
                }
                check_vendor_ie(param_1,__src,param_6 + 0x32);
                param_6[0x21] = param_6[0x32];
                param_6[0x25] = param_6[0x36];
                if (*(char *)((int)param_6 + 0xd9) == '\x01') {
                  *(undefined1 *)((int)param_6 + 0x95) = 1;
                }
                param_6[0x22] = param_6[0x33];
                param_6[0x23] = param_6[0x34];
                if (*(char *)((int)param_6 + 0xda) == '\x01') {
                  *(undefined1 *)((int)param_6 + 0x96) = 1;
                }
                uVar15 = param_6[0x2a];
                param_6[0x24] = param_6[0x35];
                if ((uVar15 & 1) == 0) {
                  iVar5 = memcmp(pbVar8,&BROADCOM_OUI,3);
                  uVar12 = (uint)__src[1];
                  if (((iVar5 == 0) && (3 < uVar12)) && (*(char *)(param_1 + 0x286285) == '\0')) {
                    bVar9 = __src[5];
                    if (0x1d < uVar12 && bVar9 == 0x33) {
                      memmove(param_6 + 0x37,__src + 6,0x1a);
                      param_6[0x2a] = uVar15 | 0x80;
                      bVar9 = __src[5];
                      uVar12 = (uint)__src[1];
                    }
                    if ((bVar9 == 0x34) && (0x19 < uVar12)) {
                      memmove((void *)((int)param_6 + 0xf6),__src + 6,0x16);
                      param_6[0x2a] = param_6[0x2a] | 2;
                      goto LAB_0011153c;
                    }
                  }
                }
                else {
LAB_0011153c:
                  uVar12 = (uint)__src[1];
                }
                iVar5 = memcmp(pbVar8,&OWE_TRANS_OUI,4);
                if ((iVar5 == 0) || (iVar5 = memcmp(pbVar8,&WPA_OUI,4), iVar5 == 0)) {
                  memmove((void *)(param_8 + (uint)*param_7),__src,uVar12 + 2);
                  *param_7 = __src[1] + 2 + *param_7;
                  uVar12 = (uint)__src[1];
                }
                else {
                  iVar5 = memcmp(pbVar8,&WME_PARM_ELEM,6);
                  if ((iVar5 == 0) && (uVar12 == 0x18)) {
                    *(undefined1 *)((int)param_6 + 0x52) = 0;
                    *(undefined1 *)((int)param_6 + 0x53) = 0;
                    *(undefined1 *)(param_6 + 0x15) = 0;
                    param_6[0x2a] = param_6[0x2a] | 0x40;
                    *(undefined1 *)(param_6 + 0x14) = 1;
                    *(byte *)((int)param_6 + 0x56) = __src[8] & 0xf;
                    *(byte *)((int)param_6 + 0x55) = __src[8] >> 7;
                    pbVar8 = __src + 0xe;
                    do {
                      pbVar13 = pbVar8 + 4;
                      uVar12 = ((uint)pbVar8[-4] << 0x19) >> 0x1e;
                      *(byte *)((int)param_6 + uVar12 + 0x6c) =
                           (byte)(((uint)pbVar8[-4] << 0x1b) >> 0x1f);
                      *(byte *)((int)param_6 + uVar12 + 0x57) = pbVar8[-4] & 0xf;
                      *(byte *)((int)param_6 + uVar12 + 0x5b) = pbVar8[-3] & 0xf;
                      *(byte *)((int)param_6 + uVar12 + 0x5f) = pbVar8[-3] >> 4;
                      *(ushort *)((int)param_6 + uVar12 * 2 + 100) =
                           (ushort)pbVar8[-2] + (ushort)pbVar8[-1] * 0x100;
                      pbVar8 = pbVar13;
                    } while (pbVar13 != __src + 0x1e);
                    goto LAB_001110dc;
                  }
                  iVar5 = memcmp(pbVar8,&WME_INFO_ELEM,6);
                  if ((iVar5 == 0) && (uVar12 == 7)) {
                    *(undefined1 *)((int)param_6 + 0x52) = 0;
                    *(undefined1 *)((int)param_6 + 0x53) = 0;
                    *(undefined1 *)(param_6 + 0x15) = 0;
                    param_6[0x2a] = param_6[0x2a] | 0x40;
                    *(undefined1 *)(param_6 + 0x14) = 1;
                    *(byte *)((int)param_6 + 0x56) = __src[8] & 0xf;
                    bVar9 = __src[8];
                    *(undefined1 *)(param_6 + 0x16) = 3;
                    *(undefined1 *)((int)param_6 + 0x6d) = 0;
                    *(byte *)((int)param_6 + 0x55) = bVar9 >> 7;
                    *(char *)(param_6 + 0x17) = "BssEntrySet"[param_1 + 3];
                    cVar3 = "BssEntrySet"[param_1 + 4];
                    *(undefined1 *)((int)param_6 + 0x57) = 7;
                    *(undefined2 *)((int)param_6 + 0x66) = 0;
                    *(undefined1 *)(param_6 + 0x1b) = 0;
                    *(char *)(param_6 + 0x18) = cVar3;
                    *(char *)((int)param_6 + 0x5b) = "BssEntrySet"[param_1 + 3];
                    cVar3 = "BssEntrySet"[param_1 + 4];
                    *(undefined2 *)(param_6 + 0x19) = 0;
                    *(undefined1 *)((int)param_6 + 0x6e) = 0;
                    *(char *)((int)param_6 + 0x5f) = cVar3;
                    *(undefined1 *)((int)param_6 + 0x59) = 2;
                    *(char *)((int)param_6 + 0x5d) = "BssEntrySet"[param_1 + 3] + -1;
                    cVar3 = "BssEntrySet"[param_1 + 4];
                    *(undefined1 *)((int)param_6 + 0x5a) = 2;
                    *(undefined1 *)((int)param_6 + 0x6f) = 0;
                    *(char *)((int)param_6 + 0x61) = cVar3;
                    *(undefined2 *)(param_6 + 0x1a) = 0x60;
                    *(char *)((int)param_6 + 0x5e) = "BssEntrySet"[param_1 + 3] + -2;
                    cVar3 = "BssEntrySet"[param_1 + 4];
                    *(undefined2 *)((int)param_6 + 0x6a) = 0x30;
                    *(char *)((int)param_6 + 0x62) = cVar3 + -1;
                    uVar12 = (uint)__src[1];
                  }
                  else {
                    iVar5 = memcmp(pbVar8,&WPS_OUI,4);
                    if (iVar5 == 0) {
                      if (local_38 == (void *)0x0) {
                        if (uVar12 < 5) goto LAB_00111a50;
LAB_00111ea0:
                        if (DebugLevel < 3) {
LAB_00111eac:
                          uVar12 = (uint)__src[1];
                          bVar10 = 0;
                        }
                        else {
                          bVar10 = 0;
                          printk("%s: Error!!! pPeerWscIe is null!\n","PeerBeaconAndProbeRspSanity")
                          ;
                          uVar12 = (uint)__src[1];
                        }
                      }
                      else if (uVar12 < 5) {
LAB_00111a50:
                        if (2 < DebugLevel) {
                          printk("%s: Error!!! Incorrect WPS IE!\n","PeerBeaconAndProbeRspSanity");
                          if (local_38 == (void *)0x0) goto LAB_00111ea0;
                          goto LAB_00111eac;
                        }
LAB_00111a68:
                        bVar10 = 0;
                      }
                      else if ((int)((uVar12 - 4) + local_5c) < 0x201) {
                        memmove((void *)((int)local_38 + local_5c),__src + 6,uVar12 - 4);
                        uVar12 = (uint)__src[1];
                        local_5c = local_5c + (uVar12 - 4);
                      }
                      else {
                        bVar10 = 0;
                        if (DebugLevel < 0) goto LAB_00111a68;
                        printk("%s: Error!!! Sum of All PeerWscIeLen = %d (> 512)\n",
                               "PeerBeaconAndProbeRspSanity");
                        uVar12 = (uint)__src[1];
                      }
                    }
                  }
                }
                goto LAB_001110e0;
              }
              if (bVar9 == 0xff) {
                parse_he_beacon_probe_rsp_ies(__src,param_6);
                uVar12 = (uint)__src[1];
                goto LAB_001110e0;
              }
              if ((bVar9 == 199) && (__n == 1 && param_10 == '\0')) {
                (**(code **)(*(int *)(param_2 + 0x904) + 0xb8))
                          (param_1,local_4c + 10,param_2,&local_34);
                if ((local_34 != 0) && ((__src[2] & 0x80) == 0)) {
                  *(byte *)(local_34 + 0xd21) = __src[2];
                  *(undefined1 *)(local_34 + 0xd20) = 1;
                }
                if (3 < DebugLevel) {
                  printk("%s() - IE_OPERATING_MODE_NOTIFY(=%d)\n","PeerBeaconAndProbeRspSanity",
                         *__src);
                }
              }
            }
            goto LAB_001110dc;
          }
          if (bVar9 == 5) {
            if ((local_78 != 0 && bVar11 == 8) &&
               ((((*(uint *)(local_78 + 0x212464) & 1) != 0 &&
                 (iVar5 = memcmp((void *)((int)param_6 + 6),(void *)(local_78 + 0x212428),6),
                 iVar5 == 0)) || (param_9 != '\0')))) {
              GetTimBit(__src,*(undefined2 *)(local_78 + 0x40b0),&uStack_3a,(int)param_6 + 0x39,
                        (int)param_6 + 0x37,param_6 + 0xe,(int)param_6 + 0x3a);
              uVar12 = (uint)__src[1];
              goto LAB_001110e0;
            }
            goto LAB_001110dc;
          }
          if (5 < bVar9) {
            if (bVar9 == 0x25) {
              if (__n == 3) {
                *(byte *)((int)param_6 + 0x31) = __src[3];
                uVar12 = (uint)__src[1];
                goto LAB_001110e0;
              }
            }
            else if (bVar9 < 0x26) {
              if (bVar9 == 6) {
                if (__n != 2) {
                  if (2 < DebugLevel) {
                    printk("%s() - wrong IE_IBSS_PARM\n","PeerBeaconAndProbeRspSanity");
                  }
LAB_00111f28:
                  if (local_38 == (void *)0x0) {
                    return 0;
                  }
                  os_free_mem();
                  return 0;
                }
                memmove((void *)((int)param_6 + 0x32),__src + 2,2);
                uVar12 = (uint)__src[1];
                goto LAB_001110e0;
              }
              if ((bVar9 == 0xb) && (__n == 5)) {
                *(undefined1 *)(param_6 + 0x1d) = 1;
                *(ushort *)((int)param_6 + 0x76) = (ushort)__src[2] + (ushort)__src[3] * 0x100;
                *(byte *)(param_6 + 0x1e) = __src[4];
                *(ushort *)((int)param_6 + 0x7a) = (ushort)__src[5] + (ushort)__src[6] * 0x100;
                pvVar6 = (void *)(param_8 + (uint)*param_7);
                __n_00 = __src[1] + 2;
                goto LAB_001117f0;
              }
            }
            else if (bVar9 == 0x2d) {
              if (__n < 0x1a) {
                if (1 < DebugLevel) {
                  printk("%s() - wrong IE_HT_CAP. pEid->Len = %d\n","PeerBeaconAndProbeRspSanity");
                  uVar12 = (uint)__src[1];
                  goto LAB_001110e0;
                }
              }
              else {
                memmove(param_6 + 0x37,__src + 2,0x1a);
                uVar12 = param_6[0x2a];
                param_6[0x2a] = uVar12 | 1;
                if (local_78 != 0) {
                  param_6[0x2a] = uVar12 & 0xffffff7f | 1;
                  uVar4 = *param_7;
LAB_00111b70:
                  __n_00 = __src[1] + 2;
                  pvVar6 = (void *)(param_8 + (uint)uVar4);
                  goto LAB_001117f0;
                }
              }
            }
            else if (bVar9 == 0x30) {
              iVar5 = memcmp(__src + 4,&RSN_OUI,3);
              if (iVar5 == 0) {
                pvVar6 = (void *)(param_8 + uVar15);
LAB_001117f0:
                memmove(pvVar6,__src,__n_00);
                *param_7 = __src[1] + 2 + *param_7;
              }
            }
            else if ((bVar9 == 0x2a) && (__n == 1)) {
              *(byte *)((int)param_6 + 0x36) = __src[2];
              uVar12 = (uint)__src[1];
              goto LAB_001110e0;
            }
            goto LAB_001110dc;
          }
          if (bVar9 == 2) {
            if (DebugLevel < 3) goto LAB_001110dc;
            printk("%s(IE_FH_PARM)\n","PeerBeaconAndProbeRspSanity");
            uVar12 = (uint)__src[1];
          }
          else if (bVar9 < 3) {
            if (bVar9 == 0) {
              if ((uVar14 & 1) != 0) goto LAB_001110dc;
              if (0x20 < __n) {
                if (2 < DebugLevel) {
                  pcVar7 = "%s() - wrong IE_SSID (len=%d)\n";
                  goto LAB_00111f5c;
                }
                goto LAB_00111d54;
              }
              memmove(param_6 + 3,__src + 2,__n);
              uVar14 = uVar14 | 1;
              *(byte *)(param_6 + 0xb) = __src[1];
              uVar12 = (uint)__src[1];
            }
            else {
              if (bVar9 != 1) goto LAB_001110dc;
              if (0xc < __n) {
                if (2 < DebugLevel) {
                  pcVar7 = "%s() - wrong IE_SUPP_RATES (len=%d)\n";
LAB_00111f5c:
                  printk(pcVar7,"PeerBeaconAndProbeRspSanity");
                }
                goto LAB_00111d54;
              }
              memmove((void *)((int)param_6 + 0xad),__src + 2,__n);
              uVar14 = uVar14 | 2;
              *(byte *)(param_6 + 0x2b) = __src[1];
              uVar12 = (uint)__src[1];
            }
          }
          else {
            if (bVar9 == 3) {
              if (__n == 1) {
                *(byte *)(param_6 + 0xc) = __src[2];
                if ((local_78 == 0) || (iVar5 = ChannelSanity(param_1), iVar5 != 0)) {
                  uVar14 = uVar14 | 4;
                  uVar12 = (uint)__src[1];
                  goto LAB_001110e0;
                }
              }
              else if (2 < DebugLevel) {
                pcVar7 = "%s() - wrong IE_DS_PARM (len=%d)\n";
                goto LAB_00111f5c;
              }
LAB_00111d54:
              bVar17 = uVar14 != 7;
              bVar11 = bVar10 ^ 1;
              pvVar6 = local_38;
              if (local_38 != (void *)0x0) goto LAB_00111164;
              bVar11 = bVar17 | bVar11;
              goto LAB_00111170;
            }
            if (bVar9 != 4) goto LAB_001110dc;
            if (__n != 6) {
              if (2 < DebugLevel) {
                printk("%s() - wrong IE_CF_PARM\n","PeerBeaconAndProbeRspSanity");
              }
              goto LAB_00111f28;
            }
            *(undefined1 *)(param_6 + 0x12) = 1;
            *(byte *)((int)param_6 + 0x49) = __src[2];
            *(byte *)((int)param_6 + 0x4a) = __src[3];
            *(ushort *)((int)param_6 + 0x4b) = (ushort)__src[4] + (ushort)__src[5] * 0x100;
            *(ushort *)((int)param_6 + 0x4d) = (ushort)__src[6] + (ushort)__src[7] * 0x100;
            uVar12 = (uint)__src[1];
          }
        }
LAB_001110e0:
        __src = __src + uVar12 + 2;
        iVar16 = iVar16 + uVar12 + 2;
        __n = (size_t)__src[1];
        __n_00 = __n + 2;
        if (param_4 < __n_00 + iVar16) goto LAB_00111128;
        uVar15 = (uint)*param_7;
        uVar12 = uVar15 + __n + 2;
      } while (uVar12 < 0x400);
    }
    else {
      uVar14 = 0;
      cVar2 = '\0';
      bVar10 = 1;
      local_5c = 0;
    }
    if (1 < DebugLevel) {
      printk("%s() - Variable IEs out of resource [len(=%d) > MAX_VIE_LEN(=%d)]\n",
             "PeerBeaconAndProbeRspSanity",uVar12,0x400);
    }
LAB_00111128:
    if ((param_5 < 0xf) || ((uVar14 & 4) != 0)) {
      bVar17 = false;
      if (uVar14 != 7) {
        bVar17 = true;
      }
    }
    else {
      uVar14 = uVar14 | 4;
      iVar16 = hc_radio_query_by_rf(param_1,2,&local_34);
      bVar17 = uVar14 != 7;
      if (iVar16 == 0) {
        if (cVar2 == '\0') goto LAB_00111d10;
      }
      else if (cVar2 == '\0') goto LAB_00111c8c;
      *(char *)(param_6 + 0xc) = cVar2;
    }
LAB_0011113c:
    pvVar6 = local_38;
    if (local_38 != (void *)0x0) {
      if (local_5c - 1 < 0x200) {
        if (bVar10 == 1) {
          uVar4 = *param_7;
          local_30 = 0x4f2;
          local_34 = CONCAT22(0x5000,CONCAT11((char)local_5c + '\x04',0xdd));
          *(int *)(param_8 + (uint)uVar4) = local_34;
          *(undefined2 *)(param_8 + (uint)uVar4 + 4) = 0x4f2;
          bVar11 = 0;
          memmove((void *)(param_8 + *param_7 + 6),local_38,local_5c);
          *param_7 = *param_7 + 6 + (short)local_5c;
          goto LAB_00111164;
        }
        bVar10 = 0;
        bVar11 = 1;
      }
      else {
LAB_00111158:
        bVar11 = bVar10 ^ 1;
        pvVar6 = local_38;
LAB_00111164:
        bVar11 = bVar17 | bVar11;
      }
      os_free_mem(pvVar6);
      goto LAB_00111170;
    }
  }
  bVar11 = bVar17 | bVar10 ^ 1;
LAB_00111170:
  if (bVar11 != 0) {
    if (param_10 != '\0') {
      bVar17 = false;
    }
    if (((bVar17 != false) || ((param_10 == '\x01' && ((uVar14 & 1) == 0)))) || (bVar10 == 0)) {
      if (4 < DebugLevel) {
        printk("%s() - missing field, Sanity=0x%02x, bWscCheck=%d\n","PeerBeaconAndProbeRspSanity",
               uVar14,bVar10);
      }
      return 0;
    }
  }
  return 1;
}

