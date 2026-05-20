// module: mt7915.ko
// function: show_muru_tx_info @ 0x184bcc
// size: 9724 bytes
//

void show_muru_tx_info(int param_1,int param_2)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  char cVar5;
  char *__s;
  size_t __n;
  int iVar6;
  undefined4 uVar7;
  uint uVar8;
  uint uVar9;
  undefined1 *__dest;
  uint uVar10;
  int iVar11;
  int iVar12;
  undefined4 local_78;
  undefined1 auStack_73 [79];
  
  uVar8 = *(uint *)(param_1 + 0x7959e8);
  if (param_2 == 0) {
    return;
  }
  cVar5 = delimitcnt(param_2,&_LC251);
  if (3 < (byte)(cVar5 + 1U)) {
    if (DebugLevel < 0) {
      return;
    }
    printk("Num of Input Parameters Wrong\n");
    return;
  }
  __s = (char *)rstrtok(param_2,&_LC251);
  if (__s == (char *)0x0) {
    bVar4 = false;
    bVar3 = false;
    bVar2 = false;
    bVar1 = false;
  }
  else {
    uVar10 = 0;
    bVar4 = false;
    bVar3 = false;
    bVar2 = false;
    bVar1 = false;
    do {
      uVar9 = uVar10 & 0xff;
      uVar10 = uVar10 + 1;
      __dest = auStack_73 + uVar9 * 0x19;
      __n = strlen(__s);
      memcpy(__dest,__s,__n);
      iVar6 = memcmp(__dest,&_LC487,3);
      if (iVar6 == 0) {
        bVar1 = true;
        bVar2 = bVar1;
        bVar3 = bVar1;
        bVar4 = bVar1;
      }
      iVar6 = memcmp(__dest,"Globaldata",10);
      if (iVar6 == 0) {
        bVar1 = true;
      }
      iVar6 = memcmp(__dest,"ProtectData",0xb);
      if (iVar6 == 0) {
        bVar2 = true;
      }
      iVar6 = memcmp(__dest,"SxnTxData",9);
      if (iVar6 == 0) {
        bVar3 = true;
      }
      iVar6 = memcmp(__dest,"SxnTrigData",0xb);
      if (iVar6 == 0) {
        bVar4 = true;
      }
      __s = (char *)rstrtok(0,&_LC251);
    } while (__s != (char *)0x0);
  }
  if (0xdfffffff < uVar8) {
    FUN_0017f59c(param_1);
  }
  if (0 < DebugLevel) {
    printk("_rMuru_Tx_Info; (0x%08X)\n",uVar8);
  }
  if (((bVar1) && (iVar6 = *(int *)(param_1 + 0x7959f0), *(char *)(param_1 + 0x7959f4) == '\0')) &&
     (0 < DebugLevel)) {
    printk("|-rGlobalData (0x%08X)\n",iVar6);
    if (DebugLevel < 1) {
LAB_00185b5c:
      if (DebugLevel < 1) {
LAB_00185c2c:
        if (DebugLevel < 1) {
LAB_00185cfc:
          if (DebugLevel < 1) {
LAB_00185de4:
            if (0 < DebugLevel) {
              uVar7 = FUN_00174570(param_1,iVar6 + 0x14);
              printk("| |-(0x%08X) u1SerialId = %d\n",iVar6 + 0x14,uVar7);
              if (0 < DebugLevel) {
                uVar7 = FUN_00174570(param_1,iVar6 + 0x15);
                printk("| |-(0x%08X) u1SpeIdx = %d\n",iVar6 + 0x15,uVar7);
LAB_00185e4c:
                if (0 < DebugLevel) {
                  uVar7 = FUN_00174570(param_1,iVar6 + 0x16);
                  printk("| |-(0x%08X) fgOptionalBackoff = %d\n",iVar6 + 0x16,uVar7);
                }
              }
            }
          }
          else {
            uVar7 = FUN_00174570(param_1,iVar6 + 0x22);
            printk("| |-(0x%08X) fgSRState = %d\n",iVar6 + 0x22,uVar7);
            if (0 < DebugLevel) {
              uVar7 = FUN_00174570(param_1,iVar6 + 0xc);
              printk("| |-(0x%08X) u1AggPolicy = %d\n",iVar6 + 0xc,uVar7);
LAB_00185d64:
              if (DebugLevel < 1) goto LAB_00185e4c;
              uVar7 = FUN_00174570(param_1,iVar6 + 0xd);
              printk("| |-(0x%08X) u1Bandwidth = %d\n",iVar6 + 0xd,uVar7);
              if (0 < DebugLevel) {
                local_78 = 0;
                mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar6 + 0x10);
                printk("| |-(0x%08X) u4AntId = %d\n",iVar6 + 0x10,local_78);
                goto LAB_00185de4;
              }
            }
          }
        }
        else {
          uVar7 = FUN_00174570(param_1,iVar6 + 8);
          printk("| |-(0x%08X) fgTxop = %d\n",iVar6 + 8,uVar7);
          if (0 < DebugLevel) {
            uVar7 = FUN_00174570(param_1,iVar6 + 9);
            printk("| |-(0x%08X) u1OwnMac = %d\n",iVar6 + 9,uVar7);
LAB_00185c94:
            if (DebugLevel < 1) goto LAB_00185d64;
            uVar7 = FUN_00174570(param_1,iVar6 + 10);
            printk("| |-(0x%08X) fgIgnoreBw = %d\n",iVar6 + 10,uVar7);
            if (0 < DebugLevel) {
              uVar7 = FUN_00174570(param_1,iVar6 + 0xb);
              printk("| |-(0x%08X) fgSmartAnt = %d\n",iVar6 + 0xb,uVar7);
              goto LAB_00185cfc;
            }
          }
        }
      }
      else {
        uVar7 = FUN_00174570(param_1,iVar6 + 4);
        printk("| |-(0x%08X) u1PresentSpTblIdx = %d\n",iVar6 + 4,uVar7);
        if (0 < DebugLevel) {
          uVar7 = FUN_00174570(param_1,iVar6 + 5);
          printk("| |-(0x%08X) fgTv = %d\n",iVar6 + 5,uVar7);
LAB_00185bc4:
          if (DebugLevel < 1) goto LAB_00185c94;
          uVar7 = FUN_00174570(param_1,iVar6 + 6);
          printk("| |-(0x%08X) fgDbdcIdx = %d\n",iVar6 + 6,uVar7);
          if (0 < DebugLevel) {
            uVar7 = FUN_00174570(param_1,iVar6 + 7);
            printk("| |-(0x%08X) fgPreload = %d\n",iVar6 + 7,uVar7);
            goto LAB_00185c2c;
          }
        }
      }
    }
    else {
      uVar7 = FUN_00174570(param_1,iVar6);
      printk("| |-(0x%08X) u1TxdNum = %d\n",iVar6,uVar7);
      if (0 < DebugLevel) {
        uVar7 = FUN_00174570(param_1,iVar6 + 1);
        printk("| |-(0x%08X) u1Qid = %d\n",iVar6 + 1,uVar7);
        if (DebugLevel < 1) goto LAB_00185bc4;
        uVar7 = FUN_00174570(param_1,iVar6 + 2);
        printk("| |-(0x%08X) u1TxcmdType = %d\n",iVar6 + 2,uVar7);
        if (0 < DebugLevel) {
          uVar7 = FUN_00174570(param_1,iVar6 + 3);
          printk("| |-(0x%08X) fgSpl = %d\n",iVar6 + 3,uVar7);
          goto LAB_00185b5c;
        }
      }
    }
  }
  if ((bVar2) && (iVar6 = *(int *)(param_1 + 0x7959f8), *(char *)(param_1 + 0x7959fc) == '\0')) {
    if ((0 < DebugLevel) && (printk("|-rProtectData (0x%08X)\n",iVar6), 0 < DebugLevel)) {
      uVar7 = FUN_00174570(param_1,iVar6);
      printk("| |-(0x%08X) u1Protect = %d\n",iVar6,uVar7);
    }
    iVar12 = iVar6 + 1;
    uVar8 = FUN_00174570(param_1,iVar12);
    if (0 < DebugLevel) {
      uVar7 = FUN_00174570(param_1,iVar12);
      printk("| |-(0x%08X) u1StaCnt = %d\n",iVar12,uVar7);
      if (DebugLevel < 1) {
LAB_00186cb8:
        if (DebugLevel < 1) {
LAB_00186d88:
          if (0 < DebugLevel) {
            printk("| |-(0x%08X) rProtRuInfo\n",iVar6 + 10);
          }
        }
        else {
          uVar7 = FUN_00174570(param_1,iVar6 + 6);
          printk("| |-(0x%08X) u1TxMode = %d\n",iVar6 + 6,uVar7);
          if (0 < DebugLevel) {
            uVar7 = FUN_00174570(param_1,iVar6 + 7);
            printk("| |-(0x%08X) u1Nsts = %d\n",iVar6 + 7,uVar7);
LAB_00186d20:
            if (0 < DebugLevel) {
              uVar7 = FUN_00174570(param_1,iVar6 + 8);
              printk("| |-(0x%08X) fgCoding = %d\n",iVar6 + 8,uVar7);
              if (0 < DebugLevel) {
                uVar7 = FUN_00174570(param_1,iVar6 + 9);
                printk("| |-(0x%08X) fgDoppler = %d\n",iVar6 + 9,uVar7);
                goto LAB_00186d88;
              }
            }
          }
        }
      }
      else {
        uVar7 = FUN_00174570(param_1,iVar6 + 2);
        printk("| |-(0x%08X) fgCascadeIdx = %d\n",iVar6 + 2,uVar7);
        if (0 < DebugLevel) {
          uVar7 = FUN_00174570(param_1,iVar6 + 3);
          printk("| |-(0x%08X) fgCsRequired = %d\n",iVar6 + 3,uVar7);
          if (DebugLevel < 1) goto LAB_00186d20;
          uVar7 = FUN_00174570(param_1,iVar6 + 4);
          printk("| |-(0x%08X) u1TfPad = %d\n",iVar6 + 4,uVar7);
          if (0 < DebugLevel) {
            uVar7 = FUN_00174570(param_1,iVar6 + 5);
            printk("| |-(0x%08X) u1Rate = %d\n",iVar6 + 5,uVar7);
            goto LAB_00186cb8;
          }
        }
      }
    }
    if (uVar8 != 0) {
      iVar6 = iVar6 + 0xc;
      uVar10 = 0;
      do {
        iVar12 = iVar6 + -2;
        if ((0 < DebugLevel) &&
           (printk("| |-|-(0x%08X) rProtRuInfo[%d]\n",iVar12,uVar10), 0 < DebugLevel)) {
          uVar7 = FUN_00174528(param_1,iVar12);
          printk("| |-|-|-(0x%08X) u2Aid = %d\n",iVar12,uVar7);
          if (0 < DebugLevel) {
            uVar7 = FUN_00174570(param_1,iVar6);
            printk("| |-|-|-(0x%08X) u1RuAlloc = %d\n",iVar6,uVar7);
          }
        }
        uVar10 = uVar10 + 1;
        iVar6 = iVar6 + 4;
      } while ((uVar10 & 0xff) < uVar8);
    }
  }
  if ((bVar3) && (iVar6 = *(int *)(param_1 + 0x795a00), *(char *)(param_1 + 0x795a04) == '\0')) {
    if (0 < DebugLevel) {
      printk("|-rSxnTxData (0x%08X)\n",iVar6);
      if (DebugLevel < 1) {
LAB_001865bc:
        if (0 < DebugLevel) {
          uVar7 = FUN_00174570(param_1,iVar6 + 4);
          printk("| |-(0x%08X) u1SigBCh2StaCnt = %d\n",iVar6 + 4,uVar7);
        }
      }
      else {
        uVar7 = FUN_00174570(param_1,iVar6);
        printk("| |-(0x%08X) u1Rxv = %d\n",iVar6,uVar7);
        if (0 < DebugLevel) {
          uVar7 = FUN_00174570(param_1,iVar6 + 1);
          printk("| |-(0x%08X) fgRsp = %d\n",iVar6 + 1,uVar7);
          if (0 < DebugLevel) {
            uVar7 = FUN_00174570(param_1,iVar6 + 2);
            printk("| |-(0x%08X) fgPsIgnore = %d\n",iVar6 + 2,uVar7);
            if (0 < DebugLevel) {
              uVar7 = FUN_00174570(param_1,iVar6 + 3);
              printk("| |-(0x%08X) u1SigBCh1StaCnt = %d\n",iVar6 + 3,uVar7);
              goto LAB_001865bc;
            }
          }
        }
      }
    }
    iVar12 = iVar6 + 5;
    uVar8 = FUN_00174570(param_1,iVar12);
    if (0 < DebugLevel) {
      uVar7 = FUN_00174570(param_1,iVar12);
      printk("| |-(0x%08X) u1StaCnt = %d\n",iVar12,uVar7);
      if (DebugLevel < 1) {
LAB_00186318:
        if (DebugLevel < 1) {
LAB_001863f0:
          if (0 < DebugLevel) {
            uVar7 = FUN_00174570(param_1,iVar6 + 0xe);
            printk("| |-(0x%08X) fgCmdPower = %d\n",iVar6 + 0xe,uVar7);
            if (0 < DebugLevel) {
              uVar7 = FUN_00174528(param_1,iVar6 + 0x10);
              printk("| |-(0x%08X) u2MuPpduDur = %d\n",iVar6 + 0x10,uVar7);
LAB_0018645c:
              if (0 < DebugLevel) {
                uVar7 = FUN_00174570(param_1,iVar6 + 0x12);
                printk("| |-(0x%08X) u1TxPower = %d\n",iVar6 + 0x12,uVar7);
                if (0 < DebugLevel) {
                  printk("| |-(0x%08X) aucRuAlloc\n",iVar6 + 0x13);
                }
              }
            }
          }
        }
        else {
          uVar7 = FUN_00174570(param_1,iVar6 + 10);
          printk("| |-(0x%08X) fgSigBCompress = %d\n",iVar6 + 10,uVar7);
          if (0 < DebugLevel) {
            uVar7 = FUN_00174570(param_1,iVar6 + 0xb);
            printk("| |-(0x%08X) u1LtfSym = %d\n",iVar6 + 0xb,uVar7);
LAB_00186384:
            if (DebugLevel < 1) goto LAB_0018645c;
            uVar7 = FUN_00174570(param_1,iVar6 + 0xc);
            printk("| |-(0x%08X) u1Gi = %d\n",iVar6 + 0xc,uVar7);
            if (0 < DebugLevel) {
              uVar7 = FUN_00174570(param_1,iVar6 + 0xd);
              printk("| |-(0x%08X) fgStbc = %d\n",iVar6 + 0xd,uVar7);
              goto LAB_001863f0;
            }
          }
        }
      }
      else {
        uVar7 = FUN_00174570(param_1,iVar6 + 6);
        printk("| |-(0x%08X) u1SigBSym = %d\n",iVar6 + 6,uVar7);
        if (0 < DebugLevel) {
          uVar7 = FUN_00174570(param_1,iVar6 + 7);
          printk("| |-(0x%08X) u1SigBMcs = %d\n",iVar6 + 7,uVar7);
          if (DebugLevel < 1) goto LAB_00186384;
          uVar7 = FUN_00174570(param_1,iVar6 + 8);
          printk("| |-(0x%08X) fgRa = %d\n",iVar6 + 8,uVar7);
          if (0 < DebugLevel) {
            uVar7 = FUN_00174570(param_1,iVar6 + 9);
            printk("| |-(0x%08X) fgSigBDcm = %d\n",iVar6 + 9,uVar7);
            goto LAB_00186318;
          }
        }
      }
    }
    iVar11 = 0;
    iVar12 = DebugLevel;
    do {
      if (0 < iVar12) {
        iVar12 = iVar11 + iVar6 + 0x13;
        uVar7 = FUN_00174570(param_1,iVar12);
        printk("| |-|-(0x%08X) aucRuAlloc[%d] = %d\n",iVar12,iVar11,uVar7);
        iVar12 = DebugLevel;
      }
      iVar11 = iVar11 + 1;
    } while (iVar11 != 8);
    if (0 < iVar12) {
      uVar7 = FUN_00174570(param_1,iVar6 + 0x1b);
      printk("| |-(0x%08X) fgDoppler = %d\n",iVar6 + 0x1b,uVar7);
      if (DebugLevel < 1) {
LAB_00186f1c:
        if (DebugLevel < 1) {
LAB_00186ff4:
          if (DebugLevel < 1) {
LAB_001870cc:
            if (DebugLevel < 1) {
LAB_001871a4:
              if (0 < DebugLevel) {
                printk("| |-(0x%08X) arTxcmdUser\n",iVar6 + 0x2e);
              }
            }
            else {
              uVar7 = FUN_00174570(param_1,iVar6 + 0x28);
              printk("| |-(0x%08X) u1PreamblePuncture = %d\n",iVar6 + 0x28,uVar7);
              if (0 < DebugLevel) {
                uVar7 = FUN_00174570(param_1,iVar6 + 0x29);
                printk("| |-(0x%08X) u1MuUser = %d\n",iVar6 + 0x29,uVar7);
LAB_00187138:
                if (0 < DebugLevel) {
                  uVar7 = FUN_00174528(param_1,iVar6 + 0x2a);
                  printk("| |-(0x%08X) u2ProtectionDuration = %d\n",iVar6 + 0x2a,uVar7);
                  if (0 < DebugLevel) {
                    uVar7 = FUN_00174528(param_1,iVar6 + 0x2c);
                    printk("| |-(0x%08X) u2ResponseDuration = %d\n",iVar6 + 0x2c,uVar7);
                    goto LAB_001871a4;
                  }
                }
              }
            }
          }
          else {
            uVar7 = FUN_00174570(param_1,iVar6 + 0x24);
            printk("| |-(0x%08X) fgRu26dSigBCh1 = %d\n",iVar6 + 0x24,uVar7);
            if (0 < DebugLevel) {
              uVar7 = FUN_00174570(param_1,iVar6 + 0x25);
              printk("| |-(0x%08X) fgRu26uSigBCh2 = %d\n",iVar6 + 0x25,uVar7);
LAB_00187060:
              if (DebugLevel < 1) goto LAB_00187138;
              uVar7 = FUN_00174570(param_1,iVar6 + 0x26);
              printk("| |-(0x%08X) u1TxMode = %d\n",iVar6 + 0x26,uVar7);
              if (0 < DebugLevel) {
                uVar7 = FUN_00174570(param_1,iVar6 + 0x27);
                printk("| |-(0x%08X) fgDynamicBw = %d\n",iVar6 + 0x27,uVar7);
                goto LAB_001870cc;
              }
            }
          }
        }
        else {
          uVar7 = FUN_00174570(param_1,iVar6 + 0x20);
          printk("| |-(0x%08X) u1Mu1UserPosition = %d\n",iVar6 + 0x20,uVar7);
          if (0 < DebugLevel) {
            uVar7 = FUN_00174570(param_1,iVar6 + 0x21);
            printk("| |-(0x%08X) u1Mu2UserPosition = %d\n",iVar6 + 0x21,uVar7);
LAB_00186f88:
            if (DebugLevel < 1) goto LAB_00187060;
            uVar7 = FUN_00174570(param_1,iVar6 + 0x22);
            printk("| |-(0x%08X) u1Mu3UserPosition = %d\n",iVar6 + 0x22,uVar7);
            if (0 < DebugLevel) {
              uVar7 = FUN_00174570(param_1,iVar6 + 0x23);
              printk("| |-(0x%08X) u1MuGroupId = %d\n",iVar6 + 0x23,uVar7);
              goto LAB_00186ff4;
            }
          }
        }
      }
      else {
        uVar7 = FUN_00174570(param_1,iVar6 + 0x1c);
        printk("| |-(0x%08X) u1PrimaryUserIdx = %d\n",iVar6 + 0x1c,uVar7);
        if (0 < DebugLevel) {
          uVar7 = FUN_00174570(param_1,iVar6 + 0x1d);
          printk("| |-(0x%08X) u1Ltf = %d\n",iVar6 + 0x1d,uVar7);
          if (DebugLevel < 1) goto LAB_00186f88;
          uVar7 = FUN_00174570(param_1,iVar6 + 0x1e);
          printk("| |-(0x%08X) u1TfPad = %d\n",iVar6 + 0x1e,uVar7);
          if (0 < DebugLevel) {
            uVar7 = FUN_00174570(param_1,iVar6 + 0x1f);
            printk("| |-(0x%08X) u1Mu0UserPosition = %d\n",iVar6 + 0x1f,uVar7);
            goto LAB_00186f1c;
          }
        }
      }
    }
    iVar6 = iVar6 + 0x2e;
    if (uVar8 != 0) {
      uVar10 = 0;
      do {
        if (0 < DebugLevel) {
          printk("| |-|-(0x%08X) arTxcmdUser[%d]\n",iVar6,uVar10);
          if (DebugLevel < 1) {
LAB_00184fec:
            if (DebugLevel < 1) {
LAB_001850ac:
              if (DebugLevel < 1) {
LAB_0018516c:
                if (DebugLevel < 1) {
LAB_0018522c:
                  if (DebugLevel < 1) {
LAB_001852ec:
                    if (DebugLevel < 1) {
LAB_001853ac:
                      if (DebugLevel < 1) {
LAB_0018546c:
                        if (DebugLevel < 1) {
LAB_0018552c:
                          if (DebugLevel < 1) {
LAB_001855ec:
                            if (DebugLevel < 1) {
LAB_001856ac:
                              if (DebugLevel < 1) {
LAB_0018576c:
                                if (DebugLevel < 1) {
LAB_0018582c:
                                  if (DebugLevel < 1) {
LAB_001858ec:
                                    if (0 < DebugLevel) {
                                      uVar7 = FUN_00174570(param_1,iVar6 + 0x3d);
                                      printk("| |-|-|-(0x%08X) u1TidInfo = %d\n",iVar6 + 0x3d,uVar7)
                                      ;
                                      if (0 < DebugLevel) {
                                        uVar7 = FUN_00174528(param_1,iVar6 + 0x3e);
                                        printk("| |-|-|-(0x%08X) u2SpatialReuse = %d\n",iVar6 + 0x3e
                                               ,uVar7);
                                      }
                                    }
                                  }
                                  else {
                                    uVar7 = FUN_00174570(param_1,iVar6 + 0x39);
                                    printk("| |-|-|-(0x%08X) u1SsAlloc = %d\n",iVar6 + 0x39,uVar7);
                                    if (0 < DebugLevel) {
                                      uVar7 = FUN_00174570(param_1,iVar6 + 0x3a);
                                      printk("| |-|-|-(0x%08X) u1TargetRssi = %d\n",iVar6 + 0x3a,
                                             uVar7);
LAB_0018588c:
                                      if (0 < DebugLevel) {
                                        uVar7 = FUN_00174570(param_1,iVar6 + 0x3b);
                                        printk("| |-|-|-(0x%08X) fgDoppler = %d\n",iVar6 + 0x3b,
                                               uVar7);
                                        if (0 < DebugLevel) {
                                          uVar7 = FUN_00174570(param_1,iVar6 + 0x3c);
                                          printk("| |-|-|-(0x%08X) fgBf = %d\n",iVar6 + 0x3c,uVar7);
                                          goto LAB_001858ec;
                                        }
                                      }
                                    }
                                  }
                                }
                                else {
                                  uVar7 = FUN_00174570(param_1,iVar6 + 0x35);
                                  printk("| |-|-|-(0x%08X) fgBarAckPol = %d\n",iVar6 + 0x35,uVar7);
                                  if (0 < DebugLevel) {
                                    uVar7 = FUN_00174570(param_1,iVar6 + 0x36);
                                    printk("| |-|-|-(0x%08X) fgAckRuAllocBn = %d\n",iVar6 + 0x36,
                                           uVar7);
LAB_001857cc:
                                    if (DebugLevel < 1) goto LAB_0018588c;
                                    uVar7 = FUN_00174570(param_1,iVar6 + 0x37);
                                    printk("| |-|-|-(0x%08X) u1AckRuAlloc = %d\n",iVar6 + 0x37,uVar7
                                          );
                                    if (0 < DebugLevel) {
                                      uVar7 = FUN_00174570(param_1,iVar6 + 0x38);
                                      printk("| |-|-|-(0x%08X) u1AckMcs = %d\n",iVar6 + 0x38,uVar7);
                                      goto LAB_0018582c;
                                    }
                                  }
                                }
                              }
                              else {
                                uVar7 = FUN_00174570(param_1,iVar6 + 0x31);
                                printk("| |-|-|-(0x%08X) fgLdpcExtraSym = %d\n",iVar6 + 0x31,uVar7);
                                if (0 < DebugLevel) {
                                  uVar7 = FUN_00174570(param_1,iVar6 + 0x32);
                                  printk("| |-|-|-(0x%08X) u1PktExt = %d\n",iVar6 + 0x32,uVar7);
LAB_0018570c:
                                  if (DebugLevel < 1) goto LAB_001857cc;
                                  uVar7 = FUN_00174570(param_1,iVar6 + 0x33);
                                  printk("| |-|-|-(0x%08X) fgCoding2 = %d\n",iVar6 + 0x33,uVar7);
                                  if (0 < DebugLevel) {
                                    uVar7 = FUN_00174570(param_1,iVar6 + 0x34);
                                    printk("| |-|-|-(0x%08X) fgDcm = %d\n",iVar6 + 0x34,uVar7);
                                    goto LAB_0018576c;
                                  }
                                }
                              }
                            }
                            else {
                              uVar7 = FUN_00174570(param_1,iVar6 + 0x2d);
                              printk("| |-|-|-(0x%08X) fgCsRequired = %d\n",iVar6 + 0x2d,uVar7);
                              if (0 < DebugLevel) {
                                uVar7 = FUN_00174570(param_1,iVar6 + 0x2e);
                                printk("| |-|-|-(0x%08X) u1LtfType = %d\n",iVar6 + 0x2e,uVar7);
LAB_0018564c:
                                if (DebugLevel < 1) goto LAB_0018570c;
                                uVar7 = FUN_00174570(param_1,iVar6 + 0x2f);
                                printk("| |-|-|-(0x%08X) u1LtfSym = %d\n",iVar6 + 0x2f,uVar7);
                                if (0 < DebugLevel) {
                                  uVar7 = FUN_00174570(param_1,iVar6 + 0x30);
                                  printk("| |-|-|-(0x%08X) fgStbc = %d\n",iVar6 + 0x30,uVar7);
                                  goto LAB_001856ac;
                                }
                              }
                            }
                          }
                          else {
                            uVar7 = FUN_00174570(param_1,iVar6 + 0x29);
                            printk("| |-|-|-(0x%08X) u1BarRate = %d\n",iVar6 + 0x29,uVar7);
                            if (0 < DebugLevel) {
                              uVar7 = FUN_00174570(param_1,iVar6 + 0x2a);
                              printk("| |-|-|-(0x%08X) u1BarMode = %d\n",iVar6 + 0x2a,uVar7);
LAB_0018558c:
                              if (DebugLevel < 1) goto LAB_0018564c;
                              uVar7 = FUN_00174570(param_1,iVar6 + 0x2b);
                              printk("| |-|-|-(0x%08X) u1BarNsts = %d\n",iVar6 + 0x2b,uVar7);
                              if (0 < DebugLevel) {
                                uVar7 = FUN_00174570(param_1,iVar6 + 0x2c);
                                printk("| |-|-|-(0x%08X) u1BaType = %d\n",iVar6 + 0x2c,uVar7);
                                goto LAB_001855ec;
                              }
                            }
                          }
                        }
                        else {
                          uVar7 = FUN_00174570(param_1,iVar6 + 0x25);
                          printk("| |-|-|-(0x%08X) u1Ac0Ratio = %d\n",iVar6 + 0x25,uVar7);
                          if (0 < DebugLevel) {
                            uVar7 = FUN_00174570(param_1,iVar6 + 0x26);
                            printk("| |-|-|-(0x%08X) u1Ac1Ratio = %d\n",iVar6 + 0x26,uVar7);
LAB_001854cc:
                            if (DebugLevel < 1) goto LAB_0018558c;
                            uVar7 = FUN_00174570(param_1,iVar6 + 0x27);
                            printk("| |-|-|-(0x%08X) u1Ac2Ratio = %d\n",iVar6 + 0x27,uVar7);
                            if (0 < DebugLevel) {
                              uVar7 = FUN_00174570(param_1,iVar6 + 0x28);
                              printk("| |-|-|-(0x%08X) u1Ac3Ratio = %d\n",iVar6 + 0x28,uVar7);
                              goto LAB_0018552c;
                            }
                          }
                        }
                      }
                      else {
                        uVar7 = FUN_00174570(param_1,iVar6 + 0x1e);
                        printk("| |-|-|-(0x%08X) u1AcNum = %d\n",iVar6 + 0x1e,uVar7);
                        if (0 < DebugLevel) {
                          uVar7 = FUN_00174528(param_1,iVar6 + 0x20);
                          printk("| |-|-|-(0x%08X) u2BarRuRatio = %d\n",iVar6 + 0x20,uVar7);
LAB_0018540c:
                          if (DebugLevel < 1) goto LAB_001854cc;
                          uVar7 = FUN_00174528(param_1,iVar6 + 0x22);
                          printk("| |-|-|-(0x%08X) u2LSigLen = %d\n",iVar6 + 0x22,uVar7);
                          if (0 < DebugLevel) {
                            uVar7 = FUN_00174570(param_1,iVar6 + 0x24);
                            printk("| |-|-|-(0x%08X) u1Bw = %d\n",iVar6 + 0x24,uVar7);
                            goto LAB_0018546c;
                          }
                        }
                      }
                    }
                    else {
                      uVar7 = FUN_00174528(param_1,iVar6 + 0x18);
                      printk("| |-|-|-(0x%08X) u2SrRate = %d\n",iVar6 + 0x18,uVar7);
                      if (0 < DebugLevel) {
                        uVar7 = FUN_00174528(param_1,iVar6 + 0x1a);
                        printk("| |-|-|-(0x%08X) u2RuRatio = %d\n",iVar6 + 0x1a,uVar7);
LAB_0018534c:
                        if (DebugLevel < 1) goto LAB_0018540c;
                        uVar7 = FUN_00174570(param_1,iVar6 + 0x1c);
                        printk("| |-|-|-(0x%08X) fgSplPrimaryUser = %d\n",iVar6 + 0x1c,uVar7);
                        if (0 < DebugLevel) {
                          uVar7 = FUN_00174570(param_1,iVar6 + 0x1d);
                          printk("| |-|-|-(0x%08X) u1AcSeq = %d\n",iVar6 + 0x1d,uVar7);
                          goto LAB_001853ac;
                        }
                      }
                    }
                  }
                  else {
                    uVar7 = FUN_00174570(param_1,iVar6 + 0x13);
                    printk("| |-|-|-(0x%08X) u1Nsts = %d\n",iVar6 + 0x13,uVar7);
                    if (0 < DebugLevel) {
                      uVar7 = FUN_00174570(param_1,iVar6 + 0x14);
                      printk("| |-|-|-(0x%08X) u1LpCtrl = %d\n",iVar6 + 0x14,uVar7);
LAB_0018528c:
                      if (DebugLevel < 1) goto LAB_0018534c;
                      uVar7 = FUN_00174570(param_1,iVar6 + 0x15);
                      printk("| |-|-|-(0x%08X) fgContentCh = %d\n",iVar6 + 0x15,uVar7);
                      if (0 < DebugLevel) {
                        uVar7 = FUN_00174570(param_1,iVar6 + 0x16);
                        printk("| |-|-|-(0x%08X) u1AckPol = %d\n",iVar6 + 0x16,uVar7);
                        goto LAB_001852ec;
                      }
                    }
                  }
                }
                else {
                  uVar7 = FUN_00174570(param_1,iVar6 + 0xf);
                  printk("| |-|-|-(0x%08X) fgCbSta = %d\n",iVar6 + 0xf,uVar7);
                  if (0 < DebugLevel) {
                    uVar7 = FUN_00174570(param_1,iVar6 + 0x10);
                    printk("| |-|-|-(0x%08X) fgAggOld = %d\n",iVar6 + 0x10,uVar7);
LAB_001851cc:
                    if (DebugLevel < 1) goto LAB_0018528c;
                    uVar7 = FUN_00174570(param_1,iVar6 + 0x11);
                    printk("| |-|-|-(0x%08X) fgPreload = %d\n",iVar6 + 0x11,uVar7);
                    if (0 < DebugLevel) {
                      uVar7 = FUN_00174570(param_1,iVar6 + 0x12);
                      printk("| |-|-|-(0x%08X) u1Rate = %d\n",iVar6 + 0x12,uVar7);
                      goto LAB_0018522c;
                    }
                  }
                }
              }
              else {
                uVar7 = FUN_00174570(param_1,iVar6 + 0xb);
                printk("| |-|-|-(0x%08X) u1RuAlloc = %d\n",iVar6 + 0xb,uVar7);
                if (0 < DebugLevel) {
                  uVar7 = FUN_00174570(param_1,iVar6 + 0xc);
                  printk("| |-|-|-(0x%08X) u1AckGroup = %d\n",iVar6 + 0xc,uVar7);
LAB_0018510c:
                  if (DebugLevel < 1) goto LAB_001851cc;
                  uVar7 = FUN_00174570(param_1,iVar6 + 0xd);
                  printk("| |-|-|-(0x%08X) fgSuBar = %d\n",iVar6 + 0xd,uVar7);
                  if (0 < DebugLevel) {
                    uVar7 = FUN_00174570(param_1,iVar6 + 0xe);
                    printk("| |-|-|-(0x%08X) fgMuBar = %d\n",iVar6 + 0xe,uVar7);
                    goto LAB_0018516c;
                  }
                }
              }
            }
            else {
              uVar7 = FUN_00174570(param_1,iVar6 + 7);
              printk("| |-|-|-(0x%08X) u1MuMimoSpatial = %d\n",iVar6 + 7,uVar7);
              if (0 < DebugLevel) {
                uVar7 = FUN_00174570(param_1,iVar6 + 8);
                printk("| |-|-|-(0x%08X) u1StartStream = %d\n",iVar6 + 8,uVar7);
LAB_0018504c:
                if (DebugLevel < 1) goto LAB_0018510c;
                uVar7 = FUN_00174570(param_1,iVar6 + 9);
                printk("| |-|-|-(0x%08X) fgMultiTid = %d\n",iVar6 + 9,uVar7);
                if (0 < DebugLevel) {
                  uVar7 = FUN_00174570(param_1,iVar6 + 10);
                  printk("| |-|-|-(0x%08X) fgRuAllocBn = %d\n",iVar6 + 10,uVar7);
                  goto LAB_001850ac;
                }
              }
            }
          }
          else {
            uVar7 = FUN_00174528(param_1,iVar6);
            printk("| |-|-|-(0x%08X) u2TxPowerAlpha = %d\n",iVar6,uVar7);
            if (0 < DebugLevel) {
              uVar7 = FUN_00174570(param_1,iVar6 + 2);
              printk("| |-|-|-(0x%08X) fgCoding = %d\n",iVar6 + 2,uVar7);
              if (DebugLevel < 1) goto LAB_0018504c;
              uVar7 = FUN_00174528(param_1,iVar6 + 4);
              printk("| |-|-|-(0x%08X) u2WlanId = %d\n",iVar6 + 4,uVar7);
              if (0 < DebugLevel) {
                uVar7 = FUN_00174570(param_1,iVar6 + 6);
                printk("| |-|-|-(0x%08X) u1MuMimoGroup = %d\n",iVar6 + 6,uVar7);
                goto LAB_00184fec;
              }
            }
          }
        }
        uVar10 = uVar10 + 1;
        iVar6 = iVar6 + 0x40;
      } while ((uVar10 & 0xff) < uVar8);
    }
  }
  if (!bVar4) {
    return;
  }
  iVar6 = *(int *)(param_1 + 0x795a08);
  if (*(char *)(param_1 + 0x795a0c) != '\0') {
    return;
  }
  if ((0 < DebugLevel) && (printk("|-rSxnTrigData (0x%08X)\n",iVar6), 0 < DebugLevel)) {
    uVar7 = FUN_00174570(param_1,iVar6);
    printk("| |-(0x%08X) u1Rxv = %d\n",iVar6,uVar7);
  }
  iVar12 = iVar6 + 1;
  uVar8 = FUN_00174570(param_1,iVar12);
  if (DebugLevel < 1) goto LAB_00184dcc;
  uVar7 = FUN_00174570(param_1,iVar12);
  printk("| |-(0x%08X) u1StaCnt = %d\n",iVar12,uVar7);
  if (DebugLevel < 1) {
LAB_00186704:
    if (0 < DebugLevel) {
      uVar7 = FUN_00174570(param_1,iVar6 + 6);
      printk("| |-(0x%08X) u1AckTxMode = %d\n",iVar6 + 6,uVar7);
      if (DebugLevel < 1) goto LAB_00184dcc;
      uVar7 = FUN_00174570(param_1,iVar6 + 7);
      printk("| |-(0x%08X) u1TrigType = %d\n",iVar6 + 7,uVar7);
      goto LAB_00186770;
    }
LAB_001867fc:
    if (0 < DebugLevel) {
      uVar7 = FUN_00174570(param_1,iVar6 + 0x10);
      printk("| |-(0x%08X) u1TfPad = %d\n",iVar6 + 0x10,uVar7);
      if (DebugLevel < 1) goto LAB_00184dcc;
      uVar7 = FUN_00174528(param_1,iVar6 + 0x12);
      printk("| |-(0x%08X) u2LSigLen = %d\n",iVar6 + 0x12,uVar7);
      goto LAB_00186868;
    }
LAB_001868d4:
    if (0 < DebugLevel) {
      uVar7 = FUN_00174570(param_1,iVar6 + 0x16);
      printk("| |-(0x%08X) u1SigBMcs = %d\n",iVar6 + 0x16,uVar7);
      if (DebugLevel < 1) goto LAB_00184dcc;
      uVar7 = FUN_00174570(param_1,iVar6 + 0x17);
      printk("| |-(0x%08X) fgSigBDcm = %d\n",iVar6 + 0x17,uVar7);
      goto LAB_00186940;
    }
LAB_001869ac:
    if (0 < DebugLevel) {
      uVar7 = FUN_00174570(param_1,iVar6 + 0x1a);
      printk("| |-(0x%08X) u1Gi = %d\n",iVar6 + 0x1a,uVar7);
      if (DebugLevel < 1) goto LAB_00184dcc;
      uVar7 = FUN_00174570(param_1,iVar6 + 0x1b);
      printk("| |-(0x%08X) fgStbc = %d\n",iVar6 + 0x1b,uVar7);
      goto LAB_00186a18;
    }
LAB_00186a84:
    if (0 < DebugLevel) {
      uVar7 = FUN_00174570(param_1,iVar6 + 0x1e);
      printk("| |-(0x%08X) u1SigBCh2StaCnt = %d\n",iVar6 + 0x1e,uVar7);
      if (DebugLevel < 1) goto LAB_00184dcc;
      uVar7 = FUN_00174528(param_1,iVar6 + 0x20);
      printk("| |-(0x%08X) u2MuPpduDur = %d\n",iVar6 + 0x20,uVar7);
      goto LAB_00186af0;
    }
  }
  else {
    uVar7 = FUN_00174570(param_1,iVar6 + 2);
    printk("| |-(0x%08X) u1BaPol = %d\n",iVar6 + 2,uVar7);
    if (DebugLevel < 1) goto LAB_00184dcc;
    uVar7 = FUN_00174570(param_1,iVar6 + 3);
    printk("| |-(0x%08X) fgPriOrder = %d\n",iVar6 + 3,uVar7);
    if (0 < DebugLevel) {
      uVar7 = FUN_00174570(param_1,iVar6 + 4);
      printk("| |-(0x%08X) u1SplAc = %d\n",iVar6 + 4,uVar7);
      if (DebugLevel < 1) goto LAB_00184dcc;
      uVar7 = FUN_00174570(param_1,iVar6 + 5);
      printk("| |-(0x%08X) u1PreambPunc = %d\n",iVar6 + 5,uVar7);
      goto LAB_00186704;
    }
LAB_00186770:
    if (0 < DebugLevel) {
      local_78 = 0;
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar6 + 8,&local_78);
      printk("| |-(0x%08X) u4RxHetbCfg1 = %d\n",iVar6 + 8,local_78);
      if (DebugLevel < 1) goto LAB_00184dcc;
      local_78 = 0;
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar6 + 0xc,&local_78);
      printk("| |-(0x%08X) u4RxHetbCfg2 = %d\n",iVar6 + 0xc,local_78);
      goto LAB_001867fc;
    }
LAB_00186868:
    if (0 < DebugLevel) {
      uVar7 = FUN_00174570(param_1,iVar6 + 0x14);
      printk("| |-(0x%08X) u1SigBCh1StaCnt = %d\n",iVar6 + 0x14,uVar7);
      if (DebugLevel < 1) goto LAB_00184dcc;
      uVar7 = FUN_00174570(param_1,iVar6 + 0x15);
      printk("| |-(0x%08X) u1SigBSym = %d\n",iVar6 + 0x15,uVar7);
      goto LAB_001868d4;
    }
LAB_00186940:
    if (0 < DebugLevel) {
      uVar7 = FUN_00174570(param_1,iVar6 + 0x18);
      printk("| |-(0x%08X) fgSigBCompress = %d\n",iVar6 + 0x18,uVar7);
      if (DebugLevel < 1) goto LAB_00184dcc;
      uVar7 = FUN_00174570(param_1,iVar6 + 0x19);
      printk("| |-(0x%08X) u1LtfSym = %d\n",iVar6 + 0x19,uVar7);
      goto LAB_001869ac;
    }
LAB_00186a18:
    if (0 < DebugLevel) {
      uVar7 = FUN_00174570(param_1,iVar6 + 0x1c);
      printk("| |-(0x%08X) fgDoppler = %d\n",iVar6 + 0x1c,uVar7);
      if (DebugLevel < 1) goto LAB_00184dcc;
      uVar7 = FUN_00174570(param_1,iVar6 + 0x1d);
      printk("| |-(0x%08X) fgCmdPower = %d\n",iVar6 + 0x1d,uVar7);
      goto LAB_00186a84;
    }
LAB_00186af0:
    if (DebugLevel < 1) goto LAB_00184dcc;
    uVar7 = FUN_00174570(param_1,iVar6 + 0x22);
    printk("| |-(0x%08X) u1Ltf = %d\n",iVar6 + 0x22,uVar7);
    if (DebugLevel < 1) goto LAB_00184dcc;
    uVar7 = FUN_00174570(param_1,iVar6 + 0x23);
    printk("| |-(0x%08X) fgRu26dSigBCh1 = %d\n",iVar6 + 0x23,uVar7);
  }
  if (0 < DebugLevel) {
    uVar7 = FUN_00174570(param_1,iVar6 + 0x24);
    printk("| |-(0x%08X) fgRu26uSigBCh2 = %d\n",iVar6 + 0x24,uVar7);
    if (0 < DebugLevel) {
      printk("| |-(0x%08X) au1RuAlloc\n",iVar6 + 0x25);
    }
  }
LAB_00184dcc:
  iVar11 = 0;
  iVar12 = DebugLevel;
  do {
    if (0 < iVar12) {
      iVar12 = iVar11 + iVar6 + 0x25;
      uVar7 = FUN_00174570(param_1,iVar12);
      printk("| |-|-(0x%08X) au1RuAlloc[%d] = %d\n",iVar12,iVar11,uVar7);
      iVar12 = DebugLevel;
    }
    iVar11 = iVar11 + 1;
  } while (iVar11 != 8);
  if (0 < iVar12) {
    uVar7 = FUN_00174570(param_1,iVar6 + 0x2d);
    printk("| |-(0x%08X) u1AckTxPower = %d\n",iVar6 + 0x2d,uVar7);
    if (0 < DebugLevel) {
      uVar7 = FUN_00174570(param_1,iVar6 + 0x2e);
      printk("| |-(0x%08X) u1SsnUser = %d\n",iVar6 + 0x2e,uVar7);
      if (0 < DebugLevel) {
        uVar7 = FUN_00174570(param_1,iVar6 + 0x2f);
        printk("| |-(0x%08X) u1MuUser = %d\n",iVar6 + 0x2f,uVar7);
        if (0 < DebugLevel) {
          uVar7 = FUN_00174528(param_1,iVar6 + 0x48);
          printk("| |-(0x%08X) u2MsduId = %d\n",iVar6 + 0x48,uVar7);
          if (0 < DebugLevel) {
            printk("| |-(0x%08X) rTxcmdUserAck\n",iVar6 + 0x4a);
          }
        }
      }
    }
  }
  if (uVar8 != 0) {
    iVar6 = iVar6 + 0x5c;
    uVar10 = 0;
    do {
      iVar12 = iVar6 + -0x12;
      if (0 < DebugLevel) {
        printk("| |-|-(0x%08X) rTxcmdUserAck[%d]\n",iVar12,uVar10);
        if (DebugLevel < 1) {
LAB_00185f54:
          if (DebugLevel < 1) {
LAB_0018601c:
            if (DebugLevel < 1) {
LAB_001860e4:
              if (0 < DebugLevel) {
                uVar7 = FUN_00174570(param_1,iVar6 + -1);
                printk("| |-|-|-(0x%08X) u1Ac = %d\n",iVar6 + -1,uVar7);
                if (0 < DebugLevel) {
                  uVar7 = FUN_00174570(param_1,iVar6);
                  printk("| |-|-|-(0x%08X) fgSplPrimaryUser = %d\n",iVar6,uVar7);
                }
              }
            }
            else {
              uVar7 = FUN_00174570(param_1,iVar6 + -7);
              printk("| |-|-|-(0x%08X) u1Nsts = %d\n",iVar6 + -7,uVar7);
              if (0 < DebugLevel) {
                uVar7 = FUN_00174570(param_1,iVar6 + -6);
                printk("| |-|-|-(0x%08X) u1RuAllNss = %d\n",iVar6 + -6,uVar7);
LAB_00186080:
                if (0 < DebugLevel) {
                  uVar7 = FUN_00174528(param_1,iVar6 + -4);
                  printk("| |-|-|-(0x%08X) u2RuRatio = %d\n",iVar6 + -4,uVar7);
                  if (0 < DebugLevel) {
                    uVar7 = FUN_00174570(param_1,iVar6 + -2);
                    printk("| |-|-|-(0x%08X) fgSfEnable = %d\n",iVar6 + -2,uVar7);
                    goto LAB_001860e4;
                  }
                }
              }
            }
          }
          else {
            uVar7 = FUN_00174528(param_1,iVar6 + -0xc);
            printk("| |-|-|-(0x%08X) u2WlanId = %d\n",iVar6 + -0xc,uVar7);
            if (0 < DebugLevel) {
              uVar7 = FUN_00174570(param_1,iVar6 + -10);
              printk("| |-|-|-(0x%08X) fgRuAllocBn = %d\n",iVar6 + -10,uVar7);
LAB_00185fb8:
              if (DebugLevel < 1) goto LAB_00186080;
              uVar7 = FUN_00174570(param_1,iVar6 + -9);
              printk("| |-|-|-(0x%08X) u1RuAlloc = %d\n",iVar6 + -9,uVar7);
              if (0 < DebugLevel) {
                uVar7 = FUN_00174570(param_1,iVar6 + -8);
                printk("| |-|-|-(0x%08X) u1Rate = %d\n",iVar6 + -8,uVar7);
                goto LAB_0018601c;
              }
            }
          }
        }
        else {
          uVar7 = FUN_00174528(param_1,iVar12);
          printk("| |-|-|-(0x%08X) u2StaId = %d\n",iVar12,uVar7);
          if (0 < DebugLevel) {
            uVar7 = FUN_00174528(param_1,iVar6 + -0x10);
            printk("| |-|-|-(0x%08X) u2AckTxPowerAlpha = %d\n",iVar6 + -0x10,uVar7);
            if (DebugLevel < 1) goto LAB_00185fb8;
            uVar7 = FUN_00174570(param_1,iVar6 + -0xe);
            printk("| |-|-|-(0x%08X) fgCoding = %d\n",iVar6 + -0xe,uVar7);
            if (0 < DebugLevel) {
              uVar7 = FUN_00174570(param_1,iVar6 + -0xd);
              printk("| |-|-|-(0x%08X) fgContentCh = %d\n",iVar6 + -0xd,uVar7);
              goto LAB_00185f54;
            }
          }
        }
      }
      uVar10 = uVar10 + 1;
      iVar6 = iVar6 + 0x14;
    } while ((uVar10 & 0xff) < uVar8);
  }
  return;
}

