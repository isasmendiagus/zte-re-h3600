// module: mt7915.ko
// function: MtCmdSendMsg @ 0x1a5860
// size: 4 bytes
//

undefined4 MtCmdSendMsg(int param_1,int param_2)

{
  byte bVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  bool bVar4;
  int *piVar5;
  short sVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  char cVar15;
  int iVar16;
  byte bVar17;
  int iVar18;
  int iVar19;
  uint auStack_70 [3];
  int iStack_64;
  uint uStack_60;
  int iStack_5c;
  int iStack_58;
  undefined1 *puStack_54;
  int iStack_50;
  int iStack_4c;
  int *piStack_48;
  int iStack_44;
  undefined4 uStack_40;
  int iStack_3c;
  uint uStack_38;
  int iStack_34;
  undefined1 auStack_2c [8];
  
  uStack_60 = ((uint)*(byte *)(param_2 + 4) << 0x1d) >> 0x1f;
  uVar14 = uStack_60;
  if ((*(uint *)(((uint)auStack_70 & 0xffffe000) + 4) & 0x1fff00) == 0) {
    uVar14 = 0;
  }
  if (uVar14 == 0) {
    uVar14 = *(uint *)(param_1 + 0xa39f84);
    if ((uVar14 & 0x21000100) == 0x1000000) {
      iVar7 = IsStopingPdma(param_1 + 0xa7bf04);
      if (iVar7 != 0) {
        if (-1 < DebugLevel) {
          uVar2 = *(undefined1 *)(param_2 + 2);
          uVar3 = *(undefined1 *)(param_2 + 3);
          auStack_70[0] = ErrRecoveryCurStat(param_1 + 0xa7bf04);
          printk("%s: SER Period,Command type = %x, Extension command type = %x  ErrRecoveryCtl=%d\n"
                 ,"AndesSendCmdMsg",uVar2,uVar3);
        }
        AndesForceFreeCmdMsg(param_2);
        WLAN_ERR_RecoverCheck(1,0);
        return 1;
      }
      WLAN_ERR_RecoverCheck(0,0);
      iVar8 = mdvt_block_command(param_1,param_2);
      if (iVar8 != 1) {
        iVar8 = param_1 + 0xa7849c;
        iVar18 = param_1 + 0xa784bc;
        iStack_34 = iVar7;
        AndesQueueTailCmdMsg(iVar18,param_2,1);
        piStack_48 = &DebugLevel;
        iStack_44 = param_1 + 0xa79000;
        puStack_54 = g_stWlanRadioStat;
        uStack_38 = 0xcccccccd;
        uStack_40 = 0;
        iStack_64 = param_1;
        iStack_3c = param_1 + 0xa70000;
        do {
          iVar7 = iStack_44;
          iStack_5c = hc_get_chip_ops(*(undefined4 *)(iStack_44 + 0x7a0));
          iStack_58 = hc_get_arch_ops(*(undefined4 *)(iVar7 + 0x7a0));
          while (iVar7 = AndesDequeueCmdMsg(iVar8,iVar18), iVar7 != 0) {
            if ((*(uint *)(param_1 + 0xa39f84) & 0x21000100) == 0x1000000) {
              uVar9 = *(undefined4 *)(iVar7 + 0x20);
              if (*(int *)(iVar7 + 0x18) != 4) {
                if ((*(byte *)(iVar7 + 4) & 4) != 0) {
                  iStack_50 = param_1 + 0xa784d0;
                  iStack_4c = iStack_64 + 0xa70000;
                  OS_SPIN_LOCK_IRQSAVE(iStack_50,auStack_2c);
                  iVar12 = iStack_4c + 0x8000;
                  iVar10 = iStack_50;
                  do {
                    iVar19 = *(int *)(iVar12 + 0x4d4);
                    bVar17 = *(byte *)(iVar12 + 0x49c);
                    iVar13 = iVar19 + -0x48;
LAB_001a5194:
                    do {
                      if (bVar17 < 0xf) {
                        bVar17 = bVar17 + 1;
                        *(byte *)(iVar12 + 0x49c) = bVar17;
                      }
                      else {
                        bVar17 = 1;
                        *(undefined1 *)(iVar12 + 0x49c) = 1;
                      }
                      if (param_1 + 0xa784d4 == iVar19) {
LAB_001a51e8:
                        OS_SPIN_UNLOCK_IRQRESTORE(iVar10,auStack_2c);
                        *(byte *)(iVar7 + 0x16) = bVar17;
                        goto LAB_001a50d0;
                      }
                      bVar1 = *(byte *)(iVar19 + -0x32);
                      iVar11 = iVar13;
                      while (bVar1 != bVar17) {
                        iVar16 = *(int *)(iVar11 + 0x48);
                        iVar11 = iVar16 + -0x48;
                        if (param_1 + 0xa784d4 == iVar16) goto LAB_001a51e8;
                        bVar1 = *(byte *)(iVar16 + -0x32);
                      }
                    } while (*piStack_48 < 0);
                    iStack_50 = iVar10;
                    iStack_4c = iVar12;
                    printk("command(seq: %d) is still running\n",bVar17);
                    iVar12 = iStack_4c;
                    if (*piStack_48 < 0) {
                      iVar19 = *(int *)(iStack_4c + 0x4d4);
                      bVar17 = *(byte *)(iStack_4c + 0x49c);
                      iVar13 = iVar19 + -0x48;
                      iVar10 = iStack_50;
                      goto LAB_001a5194;
                    }
                    iStack_4c = iStack_50;
                    iStack_50 = iVar12;
                    printk("command response nums = %d\n",0);
                    iVar12 = iStack_50;
                    iVar10 = iStack_4c;
                  } while( true );
                }
                *(byte *)(iVar7 + 0x16) = *(byte *)(iVar7 + 4) & 4;
LAB_001a50d0:
                if (*(code **)(iStack_58 + 0x194) != (code *)0x0) {
                  (**(code **)(iStack_58 + 0x194))(iStack_64,iVar7,uVar9);
                }
              }
              if (1 < *(byte *)(iVar7 + 0x17)) {
                uVar9 = skb_copy(uVar9,0x20);
                *(undefined4 *)(iVar7 + 0x24) = uVar9;
                *(int *)(puStack_54 + 8) = *(int *)(puStack_54 + 8) + 1;
              }
              if ((*(code **)(iStack_5c + 200) != (code *)0x0) &&
                 (iVar10 = (**(code **)(iStack_5c + 200))(iStack_64,iVar7), iVar12 = iStack_64,
                 iVar10 != 0)) {
                *(int *)(iStack_64 + 0xa86c5c) = *(int *)(iStack_64 + 0xa86c5c) + 1;
                WLAN_ERR_RecoverCheck(1,1);
                if (-1 < DebugLevel) {
                  printk("kick out msg fail\n");
                }
                if (iVar10 == 1) {
                  AndesForceFreeCmdMsg(iVar7);
                }
                AndesBhSchedule(iVar12);
                return uStack_40;
              }
              WLAN_ERR_RecoverCheck(0,1);
            }
            else if ((*(byte *)(iVar7 + 4) & 4) == 0) {
              AndesForceFreeCmdMsg();
            }
            else if (((1 < *(byte *)(iVar7 + 0x17)) && (*(int *)(iVar7 + 0x20) != 0)) &&
                    (*(int *)(iVar7 + 0x24) == 0)) {
              uVar9 = skb_copy(*(int *)(iVar7 + 0x20),0x20);
              *(undefined4 *)(iVar7 + 0x24) = uVar9;
              *(int *)(puStack_54 + 8) = *(int *)(puStack_54 + 8) + 1;
              RTMPFreeNdisPacket(iStack_64,*(undefined4 *)(iVar7 + 0x20));
              *(undefined4 *)(iVar7 + 0x20) = 0;
            }
          }
          AndesBhSchedule(iStack_64);
          if (uStack_60 == 0) {
            return uStack_40;
          }
          sVar6 = *(short *)(param_2 + 8);
          if (sVar6 == 0) {
            sVar6 = 3000;
          }
          uVar9 = RTMPMsecsToJiffies(sVar6);
          iVar12 = wait_for_completion_timeout(param_2 + 0x50,uVar9);
          iVar10 = OS_TEST_BIT(0,param_1 + 0xa784a0);
          iVar7 = iStack_3c;
          if (iVar10 == 0) {
            AndesFreeCmdMsg(param_2);
            return uStack_40;
          }
          if (iVar12 == 0) {
            uVar14 = (uint)*(ushort *)(iStack_3c + 0xd0b6);
            iVar12 = iStack_64 +
                     (uVar14 + (uint)((ulonglong)uStack_38 * (ulonglong)uVar14 >> 0x24) * -0x14 &
                     0xffff) * 8;
            *(undefined4 *)(iVar12 + 0xa7d0bc) = jiffies;
            *(undefined1 *)(iVar12 + 0xa7d0c0) = *(undefined1 *)(param_2 + 2);
            *(undefined1 *)(iVar12 + 0xa7d0c1) = *(undefined1 *)(param_2 + 3);
            *(undefined1 *)(iVar12 + 0xa7d0c2) = *(undefined1 *)(param_2 + 0x16);
            *(char *)(iVar12 + 0xa7d0c3) = (char)*(undefined4 *)(param_2 + 0x18);
            *(short *)(iStack_3c + 0xd0b6) = (short)(uVar14 + 1);
            bVar4 = false;
            if (*(ushort *)(iStack_3c + 0xd0b8) == 0 ||
                (uVar14 + 1 & 0xffff) <= (uint)*(ushort *)(iStack_3c + 0xd0b8)) {
              if (-1 < *piStack_48) {
                auStack_70[0] = 3000;
                if (*(ushort *)(param_2 + 8) != 0) {
                  auStack_70[0] = (uint)*(ushort *)(param_2 + 8);
                }
                printk("FWCmdTimeout: command (%x), ext_cmd_type (%x), seq(%d), timeout(%dms)\n",
                       *(undefined1 *)(param_2 + 2),*(undefined1 *)(param_2 + 3),
                       *(undefined1 *)(param_2 + 0x16));
                piVar5 = piStack_48;
                if (*piStack_48 < 0) {
LAB_001a570c:
                  piVar5 = piStack_48;
                  if (-1 < *piStack_48) {
                    uVar9 = AndesQueueLen(iVar8,param_1 + 0xa784d4);
                    printk("ackq qlen = %d\n",uVar9);
                    if (-1 < *piVar5) {
                      uVar9 = AndesQueueLen(iVar8,param_1 + 0xa784ec);
                      printk("tx_doneq.qlen = %d\n",uVar9);
LAB_001a5760:
                      if (-1 < *piStack_48) {
                        uVar9 = AndesQueueLen(iVar8,param_1 + 0xa784f8);
                        bVar4 = true;
                        printk("rx_done qlen = %d\n",uVar9);
                        goto LAB_001a5334;
                      }
                    }
                  }
                }
                else {
                  printk("pAd->Flags  = 0x%.8lx\n",*(undefined4 *)(param_1 + 0xa39f84));
                  if (-1 < *piVar5) {
                    uVar9 = AndesQueueLen(iVar8,iVar18);
                    printk("txq qlen = %d\n",uVar9);
                    if (*piVar5 < 0) goto LAB_001a5760;
                    uVar9 = AndesQueueLen(iVar8,param_1 + 0xa784c8);
                    printk("rxq qlen = %d\n",uVar9);
                    if (-1 < *piVar5) {
                      uVar9 = AndesQueueLen(iVar8,param_1 + 0xa784e0);
                      printk("kickq qlen = %d\n",uVar9);
                      goto LAB_001a570c;
                    }
                  }
                }
              }
              bVar4 = true;
            }
LAB_001a5334:
            if (*(int *)(param_2 + 0x18) == 7) {
              hif_mcu_unlink_ackq(param_2);
            }
            else if (*(int *)(param_2 + 0x18) == 8) {
              AndesUnlinkCmdMsg(param_2,param_1 + 0xa784d4);
            }
            AndesIncErrorCount(iVar8,1);
            if (*(char *)(param_2 + 0x17) != '\0') {
              *(char *)(param_2 + 0x17) = *(char *)(param_2 + 0x17) + -1;
            }
            if (bVar4) {
              if (((-1 < *piStack_48) &&
                  (printk("%s: msg state = %d\n","AndesSendCmdMsg",*(undefined4 *)(param_2 + 0x18)),
                  -1 < DebugLevel)) &&
                 (printk("msg->retry_times = %d\n",*(undefined1 *)(param_2 + 0x17)), -1 < DebugLevel
                 )) {
                printk("FwCmdTimeoutCnt  = %d\n",*(undefined2 *)(iVar7 + 0xd0b6));
              }
              if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + iStack_64 + 0xc) & 0xffff) == 0x7915) {
                iStack_34 = ChkExceptionType(iStack_64);
              }
              if (*(ushort *)(iVar7 + 0xd0b6) < 5) {
                if (iStack_34 == 0) {
                  if (0 < *piStack_48) {
                    printk("FW is normal\n");
                  }
                }
                else if (0 < *piStack_48) {
                  printk("FW is exception\n\n\n\n");
                }
                iVar12 = iStack_64;
                Show_FwDbgInfo_Proc(iStack_64,0);
                show_trinfo_proc(iVar12,0);
              }
              printk(&_LC39,0x367);
              dump_stack();
              if ((*(short *)(iVar7 + 0xd0b6) == *(short *)(iVar7 + 0xd0b8)) && (-1 < *piStack_48))
              {
                uStack_40 = 1;
                uVar9 = 3;
                printk("!!! FWCmdTimeout stop dumping... !!!\n");
                cVar15 = *(char *)(param_2 + 0x17);
                goto LAB_001a537c;
              }
            }
            cVar15 = *(char *)(param_2 + 0x17);
            uVar9 = 3;
            uStack_40 = 1;
          }
          else {
            iVar7 = *(int *)(param_2 + 0x18);
            if (iVar7 != 2) {
              if (iVar7 == 7) {
                hif_mcu_unlink_ackq(param_2);
              }
              else if (iVar7 == 8) {
                AndesUnlinkCmdMsg(param_2,param_1 + 0xa784d4);
              }
              uVar9 = 5;
              *(undefined1 *)(param_2 + 0x17) = 0;
LAB_001a53f4:
              if (*(char *)(param_2 + 3) == '%') {
                uStack_40 = *(undefined4 *)(param_2 + 0x60);
              }
              if (3 < DebugLevel) {
                printk("%s: msg state = %d\n","AndesSendCmdMsg",uVar9);
              }
              AndesQueueTailCmdMsg(param_1 + 0xa784ec,param_2,uVar9);
              return uStack_40;
            }
            cVar15 = *(char *)(param_2 + 0x17) + -1;
            *(char *)(param_2 + 0x17) = cVar15;
            uVar9 = 2;
          }
LAB_001a537c:
          if (cVar15 == '\0') goto LAB_001a53f4;
          complete(param_2 + 0x50);
          *(undefined4 *)(param_2 + 0x50) = 0;
          __init_waitqueue_head(param_2 + 0x54,"&x->wait",&_LANCHOR1);
          uVar9 = *(undefined4 *)(param_2 + 0x24);
          *(undefined4 *)(param_2 + 0x24) = 0;
          *(undefined4 *)(param_2 + 0x20) = uVar9;
          AndesQueueHeadCmdMsg(iVar18,param_2,4);
        } while( true );
      }
      if (2 < DebugLevel) {
        printk("%s: MDVT Block,Command type = %x, Extension command type = %x\n","AndesSendCmdMsg",
               *(undefined1 *)(param_2 + 2),*(undefined1 *)(param_2 + 3));
      }
    }
    else {
      if ((uVar14 & 0x1000000) == 0) {
        if (DebugLevel < 0) goto LAB_001a4e78;
        printk("%s: Could not send in band command due to diablefRTMP_ADAPTER_MCU_SEND_IN_BAND_CMD\n"
               ,"AndesSendCmdMsg");
      }
      else if ((uVar14 & 0x100) == 0) {
        if ((uVar14 & 0x20000000) != 0) {
          if (DebugLevel < 0) goto LAB_001a4e78;
          printk("%s: Could not send in band command due to fRTMP_ADAPTER_SUSPEND\n",
                 "AndesSendCmdMsg");
        }
      }
      else {
        if (DebugLevel < 0) goto LAB_001a4e78;
        printk("%s: Could not send in band command due to fRTMP_ADAPTER_NIC_NOT_EXIST\n",
               "AndesSendCmdMsg");
      }
      if (-1 < DebugLevel) {
        printk("%s: Command type = %x, Extension command type = %x\n","AndesSendCmdMsg",
               *(undefined1 *)(param_2 + 2),*(undefined1 *)(param_2 + 3));
      }
    }
  }
  else {
    if ((-1 < DebugLevel) &&
       (printk("BUG: %s is called from invalid context\n","AndesSendCmdMsg"), -1 < DebugLevel)) {
      printk("%s: Command type = %x, Extension command type = %x\n","AndesSendCmdMsg",
             *(undefined1 *)(param_2 + 2),*(undefined1 *)(param_2 + 3));
    }
    if (_LANCHOR1 == '\0') {
      dump_stack();
      _LANCHOR1 = '\x01';
    }
  }
LAB_001a4e78:
  AndesForceFreeCmdMsg(param_2);
  return 1;
}

