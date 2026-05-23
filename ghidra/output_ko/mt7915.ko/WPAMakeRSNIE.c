// module: mt7915.ko
// function: WPAMakeRSNIE @ 0x11a830
// size: 2808 bytes
//

void WPAMakeRSNIE(int param_1,uint *param_2,int *param_3)

{
  int iVar1;
  undefined2 *puVar2;
  uint extraout_r1;
  uint uVar3;
  uint extraout_r1_00;
  uint extraout_r1_01;
  undefined4 *puVar4;
  undefined2 *puVar5;
  uint uVar6;
  uint *puVar7;
  void *__dest;
  uint *puVar8;
  undefined1 *__dest_00;
  int iVar9;
  bool bVar10;
  byte local_2b [7];
  
  param_2[0x166] = 0;
  *(undefined1 *)((int)param_2 + 0x5a2) = 0;
  __memzero(param_2 + 0x169,0xff);
  param_2[0x167] = 0;
  *(undefined1 *)((int)param_2 + 0x5a3) = 0;
  __memzero((int)param_2 + 0x6a3,0xff);
  uVar3 = extraout_r1;
  if (param_1 == 1) {
    if ((*param_2 & 0x1d20d8) == 0) {
      return;
    }
    if (2 < DebugLevel) {
      printk("==> %s(AP)\n","WPAMakeRSNIE");
      uVar3 = extraout_r1_01;
    }
  }
  else if (param_1 == 2) {
    if ((*param_2 & 0x1d20f8) == 0) {
      return;
    }
    if (2 < DebugLevel) {
      printk("==> %s(STA)\n","WPAMakeRSNIE");
      uVar3 = extraout_r1_00;
    }
  }
  puVar8 = param_2 + 0x165;
  bVar10 = (*param_2 & 0x38) != 0;
  __dest = (void *)((int)param_2 + 0x5a6);
  if (bVar10) {
    *(undefined1 *)(param_2 + 0x168) = 0xdd;
    uVar3 = 1;
  }
  if (bVar10) {
    param_2[0x166] = uVar3;
  }
  if ((*param_2 & 0x120c0) != 0) {
    *(undefined1 *)((int)param_2 + 0x5a1) = 0x30;
    param_2[0x167] = 2;
  }
  puVar7 = param_2;
  do {
    puVar8 = puVar8 + 1;
    uVar3 = *puVar8;
    local_2b[0] = 0;
    if (uVar3 != 0) {
      __dest_00 = (undefined1 *)((int)__dest + -2);
      if (uVar3 == 1) {
        memmove(__dest_00,&OUI_WPA_VERSION,4);
        *(undefined1 *)((int)__dest + 2) = 1;
        *(undefined1 *)((int)__dest + 3) = 0;
        uVar3 = param_2[0x8a];
        if ((uVar3 & 2) == 0) {
          if ((uVar3 & 4) == 0) {
            if ((uVar3 & 0x10) == 0) {
              if ((uVar3 & 0x20) == 0) {
                if (-1 < DebugLevel) {
                  printk("==> %s not support group cipher on WPA1 (GroupCipher=0x%x)\n",
                         "WPAMakeRsnIeCipher");
                }
                goto LAB_0011a908;
              }
              *(undefined4 *)((int)__dest + 4) = OUI_WPA_CCMP;
            }
            else {
              *(undefined4 *)((int)__dest + 4) = OUI_WPA_TKIP;
            }
          }
          else {
            *(undefined4 *)((int)__dest + 4) = OUI_WPA_WEP104;
          }
        }
        else {
          *(undefined4 *)((int)__dest + 4) = OUI_WPA_WEP40;
        }
        uVar3 = param_2[0x52];
        bVar10 = (uVar3 & 0x10) != 0;
        if (bVar10) {
          *(undefined4 *)((int)__dest + 10) = OUI_WPA_TKIP;
          uVar3 = param_2[0x52];
        }
        uVar6 = (uint)bVar10;
        if ((uVar3 & 0x20) != 0) {
          memmove(__dest_00 + uVar6 * 4 + 0xc,&OUI_WPA_CCMP,4);
          uVar6 = uVar6 + 1;
        }
        *(short *)((int)__dest + 8) = (short)uVar6;
        iVar9 = (uVar6 + 3) * 4;
        local_2b[0] = (byte)iVar9;
LAB_0011ac70:
        uVar3 = *puVar8;
      }
      else {
        if (uVar3 == 2) {
          *(undefined1 *)((int)__dest + -1) = 0;
          *__dest_00 = 1;
          uVar3 = param_2[0x8a];
          if ((uVar3 & 2) == 0) {
            if ((uVar3 & 4) == 0) {
              if ((uVar3 & 0x10) == 0) {
                if ((uVar3 & 0x20) == 0) {
                  if ((uVar3 & 0x40) == 0) {
                    if ((uVar3 & 0x80) == 0) {
                      if ((uVar3 & 0x100) == 0) {
                        if (-1 < DebugLevel) {
                          printk("==> %s not support group cipher on WPA2 (GroupCipher=0x%x)\n",
                                 "WPAMakeRsnIeCipher");
                        }
                        goto LAB_0011a908;
                      }
                      memmove(__dest,&OUI_WPA2_CIPHER_GCMP256,4);
                    }
                    else {
                      memmove(__dest,&OUI_WPA2_CIPHER_GCMP128,4);
                    }
                  }
                  else {
                    memmove(__dest,&OUI_WPA2_CIPHER_CCMP256,4);
                  }
                }
                else {
                  memmove(__dest,&OUI_WPA2_CIPHER_CCMP128,4);
                }
              }
              else {
                memmove(__dest,&OUI_WPA2_CIPHER_TKIP,4);
              }
            }
            else {
              memmove(__dest,&OUI_WPA2_CIPHER_WEP104,4);
            }
          }
          else {
            memmove(__dest,&OUI_WPA2_CIPHER_WEP40,4);
          }
          uVar3 = param_2[0x52];
          iVar9 = 0;
          if ((uVar3 & 0x10) != 0) {
            if ((*param_2 & 0x2000) != 0) {
              if (-1 < DebugLevel) {
                printk("==> %s not support group cipher on SAE\n","WPAMakeRsnIeCipher");
              }
              goto LAB_0011a908;
            }
            iVar9 = 1;
            *(undefined4 *)((int)__dest + 6) = OUI_WPA2_CIPHER_TKIP;
            uVar3 = param_2[0x52];
          }
          if ((uVar3 & 0x20) != 0) {
            iVar1 = iVar9 + 2;
            iVar9 = iVar9 + 1;
            memmove(__dest_00 + iVar1 * 4,&OUI_WPA2_CIPHER_CCMP128,4);
            uVar3 = param_2[0x52];
          }
          if ((uVar3 & 0x40) != 0) {
            iVar1 = iVar9 + 2;
            iVar9 = iVar9 + 1;
            memmove(__dest_00 + iVar1 * 4,&OUI_WPA2_CIPHER_CCMP256,4);
            uVar3 = param_2[0x52];
          }
          if ((uVar3 & 0x80) != 0) {
            iVar1 = iVar9 + 2;
            iVar9 = iVar9 + 1;
            memmove(__dest_00 + iVar1 * 4,&OUI_WPA2_CIPHER_GCMP128,4);
            uVar3 = param_2[0x52];
          }
          if ((uVar3 & 0x100) != 0) {
            iVar1 = iVar9 + 2;
            iVar9 = iVar9 + 1;
            memmove(__dest_00 + iVar1 * 4,&OUI_WPA2_CIPHER_GCMP256,4);
          }
          *(short *)((int)__dest + 4) = (short)iVar9;
          iVar9 = (iVar9 + 2) * 4;
          local_2b[0] = (byte)iVar9;
          goto LAB_0011ac70;
        }
        iVar9 = 0;
      }
      puVar5 = (undefined2 *)(__dest_00 + iVar9);
      if (uVar3 == 1) {
        uVar6 = *param_2;
        uVar3 = 1;
        if ((uVar6 & 8) == 0) {
          if ((uVar6 & 0x10) == 0) {
            if ((uVar6 & 0x20) == 0) {
              if (-1 < DebugLevel) {
                printk("==> %s not support AKM on WPA1\n","WPAMakeRsnIeAKM");
              }
              goto LAB_0011a908;
            }
            memmove(puVar5 + 1,&OUI_WPA_NONE_AKM,4);
            uVar6 = 0;
          }
          else {
            memmove(puVar5 + 1,&OUI_WPA_PSK_AKM,4);
            uVar6 = 0;
          }
        }
        else {
          memmove(puVar5 + 1,&OUI_WPA_8021X_AKM,4);
          uVar6 = 0;
        }
      }
      else if (uVar3 == 2) {
        uVar6 = *param_2;
        uVar3 = 0;
        if ((uVar6 & 0x40) != 0) {
          if ((*(char *)((int)param_2 + 0x3e6) == '\0') ||
             (param_1 != 2 || (char)param_2[0xa1] != '\x01')) {
            if ((char)param_2[0xf9] != '\0' && param_1 == 1) {
              if (*(char *)((int)param_2 + 0x3e2) == '\0') {
                uVar3 = 2;
                puVar2 = memmove(puVar5 + 1,&OUI_WPA2_AKM_8021X,4);
                iVar1 = 4;
              }
              else {
                uVar3 = 1;
                iVar1 = 0;
                puVar2 = puVar5 + 1;
              }
              memmove((undefined1 *)((int)puVar2 + iVar1),&OUI_WPA2_AKM_8021X_SHA256,4);
              uVar6 = *param_2;
              goto LAB_0011ab54;
            }
            puVar4 = &OUI_WPA2_AKM_8021X;
          }
          else {
            puVar4 = &OUI_WPA2_AKM_8021X_SHA256;
          }
          uVar3 = 1;
          memmove(puVar5 + 1,puVar4,4);
          uVar6 = *param_2;
        }
LAB_0011ab54:
        if ((uVar6 & 0x80) != 0) {
          if ((*(char *)((int)param_2 + 0x3e6) == '\0') ||
             (param_1 != 2 || (char)param_2[0xa1] != '\x01')) {
            if ((char)param_2[0xf9] == '\0' || param_1 != 1) {
              puVar4 = &OUI_WPA2_AKM_PSK;
              goto LAB_0011abb0;
            }
            if (*(char *)((int)param_2 + 0x3e2) == '\0') {
              iVar1 = uVar3 * 2;
              uVar3 = uVar3 + 1;
              memmove(puVar5 + iVar1 + 1,&OUI_WPA2_AKM_PSK,4);
              iVar1 = 4;
            }
            else {
              iVar1 = 0;
            }
            puVar4 = &OUI_WPA2_AKM_PSK_SHA256;
            puVar2 = (undefined2 *)((int)puVar5 + iVar1 + 2);
          }
          else {
            puVar4 = &OUI_WPA2_AKM_PSK_SHA256;
LAB_0011abb0:
            puVar2 = puVar5 + uVar3 * 2 + 1;
          }
          uVar3 = uVar3 + 1;
          memmove(puVar2,puVar4,4);
          uVar6 = *param_2;
        }
        if ((uVar6 & 0x400) != 0) {
          iVar1 = uVar3 * 2;
          uVar3 = uVar3 + 1;
          memmove(puVar5 + iVar1 + 1,&OUI_WPA2_AKM_8021X_SHA256,4);
          uVar6 = *param_2;
        }
        if ((uVar6 & 0x800) != 0) {
          iVar1 = uVar3 * 2;
          uVar3 = uVar3 + 1;
          memmove(puVar5 + iVar1 + 1,&OUI_WPA2_AKM_PSK_SHA256,4);
          uVar6 = *param_2;
        }
        if ((uVar6 & 0x2000) != 0) {
          iVar1 = uVar3 * 2;
          uVar3 = uVar3 + 1;
          memmove(puVar5 + iVar1 + 1,&OUI_WPA2_AKM_SAE_SHA256,4);
          uVar6 = *param_2;
        }
        if ((uVar6 & 0x4000) != 0) {
          iVar1 = uVar3 * 2;
          uVar3 = uVar3 + 1;
          memmove(puVar5 + iVar1 + 1,&OUI_WPA2_AKM_FT_SAE_SHA256,4);
          uVar6 = *param_2;
        }
        if ((uVar6 & 0x8000) != 0) {
          memmove(puVar5 + uVar3 * 2 + 1,&OUI_WPA2_AKM_SUITEB_SHA256,4);
          uVar6 = *param_2;
          uVar3 = uVar3 + 1 & 0xff;
        }
        if ((uVar6 & 0x10000) == 0) {
          uVar6 = (uVar3 - 1) * 4 & 0xff;
        }
        else {
          memmove(puVar5 + uVar3 * 2 + 1,&OUI_WPA2_AKM_SUITEB_SHA384,4);
          uVar3 = uVar3 + 1 & 0xff;
          uVar6 = (uVar3 - 1) * 4 & 0xff;
        }
      }
      else {
        uVar6 = 0xfc;
        uVar3 = 0;
      }
      uVar6 = uVar6 + iVar9 + 6;
      *puVar5 = (short)uVar3;
      uVar3 = uVar6 & 0xff;
      local_2b[0] = (byte)uVar6;
      if (*puVar8 == 2) {
        __dest_00[uVar3] = __dest_00[uVar3] & 0xfe | *(char *)((int)param_2 + 0x4e6) == '\x01';
        __dest_00[uVar3] = __dest_00[uVar3] & 0x7f | ((char)param_2[0xf8] != '\0') << 7;
        __dest_00[uVar3] = __dest_00[uVar3] & 0xbf | (*(char *)((int)param_2 + 0x3e2) != '\0') << 6;
        if (2 < DebugLevel) {
          printk("[PMF]%s: RSNIE Capability MFPC=%d, MFPR=%d\n","WPAMakeRsnIeCap");
        }
        local_2b[0] = local_2b[0] + 2;
        uVar3 = (uint)local_2b[0];
        if (uVar3 == 0xff) {
          printk(&_LC64,0x95b);
          dump_stack();
          goto LAB_0011a9c0;
        }
      }
      else {
LAB_0011a9c0:
        uVar3 = (uint)local_2b[0];
        if (uVar3 == 0xff) goto LAB_0011a908;
      }
      if (*puVar8 == 2) {
        puVar5 = (undefined2 *)(__dest_00 + uVar3);
        if (((param_3 == (int *)0x0 || (*param_2 & 0x6000) == 0) ||
            (*param_3 != 2 && (*param_3 - 0x20001U & 0xfffdffff) != 0)) ||
           (iVar9 = is_pmkid_cache_in_sec_config(param_2), iVar9 == 0)) {
          if ((char)param_2[0xf8] != '\0') {
            local_2b[1] = 0;
            local_2b[2] = 0;
            local_2b[0] = local_2b[0] + 2;
            *puVar5 = 0;
          }
        }
        else {
          local_2b[1] = 1;
          local_2b[2] = 0;
          *puVar5 = 1;
          memmove(puVar5 + 1,(void *)param_2[0x163],0x10);
          local_2b[0] = local_2b[0] + 0x12;
          if (-1 < DebugLevel) {
            printk("%s: (SAE) including the PMKID.\n","WPAInsertRsnIePMKID");
          }
        }
        if (local_2b[0] == 0xff) {
          printk(&_LC64,0x964);
          dump_stack();
          if (local_2b[0] == 0xff) goto LAB_0011a908;
        }
      }
      iVar9 = PMF_MakeRsnIeGMgmtCipher(param_2,(int)puVar7 - (int)param_2 & 0xff,local_2b);
      if (iVar9 != 0) {
        if (local_2b[0] == 0xff) {
          printk(&_LC64,0x96f);
          dump_stack();
          if (local_2b[0] == 0xff) goto LAB_0011a908;
        }
        *(byte *)((int)puVar7 + 0x5a2) = local_2b[0];
        hex_dump("The RSNE",__dest_00);
      }
    }
LAB_0011a908:
    puVar7 = (uint *)((int)puVar7 + 1);
    __dest = (void *)((int)__dest + 0xff);
    if (puVar7 == (uint *)((int)param_2 + 2)) {
      return;
    }
  } while( true );
}

