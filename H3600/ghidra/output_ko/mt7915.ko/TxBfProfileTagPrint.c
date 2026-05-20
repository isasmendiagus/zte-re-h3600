// module: mt7915.ko
// function: TxBfProfileTagPrint @ 0x86b68
// size: 596 bytes
//

void TxBfProfileTagPrint(int param_1,int param_2,byte *param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  
  uVar7 = *(undefined4 *)(param_3 + 4);
  uVar6 = *(undefined4 *)(param_3 + 8);
  uVar5 = *(undefined4 *)(param_3 + 0xc);
  *(undefined4 *)(param_1 + 0xa786c4) = *(undefined4 *)param_3;
  *(undefined4 *)(param_1 + 0xa786c8) = uVar7;
  *(undefined4 *)(param_1 + 0xa786cc) = uVar6;
  *(undefined4 *)(param_1 + 0xa786d0) = uVar5;
  iVar1 = DebugLevel;
  uVar5 = *(undefined4 *)(param_3 + 0x14);
  uVar6 = *(undefined4 *)(param_3 + 0x18);
  *(undefined4 *)(param_1 + 0xa786d4) = *(undefined4 *)(param_3 + 0x10);
  *(undefined4 *)(param_1 + 0xa786d8) = uVar5;
  *(undefined4 *)(param_1 + 0xa786dc) = uVar6;
  if (0 < iVar1) {
    uVar8 = param_3[3] & 7;
    uVar11 = (uint)(param_3[3] >> 3) | (param_3[4] & 1) << 5;
    uVar14 = (uint)param_3[1];
    uVar2 = ((uint)param_3[4] << 0x1c) >> 0x1d;
    uVar3 = (uint)param_3[7];
    uVar19 = (uint)(param_3[2] >> 2);
    uVar12 = ((uint)*(ushort *)(param_3 + 4) << 0x16) >> 0x1a;
    uVar9 = ((uint)param_3[5] << 0x1b) >> 0x1d;
    uVar17 = (uint)(*(int *)param_3 << 0xe) >> 0x1d;
    uVar15 = (uint)(*(int *)(param_3 + 4) << 0xd) >> 0x1a;
    uVar13 = (uint)param_3[8];
    uVar4 = (uint)param_3[0xc];
    uVar10 = (uint)param_3[9];
    uVar18 = (uint)param_3[10];
    uVar16 = (uint)param_3[0xb];
    printk("============================= TxBf profile Tage1 Info ========================================\nRow data0 = 0x%x, Row data1 = 0x%x, Row data2 = 0x%x, Row data3 = 0x%x\n\nPFMU ID = %d        Invalid status = %d\niBf/eBf = %d\n\nDBW   = %d\nSU/MU = %d\nRMSD  = %d\nnrow=%d, ncol=%d, ng=%d, LM=%d, CodeBook=%d, HtcExist=%d\n\nMem Col1 = %d, Mem Row1 = %d, Mem Col2 = %d, Mem Row2 = %d\nMem Col3 = %d, Mem Row3 = %d, Mem Col4 = %d, Mem Row4 = %d\n\nSTS0_SNR =0x%x, STS1_SNR=0x%x, STS2_SNR=0x%x, STS3_SNR=0x%x\n\niBf LNA Idx=0x%x\n==============================================================================================\n"
           ,*(int *)param_3,*(int *)(param_3 + 4),*(undefined4 *)(param_3 + 8),
           *(undefined4 *)(param_3 + 0xc),*param_3 & 0x7f,(uVar14 << 0x1c) >> 0x1f,*param_3 >> 7,
           uVar14 & 3,(uVar14 << 0x1d) >> 0x1f,(uVar14 << 0x19) >> 0x1d,
           ((uint)param_3[6] << 0x1a) >> 0x1e,param_3[6] >> 6,uVar3 & 3,(uVar3 << 0x1c) >> 0x1e,
           (uVar3 << 0x1a) >> 0x1e,(uVar3 << 0x19) >> 0x1f,uVar17,uVar19,uVar8,uVar11,uVar2,uVar12,
           uVar9,uVar15,uVar13,uVar10,uVar18,uVar16,uVar4);
    if ((param_2 == 1) && (0 < DebugLevel)) {
      uVar3 = (uint)param_3[0x1a];
      printk("============================= TxBf profile Tage2 Info ========================================\nRow data0 = 0x%x, Row data1 = 0x%x, Row data2 = 0x%x\n\nSmart antenna ID = 0x%x,  SE index = %d\nRMSD threshold = %d\nMCS L1SS thd = %d, S1SS thd = %d, L2SS thd = %d, S2SS thd = %d, L3SS thd = %d, S3SS thd = %d\nTime out = 0x%x\nDesired BW = %d, Desired Ncol = %d, Desired Nrow = %d\n==============================================================================================\n"
             ,*(int *)(param_3 + 0x10),*(undefined4 *)(param_3 + 0x14),
             *(undefined4 *)(param_3 + 0x18),*(ushort *)(param_3 + 0x10) & 0xfff,
             (uint)(*(int *)(param_3 + 0x10) << 0xc) >> 0x1b,((uint)param_3[0x12] << 0x19) >> 0x1d,
             param_3[0x13] & 0xf,param_3[0x13] >> 4,param_3[0x14] & 0xf,param_3[0x14] >> 4,
             param_3[0x15] & 0xf,param_3[0x15] >> 4,param_3[0x16],uVar3 & 3,(uVar3 << 0x1c) >> 0x1e,
             (uVar3 << 0x1a) >> 0x1e,uVar17,uVar19,uVar8,uVar11,uVar2,uVar12,uVar9,uVar15,uVar13,
             uVar10,uVar18,uVar16,uVar4);
    }
  }
  return;
}

