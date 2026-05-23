// module: mt7915.ko
// function: show_scs_info @ 0x17f5b0
// size: 2204 bytes
//

void show_scs_info(int param_1)

{
  byte bVar1;
  uint *puVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint local_2c [2];
  
  uVar6 = *(uint *)(param_1 + 0x794cac);
  iVar7 = 0;
  bVar1 = *(byte *)(param_1 + 0x794cb0);
  puVar2 = (uint *)(param_1 + 0x794cac);
  do {
    uVar3 = (uint)bVar1;
    if (0xdfffffff < uVar6) {
      FUN_0017f59c(param_1);
    }
    if (uVar3 == 0) {
      if (0 < DebugLevel) {
        printk("********** Band %d  Information *********\n",iVar7);
        if (DebugLevel < 1) {
LAB_0017fad4:
          if (DebugLevel < 1) {
LAB_0017fb94:
            if (0 < DebugLevel) {
              uVar4 = FUN_00174528(param_1,uVar6 + 0x14);
              printk("| |-(0x%08X) u2OfdmFixedRssiBond = %d\n",uVar6 + 0x14,uVar4);
              if (0 < DebugLevel) {
                printk("| |-(0x%08X) u2IniAvgTput\n",uVar6 + 0x16);
              }
            }
          }
          else {
            uVar4 = FUN_00174528(param_1,uVar6 + 0xc);
            printk("| |-(0x%08X) u2CckPdBlkTh = %d\n",uVar6 + 0xc,uVar4);
            if (0 < DebugLevel) {
              uVar4 = FUN_00174528(param_1,uVar6 + 0xe);
              printk("| |-(0x%08X) u2OfdmPdBlkTh = %d\n",uVar6 + 0xe,uVar4);
LAB_0017fb34:
              if (0 < DebugLevel) {
                uVar4 = FUN_00174528(param_1,uVar6 + 0x10);
                printk("| |-(0x%08X) u2SCSMinRssiTolerance = %d\n",uVar6 + 0x10,uVar4);
                if (0 < DebugLevel) {
                  uVar4 = FUN_00174528(param_1,uVar6 + 0x12);
                  printk("| |-(0x%08X) u2CckFixedRssiBond = %d\n",uVar6 + 0x12,uVar4);
                  goto LAB_0017fb94;
                }
              }
            }
          }
        }
        else {
          printk("|-rscsband%d (0x%08X)\n",iVar7,uVar6);
          if (0 < DebugLevel) {
            uVar4 = FUN_00174570(param_1,uVar6 + 1);
            printk("| |-(0x%08X) u1SCSMinRssi = %d\n",uVar6 + 1,uVar4);
            if (DebugLevel < 1) goto LAB_0017fb34;
            local_2c[0] = uVar3;
            mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar6 + 4,local_2c);
            printk("| |-(0x%08X) u4OneSecTxByteCount = %d\n",uVar6 + 4,local_2c[0]);
            if (0 < DebugLevel) {
              local_2c[0] = uVar3;
              mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar6 + 8,local_2c);
              printk("| |-(0x%08X) u4OneSecRxByteCount = %d\n",uVar6 + 8,local_2c[0]);
              goto LAB_0017fad4;
            }
          }
        }
      }
      iVar9 = uVar6 + 0x16;
      iVar8 = 0;
      iVar5 = DebugLevel;
      do {
        if (0 < iVar5) {
          uVar4 = FUN_00174528(param_1,iVar9);
          printk("| | |-(0x%08X) u2IniAvgTput[%d] = %d\n",iVar9,iVar8,uVar4);
          iVar5 = DebugLevel;
        }
        iVar8 = iVar8 + 1;
        iVar9 = iVar9 + 2;
      } while (iVar8 != 4);
      iVar8 = uVar6 + 0x1e;
      if (0 < iVar5) {
        printk("| |-(0x%08X) u2LastTputDiff\n",iVar8);
        iVar5 = DebugLevel;
      }
      iVar9 = 0;
      do {
        if (0 < iVar5) {
          uVar4 = FUN_00174528(param_1,iVar8);
          printk("| | |-(0x%08X) u2LastTputDiff[%d] = %d\n",iVar8,iVar9,uVar4);
          iVar5 = DebugLevel;
        }
        iVar9 = iVar9 + 1;
        iVar8 = iVar8 + 2;
      } while (iVar9 != 4);
      iVar8 = uVar6 + 0x26;
      if (0 < iVar5) {
        printk("| |-(0x%08X) u2LastAvgTput\n",iVar8);
        iVar5 = DebugLevel;
      }
      iVar9 = 0;
      do {
        if (0 < iVar5) {
          uVar4 = FUN_00174528(param_1,iVar8);
          printk("| | |-(0x%08X) u2LastAvgTput[%d] = %d\n",iVar8,iVar9,uVar4);
          iVar5 = DebugLevel;
        }
        iVar9 = iVar9 + 1;
        iVar8 = iVar8 + 2;
      } while (iVar9 != 4);
      iVar8 = uVar6 + 0x2e;
      if (0 < iVar5) {
        printk("| |-(0x%08X) u2LastMaxTput\n",iVar8);
        iVar5 = DebugLevel;
      }
      iVar9 = 0;
      do {
        if (0 < iVar5) {
          uVar4 = FUN_00174528(param_1,iVar8);
          printk("| | |-(0x%08X) u2LastMaxTput[%d] = %d\n",iVar8,iVar9,uVar4);
          iVar5 = DebugLevel;
        }
        iVar9 = iVar9 + 1;
        iVar8 = iVar8 + 2;
      } while (iVar9 != 4);
      iVar8 = uVar6 + 0x36;
      if (0 < iVar5) {
        printk("| |-(0x%08X) u2LastMinTput\n",iVar8);
        iVar5 = DebugLevel;
      }
      iVar9 = 0;
      do {
        if (0 < iVar5) {
          uVar4 = FUN_00174528(param_1,iVar8);
          printk("| | |-(0x%08X) u2LastMinTput[%d] = %d\n",iVar8,iVar9,uVar4);
          iVar5 = DebugLevel;
        }
        iVar9 = iVar9 + 1;
        iVar8 = iVar8 + 2;
      } while (iVar9 != 4);
      if (0 < iVar5) {
        printk("| |-(0x%08X) u1LastTputIdx\n",uVar6 + 0x3e);
        iVar5 = DebugLevel;
      }
      iVar8 = 0;
      do {
        if (0 < iVar5) {
          iVar5 = iVar8 + uVar6 + 0x3e;
          uVar4 = FUN_00174570(param_1,iVar5);
          printk("| | |-(0x%08X) u1LastTputIdx[%d] = %d\n",iVar5,iVar8,uVar4);
          iVar5 = DebugLevel;
        }
        iVar8 = iVar8 + 1;
      } while (iVar8 != 4);
      if (0 < iVar5) {
        printk("| |-(0x%08X) fgLastTputDone\n",uVar6 + 0x42);
        iVar5 = DebugLevel;
      }
      iVar8 = 0;
      do {
        if (0 < iVar5) {
          iVar5 = uVar6 + 0x42 + iVar8;
          uVar4 = FUN_00174570(param_1,iVar5);
          printk("| | |-(0x%08X) fgLastTputDone[%d] = %d\n",iVar5,iVar8,uVar4);
          iVar5 = DebugLevel;
        }
        iVar8 = iVar8 + 1;
      } while (iVar8 != 4);
      iVar8 = uVar6 + 0x46;
      if (0 < iVar5) {
        printk("| |-(0x%08X) u2CurAvgTput\n",iVar8);
        iVar5 = DebugLevel;
      }
      iVar9 = 0;
      do {
        if (0 < iVar5) {
          uVar4 = FUN_00174528(param_1,iVar8);
          printk("| | |-(0x%08X) u2CurAvgTput[%d] = %d\n",iVar8,iVar9,uVar4);
          iVar5 = DebugLevel;
        }
        iVar9 = iVar9 + 1;
        iVar8 = iVar8 + 2;
      } while (iVar9 != 4);
      if (0 < iVar5) {
        printk("| |-(0x%08X) u1CurTputIdx\n",uVar6 + 0x4e);
        iVar5 = DebugLevel;
      }
      iVar8 = 0;
      do {
        if (0 < iVar5) {
          iVar5 = uVar6 + 0x4e + iVar8;
          uVar4 = FUN_00174570(param_1,iVar5);
          printk("| | |-(0x%08X) u1CurTputIdx[%d] = %d\n",iVar5,iVar8,uVar4);
          iVar5 = DebugLevel;
        }
        iVar8 = iVar8 + 1;
      } while (iVar8 != 4);
      if (0 < iVar5) {
        printk("| |-(0x%08X) u1TputPeriodScaleBit\n",uVar6 + 0x52);
        iVar5 = DebugLevel;
      }
      iVar8 = 0;
      do {
        if (0 < iVar5) {
          iVar5 = uVar6 + 0x52 + iVar8;
          uVar4 = FUN_00174570(param_1,iVar5);
          printk("| | |-(0x%08X) u1TputPeriodScaleBit[%d] = %d\n",iVar5,iVar8,uVar4);
          iVar5 = DebugLevel;
        }
        iVar8 = iVar8 + 1;
      } while (iVar8 != 4);
      if (0 < iVar5) {
        uVar4 = FUN_00174570(param_1,uVar6 + 0x56);
        printk("| |-(0x%08X) u1ChannelBusyTh = %d\n",uVar6 + 0x56,uVar4);
        if (DebugLevel < 1) {
LAB_0017fd5c:
          if (0 < DebugLevel) {
            local_2c[0] = 0;
            mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar6 + 0x60,local_2c);
            printk("| |-(0x%08X) u4MyTxAirtime = %d\n",uVar6 + 0x60,local_2c[0]);
            if (0 < DebugLevel) {
              local_2c[0] = 0;
              mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar6 + 100,local_2c);
              printk("| |-(0x%08X) u4MyRxAirtime = %d\n",uVar6 + 100,local_2c[0]);
LAB_0017fdec:
              if (0 < DebugLevel) {
                local_2c[0] = 0;
                mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar6 + 0x68);
                printk("| |-(0x%08X) u4OBSSAirtime = %d\n",uVar6 + 0x68,local_2c[0]);
              }
            }
          }
        }
        else {
          uVar4 = FUN_00174570(param_1,uVar6 + 0x57);
          printk("| |-(0x%08X) fgChBusy = %d\n",uVar6 + 0x57,uVar4);
          if (0 < DebugLevel) {
            uVar4 = FUN_00174570(param_1,uVar6 + 0x58);
            printk("| |-(0x%08X) u1MyTxRxTh = %d\n",uVar6 + 0x58,uVar4);
            if (DebugLevel < 1) goto LAB_0017fdec;
            uVar4 = FUN_00174570(param_1,uVar6 + 0x59);
            printk("| |-(0x%08X) fgPDreset = %d\n",uVar6 + 0x59,uVar4);
            if (0 < DebugLevel) {
              local_2c[0] = 0;
              mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar6 + 0x5c);
              printk("| |-(0x%08X) u4ChannelBusyTime = %d\n",uVar6 + 0x5c,local_2c[0]);
              goto LAB_0017fd5c;
            }
          }
        }
      }
    }
    if (iVar7 == 1) {
      return;
    }
    uVar6 = puVar2[2];
    iVar7 = 1;
    bVar1 = (byte)puVar2[3];
    puVar2 = puVar2 + 2;
  } while( true );
}

