// module: mt7915.ko
// function: mtf_trans_rxd_into_rxblk @ 0x19ee6c
// size: 5144 bytes
//

int mtf_trans_rxd_into_rxblk(int param_1,int param_2,int param_3)

{
  byte bVar1;
  ushort uVar2;
  ushort uVar3;
  uint *puVar4;
  int iVar5;
  ushort *puVar6;
  undefined1 *puVar7;
  undefined4 uVar8;
  int iVar9;
  short sVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  undefined1 uVar14;
  byte bVar15;
  ushort *puVar16;
  uint *puVar17;
  int iVar18;
  uint *puVar19;
  uint *puVar20;
  uint *puVar21;
  uint uVar22;
  uint uVar23;
  byte *pbVar24;
  uint uVar25;
  bool bVar26;
  bool bVar27;
  uint *local_30;
  
  puVar17 = *(uint **)(param_3 + 0xcc);
  if ((*(char *)(param_1 + 0xa7d07f) != '\0') &&
     (hex_dump("rxd raw data: ",puVar17,0x18), 0 < DebugLevel)) {
    printk("RxData_BASE:\n");
    if (DebugLevel < 1) {
LAB_0019f4ac:
      if (DebugLevel < 1) {
LAB_0019f53c:
        if (DebugLevel < 1) {
LAB_0019f5cc:
          if (DebugLevel < 1) {
LAB_0019f65c:
            if (DebugLevel < 1) {
LAB_0019f6ec:
              if (DebugLevel < 1) {
LAB_0019f77c:
                if (DebugLevel < 1) {
LAB_0019f80c:
                  if (DebugLevel < 1) {
LAB_0019f89c:
                    if (DebugLevel < 1) {
LAB_0019f92c:
                      if (DebugLevel < 1) {
LAB_0019f9e8:
                        if (DebugLevel < 1) {
LAB_0019fa78:
                          if (DebugLevel < 1) {
LAB_0019fb08:
                            if (DebugLevel < 1) {
LAB_0019fb98:
                              if (DebugLevel < 1) {
LAB_0019fc28:
                                if ((0 < DebugLevel) &&
                                   (printk("CLS_BITMAP = %d, ",(puVar17[4] << 3) >> 0x16),
                                   0 < DebugLevel)) {
                                  printk("PF_MODE = %d, ",(puVar17[4] << 2) >> 0x1f);
LAB_0019fc70:
                                  if (0 < DebugLevel) {
                                    printk("PF_STS = %d\n",puVar17[4] >> 0x1e);
                                  }
                                }
                              }
                              else {
                                printk("CLS = %d, ",(puVar17[4] << 0x15) >> 0x1f);
                                if (0 < DebugLevel) {
                                  printk("OFLD = %d, ",(puVar17[4] << 0x13) >> 0x1e);
LAB_0019fbe0:
                                  if (DebugLevel < 1) goto LAB_0019fc70;
                                  printk("MGC = %d\n",(puVar17[4] << 0x12) >> 0x1f);
                                  if (0 < DebugLevel) {
                                    printk("\tWOL = %d, ",(puVar17[4] << 0xd) >> 0x1b);
                                    goto LAB_0019fc28;
                                  }
                                }
                              }
                            }
                            else {
                              printk("RX_DROP = %d, ",(puVar17[3] << 1) >> 0x1f);
                              if (0 < DebugLevel) {
                                printk("VLAN2ETH = %d\n",puVar17[3] >> 0x1f);
LAB_0019fb50:
                                if (DebugLevel < 1) goto LAB_0019fbe0;
                                printk("\tPF = %d, ",puVar17[4] & 3);
                                if (0 < DebugLevel) {
                                  printk("DP = %d, ",(puVar17[4] << 0x16) >> 0x1f);
                                  goto LAB_0019fb98;
                                }
                              }
                            }
                          }
                          else {
                            printk("DIS_RHTR = %d, ",(puVar17[3] << 5) >> 0x1f);
                            if (0 < DebugLevel) {
                              printk("PSS = %d\n",(puVar17[3] << 4) >> 0x1f);
LAB_0019fac0:
                              if (DebugLevel < 1) goto LAB_0019fb50;
                              printk("\tMORE = %d, ",(puVar17[3] << 3) >> 0x1f);
                              if (0 < DebugLevel) {
                                printk("UWAT = %d, ",(puVar17[3] << 2) >> 0x1f);
                                goto LAB_0019fb08;
                              }
                            }
                          }
                        }
                        else {
                          printk("AMS = %d, ",(puVar17[3] << 9) >> 0x1f);
                          if (0 < DebugLevel) {
                            printk("MESH = %d\n",(puVar17[3] << 8) >> 0x1f);
LAB_0019fa30:
                            if (DebugLevel < 1) goto LAB_0019fac0;
                            printk("\tMHCP = %d, ",(puVar17[3] << 7) >> 0x1f);
                            if (0 < DebugLevel) {
                              printk("NO_INFO_WB = %d,",(puVar17[3] << 6) >> 0x1f);
                              goto LAB_0019fa78;
                            }
                          }
                        }
                      }
                      else {
                        uVar11 = (puVar17[3] << 0xe) >> 0x1e;
                        printk("\tHTC/UC2ME/MC/BC = %d/%d/%d/%d\n",(puVar17[3] << 0xd) >> 0x1f,
                               uVar11 == 1,uVar11 == 2,uVar11 == 3);
                        if (0 < DebugLevel) {
                          printk("\tTCL = %d, ",(puVar17[3] << 0xc) >> 0x1f);
LAB_0019f9a0:
                          if (DebugLevel < 1) goto LAB_0019fa30;
                          printk("BBM = %d, ",(puVar17[3] << 0xb) >> 0x1f);
                          if (0 < DebugLevel) {
                            printk("BU = %d, ",(puVar17[3] << 10) >> 0x1f);
                            goto LAB_0019f9e8;
                          }
                        }
                      }
                    }
                    else {
                      printk("\tNon-AMPDU Subframe(NASF) = %d, ",(puVar17[2] << 1) >> 0x1f);
                      if (0 < DebugLevel) {
                        printk("BF_RPT = %d\n",puVar17[2] >> 0x1f);
LAB_0019f8e4:
                        if (DebugLevel < 1) goto LAB_0019f9a0;
                        printk("\tRX Vector Sequence No = %d, ",puVar17[3] & 0xff);
                        if (0 < DebugLevel) {
                          printk("Channel Frequency = %d\n",(puVar17[3] << 0x10) >> 0x18);
                          goto LAB_0019f92c;
                        }
                      }
                    }
                  }
                  else {
                    printk("\tInterested Frame(INTF) = %d, ",(puVar17[2] << 5) >> 0x1f);
                    if (0 < DebugLevel) {
                      printk("Fragment Frame(FRAG) = %d\n",(puVar17[2] << 4) >> 0x1f);
LAB_0019f854:
                      if (DebugLevel < 1) goto LAB_0019f8e4;
                      printk("\tNull Frame(NULL) = %d, ",(puVar17[2] << 3) >> 0x1f);
                      if (0 < DebugLevel) {
                        printk("Non Data Frame(NDATA) = %d\n",(puVar17[2] << 2) >> 0x1f);
                        goto LAB_0019f89c;
                      }
                    }
                  }
                }
                else {
                  printk("SWBIT = %d, ",(puVar17[2] << 9) >> 0x1f);
                  if (0 < DebugLevel) {
                    printk("DeAMSDU Fail(DAF) = %d\n",(puVar17[2] << 8) >> 0x1f);
LAB_0019f7c4:
                    if (DebugLevel < 1) goto LAB_0019f854;
                    printk("\tExceedMax Rx Length(EL) = %d, ",(puVar17[2] << 7) >> 0x1f);
                    if (0 < DebugLevel) {
                      printk("HdrTransFail(HTF) = %d\n",(puVar17[2] << 6) >> 0x1f);
                      goto LAB_0019f80c;
                    }
                  }
                }
              }
              else {
                printk("\tHeaerTrans(H) = %d, ",(puVar17[2] << 0x12) >> 0x1f);
                if (0 < DebugLevel) {
                  printk("HeaerOffset(HO) = %d, ",(puVar17[2] << 0x10) >> 0x1e);
LAB_0019f734:
                  if (DebugLevel < 1) goto LAB_0019f7c4;
                  printk("TID = %d\n",(puVar17[2] << 0xc) >> 0x1c);
                  if (0 < DebugLevel) {
                    printk("\tMU_BAR = %d, ",(puVar17[2] << 10) >> 0x1f);
                    goto LAB_0019f77c;
                  }
                }
              }
            }
            else {
              printk("FCE Error(FC) = %d\n",(puVar17[1] << 4) >> 0x1f);
              if (0 < DebugLevel) {
                printk("\tBSSID = %d, ",puVar17[2] & 0x3f);
LAB_0019f6a4:
                if (DebugLevel < 1) goto LAB_0019f734;
                printk("BF_CQI = %d, ",(puVar17[2] << 0x18) >> 0x1f);
                if (0 < DebugLevel) {
                  printk("HdearLength(MAC) = %d\n",(puVar17[2] << 0x13) >> 0x1b);
                  goto LAB_0019f6ec;
                }
              }
            }
          }
          else {
            printk("CLM = %d,",(puVar17[1] << 7) >> 0x1f);
            if (0 < DebugLevel) {
              printk("ADD_OM = %d\n",(puVar17[1] << 1) >> 0x1f);
LAB_0019f614:
              if (DebugLevel < 1) goto LAB_0019f6a4;
              printk("\tICV Err(I) = %d, ",(puVar17[1] << 6) >> 0x1f);
              if (0 < DebugLevel) {
                printk("TKIP MIC Err(T) = %d, ",(puVar17[1] << 5) >> 0x1f);
                goto LAB_0019f65c;
              }
            }
          }
        }
        else {
          printk("SPP_EN = %d\n",(puVar17[1] << 2) >> 0x1f);
          if (0 < DebugLevel) {
            printk("\tSEC Mode = %d, ",(puVar17[1] << 0xb) >> 0x1b);
LAB_0019f584:
            if (DebugLevel < 1) goto LAB_0019f614;
            printk("KeyID = %d, ",(puVar17[1] << 9) >> 0x1e);
            if (0 < DebugLevel) {
              printk("CM = %d, ",(puVar17[1] << 8) >> 0x1f);
              goto LAB_0019f5cc;
            }
          }
        }
      }
      else {
        printk("SEC_DONE = %d\n",puVar17[1] & 1);
        if (0 < DebugLevel) {
          printk("\tWlanIndex = %d, ",puVar17[1] & 0x3ff);
LAB_0019f4f4:
          if (DebugLevel < 1) goto LAB_0019f584;
          printk("GroupValid = 0x%x, ",(puVar17[1] << 0x10) >> 0x1b);
          if (0 < DebugLevel) {
            printk("BN = %d, ",(puVar17[1] << 3) >> 0x1f);
            goto LAB_0019f53c;
          }
        }
      }
    }
    else {
      uVar11 = *puVar17;
      uVar8 = rxd_pkt_type_str(uVar11 >> 0x1b);
      printk("\tPktType = %d(%s), ",uVar11 >> 0x1b,uVar8);
      if (0 < DebugLevel) {
        printk("RxByteCnt = %d\n",*puVar17 & 0xffff);
        if (DebugLevel < 1) goto LAB_0019f4f4;
        printk("\tEtherTypeOffset = %d(WORD), ",(*puVar17 << 9) >> 0x19);
        if (0 < DebugLevel) {
          printk("IP/UT = %d/%d, ",(*puVar17 << 8) >> 0x1f,(*puVar17 << 7) >> 0x1f);
          goto LAB_0019f4ac;
        }
      }
    }
  }
  *(uint **)(param_2 + 0x18) = puVar17;
  iVar5 = param_2 + 0xc;
  *(int *)(param_2 + 0x10) = iVar5;
  puVar19 = puVar17 + 6;
  uVar11 = puVar17[1];
  if ((uVar11 & 0x4000) == 0) {
    iVar18 = 0x18;
    puVar20 = puVar19;
    puVar19 = (uint *)0x0;
  }
  else {
    iVar18 = 0x28;
    puVar20 = puVar17 + 10;
  }
  puVar21 = puVar20;
  puVar4 = (uint *)0x0;
  if ((uVar11 & 0x800) != 0) {
    iVar18 = iVar18 + 0x10;
    puVar21 = puVar20 + 4;
    puVar4 = puVar20;
  }
  local_30 = puVar21;
  puVar20 = (uint *)0x0;
  if ((uVar11 & 0x1000) != 0) {
    iVar18 = iVar18 + 8;
    local_30 = puVar21 + 2;
    puVar20 = puVar21;
  }
  if ((uVar11 & 0x2000) == 0) {
    puVar21 = local_30;
    local_30 = (uint *)0x0;
  }
  else {
    iVar18 = iVar18 + 8;
    puVar21 = local_30 + 2;
  }
  if ((uVar11 & 0x8000) == 0) {
    puVar21 = (uint *)0x0;
  }
  else {
    iVar18 = iVar18 + 0x48;
  }
  sVar10 = (short)*puVar17 - (short)iVar18;
  *(short *)(param_2 + 0x48) = sVar10;
  uVar11 = (puVar17[2] << 0x10) >> 0x1e;
  if (uVar11 != 0) {
    iVar9 = uVar11 * 2;
    sVar10 = sVar10 - (short)iVar9;
    iVar18 = iVar18 + iVar9;
    *(short *)(param_2 + 0x48) = sVar10;
  }
  *(short *)(param_2 + 0x40) = sVar10;
  *(byte *)(param_2 + 0x4c) = (byte)((puVar17[1] << 3) >> 0x1f);
  *(ushort *)(param_2 + 0x4e) = (ushort)((puVar17[1] << 0x16) >> 0x16);
  *(byte *)(param_2 + 0x52) = (byte)puVar17[2] & 0x3f;
  *(byte *)(param_2 + 0x72) = (byte)((puVar17[1] << 0xb) >> 0x1b);
  *(byte *)(param_2 + 0x51) = (byte)((puVar17[1] << 9) >> 0x1e);
  if ((puVar17[3] & 0x40000) != 0) {
    *(uint *)(param_2 + 0x44) = *(uint *)(param_2 + 0x44) | 8;
  }
  uVar11 = puVar17[1];
  if ((uVar11 & 0x800000) != 0) {
    *(uint *)(param_2 + 0x44) = *(uint *)(param_2 + 0x44) | 0x100000;
    uVar11 = puVar17[1];
  }
  if ((uVar11 & 0x1000000) != 0) {
    *(uint *)(param_2 + 0x44) = *(uint *)(param_2 + 0x44) | 0x200000;
    uVar11 = puVar17[1];
  }
  if ((uVar11 & 0x2000000) != 0) {
    *(uint *)(param_2 + 0x44) = *(uint *)(param_2 + 0x44) | 0x400000;
    uVar11 = puVar17[1];
  }
  if ((uVar11 & 0x4000000) != 0) {
    *(uint *)(param_2 + 0x44) = *(uint *)(param_2 + 0x44) | 0x800000;
  }
  *(ushort *)(param_2 + 0x80) = (ushort)(byte)(puVar17[3] >> 8);
  *(byte *)(param_2 + 0x53) = (byte)((puVar17[2] << 0xc) >> 0x1c);
  if ((puVar17[2] & 0x2000) != 0) {
    *(uint *)(param_2 + 0x44) = *(uint *)(param_2 + 0x44) | 0x40000;
  }
  uVar11 = (puVar17[3] << 0xe) >> 0x1e;
  if (uVar11 == 2) {
    *(byte *)(param_2 + 0xc) = *(byte *)(param_2 + 0xc) | 0x20;
  }
  else if (uVar11 == 3) {
    *(byte *)(param_2 + 0xc) = *(byte *)(param_2 + 0xc) | 0x40;
  }
  else if (uVar11 == 1) {
    *(byte *)(param_2 + 0xc) = *(byte *)(param_2 + 0xc) | 0x10;
  }
  *(byte *)(param_2 + 0x73) = (byte)puVar17[4] & 3;
  uVar11 = puVar17[2];
  if ((uVar11 & 0x800000) != 0) {
    *(undefined1 *)(param_2 + 0x74) = 1;
    uVar11 = puVar17[2];
  }
  if ((uVar11 & 0x8000000) != 0) {
    *(byte *)(param_2 + 0xc) = *(byte *)(param_2 + 0xc) | 8;
    uVar11 = puVar17[2];
  }
  if ((uVar11 & 0x10000000) != 0) {
    *(byte *)(param_2 + 0xc) = *(byte *)(param_2 + 0xc) | 4;
    uVar11 = puVar17[2];
  }
  if ((uVar11 & 0x20000000) == 0) {
    iVar5 = *(int *)(param_2 + 0x10);
    *(byte *)(param_2 + 0xc) = *(byte *)(param_2 + 0xc) | 2;
  }
  bVar26 = (puVar17[3] & 0x40000) != 0;
  if (bVar26) {
    *(byte *)(iVar5 + 1) = *(byte *)(iVar5 + 1) | 0x10;
  }
  if (bVar26) {
    iVar5 = *(int *)(param_2 + 0x10);
  }
  if ((puVar17[2] & 0x40000000) == 0) {
    *(byte *)(iVar5 + 1) = *(byte *)(iVar5 + 1) | 0x80;
    iVar5 = *(int *)(param_2 + 0x10);
  }
  *(byte *)(iVar5 + 1) = *(byte *)(iVar5 + 1) & 0xbf;
  *(byte *)(*(int *)(param_2 + 0x10) + 1) = *(byte *)(*(int *)(param_2 + 0x10) + 1) & 0xf7;
  if ((puVar17[1] & 0x4000000) == 0) {
    uVar11 = 0;
  }
  else {
    uVar11 = 2;
  }
  *(byte *)(*(int *)(param_2 + 0x10) + 1) =
       *(byte *)(*(int *)(param_2 + 0x10) + 1) & 0xf9 |
       (byte)((uVar11 | (puVar17[1] << 6) >> 0x1f) << 1);
  if ((puVar17[1] & 0x8000000) != 0) {
    *(byte *)(*(int *)(param_2 + 0x10) + 1) = *(byte *)(*(int *)(param_2 + 0x10) + 1) | 1;
  }
  **(byte **)(param_2 + 0x10) =
       **(byte **)(param_2 + 0x10) & 0x7f | (*(char *)(param_2 + 0x52) != '\x0f') << 7;
  *(byte *)(*(int *)(param_2 + 0x10) + 2) = *(byte *)(*(int *)(param_2 + 0x10) + 2) & 0xfe;
  *(int *)(param_3 + 0xcc) = *(int *)(param_3 + 0xcc) + iVar18;
  *(uint *)(param_3 + 100) = (uint)*(ushort *)(param_2 + 0x48);
  *(int *)(param_2 + 0x38) = param_3;
  uVar8 = *(undefined4 *)(param_3 + 0xcc);
  *(undefined4 *)(param_2 + 0x3c) = uVar8;
  if (*(char *)(param_1 + 0xa7d07f) != '\0') {
    if (puVar20 != (uint *)0x0) {
      hex_dump("rxd_group2",puVar20,8);
      uVar8 = *(undefined4 *)(param_2 + 0x3c);
    }
    hex_dump("rx_data",uVar8,*(undefined2 *)(param_2 + 0x48));
  }
  *(undefined4 *)(param_2 + 0x88) = 0;
  if ((*(uint *)(param_2 + 0x44) & 0x40000) == 0) {
    puVar16 = *(ushort **)(param_2 + 0x3c);
    *(ushort **)(param_2 + 0x1c) = puVar16;
    uVar2 = *puVar16;
    uVar3 = puVar16[0xb];
    uVar11 = uVar2 & 0xff;
    *(ushort *)(param_2 + 0x20) = puVar16[1];
    if ((uVar2 & 4) == 0) {
      *(byte *)(param_2 + 0x22) = (byte)uVar3 & 0xf;
      *(ushort *)(param_2 + 0x24) = uVar3 >> 4;
    }
    bVar26 = ((uint)uVar2 << 0x16) >> 0x1e == 3;
    *(ushort **)(param_2 + 0x28) = puVar16 + 2;
    puVar6 = puVar16 + 5;
    *(ushort **)(param_2 + 0x30) = puVar16 + 8;
    if (bVar26) {
      puVar16 = puVar16 + 0xc;
    }
    *(ushort **)(param_2 + 0x2c) = puVar6;
    if (bVar26) {
      *(ushort **)(param_2 + 0x34) = puVar16;
    }
  }
  else {
    if (puVar19 == (uint *)0x0) {
      return 0;
    }
    *(uint **)(param_2 + 0x1c) = puVar19;
    uVar12 = puVar19[2];
    uVar11 = (uint)(ushort)*puVar19;
    *(byte *)(param_2 + 0x22) = (byte)(ushort)uVar12 & 0xf;
    *(ushort *)(param_2 + 0x24) = (ushort)uVar12 >> 4;
    iVar5 = wdev_search_by_wcid(param_1,*(undefined2 *)(param_2 + 0x4e));
    if ((iVar5 == 0) &&
       (iVar5 = wdev_search_by_omac_idx(param_1,*(undefined1 *)(param_2 + 0x52)), iVar5 == 0)) {
      return 0;
    }
    uVar12 = (uVar11 << 0x16) >> 0x1e;
    if (uVar12 == 0) {
      uVar11 = uVar11 & 0xff;
      *(int *)(param_2 + 0x30) = iVar5 + 0x21;
      *(int *)(param_2 + 0x2c) = *(int *)(param_2 + 0x3c) + 6;
      *(int *)(param_2 + 0x28) = *(int *)(param_2 + 0x3c);
    }
    else if (uVar12 == 2) {
      uVar11 = uVar11 & 0xff;
      *(int *)(param_2 + 0x88) = iVar5 + 0x1b;
      *(int *)(param_2 + 0x28) = *(int *)(param_2 + 0x3c);
      *(int *)(param_2 + 0x30) = *(int *)(param_2 + 0x3c) + 6;
      *(int *)(param_2 + 0x2c) = iVar5 + 0x21;
    }
    else {
      iVar9 = *(int *)(param_2 + 0x3c);
      if (uVar12 == 1) {
        *(int *)(param_2 + 0x30) = iVar9;
        uVar11 = uVar11 & 0xff;
        *(ushort **)(param_2 + 0x88) = (ushort *)((int)puVar19 + 2);
        *(int *)(param_2 + 0x28) = iVar5 + 0x21;
        *(int *)(param_2 + 0x2c) = iVar9 + 6;
      }
      else {
        *(int *)(param_2 + 0x30) = iVar9;
        uVar11 = uVar11 & 0xff;
        *(int *)(param_2 + 0x28) = iVar5 + 0x1b;
        *(ushort **)(param_2 + 0x2c) = (ushort *)((int)puVar19 + 2);
        *(int *)(param_2 + 0x34) = iVar9 + 6;
      }
    }
  }
  if ((((uVar11 & 0xf0) == 0xb0) && ((puVar17[1] & 0x1f0000) != 0)) &&
     ((puVar17[1] & 0x1800000) == 0)) {
    *(byte *)(*(int *)(param_2 + 0x10) + 2) = *(byte *)(*(int *)(param_2 + 0x10) + 2) | 1;
  }
  if (puVar4 != (uint *)0x0) {
    uVar11 = puVar4[1] & 0xffff;
    if (uVar11 == 0) {
      uVar12 = *puVar4;
      uVar11 = 0;
    }
    else {
      uVar12 = *puVar4;
    }
    *(uint *)(param_2 + 0x78) = uVar12;
    *(uint *)(param_2 + 0x7c) = uVar11;
  }
  if ("Get_RBIST_IQ_Data_Proc"[param_1 + 0x14] == '\0') {
    if ((puVar17[1] & 0x8000) != 0) {
      uVar11 = puVar21[6] & 0xff;
      *(char *)(param_2 + 0x82) = (char)puVar21[6];
      *(char *)(param_2 + 0x83) = (char)(puVar21[6] >> 8);
      *(char *)(param_2 + 0x84) = (char)(puVar21[6] >> 0x10);
      *(char *)(param_2 + 0x85) = (char)(puVar21[6] >> 0x18);
      goto LAB_0019f2f4;
    }
  }
  else {
    if ("Get_RBIST_IQ_Data_Proc"[param_1 + 0x14] != '\x01') {
      *(undefined1 *)(param_2 + 0x82) = 0;
      uVar11 = 0;
      *(undefined1 *)(param_2 + 0x83) = 0;
      *(undefined1 *)(param_2 + 0x84) = 0;
      *(undefined1 *)(param_2 + 0x85) = 0;
      goto LAB_0019f2f4;
    }
    if ((puVar17[1] & 0x2000) != 0) {
      uVar11 = local_30[1] & 0xff;
      *(char *)(param_2 + 0x82) = (char)local_30[1];
      *(char *)(param_2 + 0x83) = (char)(local_30[1] >> 8);
      *(char *)(param_2 + 0x84) = (char)(local_30[1] >> 0x10);
      *(char *)(param_2 + 0x85) = (char)(local_30[1] >> 0x18);
      goto LAB_0019f2f4;
    }
  }
  uVar11 = (uint)*(byte *)(param_2 + 0x82);
LAB_0019f2f4:
  pbVar24 = (byte *)(param_2 + 0x82);
  puVar7 = (undefined1 *)(param_2 + 0x57);
  iVar5 = 0;
  while( true ) {
    iVar5 = iVar5 + 1;
    if (uVar11 == 0xff) {
      uVar14 = 0x81;
    }
    else {
      uVar14 = (undefined1)(((uVar11 - 0xdc) - ((int)(uVar11 - 0xdc) >> 0x1f)) * 0x800000 >> 0x18);
    }
    puVar7 = puVar7 + 1;
    *puVar7 = uVar14;
    if (iVar5 == 4) break;
    pbVar24 = pbVar24 + 1;
    uVar11 = (uint)*pbVar24;
  }
  uVar11 = puVar17[1];
  if ((uVar11 & 0x2000) != 0) {
    *(uint *)(param_1 + 0x285a20) = *local_30;
    uVar11 = puVar17[1];
  }
  if ((uVar11 & 0x8000) != 0) {
    *(uint *)(param_1 + 0x285a24) = *puVar21;
    uVar11 = puVar17[1];
  }
  if (((uVar11 & 0xa000) == 0xa000) && (*(char *)(param_1 + 0xa1908) != '\0')) {
    uVar12 = *puVar21;
    uVar22 = (uVar12 << 0x11) >> 0x1e;
    uVar23 = (uVar12 << 0x18) >> 0x1c;
    uVar11 = *local_30;
    if (uVar23 < 8 && 1 < uVar22) {
      if (3 < DebugLevel) {
        printk("[mode(0x%x)]Invalid gi(%d)!\n",uVar23,uVar22);
      }
    }
    else if (uVar23 < 0xc && 2 < uVar22) {
      if (3 < DebugLevel) {
        printk("[mode(0x%x)]Invalid gi(%d)!\n",uVar23,3);
      }
    }
    else {
      if (3 < DebugLevel) {
        printk("[mode(0x%x)]vlid band(%d)!\n",uVar23,uVar22);
      }
      uVar13 = (uint)*(byte *)(param_2 + 0x4c);
      if (uVar13 < 2) {
        uVar12 = (uVar12 << 0x15) >> 0x1d;
        if (uVar12 < 3) {
          iVar5 = param_1 + uVar13 * 0x1df0;
          *(int *)(iVar5 + 0x9dd18) = *(int *)(iVar5 + 0x9dd18) + 1;
          bVar15 = 0;
          if ((*(int *)(param_2 + 0x1c) != 0) &&
             (bVar1 = *(byte *)(*(int *)(param_2 + 0x1c) + 1), bVar15 = bVar1 & 8, (bVar1 & 8) != 0)
             ) {
            bVar15 = 1;
            *(int *)(iVar5 + 0x9dd1c) = *(int *)(iVar5 + 0x9dd1c) + 1;
          }
          uVar25 = (uVar11 << 0x16) >> 0x1d;
          switch(uVar23) {
          case 0:
            if ((uVar11 & 7) == 7) {
              if (2 < DebugLevel) {
                printk("[CCK]Invalid rate idx(%d)!\n");
              }
            }
            else if ((uVar11 & 4) == 0) {
              iVar5 = param_1 + ((uVar11 & 3) + uVar12 * 0x13f + uVar13 * 0x77c) * 4;
              *(int *)(iVar5 + 0x9dd20) = *(int *)(iVar5 + 0x9dd20) + 1;
              if (bVar15 != 0) {
                param_1 = param_1 + (uVar13 * 0x77c + (uVar11 & 3) + 3 + uVar12 * 0x13f) * 4;
                *(int *)(param_1 + 0x9ec14) = *(int *)(param_1 + 0x9ec14) + 1;
              }
            }
            else {
              param_1 = param_1 + (uVar13 * 0x77c + uVar12 * 0x13f + (uVar11 & 3) + 3) * 4;
              *(int *)(param_1 + 0x9dd20) = *(int *)(param_1 + 0x9dd20) + 1;
              if (bVar15 != 0) {
                *(int *)(param_1 + 0x9ec14) = *(int *)(param_1 + 0x9ec14) + 1;
              }
            }
            break;
          case 1:
            uVar11 = (uVar11 & 0xf) - 8 & 0xff;
            if (uVar11 < 8) {
              uVar11 = (uint)(byte)(&DAT_0029da70)[uVar11];
              if (7 < uVar11) {
                if (DebugLevel < 3) {
                  return iVar18;
                }
                printk("[OFDM]Invalid rate idx(%d)!\n");
                return iVar18;
              }
            }
            else {
              uVar11 = 0;
            }
            param_1 = param_1 + (uVar13 * 0x77c + uVar12 * 0x13f + uVar11) * 4;
            *(int *)(param_1 + 0x9dd3c) = *(int *)(param_1 + 0x9dd3c) + 1;
            if (bVar15 != 0) {
              *(int *)(param_1 + 0x9ec30) = *(int *)(param_1 + 0x9ec30) + 1;
            }
            break;
          case 2:
          case 3:
            if ((uVar11 & 0x3f) < 2) {
              param_1 = param_1 + (uVar13 * 0x77c + uVar12 * 0x13f + (uVar11 & 0x3f) + uVar22 * 0x20
                                  ) * 4;
              *(int *)(param_1 + 0x9dd5c) = *(int *)(param_1 + 0x9dd5c) + 1;
              if (bVar15 != 0) {
                *(int *)(param_1 + 0x9ec50) = *(int *)(param_1 + 0x9ec50) + 1;
              }
            }
            else if (2 < DebugLevel) {
              printk("[HT]Invalid rate idx(%d)!\n");
            }
            break;
          case 4:
            uVar11 = uVar11 & 0xf;
            bVar27 = 2 < uVar25;
            bVar26 = uVar25 == 3;
            if (uVar25 < 4) {
              bVar27 = 10 < uVar11;
              bVar26 = uVar11 == 0xb;
            }
            if (bVar27 && !bVar26) {
              if (2 < DebugLevel) {
                printk("[VHT]Invalid rate idx(%d)!\n");
              }
            }
            else {
              param_1 = param_1 + (uVar13 * 0x77c +
                                  uVar12 * 0x13f + uVar11 + uVar22 * 0x30 + uVar25 * 0xc) * 4;
              *(int *)(param_1 + 0x9de5c) = *(int *)(param_1 + 0x9de5c) + 1;
              if (bVar15 != 0) {
                *(int *)(param_1 + 0x9ed50) = *(int *)(param_1 + 0x9ed50) + 1;
              }
            }
            break;
          default:
            if (2 < DebugLevel) {
              printk("Unknown Mode(%x)!\n",uVar23);
            }
            break;
          case 8:
          case 9:
          case 10:
          case 0xb:
            uVar11 = uVar11 & 0xf;
            bVar27 = 2 < uVar25;
            bVar26 = uVar25 == 3;
            if (uVar25 < 4) {
              bVar27 = 10 < uVar11;
              bVar26 = uVar11 == 0xb;
            }
            if (bVar27 && !bVar26) {
              if (2 < DebugLevel) {
                printk("[HE]Invalid rate idx(%d)!\n",uVar11);
              }
            }
            else {
              param_1 = param_1 + (uVar13 * 0x77c +
                                  uVar12 * 0x13f + uVar11 + uVar22 * 0x30 + uVar25 * 0xc) * 4;
              *(int *)(param_1 + 0x9dfdc) = *(int *)(param_1 + 0x9dfdc) + 1;
              if (bVar15 != 0) {
                *(int *)(param_1 + 0x9eed0) = *(int *)(param_1 + 0x9eed0) + 1;
              }
            }
          }
        }
        else if (1 < DebugLevel) {
          printk("Invalid BW(%d)!\n",uVar12);
        }
      }
      else if (0 < DebugLevel) {
        printk("Invalid band(%d)!\n",uVar13);
      }
    }
  }
  return iVar18;
}

