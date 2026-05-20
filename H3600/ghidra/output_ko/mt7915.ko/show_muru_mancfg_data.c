// module: mt7915.ko
// function: show_muru_mancfg_data @ 0x181a58
// size: 2368 bytes
//

void show_muru_mancfg_data(int param_1,int param_2)

{
  bool bVar1;
  char cVar2;
  char *__s;
  size_t __n;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint local_48;
  undefined1 auStack_41 [29];
  
  if (param_2 == 0) {
    return;
  }
  cVar2 = delimitcnt(param_2,&_LC251);
  if (1 < (byte)(cVar2 + 1U)) {
    if (DebugLevel < 0) {
      return;
    }
    printk("Num of Input Parameters Wrong\n");
    return;
  }
  __s = (char *)rstrtok(param_2,&_LC251);
  if (__s == (char *)0x0) {
    if (DebugLevel < 1) {
      return;
    }
    bVar1 = false;
  }
  else {
    bVar1 = false;
    do {
      __n = strlen(__s);
      memcpy(auStack_41,__s,__n);
      iVar3 = memcmp(auStack_41,&_LC487,3);
      if (iVar3 == 0) {
        bVar1 = true;
      }
      __s = (char *)rstrtok(0,&_LC251);
    } while (__s != (char *)0x0);
    if (DebugLevel < 1) goto LAB_00181b28;
  }
  printk("_rMuru_ManCfg_Data\n");
LAB_00181b28:
  if (bVar1) {
    uVar5 = *(uint *)(param_1 + 0x795a30);
    cVar2 = *(char *)(param_1 + 0x795a34);
    if (0xdfffffff < uVar5) {
      FUN_0017f59c(param_1);
    }
    if (cVar2 == '\0') {
      if (0 < DebugLevel) {
        printk("|-rMuruExtCmdManCfgInf (0x%08X)\n",uVar5);
      }
      iVar3 = 0;
      do {
        uVar5 = uVar5 + iVar3 * 0x210;
        if (0 < DebugLevel) {
          printk("| |-rMuruExtCmdManCfgInf[%d] (0x%08X)\n",iVar3,uVar5);
          if (DebugLevel < 1) {
LAB_00181fa8:
            if (DebugLevel < 1) {
LAB_00182054:
              if (DebugLevel < 1) {
LAB_00182114:
                if (DebugLevel < 1) {
LAB_00182220:
                  if (DebugLevel < 1) {
LAB_001822ec:
                    if (0 < DebugLevel) {
                      uVar4 = FUN_00174528(param_1,uVar5 + 300);
                      printk("| |-|-|-(0x%08X) u2UlLength = %d\n",uVar5 + 300,uVar4);
                      if (0 < DebugLevel) {
                        uVar4 = FUN_00174570(param_1,uVar5 + 0x12e);
                        printk("| |-|-|-(0x%08X) u1TfPad = %d\n",uVar5 + 0x12e,uVar4);
LAB_0018234c:
                        if (0 < DebugLevel) {
                          uVar4 = FUN_00174570(param_1,uVar5 + 0x20c);
                          printk("| |-|-|-(0x%08X) u1BaType = %d\n",uVar5 + 0x20c,uVar4);
                        }
                      }
                    }
                  }
                  else {
                    uVar4 = FUN_00174528(param_1,uVar5 + 0x126);
                    printk("| |-|-|-(0x%08X) u2TrigCnt = %d\n",uVar5 + 0x126,uVar4);
                    if (0 < DebugLevel) {
                      uVar4 = FUN_00174528(param_1,uVar5 + 0x128);
                      printk("| |-|-|-(0x%08X) u2TrigIntv = %d\n",uVar5 + 0x128,uVar4);
LAB_00182284:
                      if (DebugLevel < 1) goto LAB_0018234c;
                      uVar4 = FUN_00174570(param_1,uVar5 + 0x12a);
                      printk("| |-|-|-(0x%08X) u1UlBw = %d\n",uVar5 + 0x12a,uVar4);
                      if (0 < DebugLevel) {
                        uVar4 = FUN_00174570(param_1,uVar5 + 299);
                        printk("| |-|-|-(0x%08X) u1UlGiLtf = %d\n",uVar5 + 299,uVar4);
                        goto LAB_001822ec;
                      }
                    }
                  }
                }
                else {
                  uVar4 = FUN_00174570(param_1,uVar5 + 0x17);
                  printk("| |-|-|-(0x%08X) u1SigBMcs = %d\n",uVar5 + 0x17,uVar4);
                  if (0 < DebugLevel) {
                    uVar4 = FUN_00174570(param_1,uVar5 + 0x18);
                    printk("| |-|-|-(0x%08X) u1SigBDcm = %d\n",uVar5 + 0x18,uVar4);
LAB_00182174:
                    if (DebugLevel < 1) goto LAB_00182220;
                    uVar4 = FUN_00174570(param_1,uVar5 + 0x19);
                    printk("| |-|-|-(0x%08X) u1SigBCmprs = %d\n",uVar5 + 0x19,uVar4);
                    if (0 < DebugLevel) {
                      iVar7 = uVar5 + 0x124;
                      printk("| |-|-(0x%08X) rCfgUl\n",iVar7);
                      if (DebugLevel < 1) goto LAB_00182284;
                      uVar4 = FUN_00174570(param_1,iVar7);
                      printk("| |-|-|-(0x%08X) u1UserCnt = %d\n",iVar7,uVar4);
                      if (0 < DebugLevel) {
                        uVar4 = FUN_00174570(param_1,uVar5 + 0x125);
                        printk("| |-|-|-(0x%08X) u1TrigType = %d\n",uVar5 + 0x125,uVar4);
                        goto LAB_00182220;
                      }
                    }
                  }
                }
              }
              else {
                uVar4 = FUN_00174570(param_1,uVar5 + 0x13);
                printk("| |-|-|-(0x%08X) u1TxMode = %d\n",uVar5 + 0x13,uVar4);
                if (0 < DebugLevel) {
                  uVar4 = FUN_00174570(param_1,uVar5 + 0x14);
                  printk("| |-|-|-(0x%08X) u1Bw = %d\n",uVar5 + 0x14,uVar4);
LAB_001820b4:
                  if (DebugLevel < 1) goto LAB_00182174;
                  uVar4 = FUN_00174570(param_1,uVar5 + 0x15);
                  printk("| |-|-|-(0x%08X) u1GI = %d\n",uVar5 + 0x15,uVar4);
                  if (0 < DebugLevel) {
                    uVar4 = FUN_00174570(param_1,uVar5 + 0x16);
                    printk("| |-|-|-(0x%08X) u1Ltf = %d\n",uVar5 + 0x16,uVar4);
                    goto LAB_00182114;
                  }
                }
              }
            }
            else {
              uVar4 = FUN_00174570(param_1,uVar5 + 0xe);
              printk("| |-|-|-(0x%08X) u1Band = %d\n",uVar5 + 0xe,uVar4);
              if (0 < DebugLevel) {
                uVar4 = FUN_00174570(param_1,uVar5 + 0xf);
                printk("| |-|-|-(0x%08X) u1WmmSet = %d\n",uVar5 + 0xf,uVar4);
LAB_00182008:
                iVar7 = uVar5 + 0x12;
                if (DebugLevel < 1) goto LAB_001820b4;
                printk("| |-|-(0x%08X) rCfgDl\n",iVar7);
                if (0 < DebugLevel) {
                  uVar4 = FUN_00174570(param_1,iVar7);
                  printk("| |-|-|-(0x%08X) u1UserCnt = %d\n",iVar7,uVar4);
                  goto LAB_00182054;
                }
              }
            }
          }
          else {
            local_48 = 0;
            mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar5,&local_48);
            printk("| |-|-(0x%08X) u4ManCfgBmpCmm = %d\n",uVar5,local_48);
            if (0 < DebugLevel) {
              local_48 = 0;
              mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar5 + 4,&local_48);
              printk("| |-|-(0x%08X) u4ManCfgBmpDl = %d\n",uVar5 + 4,local_48);
              if (DebugLevel < 1) goto LAB_00181fa8;
              local_48 = 0;
              mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar5 + 8,&local_48);
              printk("| |-|-(0x%08X) u4ManCfgBmpUl = %d\n",uVar5 + 8,local_48);
              if (0 < DebugLevel) {
                iVar7 = uVar5 + 0xc;
                printk("| |-|-(0x%08X) rCfgCmm\n",iVar7);
                if (DebugLevel < 1) goto LAB_00182008;
                uVar4 = FUN_00174570(param_1,iVar7);
                printk("| |-|-|-(0x%08X) u1PpduFmt = %d\n",iVar7,uVar4);
                if (0 < DebugLevel) {
                  uVar4 = FUN_00174570(param_1,uVar5 + 0xd);
                  printk("| |-|-|-(0x%08X) u1SchType = %d\n",uVar5 + 0xd,uVar4);
                  goto LAB_00181fa8;
                }
              }
            }
          }
        }
        if (iVar3 == 1) break;
        iVar3 = 1;
      } while( true );
    }
    uVar5 = *(uint *)(param_1 + 0x795a38);
    uVar6 = (uint)*(byte *)(param_1 + 0x795a3c);
    if (0xdfffffff < uVar5) {
      FUN_0017f59c(param_1);
    }
    if (((uVar6 == 0) && (0 < DebugLevel)) &&
       (printk("|-rMuTxPktCnt (0x%08X)\n",uVar5), 0 < DebugLevel)) {
      local_48 = uVar6;
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar5,&local_48);
      printk("| |-(0x%08X) u4MuTxPktCnt[0] = %d\n",uVar5,local_48);
      if (0 < DebugLevel) {
        local_48 = uVar6;
        mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar5 + 4,&local_48);
        printk("| |-(0x%08X) u4MuTxPktCnt[1] = %d\n",uVar5 + 4,local_48);
      }
    }
    uVar5 = *(uint *)(param_1 + 0x795a40);
    uVar6 = (uint)*(byte *)(param_1 + 0x795a44);
    if (0xdfffffff < uVar5) {
      FUN_0017f59c(param_1);
    }
    if (((uVar6 == 0) && (0 < DebugLevel)) &&
       (printk("|-rMuTxPktCntDwn (0x%08X)\n",uVar5), 0 < DebugLevel)) {
      local_48 = uVar6;
      mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar5,&local_48);
      printk("| |-(0x%08X) u4MuTxPktCntDwn[0] = %d\n",uVar5,local_48);
      if (0 < DebugLevel) {
        local_48 = uVar6;
        mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar5 + 4,&local_48);
        printk("| |-(0x%08X) u4MuTxPktCntDwn[1] = %d\n",uVar5 + 4,local_48);
      }
    }
    uVar5 = *(uint *)(param_1 + 0x795a48);
    cVar2 = *(char *)(param_1 + 0x795a4c);
    if (0xdfffffff < uVar5) {
      FUN_0017f59c(param_1);
    }
    if (((cVar2 == '\0') && (0 < DebugLevel)) &&
       (printk("|-rAggPolicy (0x%08X)\n",uVar5), 0 < DebugLevel)) {
      uVar4 = FUN_00174570(param_1,uVar5);
      printk("| |-(0x%08X) u1AggPolicy = %d\n",uVar5,uVar4);
    }
    uVar5 = *(uint *)(param_1 + 0x795a50);
    cVar2 = *(char *)(param_1 + 0x795a54);
    if (0xdfffffff < uVar5) {
      FUN_0017f59c(param_1);
    }
    if (((cVar2 == '\0') && (0 < DebugLevel)) &&
       (printk("|-rDurationComp (0x%08X)\n",uVar5), 0 < DebugLevel)) {
      uVar4 = FUN_00174570(param_1,uVar5);
      printk("| |-(0x%08X) u1DurationComp = %d\n",uVar5,uVar4);
    }
  }
  return;
}

