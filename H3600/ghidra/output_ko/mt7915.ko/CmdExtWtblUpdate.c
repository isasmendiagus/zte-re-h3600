// module: mt7915.ko
// function: CmdExtWtblUpdate @ 0x1c5988
// size: 2156 bytes
//

undefined4 CmdExtWtblUpdate(undefined4 param_1,int param_2,int param_3,ushort *param_4,uint param_5)

{
  int iVar1;
  undefined4 uVar2;
  char *pcVar3;
  uint uVar4;
  undefined1 uVar5;
  short sVar6;
  ushort *puVar7;
  ushort *puVar8;
  undefined1 uVar9;
  uint uVar10;
  uint uVar11;
  ushort *puVar12;
  code *pcVar13;
  uint local_4c;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  ushort *local_30;
  code *local_2c;
  
  uVar11 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  iVar1 = AndesAllocCmdMsg(param_1,0x15c);
  if (iVar1 == 0) {
    uVar2 = 3;
    goto LAB_001c5c50;
  }
  if (param_5 != 0) {
    if (param_4 == (ushort *)0x0) {
LAB_001c5a70:
      if (-1 < DebugLevel) {
        printk("%s, pWtblGenericTlv is NULL\n","CmdExtWtblUpdate");
      }
    }
    else {
      uVar10 = (uint)param_4[1];
      puVar8 = param_4;
      if (uVar10 != 0) {
        puVar12 = (ushort *)0x0;
        uVar4 = param_5;
        puVar7 = param_4;
        do {
          local_4c = uVar11 + 1;
          uVar4 = uVar4 - uVar10;
          puVar8 = (ushort *)((int)puVar7 + uVar10);
          uVar11 = local_4c & 0xffff;
          puVar12 = (ushort *)((uint)puVar12 | 1 << (*puVar7 & 0xff));
          if (uVar4 == 0) {
            local_4c = local_4c & 0xff;
            goto LAB_001c5a30;
          }
          if (puVar8 == (ushort *)0x0) goto LAB_001c5a70;
          uVar10 = (uint)puVar8[1];
          puVar7 = puVar8;
        } while (uVar10 != 0);
      }
      if (-1 < DebugLevel) {
        printk("%s, fail to handle T(%d), L(%d)\n","CmdExtWtblUpdate",*puVar8,0);
      }
    }
    AndesFreeCmdMsg(iVar1);
    if (DebugLevel < 0) {
      return 2;
    }
    printk("%s:(Ret = %d)\n","CmdExtWtblUpdate",2);
    return 2;
  }
  local_4c = param_5;
  uVar11 = 0;
  puVar12 = (ushort *)0x0;
LAB_001c5a30:
  if (3 < DebugLevel) {
    printk("%s, ucTLVNumber = %d\n","CmdExtWtblUpdate",uVar11);
  }
  if (param_3 == 1) {
    if (param_4 == (ushort *)0x0 && param_5 != 0) {
      return 1;
    }
LAB_001c5c98:
    sVar6 = 8;
    puVar8 = (ushort *)0x0;
  }
  else {
    if (param_3 == 2) {
      if (param_4 == (ushort *)0x0) {
        return 1;
      }
      goto LAB_001c5c98;
    }
    if (param_3 != 3) {
      if (param_3 != 4) {
        return 1;
      }
      if (param_4 != (ushort *)0x0 || param_5 != 0) {
        return 1;
      }
      goto LAB_001c5c98;
    }
    if (param_4 == (ushort *)0x0) {
      return 1;
    }
    sVar6 = (short)param_5 + 0x1c;
    puVar8 = param_4;
  }
  local_2c = CmdExtWtblUpdateCb;
  local_38 = CONCAT22(sVar6,(undefined2)local_38);
  local_3c = CONCAT13(0x32,CONCAT12(0xed,(undefined2)local_3c));
  pcVar13 = CmdExtWtblUpdateCb;
  local_38 = CONCAT31(local_38._1_3_,0xf);
  local_30 = puVar8;
  AndesInitCmdMsg(iVar1,local_3c,local_38,local_34,puVar8,CmdExtWtblUpdateCb);
  local_40 = CONCAT31(local_40._1_3_,(byte)((uint)(param_2 << 0x16) >> 0x1e));
  local_44 = CONCAT22((short)uVar11,CONCAT11((char)param_3,(char)param_2));
  AndesAppendCmdMsg(iVar1,&local_44,8);
  if ((3 < DebugLevel) &&
     (printk("%s, u2WlanIdx = %d, ucOperation = %d, u4EnableFeature = 0x%x\n","CmdExtWtblUpdate",
             param_2,param_3,puVar12), puVar8 = puVar12, 3 < DebugLevel)) {
    printk("%s, ucRemainingTLVNumber = %d, u2RemainingTLVBufLen = %d\n","CmdExtWtblUpdate",local_4c,
           param_5,puVar12);
    puVar8 = puVar12;
  }
  uVar4 = param_3 - 1U & 0xff;
  uVar10 = local_4c - 1 & 0xff;
  puVar12 = param_4;
  uVar11 = param_5;
  if (uVar10 != 0xff && param_5 != 0) {
    do {
      if (DebugLevel < 4) {
        switch(*puVar12) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 9:
        case 10:
        case 0xb:
        case 0xc:
        case 0xd:
        case 0xf:
        case 0x10:
        case 0x11:
          if (1 < uVar4) goto LAB_001c5c08;
          break;
        case 8:
          if (uVar4 < 2) goto LAB_001c5cc0;
        }
switchD_001c5bb0_caseD_e:
        puVar7 = puVar12 + 1;
        puVar12 = (ushort *)((int)puVar12 + (uint)*puVar7);
        uVar11 = uVar11 - *puVar7;
      }
      else {
        printk("%s, TLV(%d, %d)\n","CmdExtWtblUpdate",*puVar12,puVar12[1],puVar8,pcVar13);
        switch(*puVar12) {
        case 0:
          if (uVar4 < 2) {
            if (DebugLevel < 4) goto switchD_001c5bb0_caseD_e;
            puVar8 = (ushort *)(uint)(byte)puVar12[6];
            pcVar13 = (code *)(uint)*(byte *)((int)puVar12 + 0xd);
            printk("%s(WTBL_GENERIC), ucMUARIndex = %d, ucSkipTx = %d,ucCfAck = %d, ucQos = %d, ucQos = %d, ucAdm = %d, PartialAID = %d, aucPeerAddress(%02x:%02x:%02x:%02x:%02x:%02x)\n"
                   ,"CmdExtWtblUpdate",(char)puVar12[5],*(undefined1 *)((int)puVar12 + 0xb),puVar8,
                   pcVar13,(char)puVar12[7],*(undefined1 *)((int)puVar12 + 0xf),puVar12[8],
                   (char)puVar12[2],*(undefined1 *)((int)puVar12 + 5),(char)puVar12[3],
                   *(undefined1 *)((int)puVar12 + 7),(char)puVar12[4],
                   *(undefined1 *)((int)puVar12 + 9));
          }
          break;
        case 1:
          if (uVar4 < 2) {
            if (3 < DebugLevel) {
              uVar5 = (undefined1)puVar12[2];
              uVar9 = *(undefined1 *)((int)puVar12 + 5);
              pcVar3 = "%s(WTBL_RX), ucRcid = %d, ucRca1 = %d, ucRca2 = %d, ucRv = %d\n";
              puVar8 = (ushort *)(uint)(byte)puVar12[3];
              pcVar13 = (code *)(uint)*(byte *)((int)puVar12 + 7);
              goto LAB_001c60c0;
            }
            goto switchD_001c5bb0_caseD_e;
          }
          break;
        case 2:
          if (uVar4 < 2) {
            if (3 < DebugLevel) {
              uVar5 = (undefined1)puVar12[2];
              uVar9 = *(undefined1 *)((int)puVar12 + 5);
              pcVar3 = "%s(WTBL_HT), ucHt = %d, ucLdpc = %d, ucAf = %d, ucMm = %d\n";
              puVar8 = (ushort *)(uint)(byte)puVar12[3];
              pcVar13 = (code *)(uint)*(byte *)((int)puVar12 + 7);
              goto LAB_001c60c0;
            }
            goto switchD_001c5bb0_caseD_e;
          }
          break;
        case 3:
          if (uVar4 < 2) {
            if (3 < DebugLevel) {
              uVar5 = (undefined1)puVar12[2];
              uVar9 = *(undefined1 *)((int)puVar12 + 5);
              pcVar3 = "%s(WTBL_VHT), ucLdpcVht = %d, ucDynBw= %d, ucVht = %d, ucTxopPsCap = %d\n";
              puVar8 = (ushort *)(uint)(byte)puVar12[3];
              pcVar13 = (code *)(uint)*(byte *)((int)puVar12 + 7);
              goto LAB_001c60c0;
            }
            goto switchD_001c5bb0_caseD_e;
          }
          break;
        case 4:
          if (uVar4 < 2) {
            if (DebugLevel < 4) goto switchD_001c5bb0_caseD_e;
            printk("%s(WTBL_PEER_PS), ucDuIPsm = %d, ucIPsm = %d\n","CmdExtWtblUpdate",
                   (char)puVar12[2],*(undefined1 *)((int)puVar12 + 5),puVar8);
          }
          break;
        case 5:
          if (uVar4 < 2) {
            if (DebugLevel < 4) goto switchD_001c5bb0_caseD_e;
            printk("%s(WTBL_TX_PS), ucTxPs = %d\n","CmdExtWtblUpdate",(char)puVar12[2]);
          }
          break;
        case 6:
          if (uVar4 < 2) {
            if (DebugLevel < 4) goto switchD_001c5bb0_caseD_e;
            puVar8 = (ushort *)(uint)(byte)puVar12[3];
            printk("%s(WTBL_HDR_TRANS), ucTd = %d, ucFd = %d, ucDisRhtr =%d\n","CmdExtWtblUpdate",
                   (char)puVar12[2],*(undefined1 *)((int)puVar12 + 5),puVar8);
          }
          break;
        case 7:
          if (uVar4 < 2) {
            if (DebugLevel < 4) goto switchD_001c5bb0_caseD_e;
            uVar5 = (undefined1)puVar12[2];
            uVar9 = *(undefined1 *)((int)puVar12 + 5);
            pcVar3 = 
            "%s(WTBL_SECURITY_KEY), ucAddRemove = %d, ucRkv = %d, ucIkv =%d, ucAlgorithmId = %d, ucKeyId = %d, ucKeyLen = %d\n"
            ;
LAB_001c5ed8:
            puVar8 = (ushort *)(uint)(byte)puVar12[3];
            pcVar13 = (code *)(uint)*(byte *)((int)puVar12 + 7);
            printk(pcVar3,"CmdExtWtblUpdate",uVar5,uVar9,puVar8,pcVar13,(char)puVar12[4],
                   *(undefined1 *)((int)puVar12 + 9));
          }
          break;
        case 8:
          if (uVar4 < 2) {
LAB_001c5cc0:
            if (*(char *)((int)puVar12 + 5) == '\x02') {
              if (DebugLevel < 4) goto switchD_001c5bb0_caseD_e;
              puVar8 = (ushort *)(uint)(byte)puVar12[10];
              pcVar13 = (code *)(uint)*(byte *)((int)puVar12 + 0x15);
              printk("%s(WTBL_BA, Recipient), ucTid(%d), ucBaSessionType(%d), ucRstBaTid(%d), ucRstBaSel(%d), ucStartRstBaSb(%d), aucPeerAddress(%02x:%02x:%02x:%02x:%02x:%02x)\n"
                     ,"CmdExtWtblUpdate",(char)puVar12[2],2,puVar8,pcVar13,(char)puVar12[0xb],
                     (char)puVar12[7],*(undefined1 *)((int)puVar12 + 0xf),(char)puVar12[8],
                     *(undefined1 *)((int)puVar12 + 0x11),(char)puVar12[9],
                     *(undefined1 *)((int)puVar12 + 0x13));
            }
            else {
              if (DebugLevel < 4) goto switchD_001c5bb0_caseD_e;
              puVar8 = (ushort *)(uint)(byte)puVar12[5];
              pcVar13 = (code *)(uint)puVar12[6];
              printk("%s(WTBL_BA, Originator), ucTid(%d), u2Sn(%d), ucBaEn(%d), u2BaWinSize(%d), ucBaWinSizeIdx(%d)\n"
                     ,"CmdExtWtblUpdate",(char)puVar12[2],puVar12[4],puVar8,pcVar13,
                     *(undefined1 *)((int)puVar12 + 0xb));
            }
          }
          break;
        case 9:
          if (uVar4 < 2) {
            if (DebugLevel < 4) goto switchD_001c5bb0_caseD_e;
            printk("%s(WTBL_RDG), ucRdgBa = %d, ucR = %d\n","CmdExtWtblUpdate",(char)puVar12[2],
                   *(undefined1 *)((int)puVar12 + 5),puVar8);
          }
          break;
        case 10:
          if (uVar4 < 2) {
            if (DebugLevel < 4) goto switchD_001c5bb0_caseD_e;
            printk("%s(WTBL_PROTECTION), ucRts = %d\n","CmdExtWtblUpdate",(char)puVar12[2]);
          }
          break;
        case 0xb:
          if (uVar4 < 2) {
            if (DebugLevel < 4) goto switchD_001c5bb0_caseD_e;
            printk("%s(WTBL_CLEAR), ucClear = %x\n","CmdExtWtblUpdate",(char)puVar12[2]);
          }
          break;
        case 0xc:
          if (uVar4 < 2) {
            if (3 < DebugLevel) {
              uVar5 = (undefined1)puVar12[2];
              uVar9 = *(undefined1 *)((int)puVar12 + 5);
              pcVar3 = 
              "%s(WTBL_BF), ucTiBf = %d, ucTeBf = %d, ucTibfVh = %d, ucTebfVht = %d, ucGid = %d, ucPfmuIdx = %d\n"
              ;
              goto LAB_001c5ed8;
            }
            goto switchD_001c5bb0_caseD_e;
          }
          break;
        case 0xd:
          if (uVar4 < 2) {
            if (DebugLevel < 4) goto switchD_001c5bb0_caseD_e;
            printk("%s(WTBL_SMPS), ucSmPs = %d\n","CmdExtWtblUpdate",(char)puVar12[2]);
          }
          break;
        case 0xe:
          if (DebugLevel < 4) goto switchD_001c5bb0_caseD_e;
          uVar5 = (undefined1)puVar12[2];
          uVar9 = *(undefined1 *)((int)puVar12 + 5);
          pcVar3 = 
          "%s(WTBL_RAW_DATA_RW), ucWtblIdx = %d, ucWhichDW = %d, u4DwMask = 0x%x, u4DwValue = 0x%x\n"
          ;
          puVar8 = *(ushort **)(puVar12 + 4);
          pcVar13 = *(code **)(puVar12 + 6);
LAB_001c60c0:
          printk(pcVar3,"CmdExtWtblUpdate",uVar5,uVar9,puVar8,pcVar13);
          break;
        case 0xf:
          if (uVar4 < 2) {
            if (3 < DebugLevel) {
              uVar5 = (undefined1)puVar12[2];
              uVar9 = *(undefined1 *)((int)puVar12 + 5);
              pcVar3 = "%s(WTBL_PN), PN = %02x:%02x:%02x:%02x:%02x:%02x\n";
              goto LAB_001c5ed8;
            }
            goto switchD_001c5bb0_caseD_e;
          }
          break;
        case 0x10:
          if (uVar4 < 2) {
            if (DebugLevel < 4) goto switchD_001c5bb0_caseD_e;
            printk("%s(WTBL_BF), ucSpeIdx = %d\n","CmdExtWtblUpdate",(char)puVar12[2]);
          }
          break;
        case 0x11:
          if (uVar4 < 2) {
            if (DebugLevel < 4) goto switchD_001c5bb0_caseD_e;
            printk("%s(WTBL_SECURITY_KEY_V2), ucAddRemove = %d, ucEntryCount = %d\n",
                   "CmdExtWtblUpdate",(char)puVar12[2],*(undefined1 *)((int)puVar12 + 5),puVar8);
          }
          break;
        default:
          if (DebugLevel < 4) goto switchD_001c5bb0_caseD_e;
          printk("%s, Unknown WTBL TLV Tag(%d)\n","CmdExtWtblUpdate");
        }
LAB_001c5c08:
        puVar7 = puVar12 + 1;
        puVar12 = (ushort *)((int)puVar12 + (uint)*puVar7);
        uVar11 = uVar11 - *puVar7;
        if (3 < DebugLevel) {
          printk("%s in while loop, ucRemainingTLVNumber = %d, u2RemainingTLVBufLen = %d\n",
                 "CmdExtWtblUpdate",uVar10,uVar11,puVar8,pcVar13);
        }
      }
      uVar10 = uVar10 - 1 & 0xff;
    } while (uVar10 != 0xff && uVar11 != 0);
  }
  AndesAppendCmdMsg(iVar1,param_4,param_5);
  uVar2 = AndesSendCmdMsg(param_1,iVar1);
LAB_001c5c50:
  if (3 < DebugLevel) {
    printk("%s:(Ret = %d)\n","CmdExtWtblUpdate",uVar2);
    return uVar2;
  }
  return uVar2;
}

