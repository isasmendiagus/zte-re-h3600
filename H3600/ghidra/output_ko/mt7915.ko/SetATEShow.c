// module: mt7915.ko
// function: SetATEShow @ 0x26294c
// size: 4852 bytes
//

undefined4 SetATEShow(int param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  undefined1 uVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  char cVar12;
  char *pcVar13;
  char *pcVar14;
  uint uVar15;
  char *local_44;
  undefined *local_32;
  undefined2 local_2e;
  undefined2 local_2c;
  undefined2 local_2a;
  
  iVar6 = net_ad_wrap_service();
  uVar15 = (uint)*(byte *)(iVar6 + 0x4cc);
  if (param_2 == 0) {
    if ((-1 < DebugLevel) && (printk("%s: No parameters!!\n","SetATEShow"), -1 < DebugLevel)) {
      printk("%s: Please use parameter 0 for Summary INFO, 1 for Detail INFO!!\n","SetATEShow");
      return 0;
    }
    return 0;
  }
  iVar6 = rstrtok(param_2,&_LC2);
  if (iVar6 == 0) {
    cVar5 = '\0';
  }
  else {
    cVar5 = '\0';
    cVar12 = '\0';
    do {
      if (cVar12 == '\0') {
        cVar5 = simple_strtol(iVar6,0,10);
        iVar6 = rstrtok(0,&_LC2);
        cVar12 = '\x01';
        if (iVar6 == 0) break;
      }
      if (-1 < DebugLevel) {
        printk("%s: Set wrong parameters\n","SetATEShow");
      }
      cVar12 = cVar12 + '\x01';
      iVar6 = rstrtok(0,&_LC2);
    } while (iVar6 != 0);
  }
  if (((0 < DebugLevel) && (printk("%s: ExtendInfo = %d\n","SetATEShow",cVar5), 0 < DebugLevel)) &&
     (printk("%s: control_band_idx = %d !!!!!\n","SetATEShow",uVar15), 0 < DebugLevel)) {
    iVar6 = net_ad_wrap_service(param_1);
    uVar4 = *(undefined1 *)(iVar6 + 0x4cc);
    iVar6 = net_ad_wrap_service(param_1);
    iVar7 = net_ad_wrap_service(param_1);
    printk("%s: band[%d] ATE Mode = 0x%x !!!!!\n","SetATEShow",uVar4,
           *(undefined4 *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x4e0));
  }
  iVar6 = net_ad_wrap_service(param_1);
  iVar7 = net_ad_wrap_service(param_1);
  uVar11 = *(uint *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x4e0);
  if (uVar11 == 10) {
    pcVar14 = "TXCONT";
  }
  else if (uVar11 < 0xb) {
    if (uVar11 == 2) {
      pcVar14 = "TXFRAME";
    }
    else if (uVar11 == 4) {
      pcVar14 = "RXFRAME";
    }
    else {
      if (uVar11 != 1) goto LAB_00262a5c;
      pcVar14 = "ATESTART";
    }
  }
  else if (uVar11 == 0x22) {
    pcVar14 = "TXCARS";
  }
  else if (uVar11 == 0x100) {
    pcVar14 = "ATESTOP";
  }
  else if (uVar11 == 0x12) {
    pcVar14 = "TXCARR";
  }
  else {
LAB_00262a5c:
    if (DebugLevel < 0) {
      pcVar14 = "Unknown ATE mode";
    }
    else {
      iVar6 = net_ad_wrap_service(param_1);
      pcVar14 = "Unknown ATE mode";
      printk("ERROR! Unknown ATE mode(0x%x)!\n",*(undefined4 *)(iVar6 + 0x4e0));
    }
  }
  iVar6 = net_ad_wrap_service(param_1);
  iVar7 = net_ad_wrap_service(param_1);
  if (*(byte *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x1135) < 0xd) {
    iVar6 = net_ad_wrap_service(param_1);
    iVar7 = net_ad_wrap_service(param_1);
    local_44 = &DAT_005e1d20 +
               (uint)*(byte *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x1135) * 0xf;
  }
  else {
    local_44 = "Unknown phy mode";
  }
  if (((0 < DebugLevel) &&
      (printk("=============================================\n"), 0 < DebugLevel)) &&
     (printk("\t\tBand %d Generic INFO\n",uVar15), 0 < DebugLevel)) {
    printk("=============================================\n");
  }
  iVar6 = net_ad_wrap_service(param_1);
  iVar7 = net_ad_wrap_service(param_1);
  bVar1 = *(byte *)(iVar7 + 0x4cc);
  iVar7 = net_ad_wrap_service(param_1);
  pcVar13 = (char *)((uint)bVar1 * 0xd18 + iVar6 + 0x6e5);
  iVar6 = net_ad_wrap_service(param_1);
  bVar1 = *(byte *)(iVar6 + 0x4cc);
  iVar6 = net_ad_wrap_service(param_1);
  iVar8 = net_ad_wrap_service(param_1);
  bVar2 = *(byte *)(iVar8 + 0x4cc);
  iVar8 = net_ad_wrap_service(param_1);
  iVar9 = net_ad_wrap_service(param_1);
  bVar3 = *(byte *)(iVar9 + 0x4cc);
  if ((0 < DebugLevel) && (printk("ATE Mode = %s\n",pcVar14), 0 < DebugLevel)) {
    printk("ATE Tx Methods:\n");
  }
  pcVar14 = &DAT_005e1d20;
  iVar9 = DebugLevel;
  do {
    local_32 = &DAT_00445854;
    local_2e = 0;
    local_2c = 0;
    local_2a = 0;
    if (*pcVar14 != '\0') {
      if (*pcVar13 != '\0') {
        local_32 = &DAT_00435854;
      }
      if (0 < iVar9) {
        printk("\t%s = %s\n",pcVar14,&local_32);
        iVar9 = DebugLevel;
      }
    }
    pcVar14 = pcVar14 + 0xf;
    pcVar13 = pcVar13 + 1;
  } while (pcVar14 != (char *)0x5e1de3);
  if (0 < iVar9) {
    iVar9 = net_ad_wrap_service(param_1);
    iVar10 = net_ad_wrap_service(param_1);
    printk("TxAntennaSel = 0x%x\n",
           *(undefined4 *)((uint)*(byte *)(iVar10 + 0x4cc) * 0xd18 + iVar9 + 0x1128));
    if (DebugLevel < 1) {
LAB_00262e58:
      if (DebugLevel < 1) {
LAB_00262f8c:
        if (DebugLevel < 1) {
LAB_00263094:
          if (DebugLevel < 1) {
LAB_00263194:
            if (DebugLevel < 1) {
LAB_00263298:
              if (DebugLevel < 1) {
LAB_00263398:
                if (DebugLevel < 1) {
LAB_002634a0:
                  if (0 < DebugLevel) {
                    iVar6 = net_ad_wrap_service(param_1);
                    iVar7 = net_ad_wrap_service(param_1);
                    printk("LDPC = %d\n",
                           *(undefined1 *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x113b))
                    ;
                    if (0 < DebugLevel) {
                      iVar6 = net_ad_wrap_service(param_1);
                      iVar7 = net_ad_wrap_service(param_1);
                      printk("Preamble = %d\n",
                             *(undefined1 *)
                              ((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x113d));
LAB_00263524:
                      if (0 < DebugLevel) {
                        iVar6 = net_ad_wrap_service(param_1);
                        iVar7 = net_ad_wrap_service(param_1);
                        printk("FixedPayload = %d\n",
                               *(undefined4 *)
                                ((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x6e0));
                        if (0 < DebugLevel) {
                          iVar6 = net_ad_wrap_service(param_1);
                          iVar7 = net_ad_wrap_service(param_1);
                          printk("Thermal Value = %d\n",
                                 *(undefined4 *)
                                  ((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x114c));
                        }
                      }
                    }
                  }
                }
                else {
                  iVar6 = net_ad_wrap_service(param_1);
                  iVar7 = net_ad_wrap_service(param_1);
                  printk("Nss = %d\n",
                         *(undefined1 *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x1139));
                  if (0 < DebugLevel) {
                    iVar6 = net_ad_wrap_service(param_1);
                    iVar7 = net_ad_wrap_service(param_1);
                    printk("PerPktBW = %d\n",
                           *(undefined1 *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x1137))
                    ;
LAB_0026341c:
                    if (DebugLevel < 1) goto LAB_00263524;
                    iVar6 = net_ad_wrap_service(param_1);
                    iVar7 = net_ad_wrap_service(param_1);
                    printk("PrimaryBWSel = %d\n",
                           (int)*(char *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x1134));
                    if (0 < DebugLevel) {
                      iVar6 = net_ad_wrap_service(param_1);
                      iVar7 = net_ad_wrap_service(param_1);
                      printk("STBC = %d\n",
                             *(undefined1 *)
                              ((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x113a));
                      goto LAB_002634a0;
                    }
                  }
                }
              }
              else {
                iVar6 = net_ad_wrap_service(param_1);
                iVar7 = net_ad_wrap_service(param_1);
                printk("SKB Allocate = %d\n",
                       *(undefined4 *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x4ec));
                if (0 < DebugLevel) {
                  iVar6 = net_ad_wrap_service(param_1);
                  iVar7 = net_ad_wrap_service(param_1);
                  printk("wdev_idx = %d\n",
                         *(undefined1 *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x50c));
LAB_00263314:
                  if (DebugLevel < 1) goto LAB_0026341c;
                  iVar6 = net_ad_wrap_service(param_1);
                  iVar7 = net_ad_wrap_service(param_1);
                  printk("QID = %d\n",
                         *(undefined2 *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x50e));
                  if (0 < DebugLevel) {
                    iVar6 = net_ad_wrap_service(param_1);
                    iVar7 = net_ad_wrap_service(param_1);
                    printk("PriSel = %d\n",
                           *(undefined1 *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x1133))
                    ;
                    goto LAB_00263398;
                  }
                }
              }
            }
            else {
              iVar6 = net_ad_wrap_service(param_1);
              iVar7 = net_ad_wrap_service(param_1);
              printk("Duty Cycle = %d%%\n",
                     *(undefined4 *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x10e8));
              if (0 < DebugLevel) {
                iVar6 = net_ad_wrap_service(param_1);
                iVar7 = net_ad_wrap_service(param_1);
                printk("Pkt Tx Time = %dus\n",
                       *(undefined4 *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x10f0));
LAB_00263218:
                if (DebugLevel < 1) goto LAB_00263314;
                iVar6 = net_ad_wrap_service(param_1);
                iVar7 = net_ad_wrap_service(param_1);
                printk("Payload Pattern = 0x%02x\n",
                       *(undefined1 *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x651));
                if (0 < DebugLevel) {
                  iVar6 = net_ad_wrap_service(param_1);
                  iVar7 = net_ad_wrap_service(param_1);
                  printk("RFFreqOffset = %u\n",
                         *(undefined4 *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x1148));
                  goto LAB_00263298;
                }
              }
            }
          }
          else {
            iVar6 = net_ad_wrap_service(param_1);
            iVar7 = net_ad_wrap_service(param_1);
            printk("TxLength = %u\n",
                   *(undefined4 *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x6dc));
            if (0 < DebugLevel) {
              iVar6 = net_ad_wrap_service(param_1);
              iVar7 = net_ad_wrap_service(param_1);
              printk("Header Length = %d\n",
                     *(undefined2 *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x6d6));
LAB_00263114:
              if (DebugLevel < 1) goto LAB_00263218;
              iVar6 = net_ad_wrap_service(param_1);
              iVar7 = net_ad_wrap_service(param_1);
              printk("Payload Length = %d\n",
                     *(undefined4 *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x6d8));
              if (0 < DebugLevel) {
                iVar6 = net_ad_wrap_service(param_1);
                iVar7 = net_ad_wrap_service(param_1);
                printk("IPG = %dus\n",
                       *(undefined4 *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x10f4));
                goto LAB_00263194;
              }
            }
          }
        }
        else {
          iVar6 = net_ad_wrap_service(param_1);
          iVar7 = net_ad_wrap_service(param_1);
          printk("Channel = %u\n",
                 *(undefined1 *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x1130));
          if (0 < DebugLevel) {
            iVar6 = net_ad_wrap_service(param_1);
            iVar7 = net_ad_wrap_service(param_1);
            printk("Channel_2nd = %u\n",
                   *(undefined1 *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x1143));
LAB_00263010:
            if (DebugLevel < 1) goto LAB_00263114;
            iVar6 = net_ad_wrap_service(param_1);
            iVar7 = net_ad_wrap_service(param_1);
            printk("Ch_Band = %d\n",
                   *(undefined1 *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x1131));
            if (0 < DebugLevel) {
              iVar6 = net_ad_wrap_service(param_1);
              iVar7 = net_ad_wrap_service(param_1);
              printk("Control Channel = %d\n",
                     *(undefined1 *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x1132));
              goto LAB_00263094;
            }
          }
        }
      }
      else {
        printk("TxMode = %s\n",local_44);
        if (0 < DebugLevel) {
          iVar7 = iVar7 + (uint)bVar1 * 0xd18;
          printk("Addr1 = %02x:%02x:%02x:%02x:%02x:%02x\n",*(undefined1 *)(iVar7 + 0x531),
                 *(undefined1 *)(iVar7 + 0x532),*(undefined1 *)(iVar7 + 0x533),
                 *(undefined1 *)(iVar7 + 0x534),*(undefined1 *)(iVar7 + 0x535),
                 *(undefined1 *)(iVar7 + 0x536));
LAB_00262ed8:
          if (DebugLevel < 1) goto LAB_00263010;
          iVar6 = iVar6 + (uint)bVar2 * 0xd18;
          printk("Addr2 = %02x:%02x:%02x:%02x:%02x:%02x\n",*(undefined1 *)(iVar6 + 0x591),
                 *(undefined1 *)(iVar6 + 0x592),*(undefined1 *)(iVar6 + 0x593),
                 *(undefined1 *)(iVar6 + 0x594),*(undefined1 *)(iVar6 + 0x595),
                 *(undefined1 *)(iVar6 + 0x596));
          if (0 < DebugLevel) {
            iVar8 = iVar8 + (uint)bVar3 * 0xd18;
            printk("Addr3 = %02x:%02x:%02x:%02x:%02x:%02x\n",*(undefined1 *)(iVar8 + 0x5f1),
                   *(undefined1 *)(iVar8 + 0x5f2),*(undefined1 *)(iVar8 + 0x5f3),
                   *(undefined1 *)(iVar8 + 0x5f4),*(undefined1 *)(iVar8 + 0x5f5),
                   *(undefined1 *)(iVar8 + 0x5f6));
            goto LAB_00262f8c;
          }
        }
      }
    }
    else {
      iVar9 = net_ad_wrap_service(param_1);
      iVar10 = net_ad_wrap_service(param_1);
      printk("RxAntennaSel = 0x%x\n",
             *(undefined2 *)((uint)*(byte *)(iVar10 + 0x4cc) * 0xd18 + iVar9 + 0x112e));
      if (0 < DebugLevel) {
        iVar9 = net_ad_wrap_service(param_1);
        iVar10 = net_ad_wrap_service(param_1);
        printk("BBPCurrentBW = %u\n",
               *(undefined1 *)((uint)*(byte *)(iVar10 + 0x4cc) * 0xd18 + iVar9 + 0x1136));
        if (DebugLevel < 1) goto LAB_00262ed8;
        iVar9 = net_ad_wrap_service(param_1);
        iVar10 = net_ad_wrap_service(param_1);
        printk("GI = %u\n",*(undefined1 *)((uint)*(byte *)(iVar10 + 0x4cc) * 0xd18 + iVar9 + 0x113c)
              );
        if (0 < DebugLevel) {
          iVar9 = net_ad_wrap_service(param_1);
          iVar10 = net_ad_wrap_service(param_1);
          printk("MCS = %u\n",
                 *(undefined1 *)((uint)*(byte *)(iVar10 + 0x4cc) * 0xd18 + iVar9 + 0x1138));
          goto LAB_00262e58;
        }
      }
    }
  }
  if (cVar5 == '\0') {
    return 1;
  }
  if (DebugLevel < 1) {
LAB_00262bd4:
    if (uVar15 == 0) {
      return 1;
    }
LAB_00262bdc:
    if (DebugLevel < 1) {
      return 1;
    }
    printk("=============================================\n");
LAB_0026383c:
    if (0 < DebugLevel) {
      printk("\t\tTx Power INFO\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk("=============================================\n");
      goto LAB_00263874;
    }
LAB_002638c4:
    if (0 < DebugLevel) {
      printk("TxPower2 = %d\n",(int)*(char *)(param_1 + 0xa3ac1e));
      if (DebugLevel < 1) {
        return 1;
      }
      printk("TxPower3 = %d\n",(int)*(char *)(param_1 + 0xa3ac1f));
      goto LAB_00263914;
    }
LAB_0026394c:
    if (0 < DebugLevel) {
      printk("=============================================\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk("Current_Init_Thread = %d\n",*(undefined4 *)(param_1 + 0xa3a054));
      goto LAB_00263990;
    }
LAB_002639d4:
    if (0 < DebugLevel) {
      printk("\t\tBF Band %d INFO\n",uVar15);
      if (DebugLevel < 1) {
        return 1;
      }
      printk("=============================================\n");
      goto LAB_00263a10;
    }
LAB_00263a6c:
    if (0 < DebugLevel) {
      iVar6 = net_ad_wrap_service(param_1);
      iVar7 = net_ad_wrap_service(param_1);
      printk("ETXBF = %d\n",*(undefined1 *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x11cd)
            );
      if (DebugLevel < 1) {
        return 1;
      }
      iVar6 = net_ad_wrap_service(param_1);
      iVar7 = net_ad_wrap_service(param_1);
      printk("ITXBF = %d\n",*(undefined1 *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x11cc)
            );
      goto LAB_00263af0;
    }
  }
  else {
    printk("=============================================\n");
    if (0 < DebugLevel) {
      printk("\t\tTX INFO\n");
      if (0 < DebugLevel) {
        printk("=============================================\n");
        if (DebugLevel < 1) goto LAB_0026372c;
        iVar6 = net_ad_wrap_service(param_1);
        iVar7 = net_ad_wrap_service(param_1);
        printk("Sequence = %d\n",
               *(undefined2 *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x6d4));
        if (0 < DebugLevel) {
          iVar6 = net_ad_wrap_service(param_1);
          iVar7 = net_ad_wrap_service(param_1);
          printk("TxDoneCount = %d\n",
                 *(undefined4 *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x111c));
          goto LAB_002636e0;
        }
      }
      goto LAB_00262bd4;
    }
LAB_002636e0:
    if (DebugLevel < 1) goto LAB_00262bd4;
    iVar6 = net_ad_wrap_service(param_1);
    iVar7 = net_ad_wrap_service(param_1);
    printk("TxedCount = %d\n",
           *(undefined4 *)((uint)*(byte *)(iVar7 + 0x4cc) * 0xd18 + iVar6 + 0x1120));
LAB_0026372c:
    if (uVar15 != 0) goto LAB_00262bdc;
    if (DebugLevel < 1) {
      return 1;
    }
    printk("=============================================\n");
    if (0 < DebugLevel) {
      printk("\t\tRX INFO\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk("=============================================\n");
      if (0 < DebugLevel) {
        printk("RxTotalCnt = %d\n",*(undefined4 *)(param_1 + 0xa3b74c));
        if (DebugLevel < 1) {
          return 1;
        }
        printk("RxMacMdrdyCount = %d\n",*(undefined4 *)(param_1 + 0xa3b75c));
        goto LAB_002637c0;
      }
      goto LAB_0026383c;
    }
LAB_002637c0:
    if (0 < DebugLevel) {
      printk("RxMacFCSErrCount = %d\n",*(undefined4 *)(param_1 + 0xa3b758));
      goto LAB_00262bdc;
    }
LAB_00263874:
    if (0 < DebugLevel) {
      printk("TxPower0 = %d\n",(int)*(char *)(param_1 + 0xa3ac1c));
      if (DebugLevel < 1) {
        return 1;
      }
      printk("TxPower1 = %d\n",(int)*(char *)(param_1 + 0xa3ac1d));
      goto LAB_002638c4;
    }
LAB_00263914:
    if (0 < DebugLevel) {
      printk("=============================================\n");
      if (DebugLevel < 1) {
        return 1;
      }
      printk("\t\tATE TX Thread INFO\n");
      goto LAB_0026394c;
    }
LAB_00263990:
    if (0 < DebugLevel) {
      printk("Dequeue Count = %d\n",*(undefined4 *)(param_1 + 0xa3a058));
      if (DebugLevel < 1) {
        return 1;
      }
      printk("=============================================\n");
      goto LAB_002639d4;
    }
LAB_00263a10:
    if (0 < DebugLevel) {
      iVar6 = net_ad_wrap_service(param_1);
      printk("fgEBfEverEnabled = %d\n",*(undefined1 *)(uVar15 * 0xd18 + iVar6 + 0x11ce));
      if (DebugLevel < 1) {
        return 1;
      }
      printk("TXBF INFO Length = %d\n",*(undefined4 *)(param_1 + 0xa3ae10));
      goto LAB_00263a6c;
    }
LAB_00263af0:
    if (DebugLevel < 1) goto LAB_00263b6c;
    printk("=============================================\n");
    if (DebugLevel < 1) {
      return 1;
    }
    printk("\t\tMU INFO\n");
  }
  if (DebugLevel < 1) {
    return 1;
  }
  printk("=============================================\n");
  if (DebugLevel < 1) {
    return 1;
  }
  printk("MU Enable = %d\n",*(undefined1 *)(param_1 + 0xa3b000));
LAB_00263b6c:
  if ((0 < DebugLevel) &&
     (printk("MU Users = %d\n",*(undefined4 *)(param_1 + 0xa3b004)), 0 < DebugLevel)) {
    printk("wcid_ref = %d\n",*(undefined2 *)(param_1 + 0xa3b008));
  }
  return 1;
}

