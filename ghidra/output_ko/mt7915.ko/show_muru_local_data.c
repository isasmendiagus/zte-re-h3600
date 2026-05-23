// module: mt7915.ko
// function: show_muru_local_data @ 0x1871c8
// size: 3456 bytes
//

void show_muru_local_data(int param_1,int param_2)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  char cVar6;
  char *__s;
  size_t __n;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  undefined1 *__dest;
  uint uVar12;
  int iVar13;
  int iVar14;
  uint local_78;
  undefined1 auStack_73 [79];
  
  uVar10 = *(uint *)(param_1 + 0x7959c0);
  if (param_2 == 0) {
    return;
  }
  cVar6 = delimitcnt(param_2,&_LC251);
  if (3 < (byte)(cVar6 + 1U)) {
    if (DebugLevel < 0) {
      return;
    }
    printk("Num of Input Parameters Wrong\n");
    return;
  }
  __s = (char *)rstrtok(param_2,&_LC251);
  if (__s == (char *)0x0) {
    bVar5 = false;
    bVar3 = false;
    bVar4 = false;
    bVar2 = false;
  }
  else {
    uVar12 = 0;
    bVar5 = false;
    bVar4 = false;
    bVar3 = false;
    bVar2 = false;
    do {
      uVar11 = uVar12 & 0xff;
      uVar12 = uVar12 + 1;
      __dest = auStack_73 + uVar11 * 0x19;
      __n = strlen(__s);
      memcpy(__dest,__s,__n);
      iVar7 = memcmp(__dest,&_LC487,3);
      if (iVar7 == 0) {
        bVar2 = true;
        bVar3 = bVar2;
        bVar4 = bVar2;
        bVar5 = bVar2;
      }
      iVar7 = memcmp(__dest,"muruparam",9);
      if (iVar7 == 0) {
        bVar2 = true;
      }
      iVar7 = memcmp(__dest,"qleninfo",8);
      if (iVar7 == 0) {
        bVar3 = true;
      }
      iVar7 = memcmp(__dest,"bsrpctrl",8);
      if (iVar7 == 0) {
        bVar4 = true;
      }
      iVar7 = memcmp(__dest,"txcmdctrl",9);
      if (iVar7 == 0) {
        bVar5 = true;
      }
      __s = (char *)rstrtok(0,&_LC251);
    } while (__s != (char *)0x0);
  }
  if (0xdfffffff < uVar10) {
    FUN_0017f59c(param_1);
  }
  if (0 < DebugLevel) {
    printk("_rMuru_Local_Data (0x%08X)\n",uVar10);
  }
  cVar6 = *(char *)(param_1 + 0x7959cc);
  if (bVar2) {
    iVar7 = *(int *)(param_1 + 0x7959c8);
    if (cVar6 == '\0') {
      if (0 < DebugLevel) {
        printk("|-rMuruPara (0x%08X)\n",iVar7);
        if (DebugLevel < 1) {
LAB_00187ba4:
          if (DebugLevel < 1) {
LAB_00187c8c:
            if (0 < DebugLevel) {
              uVar8 = FUN_00174570(param_1,iVar7 + 10);
              printk("| |-(0x%08X) u1UlMpduCntPolicy = %d\n",iVar7 + 10,uVar8);
              if (0 < DebugLevel) {
                uVar8 = FUN_00174570(param_1,iVar7 + 0xb);
                printk("| |-(0x%08X) u1DelayPolicy = %d\n",iVar7 + 0xb,uVar8);
LAB_00187d00:
                if ((0 < DebugLevel) &&
                   (printk("| |-(0x%08X) rTpcManPara\n",iVar7 + 0xc), 0 < DebugLevel)) {
                  printk("| |-|-(0x%08X) ai1ManTargetRssi\n",iVar7 + 0xc);
                }
              }
            }
          }
          else {
            uVar8 = FUN_00174570(param_1,iVar7 + 4);
            printk("| |-(0x%08X) fgTxcmdsnd = %d\n",iVar7 + 4,uVar8);
            if (0 < DebugLevel) {
              uVar8 = FUN_00174570(param_1,iVar7 + 5);
              printk("| |-(0x%08X) fgTpc = %d\n",iVar7 + 5,uVar8);
LAB_00187c18:
              if (DebugLevel < 1) goto LAB_00187d00;
              uVar8 = FUN_00174570(param_1,iVar7 + 6);
              printk("| |-(0x%08X) fgTpcManualMode = %d\n",iVar7 + 6,uVar8);
              if (0 < DebugLevel) {
                uVar8 = FUN_00174528(param_1,iVar7 + 8);
                printk("| |-(0x%08X) u2fixedTPNum = %d\n",iVar7 + 8,uVar8);
                goto LAB_00187c8c;
              }
            }
          }
        }
        else {
          uVar8 = FUN_00174570(param_1,iVar7);
          printk("| |-(0x%08X) fgPingPongAlgo = %d\n",iVar7,uVar8);
          if (0 < DebugLevel) {
            uVar8 = FUN_00174570(param_1,iVar7 + 1);
            printk("| |-(0x%08X) fgSu = %d\n",iVar7 + 1,uVar8);
            if (DebugLevel < 1) goto LAB_00187c18;
            uVar8 = FUN_00174570(param_1,iVar7 + 2);
            printk("| |-(0x%08X) fg256BitMap = %d\n",iVar7 + 2,uVar8);
            if (0 < DebugLevel) {
              uVar8 = FUN_00174570(param_1,iVar7 + 3);
              printk("| |-(0x%08X) fgUlBsrp = %d\n",iVar7 + 3,uVar8);
              goto LAB_00187ba4;
            }
          }
        }
      }
      iVar14 = 0;
      iVar9 = DebugLevel;
      do {
        if (0 < iVar9) {
          iVar9 = iVar14 + iVar7 + 0xc;
          uVar8 = FUN_00174570(param_1,iVar9);
          printk("| |-|-|-(0x%08X) ai1ManTargetRssi[%d] = %d\n",iVar9,iVar14,uVar8);
          iVar9 = DebugLevel;
        }
        iVar14 = iVar14 + 1;
      } while (iVar14 != 0x10);
      if (0 < iVar9) {
        uVar8 = FUN_00174570(param_1,iVar7 + 0x1c);
        printk("| |-(0x%08X) fgTpcOptMode = %d\n",iVar7 + 0x1c,uVar8);
        iVar9 = DebugLevel;
        if (0 < DebugLevel) {
          printk("| |-(0x%08X) u1TxCmdQLen\n",iVar7 + 0x1d);
          iVar9 = DebugLevel;
        }
      }
      iVar14 = 0;
      do {
        if (0 < iVar9) {
          iVar9 = iVar14 + iVar7 + 0x1d;
          uVar8 = FUN_00174570(param_1,iVar9);
          printk("| |-|-(0x%08X) u1TxCmdQLen[%d] = %d\n",iVar9,iVar14,uVar8);
          iVar9 = DebugLevel;
        }
        iVar14 = iVar14 + 1;
      } while (iVar14 != 4);
      if (0 < iVar9) {
        uVar8 = FUN_00174570(param_1,iVar7 + 0x21);
        printk("| |-(0x%08X) fgTBSuAdaptiveLSIGLen = %d\n",iVar7 + 0x21,uVar8);
        if (DebugLevel < 1) {
LAB_0018773c:
          if (DebugLevel < 1) {
LAB_00187850:
            if (0 < DebugLevel) {
              uVar8 = FUN_00174570(param_1,iVar7 + 0x2f);
              printk("| |-(0x%08X) u1DlSolictAckPolicy = %d\n",iVar7 + 0x2f,uVar8);
              goto LAB_00187370;
            }
          }
          else {
            uVar8 = FUN_00174570(param_1,iVar7 + 0x2a);
            printk("| |-(0x%08X) fgPreGrp = %d\n",iVar7 + 0x2a,uVar8);
            if (0 < DebugLevel) {
              uVar8 = FUN_00174570(param_1,iVar7 + 0x2b);
              printk("| |-(0x%08X) fgTxopBurst = %d\n",iVar7 + 0x2b,uVar8);
LAB_001877b0:
              uVar12 = iVar7 + 0x2c;
              if (DebugLevel < 1) goto LAB_00187370;
              local_78 = 0;
              mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar12 & 0xfffffffc);
              printk("| |-(0x%08X) i2PsdDiffThr = %d\n",uVar12,
                     (int)(short)(local_78 >> ((uVar12 & 3) << 3)));
              if (0 < DebugLevel) {
                uVar8 = FUN_00174570(param_1,iVar7 + 0x2e);
                printk("| |-(0x%08X) u1SplPriority = %d\n",iVar7 + 0x2e,uVar8);
                goto LAB_00187850;
              }
            }
          }
        }
        else {
          uVar8 = FUN_00174570(param_1,iVar7 + 0x22);
          printk("| |-(0x%08X) fgSRState = %d\n",iVar7 + 0x22,uVar8);
          if (0 < DebugLevel) {
            uVar8 = FUN_00174570(param_1,iVar7 + 0x23);
            printk("| |-(0x%08X) u1TypeCDelayReq = %d\n",iVar7 + 0x23,uVar8);
            if (DebugLevel < 1) goto LAB_001877b0;
            local_78 = 0;
            mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar7 + 0x24);
            printk("| |-(0x%08X) u4BsrTruncateThr = %d\n",iVar7 + 0x24,local_78);
            if (0 < DebugLevel) {
              uVar8 = FUN_00174528(param_1,iVar7 + 0x28);
              printk("| |-(0x%08X) u2MaxStaCntLimit = %d\n",iVar7 + 0x28,uVar8);
              goto LAB_0018773c;
            }
          }
        }
      }
      goto LAB_00187378;
    }
LAB_001873dc:
    if (bVar3) goto LAB_001873e4;
    goto LAB_0018738c;
  }
  if (cVar6 != '\0') goto LAB_001873dc;
LAB_00187370:
  if (0 < DebugLevel) {
    local_78 = 0;
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar10 + 0x30);
    printk("|-(0x%08X) eDuSchWeight = %d\n",uVar10 + 0x30,local_78);
  }
LAB_00187378:
  if (bVar3) {
LAB_001873e4:
    iVar7 = *(int *)(param_1 + 0x7959d0);
    if (*(char *)(param_1 + 0x7959d4) == '\0') {
      if ((0 < DebugLevel) && (printk("|-rQlenInfo (0x%08X)\n",iVar7), 0 < DebugLevel)) {
        printk("| |-(0x%08X) au4DLQlen\n",iVar7);
      }
      iVar13 = 0;
      iVar9 = DebugLevel;
      iVar14 = iVar7;
      do {
        if (0 < iVar9) {
          local_78 = 0;
          mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar14);
          printk("| |-|-(0x%08X) au4DLQlen[%d] = %d\n",iVar14,iVar13,local_78);
          iVar9 = DebugLevel;
        }
        iVar13 = iVar13 + 1;
        iVar14 = iVar14 + 4;
      } while (iVar13 != 4);
      iVar14 = iVar7 + 0x10;
      if (0 < iVar9) {
        printk("| |-(0x%08X) au4ULQlen\n",iVar14);
        iVar9 = DebugLevel;
      }
      iVar13 = 0;
      do {
        if (0 < iVar9) {
          local_78 = 0;
          mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar14);
          printk("| |-|-(0x%08X) au4ULQlen[%d] = %d\n",iVar14,iVar13,local_78);
          iVar9 = DebugLevel;
        }
        iVar13 = iVar13 + 1;
        iVar14 = iVar14 + 4;
      } while (iVar13 != 4);
      if (0 < iVar9) {
        local_78 = 0;
        mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar7 + 0x20,&local_78);
        printk("| |-(0x%08X) u4TotDLQlenAllAc = %d\n",iVar7 + 0x20,local_78);
        if (0 < DebugLevel) {
          local_78 = 0;
          mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar7 + 0x24,&local_78);
          printk("| |-(0x%08X) u4TotULQlenAllAc = %d\n",iVar7 + 0x24,local_78);
          if (DebugLevel < 1) goto LAB_0018738c;
          local_78 = 0;
          mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar7 + 0x28,&local_78);
          printk("| |-(0x%08X) u4BsrTruncateThr = %d\n",iVar7 + 0x28,local_78);
        }
        goto LAB_00187564;
      }
    }
    else {
LAB_00187564:
      if (cVar6 == '\0') goto LAB_00187380;
    }
  }
  else {
LAB_00187380:
    if (0 < DebugLevel) {
      uVar8 = FUN_00174528(param_1,uVar10 + 0x60);
      printk("|-(0x%08X) u2MuruSplHeadWlanId = %d\n",uVar10 + 0x60,uVar8);
    }
  }
LAB_0018738c:
  if (bVar4) {
    bVar1 = *(byte *)(param_1 + 0x7959dc);
    iVar7 = *(int *)(param_1 + 0x7959d8);
    if ((bVar1 == 0) && (0 < DebugLevel)) {
      printk("|-rExt_Cmd_Bsrp_Ctrl (0x%08X)\n",iVar7);
      if (0 < DebugLevel) {
        uVar8 = FUN_00174570(param_1,iVar7 + 8);
        printk("| |-(0x%08X) u1TriggerFlow = %d\n",iVar7 + 8,uVar8);
        if (DebugLevel < 1) goto LAB_00187394;
        uVar8 = FUN_00174570(param_1,iVar7);
        printk("| |-(0x%08X) u2BsrpInterval = %d\n",iVar7,uVar8);
        if (DebugLevel < 1) goto LAB_00187394;
        uVar8 = FUN_00174528(param_1,iVar7 + 2);
        printk("| |-(0x%08X) u2BsrpRuAlloc = %d\n",iVar7 + 2,uVar8);
        if (DebugLevel < 1) goto LAB_00187394;
        local_78 = (uint)bVar1;
        mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0));
        printk("| |-(0x%08X) u4PpduDur = %d\n",iVar7 + 4,local_78);
      }
      if (0 < DebugLevel) {
        uVar8 = FUN_00174570(param_1,iVar7 + 9);
        printk("| |-(0x%08X) fgExtCmdBsrp = %d\n",iVar7 + 9,uVar8);
      }
    }
  }
LAB_00187394:
  if (bVar5) {
    bVar1 = *(byte *)(param_1 + 0x7959e4);
    iVar7 = *(int *)(param_1 + 0x7959e0);
    if (bVar1 == 0) {
      if (DebugLevel < 1) {
        return;
      }
      printk("|-rMuru_TxCmd_Ctrl (0x%08X)\n",iVar7);
      if (0 < DebugLevel) {
        uVar8 = FUN_00174570(param_1,iVar7);
        printk("| |-(0x%08X) fgGlobalPreLoad = %d\n",iVar7,uVar8);
        if (DebugLevel < 1) {
          return;
        }
        uVar12 = iVar7 + 2;
        local_78 = (uint)bVar1;
        mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar12 & 0xfffffffc);
        printk("| |-(0x%08X) i2PuPreGrpMaxPsd_dBm = %d\n",uVar12,
               (int)(short)(local_78 >> ((uVar12 & 3) << 3)));
      }
    }
  }
  if ((cVar6 == '\0') && (0 < DebugLevel)) {
    uVar8 = FUN_00174570(param_1,uVar10 + 0x84);
    printk("|-(0x%08X) fgMumUl = %d\n",uVar10 + 0x84,uVar8);
  }
  return;
}

