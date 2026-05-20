// module: mt7915.ko
// function: TxBfProfileTagWrite @ 0x86948
// size: 544 bytes
//

undefined1 TxBfProfileTagWrite(int param_1,byte *param_2,ushort *param_3,undefined4 param_4)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
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
  
  iVar2 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  uVar1 = 0;
  if (*(code **)(iVar2 + 0x15c) != (code *)0x0) {
    uVar1 = (**(code **)(iVar2 + 0x15c))(*(undefined4 *)(param_1 + 0xa797a0),param_4);
  }
  if (2 < DebugLevel) {
    uVar10 = param_2[3] & 7;
    uVar3 = (uint)(param_2[3] >> 3) | (param_2[4] & 1) << 5;
    uVar14 = (uint)param_2[1];
    uVar7 = ((uint)param_2[4] << 0x1c) >> 0x1d;
    uVar4 = (uint)param_2[7];
    uVar17 = (uint)(param_2[2] >> 2);
    uVar11 = ((uint)*(ushort *)(param_2 + 4) << 0x16) >> 0x1a;
    uVar8 = ((uint)param_2[5] << 0x1b) >> 0x1d;
    uVar15 = (uint)(*(int *)param_2 << 0xe) >> 0x1d;
    uVar5 = (uint)(*(int *)(param_2 + 4) << 0xd) >> 0x1a;
    uVar6 = (uint)param_2[0xc];
    uVar13 = (uint)param_2[8];
    uVar12 = (uint)param_2[9];
    uVar9 = (uint)param_2[10];
    uVar16 = (uint)param_2[0xb];
    printk("============================= TxBf profile Tage1 Info ========================================\nRow data0 = 0x%x, Row data1 = 0x%x, Row data2 = 0x%x, Row data3 = 0x%x\n\nPFMU ID = %d        Invalid status = %d\niBf/eBf = %d\n\nDBW   = %d\nSU/MU = %d\nRMSD  = %d\nnrow=%d, ncol=%d, ng=%d, LM=%d, CodeBook=%d, HtcExist=%d\n\nMem Col1 = %d, Mem Row1 = %d, Mem Col2 = %d, Mem Row2 = %d\nMem Col3 = %d, Mem Row3 = %d, Mem Col4 = %d, Mem Row4 = %d\n\nSTS0_SNR =0x%x, STS1_SNR=0x%x, STS2_SNR=0x%x, STS3_SNR=0x%x\n\niBf LNA Idx=0x%x\n==============================================================================================\n"
           ,*(int *)param_2,*(int *)(param_2 + 4),*(undefined4 *)(param_2 + 8),
           *(undefined4 *)(param_2 + 0xc),*param_2 & 0x7f,(uVar14 << 0x1c) >> 0x1f,*param_2 >> 7,
           uVar14 & 3,(uVar14 << 0x1d) >> 0x1f,(uVar14 << 0x19) >> 0x1d,
           ((uint)param_2[6] << 0x1a) >> 0x1e,param_2[6] >> 6,uVar4 & 3,(uVar4 << 0x1c) >> 0x1e,
           (uVar4 << 0x1a) >> 0x1e,(uVar4 << 0x19) >> 0x1f,uVar15,uVar17,uVar10,uVar3,uVar7,uVar11,
           uVar8,uVar5,uVar13,uVar12,uVar9,uVar16,uVar6);
    if (2 < DebugLevel) {
      uVar4 = (uint)(byte)param_3[5];
      printk("============================= TxBf profile Tage2 Info ========================================\nRow data0 = 0x%x, Row data1 = 0x%x, Row data2 = 0x%x\n\nSmart antenna ID = 0x%x,  SE index = %d\nRMSD threshold = %d\nMCS L1SS thd = %d, S1SS thd = %d, L2SS thd = %d, S2SS thd = %d, L3SS thd = %d, S3SS thd = %d\nTime out = 0x%x\nDesired BW = %d, Desired Ncol = %d, Desired Nrow = %d\n==============================================================================================\n"
             ,*(int *)param_3,*(undefined4 *)(param_3 + 2),*(undefined4 *)(param_3 + 4),
             *param_3 & 0xfff,(uint)(*(int *)param_3 << 0xc) >> 0x1b,
             ((uint)(byte)param_3[1] << 0x19) >> 0x1d,*(byte *)((int)param_3 + 3) & 0xf,
             *(byte *)((int)param_3 + 3) >> 4,(byte)param_3[2] & 0xf,(byte)param_3[2] >> 4,
             *(byte *)((int)param_3 + 5) & 0xf,*(byte *)((int)param_3 + 5) >> 4,(char)param_3[3],
             uVar4 & 3,(uVar4 << 0x1c) >> 0x1e,(uVar4 << 0x1a) >> 0x1e,uVar15,uVar17,uVar10,uVar3,
             uVar7,uVar11,uVar8,uVar5,uVar13,uVar12,uVar9,uVar16,uVar6);
    }
  }
  return uVar1;
}

