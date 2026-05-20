// module: mt7915.ko
// function: show_muru_shared_data @ 0x182398
// size: 10292 bytes
//

void show_muru_shared_data(int param_1,int param_2)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  char cVar4;
  char *__s;
  size_t __n;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  bool bVar10;
  uint local_60;
  uint local_48;
  undefined1 auStack_41 [29];
  
  uVar8 = *(uint *)(param_1 + 0x795a10);
  if (param_2 == 0) {
    return;
  }
  cVar4 = delimitcnt(param_2,&_LC251);
  if (2 < (byte)(cVar4 + 1U)) {
    if (DebugLevel < 0) {
      return;
    }
    printk("Num of Input Parameters Wrong\n");
    return;
  }
  __s = (char *)rstrtok(param_2,&_LC251);
  if (__s == (char *)0x0) {
    bVar1 = false;
    bVar2 = false;
    bVar3 = false;
    bVar10 = false;
    local_60 = 0;
  }
  else {
    cVar4 = '\0';
    local_60 = 0;
    bVar1 = false;
    bVar2 = false;
    bVar3 = false;
    bVar10 = false;
    do {
      if (cVar4 == '\0') {
        __n = strlen(__s);
        memcpy(auStack_41,__s,__n);
        iVar5 = memcmp(auStack_41,"ShareData",9);
        if (iVar5 == 0) {
          bVar10 = true;
        }
        iVar5 = memcmp(auStack_41,"RuAllocData",0xb);
        if (iVar5 == 0) {
          bVar3 = true;
        }
        iVar5 = memcmp(auStack_41,"UserInfo",8);
        if (iVar5 == 0) {
          bVar2 = true;
        }
        iVar5 = memcmp(auStack_41,"StaRuRecord",0xb);
        if (iVar5 == 0) {
          bVar1 = true;
        }
      }
      else if ((cVar4 == '\x01') && (bVar1 || bVar2)) {
        local_60 = os_str_tol(__s,0,10);
        local_60 = local_60 & 0xffff;
      }
      cVar4 = cVar4 + '\x01';
      __s = (char *)rstrtok(0,&_LC251);
    } while (__s != (char *)0x0);
  }
  if (0xdfffffff < uVar8) {
    FUN_0017f59c(param_1);
  }
  if (0 < DebugLevel) {
    printk("_rMuru_Shared_Data; (0x%08X)\n",uVar8);
  }
  if ((bVar10) && (iVar5 = *(int *)(param_1 + 0x795a10), *(char *)(param_1 + 0x795a14) == '\0')) {
    if (0 < DebugLevel) {
      printk("|-_rMuru_Share_Data (0x%08X)\n",iVar5);
      if (DebugLevel < 1) {
LAB_00184430:
        if (DebugLevel < 1) {
LAB_00184520:
          if (0 < DebugLevel) {
            local_48 = 0;
            mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x1054);
            printk("| |-(0x%08X) eBandIdx = %d\n",iVar5 + 0x1054,local_48);
            if (0 < DebugLevel) {
              uVar6 = FUN_00174570(param_1,iVar5 + 0x1058);
              printk("| |-(0x%08X) u1GlobalBw = %d\n",iVar5 + 0x1058,uVar6);
LAB_001845ac:
              if (0 < DebugLevel) {
                printk("| |-(0x%08X) fgBsrpBandRequest\n",iVar5 + 0x1059);
              }
            }
          }
        }
        else {
          uVar6 = FUN_00174570(param_1,iVar5 + 0xfb9);
          printk("| |-(0x%08X) u1MaxStaCntInPpdu = %d\n",iVar5 + 0xfb9,uVar6);
          if (0 < DebugLevel) {
            uVar6 = FUN_00174528(param_1,iVar5 + 0xfba);
            printk("| |-(0x%08X) u2TypeAStaCnt = %d\n",iVar5 + 0xfba,uVar6);
LAB_001844a8:
            if (DebugLevel < 1) goto LAB_001845ac;
            uVar6 = FUN_00174528(param_1,iVar5 + 0xfbc);
            printk("| |-(0x%08X) u2TypeBStaCnt = %d\n",iVar5 + 0xfbc,uVar6);
            if (0 < DebugLevel) {
              uVar6 = FUN_00174528(param_1,iVar5 + 0xfbe);
              printk("| |-(0x%08X) u2TypeCStaCnt = %d\n",iVar5 + 0xfbe,uVar6);
              goto LAB_00184520;
            }
          }
        }
      }
      else {
        uVar6 = FUN_00174570(param_1,iVar5 + 0xca4);
        printk("| |-(0x%08X) u1PrimaryAc = %d\n",iVar5 + 0xca4,uVar6);
        if (0 < DebugLevel) {
          uVar6 = FUN_00174570(param_1,iVar5 + 0xca5);
          printk("| |-(0x%08X) u1PrimaryStaIdx = %d\n",iVar5 + 0xca5,uVar6);
          if (DebugLevel < 1) goto LAB_001844a8;
          uVar6 = FUN_00174570(param_1,iVar5 + 0xca6);
          printk("| |-(0x%08X) u1Qid = %d\n",iVar5 + 0xca6,uVar6);
          if (0 < DebugLevel) {
            uVar6 = FUN_00174570(param_1,iVar5 + 0xfb8);
            printk("| |-(0x%08X) u2MuRuMaxSplCnt = %d\n",iVar5 + 0xfb8,uVar6);
            goto LAB_00184430;
          }
        }
      }
    }
    iVar7 = 0;
    iVar9 = DebugLevel;
    do {
      if (0 < iVar9) {
        iVar9 = iVar7 + iVar5 + 0x1059;
        uVar6 = FUN_00174570(param_1,iVar9);
        printk("| | |-(0x%08X) fgBsrpBandRequest[%d] = %d\n",iVar9,iVar7,uVar6);
        iVar9 = DebugLevel;
      }
      bVar10 = iVar7 != 1;
      iVar7 = 1;
    } while (bVar10);
    if (0 < iVar9) {
      local_48 = 0;
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x105c,&local_48);
      printk("| |-(0x%08X) eLastBsrpBandTx = %d\n",iVar5 + 0x105c,local_48);
      if (DebugLevel < 1) {
LAB_00183994:
        if (DebugLevel < 1) {
LAB_00183a94:
          if (DebugLevel < 1) {
LAB_00183b74:
            if (DebugLevel < 1) {
LAB_00183c54:
              if (DebugLevel < 1) {
LAB_00183d44:
                if (DebugLevel < 1) {
LAB_00183e44:
                  if (DebugLevel < 1) {
LAB_00183f34:
                    if (DebugLevel < 1) {
LAB_00184024:
                      if (DebugLevel < 1) {
LAB_00184114:
                        if (DebugLevel < 1) {
LAB_001841f8:
                          if (0 < DebugLevel) {
                            local_48 = 0;
                            mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x2de48,
                                          &local_48);
                            printk("| |-(0x%08X) u4AcBitmapPreviousBsrp = %d\n",iVar5 + 0x2de48,
                                   local_48);
                            if (0 < DebugLevel) {
                              uVar6 = FUN_00174570(param_1,iVar5 + 0x2de50);
                              printk("| |-(0x%08X) u1TriggerTypeOfBsrpTimer = %d\n",iVar5 + 0x2de50,
                                     uVar6);
LAB_00184280:
                              if (0 < DebugLevel) {
                                uVar6 = FUN_00174570(param_1,iVar5 + 0x2de51);
                                printk("| |-(0x%08X) u1DisableBsrpTimer = %d\n",iVar5 + 0x2de51,
                                       uVar6);
                                if (0 < DebugLevel) {
                                  uVar6 = FUN_00174570(param_1,iVar5 + 0x2de52);
                                  printk("| |-(0x%08X) u1DisableULData = %d\n",iVar5 + 0x2de52,uVar6
                                        );
                                }
                              }
                            }
                          }
                        }
                        else {
                          uVar6 = FUN_00174570(param_1,iVar5 + 0x2bcc0);
                          printk("| |-(0x%08X) u2MpduByte = %d\n",iVar5 + 0x2bcc0,uVar6);
                          if (0 < DebugLevel) {
                            uVar6 = FUN_00174528(param_1,iVar5 + 0x2bcc2);
                            printk("| |-(0x%08X) u2QidNeedsDlSplTrigger = %d\n",iVar5 + 0x2bcc2,
                                   uVar6);
LAB_00184184:
                            if (DebugLevel < 1) goto LAB_00184280;
                            uVar6 = FUN_00174528(param_1,iVar5 + 0x2bcc4);
                            printk("| |-(0x%08X) u2NonBsrpCount = %d\n",iVar5 + 0x2bcc4,uVar6);
                            if (0 < DebugLevel) {
                              uVar6 = FUN_00174570(param_1,iVar5 + 0x2de46);
                              printk("| |-(0x%08X) u1SplBackupSeq = %d\n",iVar5 + 0x2de46,uVar6);
                              goto LAB_001841f8;
                            }
                          }
                        }
                      }
                      else {
                        local_48 = 0;
                        mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x2bcb8,&local_48)
                        ;
                        printk("| |-(0x%08X) u4UlAvgMpduSize = %d\n",iVar5 + 0x2bcb8,local_48);
                        if (0 < DebugLevel) {
                          uVar6 = FUN_00174570(param_1,iVar5 + 0x2bcbc);
                          printk("| |-(0x%08X) u1MaxMuNum = %d\n",iVar5 + 0x2bcbc,uVar6);
LAB_001840a4:
                          if (DebugLevel < 1) goto LAB_00184184;
                          uVar6 = FUN_00174570(param_1,iVar5 + 0x2bcbd);
                          printk("| |-(0x%08X) u1TypeA_SwPdaPolicy = %d\n",iVar5 + 0x2bcbd,uVar6);
                          if (0 < DebugLevel) {
                            uVar6 = FUN_00174570(param_1,iVar5 + 0x2bcbe);
                            printk("| |-(0x%08X) u1TypeB_SwPdaPolicy = %d\n",iVar5 + 0x2bcbe,uVar6);
                            goto LAB_00184114;
                          }
                        }
                      }
                    }
                    else {
                      uVar6 = FUN_00174570(param_1,iVar5 + 0x2bcaf);
                      printk("| |-(0x%08X) u1FixedBaNss = %d\n",iVar5 + 0x2bcaf,uVar6);
                      if (0 < DebugLevel) {
                        local_48 = 0;
                        mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x2bcb0,&local_48)
                        ;
                        printk("| |-(0x%08X) u4PpduDuration = %d\n",iVar5 + 0x2bcb0,local_48);
LAB_00183fb4:
                        if (DebugLevel < 1) goto LAB_001840a4;
                        uVar6 = FUN_00174570(param_1,iVar5 + 0x2bcb4);
                        printk("| |-(0x%08X) fgUlMuBa = %d\n",iVar5 + 0x2bcb4,uVar6);
                        if (0 < DebugLevel) {
                          uVar6 = FUN_00174528(param_1,iVar5 + 0x2bcb6);
                          printk("| |-(0x%08X) u2UlAvgMpduCnt = %d\n",iVar5 + 0x2bcb6,uVar6);
                          goto LAB_00184024;
                        }
                      }
                    }
                  }
                  else {
                    local_48 = 0;
                    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x2bca8,&local_48);
                    printk("| |-(0x%08X) eTonePlanPolicy = %d\n",iVar5 + 0x2bca8,local_48);
                    if (0 < DebugLevel) {
                      uVar6 = FUN_00174570(param_1,iVar5 + 0x2bcac);
                      printk("| |-(0x%08X) u1FixedMcs = %d\n",iVar5 + 0x2bcac,uVar6);
LAB_00183ec4:
                      if (DebugLevel < 1) goto LAB_00183fb4;
                      uVar6 = FUN_00174570(param_1,iVar5 + 0x2bcad);
                      printk("| |-(0x%08X) u1FixedNss = %d\n",iVar5 + 0x2bcad,uVar6);
                      if (0 < DebugLevel) {
                        uVar6 = FUN_00174570(param_1,iVar5 + 0x2bcae);
                        printk("| |-(0x%08X) u1FixedBaMcs = %d\n",iVar5 + 0x2bcae,uVar6);
                        goto LAB_00183f34;
                      }
                    }
                  }
                }
                else {
                  local_48 = 0;
                  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x2bc9c,&local_48);
                  printk("| |-(0x%08X) u4TxDataSec_MuPpduDur = %d\n",iVar5 + 0x2bc9c,local_48);
                  if (0 < DebugLevel) {
                    uVar6 = FUN_00174570(param_1,iVar5 + 0x2bca0);
                    printk("| |-(0x%08X) u1TrigSec_BA_Policy = %d\n",iVar5 + 0x2bca0,uVar6);
LAB_00183dc4:
                    if (DebugLevel < 1) goto LAB_00183ec4;
                    uVar6 = FUN_00174570(param_1,iVar5 + 0x2bca1);
                    printk("| |-(0x%08X) u1TrigSec_Global_BA_BW = %d\n",iVar5 + 0x2bca1,uVar6);
                    if (0 < DebugLevel) {
                      local_48 = 0;
                      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x2bca4,&local_48);
                      printk("| |-(0x%08X) u4TrigSec_Global_BA_Dur = %d\n",iVar5 + 0x2bca4,local_48)
                      ;
                      goto LAB_00183e44;
                    }
                  }
                }
              }
              else {
                local_48 = 0;
                mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x2bc94,&local_48);
                printk("| |-(0x%08X) u4ProtFrameThr = %d\n",iVar5 + 0x2bc94,local_48);
                if (0 < DebugLevel) {
                  uVar6 = FUN_00174570(param_1,iVar5 + 0x2bc99);
                  printk("| |-(0x%08X) u1ProtRuAlloc = %d\n",iVar5 + 0x2bc99,uVar6);
LAB_00183cd4:
                  if (DebugLevel < 1) goto LAB_00183dc4;
                  uVar6 = FUN_00174570(param_1,iVar5 + 0x2bc9a);
                  printk("| |-(0x%08X) fgFixedRate = %d\n",iVar5 + 0x2bc9a,uVar6);
                  if (0 < DebugLevel) {
                    uVar6 = FUN_00174570(param_1,iVar5 + 0x2bc9b);
                    printk("| |-(0x%08X) u1TxDataSec_Bw = %d\n",iVar5 + 0x2bc9b,uVar6);
                    goto LAB_00183d44;
                  }
                }
              }
            }
            else {
              uVar6 = FUN_00174528(param_1,iVar5 + 0x2bc8c);
              printk("| |-(0x%08X) i2PsdDiffThr = %d\n",iVar5 + 0x2bc8c,uVar6);
              if (0 < DebugLevel) {
                uVar6 = FUN_00174570(param_1,iVar5 + 0x2bc8e);
                printk("| |-(0x%08X) fgExp = %d\n",iVar5 + 0x2bc8e,uVar6);
LAB_00183be4:
                if (DebugLevel < 1) goto LAB_00183cd4;
                uVar6 = FUN_00174570(param_1,iVar5 + 0x2bc8f);
                printk("| |-(0x%08X) u1Pdc = %d\n",iVar5 + 0x2bc8f,uVar6);
                if (0 < DebugLevel) {
                  uVar6 = FUN_00174570(param_1,iVar5 + 0x2bc90);
                  printk("| |-(0x%08X) fgProt = %d\n",iVar5 + 0x2bc90,uVar6);
                  goto LAB_00183c54;
                }
              }
            }
          }
          else {
            uVar6 = FUN_00174570(param_1,iVar5 + 0x2bc84);
            printk("| |-(0x%08X) u1PpduDurBias = %d\n",iVar5 + 0x2bc84,uVar6);
            if (0 < DebugLevel) {
              uVar6 = FUN_00174570(param_1,iVar5 + 0x2bc85);
              printk("| |-(0x%08X) u1PreGrp = %d\n",iVar5 + 0x2bc85,uVar6);
LAB_00183b04:
              if (DebugLevel < 1) goto LAB_00183be4;
              uVar6 = FUN_00174570(param_1,iVar5 + 0x2bc8a);
              printk("| |-(0x%08X) fgTxopBurst = %d\n",iVar5 + 0x2bc8a,uVar6);
              if (0 < DebugLevel) {
                uVar6 = FUN_00174570(param_1,iVar5 + 0x2bc8b);
                printk("| |-(0x%08X) fgOptionalBackoff = %d\n",iVar5 + 0x2bc8b,uVar6);
                goto LAB_00183b74;
              }
            }
          }
        }
        else {
          uVar6 = FUN_00174570(param_1,iVar5 + 0x2bc71);
          printk("| |-(0x%08X) fgUlSnd = %d\n",iVar5 + 0x2bc71,uVar6);
          if (0 < DebugLevel) {
            local_48 = 0;
            mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x2bc74,&local_48);
            printk("| |-(0x%08X) eSchtype = %d\n",iVar5 + 0x2bc74,local_48);
LAB_00183a14:
            if (DebugLevel < 1) goto LAB_00183b04;
            uVar6 = FUN_00174570(param_1,iVar5 + 0x2bc78);
            printk("| |-(0x%08X) u1LastBSRPStaIdx = %d\n",iVar5 + 0x2bc78,uVar6);
            if (0 < DebugLevel) {
              local_48 = 0;
              mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x2bc80,&local_48);
              printk("| |-(0x%08X) u4MaxRuAlgoTimeOut = %d\n",iVar5 + 0x2bc80,local_48);
              goto LAB_00183a94;
            }
          }
        }
      }
      else {
        uVar6 = FUN_00174570(param_1,iVar5 + 0x2bc66);
        printk("| |-(0x%08X) u1PuBw = %d\n",iVar5 + 0x2bc66,uVar6);
        if (0 < DebugLevel) {
          local_48 = 0;
          mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x2bc68,&local_48);
          printk("| |-(0x%08X) eTxCmdTye = %d\n",iVar5 + 0x2bc68,local_48);
          if (DebugLevel < 1) goto LAB_00183a14;
          local_48 = 0;
          mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x2bc6c,&local_48);
          printk("| |-(0x%08X) ePuRuBuftype = %d\n",iVar5 + 0x2bc6c,local_48);
          if (0 < DebugLevel) {
            uVar6 = FUN_00174570(param_1,iVar5 + 0x2bc70);
            printk("| |-(0x%08X) fgUplink = %d\n",iVar5 + 0x2bc70,uVar6);
            goto LAB_00183994;
          }
        }
      }
    }
  }
  if (bVar3) {
    uVar8 = (uint)*(byte *)(param_1 + 0x795a1c);
    iVar5 = *(int *)(param_1 + 0x795a18);
    if ((uVar8 == 0) && (0 < DebugLevel)) {
      printk("|-rRuAllocData (0x%08X)\n",iVar5);
      if (DebugLevel < 1) {
LAB_00182db4:
        if (DebugLevel < 1) {
LAB_00182e84:
          if (DebugLevel < 1) {
LAB_00182f54:
            if (DebugLevel < 1) {
LAB_00183038:
              if (DebugLevel < 1) {
LAB_0018311c:
                if (DebugLevel < 1) {
LAB_0018322c:
                  if (DebugLevel < 1) {
LAB_0018330c:
                    if (DebugLevel < 1) {
LAB_001833fc:
                      if (DebugLevel < 1) {
LAB_001834f0:
                        if (DebugLevel < 1) {
LAB_001835dc:
                          if (DebugLevel < 1) {
LAB_00183738:
                            if (0 < DebugLevel) {
                              local_48 = 0;
                              mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x638,
                                            &local_48);
                              printk("| |-(0x%08X) u4PpduTxDur = %d\n",iVar5 + 0x638,local_48);
                              if (0 < DebugLevel) {
                                local_48 = 0;
                                mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x63c,
                                              &local_48);
                                printk("| |-(0x%08X) u4MuPpduUtilization = %d\n",iVar5 + 0x63c,
                                       local_48);
                              }
                            }
                          }
                          else {
                            local_48 = 0;
                            mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x628,
                                          &local_48);
                            printk("| |-(0x%08X) u4MaxScore = %d\n",iVar5 + 0x628,local_48);
                            if (0 < DebugLevel) {
                              local_48 = 0;
                              mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x62c,
                                            &local_48);
                              printk("| |-(0x%08X) u4SuScore = %d\n",iVar5 + 0x62c,local_48);
LAB_0018368c:
                              if (0 < DebugLevel) {
                                local_48 = 0;
                                mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x630,
                                              &local_48);
                                printk("| |-(0x%08X) u4MuScore = %d\n",iVar5 + 0x630,local_48);
                                if (0 < DebugLevel) {
                                  local_48 = 0;
                                  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x634,
                                                &local_48);
                                  printk("| |-(0x%08X) u4TotBitsOfThisTP = %d\n",iVar5 + 0x634,
                                         local_48);
                                  goto LAB_00183738;
                                }
                              }
                            }
                          }
                        }
                        else {
                          uVar6 = FUN_00174528(param_1,iVar5 + 0x61c);
                          printk("| |-(0x%08X) u2TonePlanIdx = %d\n",iVar5 + 0x61c,uVar6);
                          if (0 < DebugLevel) {
                            uVar6 = FUN_00174528(param_1,iVar5 + 0x61e);
                            printk("| |-(0x%08X) u2TypeAStaCnt = %d\n",iVar5 + 0x61e,uVar6);
LAB_00183560:
                            if (DebugLevel < 1) goto LAB_0018368c;
                            uVar6 = FUN_00174528(param_1,iVar5 + 0x620);
                            printk("| |-(0x%08X) u2TypeBStaCnt = %d\n",iVar5 + 0x620,uVar6);
                            if (0 < DebugLevel) {
                              local_48 = 0;
                              mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x624);
                              printk("| |-(0x%08X) u4MaxHeadTime = %d\n",iVar5 + 0x624,local_48);
                              goto LAB_001835dc;
                            }
                          }
                        }
                      }
                      else {
                        local_48 = 0;
                        mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x614);
                        printk("| |-(0x%08X) eSchType = %d\n",iVar5 + 0x614,local_48);
                        if (0 < DebugLevel) {
                          uVar6 = FUN_00174570(param_1,iVar5 + 0x618);
                          printk("| |-(0x%08X) u1OperateBw = %d\n",iVar5 + 0x618,uVar6);
LAB_00183480:
                          if (DebugLevel < 1) goto LAB_00183560;
                          uVar6 = FUN_00174570(param_1,iVar5 + 0x619);
                          printk("| |-(0x%08X) u1HavmDLULIdx = %d\n",iVar5 + 0x619,uVar6);
                          if (0 < DebugLevel) {
                            uVar6 = FUN_00174570(param_1,iVar5 + 0x61a);
                            printk("| |-(0x%08X) u1SplStaCnt = %d\n",iVar5 + 0x61a,uVar6);
                            goto LAB_001834f0;
                          }
                        }
                      }
                    }
                    else {
                      uVar6 = FUN_00174570(param_1,iVar5 + 0x5fd);
                      printk("| |-(0x%08X) u1TrigAckTxMode = %d\n",iVar5 + 0x5fd,uVar6);
                      if (0 < DebugLevel) {
                        local_48 = 0;
                        mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x600);
                        printk("| |-(0x%08X) u4LSigLength = %d\n",iVar5 + 0x600,local_48);
LAB_0018338c:
                        if (DebugLevel < 1) goto LAB_00183480;
                        uVar6 = FUN_00174570(param_1,iVar5 + 0x608);
                        printk("| |-(0x%08X) ucTfPe = %d\n",iVar5 + 0x608,uVar6);
                        if (0 < DebugLevel) {
                          uVar6 = FUN_00174570(param_1,iVar5 + 0x609);
                          printk("| |-(0x%08X) u1TotMumGrpCnt = %d\n",iVar5 + 0x609,uVar6);
                          goto LAB_001833fc;
                        }
                      }
                    }
                  }
                  else {
                    uVar6 = FUN_00174570(param_1,iVar5 + 0x5f9);
                    printk("| |-(0x%08X) u1TfType = %d\n",iVar5 + 0x5f9,uVar6);
                    if (0 < DebugLevel) {
                      uVar6 = FUN_00174570(param_1,iVar5 + 0x5fa);
                      printk("| |-(0x%08X) u1TrigSplAc = %d\n",iVar5 + 0x5fa,uVar6);
LAB_0018329c:
                      if (DebugLevel < 1) goto LAB_0018338c;
                      uVar6 = FUN_00174570(param_1,iVar5 + 0x5fb);
                      printk("| |-(0x%08X) u1TrigAckBw = %d\n",iVar5 + 0x5fb,uVar6);
                      if (0 < DebugLevel) {
                        uVar6 = FUN_00174570(param_1,iVar5 + 0x5fc);
                        printk("| |-(0x%08X) u1TrigAckTxPwr = %d\n",iVar5 + 0x5fc,uVar6);
                        goto LAB_0018330c;
                      }
                    }
                  }
                }
                else {
                  local_48 = 0;
                  mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x68,&local_48);
                  printk("| |-(0x%08X) u4MaxBaMuPpduDur = %d\n",iVar5 + 0x68,local_48);
                  if (0 < DebugLevel) {
                    local_48 = 0;
                    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x6c,&local_48);
                    printk("| |-(0x%08X) u4MaxBaDurForLSig = %d\n",iVar5 + 0x6c,local_48);
LAB_001831c0:
                    if (DebugLevel < 1) goto LAB_0018329c;
                    uVar6 = FUN_00174570(param_1,iVar5 + 0x74);
                    printk("| |-(0x%08X) u1GrpId = %d\n",iVar5 + 0x74,uVar6);
                    if (0 < DebugLevel) {
                      uVar6 = FUN_00174570(param_1,iVar5 + 0x5f8);
                      printk("| |-(0x%08X) u1TrigBaPL = %d\n",iVar5 + 0x5f8,uVar6);
                      goto LAB_0018322c;
                    }
                  }
                }
              }
              else {
                uVar6 = FUN_00174570(param_1,iVar5 + 0x5c);
                printk("| |-(0x%08X) u1TxPwr_dBm = %d\n",iVar5 + 0x5c,uVar6);
                if (0 < DebugLevel) {
                  uVar6 = FUN_00174570(param_1,iVar5 + 0x5d);
                  printk("| |-(0x%08X) u1Bw = %d\n",iVar5 + 0x5d,uVar6);
LAB_001830a0:
                  if (DebugLevel < 1) goto LAB_001831c0;
                  uVar6 = FUN_00174570(param_1,iVar5 + 0x5e);
                  printk("| |-(0x%08X) u1PrimaryUserIdx = %d\n",iVar5 + 0x5e,uVar6);
                  if (0 < DebugLevel) {
                    local_48 = 0;
                    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 100);
                    printk("| |-(0x%08X) u4MuPpduDuration = %d\n",iVar5 + 100,local_48);
                    goto LAB_0018311c;
                  }
                }
              }
            }
            else {
              local_48 = 0;
              mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x50);
              printk("| |-(0x%08X) eTxMode = %d\n",iVar5 + 0x50,local_48);
              if (0 < DebugLevel) {
                uVar6 = FUN_00174570(param_1,iVar5 + 0x54);
                printk("| |-(0x%08X) u1AckGiType = %d\n",iVar5 + 0x54,uVar6);
LAB_00182fd0:
                if (DebugLevel < 1) goto LAB_001830a0;
                uVar6 = FUN_00174570(param_1,iVar5 + 0x55);
                printk("| |-(0x%08X) u1AckLtfType = %d\n",iVar5 + 0x55,uVar6);
                if (0 < DebugLevel) {
                  uVar6 = FUN_00174570(param_1,iVar5 + 0x56);
                  printk("| |-(0x%08X) u1AckMaxNss = %d\n",iVar5 + 0x56,uVar6);
                  goto LAB_00183038;
                }
              }
            }
          }
          else {
            uVar6 = FUN_00174570(param_1,iVar5 + 0x4a);
            printk("| |-(0x%08X) u1SigbMcs = %d\n",iVar5 + 0x4a,uVar6);
            if (0 < DebugLevel) {
              uVar6 = FUN_00174570(param_1,iVar5 + 0x4b);
              printk("| |-(0x%08X) u1GiType = %d\n",iVar5 + 0x4b,uVar6);
LAB_00182eec:
              if (DebugLevel < 1) goto LAB_00182fd0;
              uVar6 = FUN_00174570(param_1,iVar5 + 0x4c);
              printk("| |-(0x%08X) u1LtfType = %d\n",iVar5 + 0x4c,uVar6);
              if (0 < DebugLevel) {
                uVar6 = FUN_00174570(param_1,iVar5 + 0x4d);
                printk("| |-(0x%08X) u1StaCnt = %d\n",iVar5 + 0x4d,uVar6);
                goto LAB_00182f54;
              }
            }
          }
        }
        else {
          uVar6 = FUN_00174570(param_1,iVar5 + 0x10);
          printk("| |-(0x%08X) u1SerialId = %d\n",iVar5 + 0x10,uVar6);
          if (0 < DebugLevel) {
            uVar6 = FUN_00174570(param_1,iVar5 + 0x11);
            printk("| |-(0x%08X) u1SpeIdx = %d\n",iVar5 + 0x11,uVar6);
LAB_00182e1c:
            if (DebugLevel < 1) goto LAB_00182eec;
            uVar6 = FUN_00174570(param_1,iVar5 + 0x48);
            printk("| |-(0x%08X) u1SigbSym = %d\n",iVar5 + 0x48,uVar6);
            if (0 < DebugLevel) {
              uVar6 = FUN_00174570(param_1,iVar5 + 0x49);
              printk("| |-(0x%08X) u1LtfSym = %d\n",iVar5 + 0x49,uVar6);
              goto LAB_00182e84;
            }
          }
        }
      }
      else {
        local_48 = uVar8;
        mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 4,&local_48);
        printk("| |-(0x%08X) eBand = %d\n",iVar5 + 4,local_48);
        if (0 < DebugLevel) {
          uVar6 = FUN_00174570(param_1,iVar5 + 8);
          printk("| |-(0x%08X) u1AggPol = %d\n",iVar5 + 8,uVar6);
          if (DebugLevel < 1) goto LAB_00182e1c;
          uVar6 = FUN_00174570(param_1,iVar5 + 9);
          printk("| |-(0x%08X) u1Ac = %d\n",iVar5 + 9,uVar6);
          if (0 < DebugLevel) {
            local_48 = uVar8;
            mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0xc,&local_48);
            printk("| |-(0x%08X) txCmdType = %d\n",iVar5 + 0xc,local_48);
            goto LAB_00182db4;
          }
        }
      }
    }
  }
  if ((!bVar2) || (*(char *)(param_1 + 0x795a24) != '\0')) goto LAB_0018254c;
  iVar5 = *(int *)(param_1 + 0x795a20) + local_60 * 0x58;
  if (0 < DebugLevel) {
    printk("|-userInfo (0x%08X)\n",iVar5);
    if (DebugLevel < 1) {
LAB_001846f4:
      if (DebugLevel < 1) {
LAB_001847c4:
        if (DebugLevel < 1) {
LAB_00184894:
          if (DebugLevel < 1) {
LAB_00184964:
            if (DebugLevel < 1) {
LAB_00184a34:
              if (DebugLevel < 1) {
LAB_00184b04:
                if (0 < DebugLevel) {
                  uVar6 = FUN_00174570(param_1,iVar5 + 0x1c);
                  printk("| |-(0x%08X) u1AcSeq = %d\n",iVar5 + 0x1c,uVar6);
                  if (0 < DebugLevel) {
                    uVar6 = FUN_00174570(param_1,iVar5 + 0x1d);
                    printk("| |-(0x%08X) u1AcNum = %d\n",iVar5 + 0x1d,uVar6);
LAB_00184b6c:
                    if (0 < DebugLevel) {
                      uVar6 = FUN_00174528(param_1,iVar5 + 0x1e);
                      printk("| |-(0x%08X) u2BarRuRatio = %d\n",iVar5 + 0x1e,uVar6);
                      if (0 < DebugLevel) {
                        printk("| |-(0x%08X) u1AcRatio\n",iVar5 + 0x20);
                      }
                    }
                  }
                }
              }
              else {
                uVar6 = FUN_00174570(param_1,iVar5 + 0x18);
                printk("| |-(0x%08X) u1RuAllNss = %d\n",iVar5 + 0x18,uVar6);
                if (0 < DebugLevel) {
                  uVar6 = FUN_00174570(param_1,iVar5 + 0x19);
                  printk("| |-(0x%08X) fgAggOld = %d\n",iVar5 + 0x19,uVar6);
LAB_00184a9c:
                  if (DebugLevel < 1) goto LAB_00184b6c;
                  uVar6 = FUN_00174570(param_1,iVar5 + 0x1a);
                  printk("| |-(0x%08X) fgCB = %d\n",iVar5 + 0x1a,uVar6);
                  if (0 < DebugLevel) {
                    uVar6 = FUN_00174570(param_1,iVar5 + 0x1b);
                    printk("| |-(0x%08X) u1AckBw = %d\n",iVar5 + 0x1b,uVar6);
                    goto LAB_00184b04;
                  }
                }
              }
            }
            else {
              uVar6 = FUN_00174570(param_1,iVar5 + 0x12);
              printk("| |-(0x%08X) u1SrMcs = %d\n",iVar5 + 0x12,uVar6);
              if (0 < DebugLevel) {
                uVar6 = FUN_00174570(param_1,iVar5 + 0x13);
                printk("| |-(0x%08X) u1UpperMCS = %d\n",iVar5 + 0x13,uVar6);
LAB_001849cc:
                if (DebugLevel < 1) goto LAB_00184a9c;
                uVar6 = FUN_00174570(param_1,iVar5 + 0x14);
                printk("| |-(0x%08X) fgDcm = %d\n",iVar5 + 0x14,uVar6);
                if (0 < DebugLevel) {
                  uVar6 = FUN_00174528(param_1,iVar5 + 0x16);
                  printk("| |-(0x%08X) u2RuRatio = %d\n",iVar5 + 0x16,uVar6);
                  goto LAB_00184a34;
                }
              }
            }
          }
          else {
            uVar6 = FUN_00174570(param_1,iVar5 + 0xd);
            printk("| |-(0x%08X) u1Mcs = %d\n",iVar5 + 0xd,uVar6);
            if (0 < DebugLevel) {
              uVar6 = FUN_00174570(param_1,iVar5 + 0xe);
              printk("| |-(0x%08X) u1Gi = %d\n",iVar5 + 0xe,uVar6);
LAB_001848fc:
              if (DebugLevel < 1) goto LAB_001849cc;
              uVar6 = FUN_00174570(param_1,iVar5 + 0xf);
              printk("| |-(0x%08X) fgLdpc = %d\n",iVar5 + 0xf,uVar6);
              if (0 < DebugLevel) {
                uVar6 = FUN_00174528(param_1,iVar5 + 0x10);
                printk("| |-(0x%08X) u2WeightFactor = %d\n",iVar5 + 0x10,uVar6);
                goto LAB_00184964;
              }
            }
          }
        }
        else {
          uVar6 = FUN_00174570(param_1,iVar5 + 9);
          printk("| |-(0x%08X) u1StartStream = %d\n",iVar5 + 9,uVar6);
          if (0 < DebugLevel) {
            uVar6 = FUN_00174570(param_1,iVar5 + 10);
            printk("| |-(0x%08X) u1RateMode = %d\n",iVar5 + 10,uVar6);
LAB_0018482c:
            if (DebugLevel < 1) goto LAB_001848fc;
            uVar6 = FUN_00174570(param_1,iVar5 + 0xb);
            printk("| |-(0x%08X) u1Nss = %d\n",iVar5 + 0xb,uVar6);
            if (0 < DebugLevel) {
              uVar6 = FUN_00174570(param_1,iVar5 + 0xc);
              printk("| |-(0x%08X) u1StartSpatialStream = %d\n",iVar5 + 0xc,uVar6);
              goto LAB_00184894;
            }
          }
        }
      }
      else {
        uVar6 = FUN_00174570(param_1,iVar5 + 5);
        printk("| |-(0x%08X) u1RuTreeMapArrayIdx = %d\n",iVar5 + 5,uVar6);
        if (0 < DebugLevel) {
          uVar6 = FUN_00174570(param_1,iVar5 + 6);
          printk("| |-(0x%08X) u1RuMapArrayIdx = %d\n",iVar5 + 6,uVar6);
LAB_0018475c:
          if (DebugLevel < 1) goto LAB_0018482c;
          uVar6 = FUN_00174570(param_1,iVar5 + 7);
          printk("| |-(0x%08X) fgRuAllocBn = %d\n",iVar5 + 7,uVar6);
          if (0 < DebugLevel) {
            uVar6 = FUN_00174570(param_1,iVar5 + 8);
            printk("| |-(0x%08X) u1MuMimoSpatial = %d\n",iVar5 + 8,uVar6);
            goto LAB_001847c4;
          }
        }
      }
    }
    else {
      uVar6 = FUN_00174528(param_1,iVar5);
      printk("| |-(0x%08X) u2WlanId = %d\n",iVar5,uVar6);
      if (0 < DebugLevel) {
        uVar6 = FUN_00174570(param_1,iVar5 + 2);
        printk("| |-(0x%08X) fgUserPreLoad = %d\n",iVar5 + 2,uVar6);
        if (DebugLevel < 1) goto LAB_0018475c;
        uVar6 = FUN_00174570(param_1,iVar5 + 3);
        printk("| |-(0x%08X) u1MuMimoGrp = %d\n",iVar5 + 3,uVar6);
        if (0 < DebugLevel) {
          uVar6 = FUN_00174570(param_1,iVar5 + 4);
          printk("| |-(0x%08X) u1RuAlloc = %d\n",iVar5 + 4,uVar6);
          goto LAB_001846f4;
        }
      }
    }
  }
  iVar7 = 0;
  iVar9 = DebugLevel;
  do {
    if (0 < iVar9) {
      iVar9 = iVar7 + iVar5 + 0x20;
      uVar6 = FUN_00174570(param_1,iVar9);
      printk("| |-|-(0x%08X) u1AcRatio[%d] = %d\n",iVar9,iVar7,uVar6);
      iVar9 = DebugLevel;
    }
    iVar7 = iVar7 + 1;
  } while (iVar7 != 4);
  if (iVar9 < 1) goto LAB_0018254c;
  uVar6 = FUN_00174528(param_1,iVar5 + 0x24);
  printk("| |-(0x%08X) u2MumGrpIdx = %d\n",iVar5 + 0x24,uVar6);
  if (DebugLevel < 1) {
LAB_001826e0:
    if (0 < DebugLevel) {
      uVar6 = FUN_00174570(param_1,iVar5 + 0x2a);
      printk("| |-(0x%08X) u1AckPol = %d\n",iVar5 + 0x2a,uVar6);
      if (DebugLevel < 1) goto LAB_0018254c;
      uVar6 = FUN_00174570(param_1,iVar5 + 0x2b);
      printk("| |-(0x%08X) u1AckGrp = %d\n",iVar5 + 0x2b,uVar6);
      goto LAB_00182748;
    }
LAB_001827b0:
    if (0 < DebugLevel) {
      uVar6 = FUN_00174570(param_1,iVar5 + 0x2e);
      printk("| |-(0x%08X) u1BarRate = %d\n",iVar5 + 0x2e,uVar6);
      if (DebugLevel < 1) goto LAB_0018254c;
      uVar6 = FUN_00174570(param_1,iVar5 + 0x2f);
      printk("| |-(0x%08X) u1BarMode = %d\n",iVar5 + 0x2f,uVar6);
      goto LAB_00182818;
    }
LAB_00182880:
    if (0 < DebugLevel) {
      local_48 = 0;
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x34,&local_48);
      printk("| |-(0x%08X) u4BaMuPpduDur = %d\n",iVar5 + 0x34,local_48);
      if (DebugLevel < 1) goto LAB_0018254c;
      local_48 = 0;
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x38,&local_48);
      printk("| |-(0x%08X) u4BaLSigDur = %d\n",iVar5 + 0x38,local_48);
      goto LAB_00182918;
    }
LAB_00182980:
    if (0 < DebugLevel) {
      uVar6 = FUN_00174570(param_1,iVar5 + 0x3e);
      printk("| |-(0x%08X) u1AckRuAlloc = %d\n",iVar5 + 0x3e,uVar6);
      if (DebugLevel < 1) goto LAB_0018254c;
      uVar6 = FUN_00174570(param_1,iVar5 + 0x3f);
      printk("| |-(0x%08X) fgAckRuAllocBn = %d\n",iVar5 + 0x3f,uVar6);
      goto LAB_001829e8;
    }
LAB_00182a50:
    if (0 < DebugLevel) {
      uVar6 = FUN_00174570(param_1,iVar5 + 0x42);
      printk("| |-(0x%08X) fgAckLdpc = %d\n",iVar5 + 0x42,uVar6);
      if (DebugLevel < 1) goto LAB_0018254c;
      uVar6 = FUN_00174570(param_1,iVar5 + 0x43);
      printk("| |-(0x%08X) u1BarAckPol = %d\n",iVar5 + 0x43,uVar6);
      goto LAB_00182ab8;
    }
LAB_00182b20:
    if (0 < DebugLevel) {
      uVar6 = FUN_00174570(param_1,iVar5 + 0x46);
      printk("| |-(0x%08X) u1TidInfo = %d\n",iVar5 + 0x46,uVar6);
      if (DebugLevel < 1) goto LAB_0018254c;
      uVar6 = FUN_00174528(param_1,iVar5 + 0x48);
      printk("| |-(0x%08X) u2EffSnr = %d\n",iVar5 + 0x48,uVar6);
      goto LAB_00182b88;
    }
  }
  else {
    uVar6 = FUN_00174570(param_1,iVar5 + 0x26);
    printk("| |-(0x%08X) u2MumGrpStaCnt = %d\n",iVar5 + 0x26,uVar6);
    if (DebugLevel < 1) goto LAB_0018254c;
    uVar6 = FUN_00174570(param_1,iVar5 + 0x27);
    printk("| |-(0x%08X) u1LtfType = %d\n",iVar5 + 0x27,uVar6);
    if (0 < DebugLevel) {
      uVar6 = FUN_00174570(param_1,iVar5 + 0x28);
      printk("| |-(0x%08X) fgSplPrimaryUser = %d\n",iVar5 + 0x28,uVar6);
      if (DebugLevel < 1) goto LAB_0018254c;
      uVar6 = FUN_00174570(param_1,iVar5 + 0x29);
      printk("| |-(0x%08X) u1BfType = %d\n",iVar5 + 0x29,uVar6);
      goto LAB_001826e0;
    }
LAB_00182748:
    if (0 < DebugLevel) {
      uVar6 = FUN_00174570(param_1,iVar5 + 0x2c);
      printk("| |-(0x%08X) fgSuBar = %d\n",iVar5 + 0x2c,uVar6);
      if (DebugLevel < 1) goto LAB_0018254c;
      uVar6 = FUN_00174570(param_1,iVar5 + 0x2d);
      printk("| |-(0x%08X) fgMuBar = %d\n",iVar5 + 0x2d,uVar6);
      goto LAB_001827b0;
    }
LAB_00182818:
    if (0 < DebugLevel) {
      uVar6 = FUN_00174570(param_1,iVar5 + 0x30);
      printk("| |-(0x%08X) u1BarNsts = %d\n",iVar5 + 0x30,uVar6);
      if (DebugLevel < 1) goto LAB_0018254c;
      uVar6 = FUN_00174570(param_1,iVar5 + 0x31);
      printk("| |-(0x%08X) u1BaType = %d\n",iVar5 + 0x31,uVar6);
      goto LAB_00182880;
    }
LAB_00182918:
    if (0 < DebugLevel) {
      uVar6 = FUN_00174570(param_1,iVar5 + 0x3c);
      printk("| |-(0x%08X) fgBaDcm = %d\n",iVar5 + 0x3c,uVar6);
      if (DebugLevel < 1) goto LAB_0018254c;
      uVar6 = FUN_00174570(param_1,iVar5 + 0x3d);
      printk("| |-(0x%08X) fgBaStbc = %d\n",iVar5 + 0x3d,uVar6);
      goto LAB_00182980;
    }
LAB_001829e8:
    if (0 < DebugLevel) {
      uVar6 = FUN_00174570(param_1,iVar5 + 0x40);
      printk("| |-(0x%08X) u1AckMcs = %d\n",iVar5 + 0x40,uVar6);
      if (DebugLevel < 1) goto LAB_0018254c;
      uVar6 = FUN_00174570(param_1,iVar5 + 0x41);
      printk("| |-(0x%08X) u1AckNss = %d\n",iVar5 + 0x41,uVar6);
      goto LAB_00182a50;
    }
LAB_00182ab8:
    if (0 < DebugLevel) {
      uVar6 = FUN_00174570(param_1,iVar5 + 0x44);
      printk("| |-(0x%08X) u1SsAaloc = %d\n",iVar5 + 0x44,uVar6);
      if (DebugLevel < 1) goto LAB_0018254c;
      uVar6 = FUN_00174570(param_1,iVar5 + 0x45);
      printk("| |-(0x%08X) u1TargetRssi = %d\n",iVar5 + 0x45,uVar6);
      goto LAB_00182b20;
    }
LAB_00182b88:
    if (DebugLevel < 1) goto LAB_0018254c;
    uVar6 = FUN_00174528(param_1,iVar5 + 0x4a);
    printk("| |-(0x%08X) u2TxPwrAlpha_dB = %d\n",iVar5 + 0x4a,uVar6);
    if (DebugLevel < 1) goto LAB_0018254c;
    local_48 = 0;
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x4c);
    printk("| |-(0x%08X) u4RuScore = %d\n",iVar5 + 0x4c,local_48);
  }
  if (0 < DebugLevel) {
    local_48 = 0;
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),iVar5 + 0x50);
    printk("| |-(0x%08X) u4StaMuPpduDur = %d\n",iVar5 + 0x50,local_48);
    if (0 < DebugLevel) {
      uVar6 = FUN_00174570(param_1,iVar5 + 0x54);
      printk("| |-(0x%08X) fgLargeRu = %d\n",iVar5 + 0x54,uVar6);
    }
  }
LAB_0018254c:
  if (bVar1) {
    FUN_001748cc(param_1,*(undefined4 *)(param_1 + 0x795a28),local_60);
  }
  return;
}

