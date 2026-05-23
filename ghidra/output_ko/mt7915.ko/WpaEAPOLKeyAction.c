// module: mt7915.ko
// function: WpaEAPOLKeyAction @ 0x12164c
// size: 1412 bytes
//

void WpaEAPOLKeyAction(int param_1,int param_2)

{
  byte bVar1;
  ushort uVar2;
  byte bVar3;
  undefined4 uVar4;
  int *piVar5;
  char *pcVar6;
  undefined1 uVar7;
  undefined1 uVar8;
  undefined4 uVar9;
  int iVar10;
  byte *pbVar11;
  int iVar12;
  undefined4 uVar13;
  bool bVar14;
  byte local_2a;
  byte bStack_29;
  
  bVar14 = (*(byte *)(param_2 + 1) & 3) != 3;
  iVar12 = *(int *)(param_2 + 0x92c);
  if (bVar14) {
    iVar10 = 0x20;
  }
  else {
    iVar10 = 0x26;
  }
  pbVar11 = (byte *)(param_2 + iVar10);
  if (bVar14) {
    iVar10 = 0x18;
  }
  else {
    iVar10 = 0x1e;
  }
  bVar3 = pbVar11[2];
  bVar1 = pbVar11[3];
  if (2 < DebugLevel) {
    printk("%s:Receive EAPoL-Key frame from %02x:%02x:%02x:%02x:%02x:%02x\n","WpaEAPOLKeyAction",
           *(undefined1 *)(param_2 + 10),*(undefined1 *)(param_2 + 0xb),
           *(undefined1 *)(param_2 + 0xc),*(undefined1 *)(param_2 + 0xd),
           *(undefined1 *)(param_2 + 0xe),*(undefined1 *)(param_2 + 0xf));
  }
  if ((iVar12 == 0) || (*(int *)(iVar12 + 0x14) != 2)) {
    uVar4 = MacTableLookup(param_1,param_2 + 10);
    uVar13 = 0x19df;
    uVar9 = 0;
  }
  else if (*(byte *)(iVar12 + 0x1a) < 0xf) {
    uVar4 = MacTableLookup(param_1,param_2 + 10);
    uVar13 = 0x19d7;
    uVar9 = 0xffffffff;
  }
  else {
    uVar4 = MacTableLookup(param_1,param_2 + 10);
    uVar13 = 0x19db;
    uVar9 = 0xfffffffb;
  }
  __ZTE_STA_Assoc_Process(param_1,0xb,0,uVar9,0,0,uVar4,"WpaEAPOLKeyAction",uVar13);
  if ((uint)((*(int *)(param_2 + 0x908) + -8) - iVar10) < CONCAT11(bVar3,bVar1) + 4) {
    if (DebugLevel < 0) {
      return;
    }
    uVar7 = *(undefined1 *)(param_2 + 10);
    uVar8 = *(undefined1 *)(param_2 + 0xb);
    pcVar6 = "The length of EAPoL packet is invalid from %02x:%02x:%02x:%02x:%02x:%02x\n";
    goto LAB_0012181c;
  }
  uVar2 = *(ushort *)(pbVar11 + 5);
  if (*pbVar11 - 1 < 2) {
    bVar3 = pbVar11[4];
    bVar14 = 0xfd < bVar3;
    if (bVar3 != 0xfe) {
      bVar14 = bVar3 != 2;
    }
    if (!bVar14 || (bVar3 == 0xfe || bVar3 == 3)) {
      if (((&DAT_0036790d)[param_1] == '\0') ||
         (iVar12 = lookup_rept_entry(param_1,param_2 + 4), iVar12 == 0)) {
        if (*(int *)(param_2 + 0x92c) == 0) {
          return;
        }
        iVar12 = *(int *)(*(int *)(param_2 + 0x92c) + 0x14);
        if (iVar12 == 1) {
          piVar5 = (int *)MacTableLookup(param_1,param_2 + 10);
LAB_00121a2c:
          if (piVar5 != (int *)0x0) {
            piVar5[0x156] = (uint)*(byte *)(piVar5[2] + 0x999);
            goto LAB_0012186c;
          }
        }
        else if ((iVar12 - 2U & 0xfffffffd) == 0) {
          piVar5 = (int *)MacTableLookup2(param_1,param_2 + 10);
          goto LAB_00121a2c;
        }
        if (DebugLevel < 0) {
          return;
        }
        uVar7 = *(undefined1 *)(param_2 + 10);
        uVar8 = *(undefined1 *)(param_2 + 0xb);
        pcVar6 = "MacTableLookup FAILE with A2 %02x:%02x:%02x:%02x:%02x:%02x\n";
        goto LAB_0012181c;
      }
      piVar5 = *(int **)(iVar12 + 0x4144);
      if (piVar5 == (int *)0x0) {
        return;
      }
      piVar5[0x156] = (uint)*(byte *)(*(int *)(iVar12 + 0x4140) + 0x999);
LAB_0012186c:
      if (*piVar5 == 0) {
        if (DebugLevel < 0) {
          return;
        }
        printk("%s:pEntry is none ,wcid = %d, A2=%02x:%02x:%02x:%02x:%02x:%02x\n",
               "WpaEAPOLKeyAction",(short)piVar5[0x38],*(undefined1 *)(param_2 + 10),
               *(undefined1 *)(param_2 + 0xb),*(undefined1 *)(param_2 + 0xc),
               *(undefined1 *)(param_2 + 0xd),*(undefined1 *)(param_2 + 0xe),
               *(undefined1 *)(param_2 + 0xf));
        return;
      }
      bStack_29 = (byte)(uVar2 >> 8);
      if ((piVar5[0xb1] & 0x10U) == 0) {
        if ((char)piVar5[0x100] == '\x01') {
          bVar3 = bStack_29 & 7;
          if ((uVar2 & 0x700) != 0) {
            bVar3 = 1;
          }
          if ((bStack_29 & 7) == 3) {
            bVar3 = 0;
          }
          else {
            bVar3 = bVar3 & 1;
          }
          if (bVar3 != 0) goto LAB_00121998;
        }
        if (((bStack_29 & 7) == 2) && ((piVar5[0xb1] & 0x1f0U) == 0)) {
          if (DebugLevel < 0) {
            return;
          }
          printk("Key descripter version not match peerKeyInfo.KeyDescVer=%d, PairwiseCipher=0x%x  from %02x:%02x:%02x:%02x:%02x:%02x\n"
                 ,bStack_29 & 7,piVar5[0xb1],*(undefined1 *)(param_2 + 10),
                 *(undefined1 *)(param_2 + 0xb),*(undefined1 *)(param_2 + 0xc),
                 *(undefined1 *)(param_2 + 0xd),*(undefined1 *)(param_2 + 0xe),
                 *(undefined1 *)(param_2 + 0xf));
          return;
        }
      }
      else {
        if ((bStack_29 & 7) != 1) {
          if (DebugLevel < 0) {
            return;
          }
          uVar7 = *(undefined1 *)(param_2 + 10);
          uVar8 = *(undefined1 *)(param_2 + 0xb);
          pcVar6 = "Key descripter version not match(TKIP) from %02x:%02x:%02x:%02x:%02x:%02x\n";
          goto LAB_0012181c;
        }
        if ((char)piVar5[0x100] == '\x01') {
LAB_00121998:
          if (-1 < DebugLevel) {
            printk("[PMF] Key descripter version not match(AES-128/NOT_DEFINED)\n");
          }
        }
      }
      if (piVar5[0x3f] != 2) {
        return;
      }
      if (*(byte *)(piVar5 + 0x145) < 7) {
        return;
      }
      local_2a = (byte)uVar2;
      if ((uVar2 & 0x8000) == 0) {
        if ((local_2a & 0xd) == 0xd) {
          if (-1 < DebugLevel) {
            printk("Received an Michael MIC Failure Report, active countermeasure\n");
          }
          HandleCounterMeasure(param_1,piVar5);
          return;
        }
        if ((uVar2 & 0xc) == 0) {
          local_2a = local_2a & 1;
        }
        else {
          local_2a = 0;
        }
        if (local_2a == 0) {
          return;
        }
        if ((uVar2 & 2) == 0) {
          if ((uVar2 & 0x800) == 0) {
            return;
          }
          if ((piVar5[0x5f] & 0x30000U) == 0) {
            iVar12 = 0x10;
          }
          else {
            iVar12 = 0x18;
          }
          if (CONCAT11(pbVar11[iVar12 + 0x51],pbVar11[iVar12 + 0x52]) != 0) {
            PeerPairMsg2Action();
            return;
          }
        }
        else if ((uVar2 & 0x800) == 0) {
          PeerGroupMsg2Action(param_1,piVar5,piVar5 + 0x5f,param_2);
          return;
        }
        PeerPairMsg4Action(param_1,piVar5,piVar5 + 0x5f,param_2);
        return;
      }
      if ((uVar2 & 0xe) == 0) {
        if ((uVar2 & 0x800) != 0) {
          if ((uVar2 & 1) == 0) {
            PeerPairMsg1Action();
            return;
          }
LAB_00121adc:
          PeerPairMsg3Action(param_1,piVar5,piVar5 + 0x5f,param_2);
          return;
        }
        if ((local_2a & 0xf) != 3) {
          return;
        }
      }
      else {
        if ((local_2a & 0xf) != 3) {
          return;
        }
        if ((uVar2 & 0x800) != 0) goto LAB_00121adc;
      }
      PeerGroupMsg1Action(param_1,piVar5,piVar5 + 0x5f,param_2);
      return;
    }
  }
  if (DebugLevel < 0) {
    return;
  }
  uVar7 = *(undefined1 *)(param_2 + 10);
  uVar8 = *(undefined1 *)(param_2 + 0xb);
  pcVar6 = "Key descripter does not match with WPA rule from %02x:%02x:%02x:%02x:%02x:%02x\n";
LAB_0012181c:
  printk(pcVar6,uVar7,uVar8,*(undefined1 *)(param_2 + 0xc),*(undefined1 *)(param_2 + 0xd),
         *(undefined1 *)(param_2 + 0xe),*(undefined1 *)(param_2 + 0xf));
  return;
}

