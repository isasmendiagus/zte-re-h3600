// module: mt7915.ko
// function: Show_TxBfInfo_Proc @ 0x2e02c
// size: 3492 bytes
//

undefined4 Show_TxBfInfo_Proc(int *param_1,char *param_2)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  char *pcVar4;
  uint uVar5;
  uint uVar6;
  undefined4 uVar7;
  void *__src;
  undefined4 uVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  int *piVar14;
  uint uVar15;
  uint uVar16;
  bool bVar17;
  char *local_5c [2];
  undefined4 local_54;
  uint local_50;
  undefined1 local_4c;
  undefined1 local_4b;
  undefined1 local_4a;
  undefined1 local_49;
  undefined1 local_48;
  undefined1 auStack_42 [21];
  byte local_2d;
  undefined2 local_2c;
  byte local_2a;
  
  iVar10 = *param_1;
  local_5c[0] = param_2;
  iVar3 = hc_get_chip_cap(param_1[0x29e5e8]);
  if (*(char *)(iVar3 + 0x96) == '\0') {
    return 1;
  }
  pcVar4 = strsep(local_5c,":");
  if ((pcVar4 != (char *)0x0) && (cVar2 = os_str_tol(pcVar4,0,10), cVar2 != '\0')) {
    pcVar4 = strsep(local_5c,"");
    if (pcVar4 == (char *)0x0) {
      return 0;
    }
    uVar5 = os_str_tol(pcVar4,0,10);
    uVar6 = HcGetMaxStaNum(param_1);
    uVar5 = uVar5 & 0xffff;
    if (uVar6 <= uVar5) {
      return 0;
    }
    switch(*(byte *)((int)param_1 + uVar5 * 0x14c0 + 0xa1ddf) >> 5) {
    case 0:
    case 1:
      uVar11 = 0;
      uVar15 = 1;
      uVar12 = 0;
      uVar6 = 0;
      uVar13 = 0;
      uVar9 = 0;
      uVar16 = ((uint)*(ushort *)((int)param_1 + uVar5 * 0x14c0 + 0xa1dde) << 0x17) >> 0x1e;
      break;
    case 2:
    case 3:
      iVar3 = uVar5 * 0x14c0;
      uVar9 = mt_WrapClientSupportsETxBF(param_1,(int)param_1 + iVar3 + 0xa29d9);
      bVar17 = *(char *)((int)param_1 + iVar3 + 0xa29c9) != '\0';
      uVar15 = (uint)*(byte *)((int)param_1 + iVar3 + 0xa29d3);
      uVar12 = (uint)*(byte *)(param_1 + uVar5 * 0x530 + 0x28a72);
      if (bVar17) {
        uVar12 = 2;
      }
      uVar6 = (*(byte *)(param_1 + uVar5 * 0x530 + 0x28a77) & 1) << 1 |
              (uint)(*(byte *)((int)param_1 + iVar3 + 0xa29db) >> 7);
      uVar16 = ((uint)*(ushort *)((int)param_1 + iVar3 + 0xa1dde) << 0x17) >> 0x1e;
      if ((!bVar17) && (uVar12 != 0)) {
        uVar12 = 1;
      }
      if (*(char *)((int)param_1 + uVar5 * 0x14c0 + 0xa29ca) != '\0') {
        uVar12 = 3;
      }
      uVar11 = uVar12;
      if (((uVar15 << 0x1e) >> 0x1f & uVar15) != 0) {
        uVar11 = (uVar15 << 0x1c) >> 0x1e;
      }
      uVar13 = 0;
      uVar15 = 2;
      break;
    case 4:
      iVar3 = uVar5 * 0x14c0;
      uVar9 = mt_WrapClientSupportsVhtETxBF(param_1,param_1 + uVar5 * 0x530 + 0x28a8d);
      uVar16 = ((uint)*(ushort *)((int)param_1 + iVar3 + 0xa1dde) << 0x17) >> 0x1e;
      bVar1 = *(byte *)(param_1 + uVar5 * 0x530 + 0x28a8e);
      uVar6 = (uint)(*(byte *)((int)param_1 + iVar3 + 0xa2a35) >> 5);
      uVar13 = ((uint)*(byte *)((int)param_1 + iVar3 + 0xa2a36) << 0x1b) >> 0x1f;
      if ((bVar1 & 0x30) == 0x30) {
        uVar12 = (uint)((bVar1 & 0xc) != 0xc);
      }
      else {
        uVar12 = 2;
      }
      if ((bVar1 & 0xc0) != 0xc0) {
        uVar12 = 3;
      }
      uVar15 = 4;
      uVar11 = uVar12;
      break;
    case 5:
      uVar15 = 8;
      uVar9 = txbf_peer_he_bfee_cap(param_1 + uVar5 * 0x530 + 0x2876a);
      uVar12 = (uint)*(byte *)(param_1 + uVar5 * 0x530 + 0x2876c);
      uVar6 = (uint)*(byte *)(param_1 + uVar5 * 0x530 + 0x2876b);
      uVar13 = ((uint)*(byte *)((int)param_1 + uVar5 * 0x14c0 + 0xa2a36) << 0x1b) >> 0x1f;
      uVar16 = ((uint)*(ushort *)((int)param_1 + uVar5 * 0x14c0 + 0xa1dde) << 0x17) >> 0x1e;
      uVar11 = uVar12;
      break;
    default:
      uVar12 = 0;
      uVar11 = uVar12;
      uVar13 = uVar12;
      uVar6 = uVar12;
      uVar9 = uVar12;
      uVar15 = uVar12;
      uVar16 = uVar12;
    }
    if (0 < DebugLevel) {
      printk("Wcid:%d\n",uVar5);
      if (DebugLevel < 1) {
LAB_0002ed80:
        if ((0 < DebugLevel) && (printk("Peer_BFeeNr:%d\n",uVar6), 0 < DebugLevel)) {
          printk("Peer_RxNumSupport:%d\n",uVar12);
LAB_0002edc8:
          if (0 < DebugLevel) {
            printk("Peer_Nc:%d\n",uVar11);
          }
        }
      }
      else {
        printk("Peer_TxMode:%d\n",uVar15);
        if (0 < DebugLevel) {
          printk("Peer_ETxBfCap:%d\n",uVar9);
          if (DebugLevel < 1) goto LAB_0002edc8;
          printk("Peer_SUMU:%d\n",uVar13);
          if (0 < DebugLevel) {
            printk("Peer_Bw:%d\n",uVar16);
            goto LAB_0002ed80;
          }
        }
      }
    }
    if ((*(byte *)((int)param_1 + uVar5 * 0x14c0 + 0xa1ddf) & 0xe0) != 0xa0) {
      return 1;
    }
    if (DebugLevel < 1) {
      return 1;
    }
    piVar14 = param_1 + uVar5 * 0x530 + 0x2876a;
    printk("Peer_Beamformee STS <= 80MHz:%d\n",(char)param_1[uVar5 * 0x530 + 0x2876b]);
    if (0 < DebugLevel) {
      printk("Peer_Beamformee STS > 80MHz:%d\n",
             *(undefined1 *)((int)param_1 + uVar5 * 0x14c0 + 0xa1dad));
      if (DebugLevel < 1) {
        return 1;
      }
      printk("Peer_Ng16 SU :%d\n",(uint)(*piVar14 << 0x1c) >> 0x1f);
      if (DebugLevel < 1) goto LAB_0002e600;
      printk("Peer_Ng16 MU :%d\n",(uint)(*piVar14 << 0x1b) >> 0x1f);
      if (DebugLevel < 1) {
        return 1;
      }
      printk("Peer_Codebook Size = {4,2} SU :%d\n",(uint)(*piVar14 << 0x1a) >> 0x1f);
    }
    if (DebugLevel < 1) {
      return 1;
    }
    printk("Peer_Codebook Size = {7,5} MU :%d\n",
           (uint)(param_1[uVar5 * 0x530 + 0x2876a] << 0x19) >> 0x1f);
    if (DebugLevel < 1) {
      return 1;
    }
    printk("Peer_Triggered SU :%d\n",(uint)(param_1[uVar5 * 0x530 + 0x2876a] << 0x18) >> 0x1f);
LAB_0002e600:
    if (DebugLevel < 1) {
      return 1;
    }
    printk("Peer_Triggered MU :%d\n",(uint)(param_1[uVar5 * 0x530 + 0x2876a] << 0x17) >> 0x1f);
    if (DebugLevel < 1) {
      return 1;
    }
    printk("Peer_Max Nc :%d\n",(char)param_1[uVar5 * 0x530 + 0x2876c]);
    return 1;
  }
  iVar3 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(iVar10 + 0x3c),*(undefined4 *)(iVar10 + 0x38));
  if (iVar3 == 0) {
    return 0;
  }
  if (*(int *)(iVar3 + 0xabc) == 0) {
    uVar7 = 0;
  }
  else {
    uVar7 = HcGetBandByWdev();
  }
  __src = (void *)wlan_operate_get_ht_cap(iVar3);
  memmove(auStack_42,__src,0x1a);
  iVar10 = HcIsBfCapSupport(iVar3);
  if (iVar10 == 0) {
    uVar8 = wlan_config_get_etxbf(iVar3);
    wlan_config_set_etxbf(iVar3,0);
    mt_WrapSetETxBFCap(param_1,iVar3,&local_2d);
    wlan_config_set_etxbf(iVar3,uVar8);
  }
  if (0 < DebugLevel) {
    printk(&_LC283);
    if (DebugLevel < 1) {
LAB_0002e944:
      if (DebugLevel < 1) {
LAB_0002e9d8:
        if (DebugLevel < 1) {
LAB_0002ea60:
          if (DebugLevel < 1) {
LAB_0002eaf0:
            if (DebugLevel < 1) {
LAB_0002eb80:
              if (DebugLevel < 1) {
LAB_0002ec10:
                if (DebugLevel < 1) {
LAB_0002ecac:
                  if (0 < DebugLevel) {
                    printk("  rsv:%d\n",local_2a >> 5);
                  }
                }
                else {
                  printk("  NoComSteerBFAntSup:%d\n",((uint)local_2c._1_1_ << 0x19) >> 0x1e);
                  if (0 < DebugLevel) {
                    printk("  ComSteerBFAntSup:%d\n",(local_2a & 1) << 1 | local_2c._1_1_ >> 7);
LAB_0002ec64:
                    if ((0 < DebugLevel) &&
                       (printk("  CSIRowBFSup:%d\n",((uint)local_2a << 0x1d) >> 0x1e),
                       0 < DebugLevel)) {
                      printk("  ChanEstimation:%d\n",((uint)local_2a << 0x1b) >> 0x1e);
                      goto LAB_0002ecac;
                    }
                  }
                }
              }
              else {
                printk("  ExpNoComBF:%d\n",((uint)(byte)local_2c << 0x19) >> 0x1e);
                if (0 < DebugLevel) {
                  printk("  ExpComBF:%d\n",((uint)local_2c << 0x17) >> 0x1e);
LAB_0002ebc8:
                  if (DebugLevel < 1) goto LAB_0002ec64;
                  printk("  MinGrouping:%d\n",((uint)local_2c._1_1_ << 0x1d) >> 0x1e);
                  if (0 < DebugLevel) {
                    printk("  CSIBFAntSup:%d\n",((uint)local_2c._1_1_ << 0x1b) >> 0x1e);
                    goto LAB_0002ec10;
                  }
                }
              }
            }
            else {
              printk("  ExpCSICapable:%d\n",(byte)local_2c & 1);
              if (0 < DebugLevel) {
                printk("  ExpNoComSteerCapable:%d\n",((uint)(byte)local_2c << 0x1e) >> 0x1f);
LAB_0002eb38:
                if (DebugLevel < 1) goto LAB_0002ebc8;
                printk("  ExpComSteerCapable:%d\n",((uint)(byte)local_2c << 0x1d) >> 0x1f);
                if (0 < DebugLevel) {
                  printk("  ExpCSIFbk:%d\n",((uint)(byte)local_2c << 0x1b) >> 0x1e);
                  goto LAB_0002eb80;
                }
              }
            }
          }
          else {
            printk("  RxNDPCapable:%d\n",((uint)local_2d << 0x1c) >> 0x1f);
            if (0 < DebugLevel) {
              printk("  TxNDPCapable:%d\n",((uint)local_2d << 0x1b) >> 0x1f);
LAB_0002eaa8:
              if (DebugLevel < 1) goto LAB_0002eb38;
              printk("  ImpTxBFCapable:%d\n",((uint)local_2d << 0x1a) >> 0x1f);
              if (0 < DebugLevel) {
                printk("  Calibration:%d\n",local_2d >> 6);
                goto LAB_0002eaf0;
              }
            }
          }
        }
        else {
          printk("HT TxBF Cap:\n");
          if (0 < DebugLevel) {
            printk("  TxBFRecCapable:%d\n",local_2d & 1);
LAB_0002ea18:
            if (DebugLevel < 1) goto LAB_0002eaa8;
            printk("  RxSoundCapable:%d\n",((uint)local_2d << 0x1e) >> 0x1f);
            if (0 < DebugLevel) {
              printk("  TxSoundCapable:%d\n",((uint)local_2d << 0x1d) >> 0x1f);
              goto LAB_0002ea60;
            }
          }
        }
      }
      else {
        printk("CommonCfg.ITxBfEn:%d\n",((uint)*(byte *)((int)param_1 + 0x794ccd) << 0x1d) >> 0x1f);
        if (0 < DebugLevel) {
          uVar7 = wlan_config_get_itxbf(iVar3);
          printk("ITxBfEn:%d\n",uVar7);
LAB_0002e994:
          if (DebugLevel < 1) goto LAB_0002ea18;
          printk("bfdm_bitmap:%d\n",param_1[0x29e274]);
          if (0 < DebugLevel) {
            printk("bfdm_bfee_enabled:%d\n",(char)param_1[0x29e275]);
            goto LAB_0002e9d8;
          }
        }
      }
    }
    else {
      printk("Band Index:%d\n",uVar7);
      if (0 < DebugLevel) {
        uVar7 = HcIsBfCapSupport(iVar3);
        printk("IsBfBand:%d\n",uVar7);
        if (DebugLevel < 1) goto LAB_0002e994;
        printk("CommonCfg.ETxBfEnCond:%ld\n",param_1[0x1e5667]);
        if (0 < DebugLevel) {
          uVar7 = wlan_config_get_etxbf(iVar3);
          printk("ETxBfEnCond:%d\n",uVar7);
          goto LAB_0002e944;
        }
      }
    }
  }
  local_54 = param_1[0x1e5658];
  uVar7 = wlan_config_get_etxbf(iVar3);
  iVar10 = HcIsBfCapSupport(iVar3);
  if (iVar10 == 0) {
    wlan_config_set_etxbf(iVar3);
  }
  mt_WrapSetVHTETxBFCap(param_1,iVar3,&local_54);
  wlan_config_set_etxbf(iVar3,uVar7);
  if ((0 < DebugLevel) && (printk("VHT TxBF Cap:\n"), 0 < DebugLevel)) {
    printk("  num_snd_dimension:%d\n",local_54._2_1_ & 7);
    if (0 < DebugLevel) {
      printk("  bfee_sts_cap:%d\n",local_54._1_1_ >> 5);
      if ((0 < DebugLevel) &&
         (printk("  bfee_cap_su:%d\n",((local_54 >> 8) << 0x1b) >> 0x1f), 0 < DebugLevel)) {
        printk("  bfer_cap_su:%d\n",((local_54 >> 8) << 0x1c) >> 0x1f);
      }
    }
  }
  uVar5 = wlan_config_get_phy_caps(iVar3);
  if ((uVar5 & 0x20) == 0) {
    if (DebugLevel < 1) {
      return 1;
    }
    printk("Wlan Device has no HE TxBF Cap\n");
    return 1;
  }
  __memzero(&local_50,0xc);
  mt_wrap_get_he_bf_cap(iVar3,&local_50);
  if (DebugLevel < 1) {
    return 1;
  }
  printk("HE TxBF Cap from he_bf_struct:\n");
  if (DebugLevel < 1) {
LAB_0002e2c4:
    if (0 < DebugLevel) {
      printk("  Beamformee STS > 80MHz:%d\n",local_4b);
      if (DebugLevel < 1) {
        return 1;
      }
      printk("  Number Of Sounding Dimensions <= 80MHz:%d\n",local_4a);
      goto LAB_0002e304;
    }
LAB_0002e348:
    if (DebugLevel < 1) goto LAB_0002e3d8;
    printk("  Ng = 16 MU Feedback:%d\n",(local_50 << 0x1b) >> 0x1f);
    if (DebugLevel < 1) {
      return 1;
    }
    printk("  Codebook Size = {4,2} SU Feedback:%d\n",(local_50 << 0x1a) >> 0x1f);
  }
  else {
    printk("  SU Beamformer:%d\n",local_50 & 1);
    if (DebugLevel < 1) {
      return 1;
    }
    printk("  SU Beamformee:%d\n",(local_50 << 0x1e) >> 0x1f);
    if (0 < DebugLevel) {
      printk("  MU Beamformer:%d\n",(local_50 << 0x1d) >> 0x1f);
      if (DebugLevel < 1) {
        return 1;
      }
      printk("  Beamformee STS <= 80MHz:%d\n",local_4c);
      goto LAB_0002e2c4;
    }
LAB_0002e304:
    if (0 < DebugLevel) {
      printk("  Number Of Sounding Dimensions > 80MHz:%d\n",local_49);
      if (DebugLevel < 1) {
        return 1;
      }
      printk("  Ng = 16 SU Feedback:%d\n",(local_50 << 0x1c) >> 0x1f);
      goto LAB_0002e348;
    }
  }
  if (DebugLevel < 1) {
    return 1;
  }
  printk("  Codebook Size = {7,5} MU Feedback:%d\n",(local_50 << 0x19) >> 0x1f);
  if (DebugLevel < 1) {
    return 1;
  }
  printk("  Triggered SU Beamforming Feedback:%d\n",(local_50 << 0x18) >> 0x1f);
LAB_0002e3d8:
  if ((0 < DebugLevel) &&
     (printk("  Triggered MU Beamforming Feedback:%d\n",(local_50 << 0x17) >> 0x1f), 0 < DebugLevel)
     ) {
    printk("  Max Nc:%d\n",local_48);
  }
  return 1;
}

