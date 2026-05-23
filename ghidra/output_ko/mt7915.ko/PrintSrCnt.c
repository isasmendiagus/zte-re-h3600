// module: mt7915.ko
// function: PrintSrCnt @ 0x16d594
// size: 1076 bytes
//

void PrintSrCnt(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  int iVar8;
  int iVar9;
  short sVar10;
  short *psVar11;
  short *psVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  int local_5c;
  short local_40 [8];
  char *apcStack_30 [3];
  
  apcStack_30[0] = "RXRPT";
  apcStack_30[1] = "CMDRPT-TX";
  local_40[0] = 0;
  local_40[1] = 0;
  local_40[2] = 0;
  local_40[3] = 0;
  local_40[4] = 0;
  local_40[5] = 0;
  local_40[6] = 0;
  local_40[7] = 0;
  if (-1 < DebugLevel) {
    printk("%s: Band%d\n","PrintSrCnt",param_1);
  }
  psVar12 = local_40;
  psVar11 = local_40 + 6;
  iVar1 = param_2 + param_1 * 2;
  iVar9 = 0;
  sVar7 = 0;
  sVar6 = 0;
  sVar5 = 0;
  sVar10 = 0;
  iVar8 = 0;
  local_5c = param_2 + param_1 * 0x50;
  do {
    iVar3 = local_5c;
    do {
      iVar4 = iVar3 + 8;
      sVar10 = sVar10 + *(short *)(iVar3 + 0x10);
      sVar5 = sVar5 + *(short *)(iVar3 + 0x12);
      sVar6 = sVar6 + *(short *)(iVar3 + 0x14);
      sVar7 = sVar7 + *(short *)(iVar3 + 0x16);
      iVar3 = iVar4;
    } while (iVar4 != local_5c + 0x28);
    *psVar12 = sVar10;
    *(short *)((int)local_40 + iVar8 + 4) = sVar5;
    *psVar11 = sVar7;
    *(short *)((int)local_40 + iVar8 + 8) = sVar6;
    if (iVar9 == 0) {
      local_40[0] = *(short *)(iVar1 + 8) + *(short *)(iVar1 + 0xc) + (short)local_40._0_4_;
    }
    if (DebugLevel < 0) {
      if (iVar9 != 0) {
LAB_0016d694:
        if (-1 < DebugLevel) {
          printk("-------------------------------------------------------------------\n");
          goto LAB_0016d718;
        }
      }
    }
    else {
      uVar2 = (uint)*(ushort *)(local_5c + 0x18);
      uVar13 = (uint)*(ushort *)(local_5c + 0x20);
      uVar14 = (uint)*(ushort *)(local_5c + 0x28);
      uVar15 = (uint)*(ushort *)(local_5c + 0x30);
      printk("-------------------------------------------------------------------\nSR Rxrpt Source : %s\nTotal Rxrpt  = %4x,\n      NewRxv = %4x, OriRxvVht = %4x, OriRxvHe = %4x,\n      NewMac = %4x, OriMac    = %4x,\n"
             ,apcStack_30[iVar9],*psVar12,*(undefined2 *)(local_5c + 0x10),uVar2,uVar13,uVar14,
             uVar15);
      if (iVar9 != 0) goto LAB_0016d694;
      if (DebugLevel < 0) goto LAB_0016d69c;
      printk("      NoSr   = %4x, Fail      = %4x,\n-------------------------------------------------------------------\n"
             ,*(undefined2 *)(iVar1 + 8),*(undefined2 *)(iVar1 + 0xc),iVar1,uVar2,uVar13,uVar14,
             uVar15);
LAB_0016d718:
      if (-1 < DebugLevel) {
        printk("Total Period    Succ  = %4x, Fail = %4x,\n      NewRxv    Succ  = %4x, Fail = %4x,\n      OriRxvVht Succ  = %4x, Fail = %4x,\n      OriRxvHe  Succ  = %4x, Fail = %4x,\n      NewMac    Succ  = %4x, Fail = %4x,\n      OriMac    Succ  = %4x, Fail = %4x,\n-------------------------------------------------------------------\n"
               ,sVar5,sVar10 - sVar5,(uint)*(ushort *)(local_5c + 0x12),
               (uint)*(ushort *)(local_5c + 0x10) - (uint)*(ushort *)(local_5c + 0x12),
               (uint)*(ushort *)(local_5c + 0x1a),
               (uint)*(ushort *)(local_5c + 0x18) - (uint)*(ushort *)(local_5c + 0x1a),
               (uint)*(ushort *)(local_5c + 0x22),
               (uint)*(ushort *)(local_5c + 0x20) - (uint)*(ushort *)(local_5c + 0x22),
               (uint)*(ushort *)(local_5c + 0x2a),
               (uint)*(ushort *)(local_5c + 0x28) - (uint)*(ushort *)(local_5c + 0x2a),
               (uint)*(ushort *)(local_5c + 0x32),
               (uint)*(ushort *)(local_5c + 0x30) - (uint)*(ushort *)(local_5c + 0x32));
        if (-1 < DebugLevel) {
          printk("Total Gen Txc   Succ  = %4x, Fail = %4x,\n      NewRxv    Succ  = %4x, Fail = %4x,\n      OriRxvVht Succ  = %4x, Fail = %4x,\n      OriRxvHe  Succ  = %4x, Fail = %4x,\n      NewMac    Succ  = %4x, Fail = %4x,\n      OriMac    Succ  = %4x, Fail = %4x,\n-------------------------------------------------------------------\n"
                 ,sVar6,sVar5 - sVar6,(uint)*(ushort *)(local_5c + 0x14),
                 (uint)*(ushort *)(local_5c + 0x12) - (uint)*(ushort *)(local_5c + 0x14),
                 (uint)*(ushort *)(local_5c + 0x1c),
                 (uint)*(ushort *)(local_5c + 0x1a) - (uint)*(ushort *)(local_5c + 0x1c),
                 (uint)*(ushort *)(local_5c + 0x24),
                 (uint)*(ushort *)(local_5c + 0x22) - (uint)*(ushort *)(local_5c + 0x24),
                 (uint)*(ushort *)(local_5c + 0x2c),
                 (uint)*(ushort *)(local_5c + 0x2a) - (uint)*(ushort *)(local_5c + 0x2c),
                 (uint)*(ushort *)(local_5c + 0x34),
                 (uint)*(ushort *)(local_5c + 0x32) - (uint)*(ushort *)(local_5c + 0x34));
          if (-1 < DebugLevel) {
            printk("Total SR Tx     Succ  = %4x, Fail = %4x,\n      NewRxv    Succ  = %4x, Fail = %4x,\n      OriRxvVht Succ  = %4x, Fail = %4x,\n      OriRxvHe  Succ  = %4x, Fail = %4x,\n      NewMac    Succ  = %4x, Fail = %4x,\n      OriMac    Succ  = %4x, Fail = %4x,\n-------------------------------------------------------------------\n"
                   ,*psVar11,sVar6 - sVar7,(uint)*(ushort *)(local_5c + 0x16),
                   (uint)*(ushort *)(local_5c + 0x14) - (uint)*(ushort *)(local_5c + 0x16),
                   (uint)*(ushort *)(local_5c + 0x1e),
                   (uint)*(ushort *)(local_5c + 0x1c) - (uint)*(ushort *)(local_5c + 0x1e),
                   (uint)*(ushort *)(local_5c + 0x26),
                   (uint)*(ushort *)(local_5c + 0x24) - (uint)*(ushort *)(local_5c + 0x26),
                   (uint)*(ushort *)(local_5c + 0x2e),
                   (uint)*(ushort *)(local_5c + 0x2c) - (uint)*(ushort *)(local_5c + 0x2e),
                   (uint)*(ushort *)(local_5c + 0x36),
                   (uint)*(ushort *)(local_5c + 0x34) - (uint)*(ushort *)(local_5c + 0x36));
          }
        }
      }
    }
LAB_0016d69c:
    iVar9 = iVar9 + 1;
    psVar12 = psVar12 + 1;
    psVar11 = psVar11 + 1;
    if (iVar8 + 2 == 4) {
      return;
    }
    sVar10 = *psVar12;
    sVar7 = *psVar11;
    sVar5 = *(short *)((int)local_40 + iVar8 + 6);
    sVar6 = *(short *)((int)local_40 + iVar8 + 10);
    iVar8 = iVar8 + 2;
    local_5c = local_5c + 0x28;
  } while( true );
}

