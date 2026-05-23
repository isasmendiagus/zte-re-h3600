// module: mt7915.ko
// function: mt_engine_calc_phy @ 0x254c40
// size: 1488 bytes
//

undefined4
mt_engine_calc_phy(int param_1,int param_2,int param_3,undefined4 param_4,undefined1 param_5)

{
  short sVar1;
  uint uVar2;
  short sVar3;
  byte *pbVar4;
  ushort uVar5;
  uint uVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  int extraout_r1;
  int extraout_r1_00;
  uint uVar10;
  uint uVar11;
  int iVar12;
  uint uVar13;
  undefined1 *puVar14;
  int iVar15;
  int iVar16;
  int local_30;
  int local_2c [2];
  
  uVar6 = *(uint *)(param_1 + 0x10) & 0xffffffdf;
  if (uVar6 < 0xc) {
    uVar11 = (uint)(byte)(&DAT_002a4ec4)[uVar6];
  }
  else {
    uVar11 = 0;
  }
  uVar2 = *(uint *)(param_1 + 0xc) >> 1;
  uVar10 = uVar2 & 0xff;
  if (uVar10 < 0x25) {
    iVar9 = 0;
LAB_00255020:
    uVar13 = *(uint *)(param_1 + 0x10) & 0x20;
    if (uVar13 == 0) {
      uVar5 = *(ushort *)(&UNK_002a4e72 + iVar9 * 10);
    }
    else {
      uVar5 = (&DAT_002a4e74)[iVar9 * 5];
    }
    if (uVar5 == 0) goto LAB_00254cb4;
    iVar9 = 0;
    do {
      iVar7 = iVar9 * 10;
      iVar9 = iVar9 + 1;
      if (uVar10 < (byte)(&DAT_002a4e70)[iVar7]) {
        if (uVar13 == 0) {
          uVar10 = (uint)*(ushort *)(&UNK_002a4e76 + iVar7);
        }
        else {
          uVar10 = (uint)*(ushort *)(&UNK_002a4e78 + iVar7);
        }
        goto LAB_002550a4;
      }
    } while (iVar9 != 7);
    uVar10 = 0;
LAB_002550a4:
    if (param_3 == 0) {
      iVar9 = 1;
    }
    else {
      iVar9 = 2;
    }
    if (*(int *)(param_1 + 0x14) == 0) {
      iVar7 = 6;
    }
    else {
      iVar7 = 0;
    }
    if (uVar6 < 0xc) {
      iVar15 = *(int *)(param_1 + 0x18) * (uint)(byte)(&DAT_002a4eb8)[uVar6];
      iVar16 = iVar15 * (uint)uVar5;
      *(int *)(param_1 + 0x40) = iVar16;
      iVar16 = __aeabi_uidiv((uVar11 - 1) * iVar16,uVar11);
      *(uint *)(param_1 + 0x48) = iVar15 * uVar10;
      *(int *)(param_1 + 0x3c) = iVar16;
    }
    else {
      iVar16 = __aeabi_uidiv(*(int *)(param_1 + 0x40) * (uVar11 - 1),uVar11);
      *(int *)(param_1 + 0x3c) = iVar16;
    }
    iVar16 = iVar9 * iVar16;
    uVar8 = __aeabi_uidiv(*(int *)(param_1 + 0x48) * (uVar11 - 1),uVar11);
    *(undefined4 *)(param_1 + 0x44) = uVar8;
    iVar7 = iVar7 + param_2 * 8 + 0x10;
    __aeabi_uidivmod(iVar7,iVar16);
    if (extraout_r1_00 == 0) {
      iVar16 = __aeabi_uidiv(iVar7,iVar16);
    }
    else {
      iVar16 = __aeabi_uidiv(iVar7,iVar16);
      iVar16 = iVar16 + 1;
    }
    *(int *)(param_1 + 0x38) = extraout_r1_00;
    *(int *)(param_1 + 0x34) = iVar9 * iVar16;
    printk("%s: RU index[%d], apep length:%d symbol_init:%d,\n","mt_engine_calc_symbol_by_bytes",
           uVar2,iVar7,iVar9 * iVar16);
    printk("\t%s: R[%d/%d], cbps:%d, dbps:%d,\n","mt_engine_calc_symbol_by_bytes",uVar11 - 1,uVar11,
           *(undefined4 *)(param_1 + 0x40),*(undefined4 *)(param_1 + 0x3c));
    printk("\t%s: cbps_s:%d, dbps_s:%d excess:%d\n","mt_engine_calc_symbol_by_bytes",
           *(undefined4 *)(param_1 + 0x48),*(undefined4 *)(param_1 + 0x44),
           *(undefined4 *)(param_1 + 0x38));
  }
  else {
    puVar14 = &DAT_002a4e70;
    iVar9 = 1;
    do {
      pbVar4 = puVar14 + 10;
      puVar14 = puVar14 + 10;
      if (uVar10 < *pbVar4) goto LAB_00255020;
      iVar9 = iVar9 + 1;
    } while (iVar9 != 7);
LAB_00254cb4:
    printk("%s: unknown RU Index:[%d]!\n","mt_engine_calc_symbol_by_bytes");
  }
  iVar9 = *(int *)(param_1 + 0x38);
  if (iVar9 == 0) {
    iVar15 = *(int *)(param_1 + 0x3c);
    *(undefined4 *)(param_1 + 0x30) = 4;
    *(int *)(param_1 + 0x38) = iVar15;
  }
  else {
    iVar7 = *(int *)(param_1 + 0x44);
    __aeabi_uidivmod(iVar9,iVar7);
    if (extraout_r1 == 0) {
      uVar6 = __aeabi_uidiv(iVar9,iVar7);
    }
    else {
      iVar9 = __aeabi_uidiv(iVar9,iVar7);
      uVar6 = iVar9 + 1;
    }
    if (3 < uVar6) {
      uVar6 = 4;
    }
    *(uint *)(param_1 + 0x30) = uVar6;
    if (uVar6 != 4) {
      iVar7 = iVar7 * uVar6;
      iVar16 = *(int *)(param_1 + 0x40);
      iVar9 = *(int *)(param_1 + 0x48) * uVar6;
      iVar15 = *(int *)(param_1 + 0x3c);
      *(int *)(param_1 + 0x54) = iVar7;
      *(int *)(param_1 + 0x58) = iVar9;
      goto LAB_00254cf8;
    }
    iVar15 = *(int *)(param_1 + 0x3c);
  }
  iVar16 = *(int *)(param_1 + 0x40);
  uVar6 = 4;
  *(int *)(param_1 + 0x54) = iVar15;
  *(int *)(param_1 + 0x58) = iVar16;
  iVar7 = iVar15;
  iVar9 = iVar16;
LAB_00254cf8:
  iVar12 = *(int *)(param_1 + 0x34) + -1;
  *(int *)(param_1 + 0x4c) = iVar12 * iVar15 + iVar7;
  *(int *)(param_1 + 0x50) = iVar12 * iVar16 + iVar9;
  printk("\t%s: \tafactor=%d, symbol cnt=%d\n","mt_engine_calc_afactor",uVar6);
  printk("\t%s: cbps_l:%d, dbps_l:%d, pld:%d, avbits:%d\n","mt_engine_calc_afactor",
         *(undefined4 *)(param_1 + 0x58),*(undefined4 *)(param_1 + 0x54),
         *(undefined4 *)(param_1 + 0x4c),*(undefined4 *)(param_1 + 0x50));
  FUN_00253b54(param_1,param_4,param_5);
  if (*(int *)(param_1 + 0x14) != 0) {
    local_30 = 0;
    local_2c[0] = 0;
    FUN_00253c50(*(undefined4 *)(param_1 + 0x50),*(undefined4 *)(param_1 + 0x4c),uVar11,&local_30,
                 local_2c);
    iVar15 = local_2c[0];
    iVar16 = local_30;
    iVar12 = local_2c[0] * local_30;
    iVar9 = __aeabi_idiv((uVar11 - 1) * iVar12,uVar11);
    uVar6 = iVar9 - *(int *)(param_1 + 0x4c);
    iVar9 = 0;
    uVar6 = uVar6 & ~((int)uVar6 >> 0x1f);
    sVar3 = ((short)iVar15 * (short)iVar16 - (short)*(undefined4 *)(param_1 + 0x50)) - (short)uVar6;
    iVar7 = (int)sVar3;
    if (iVar7 < 0) {
      *(undefined2 *)(param_1 + 0x66) = 0;
      iVar7 = iVar9;
    }
    else {
      *(short *)(param_1 + 0x66) = sVar3;
      iVar9 = iVar7 * 10;
    }
    iVar12 = __aeabi_idiv(iVar12,uVar11);
    if (((iVar9 <= iVar12) || ((int)(iVar7 * 6 * (uVar11 - 1)) <= (int)(uVar6 * 5))) &&
       (iVar7 = __aeabi_idiv(iVar16 * 3 * iVar15,uVar11), iVar9 <= iVar7)) {
      printk("\t%s: LDPC extra symbol:%d\n","mt_engine_calc_extr_sym",0);
      return 0;
    }
    printk("\t%s: LDPC extra symbol:%d\n","mt_engine_calc_extr_sym",1);
    uVar6 = *(uint *)(param_1 + 0x10) & 0xffffffdf;
    *(undefined1 *)(param_1 + 0x5c) = 1;
    if (param_3 == 0) {
      iVar9 = 1;
    }
    else {
      iVar9 = 2;
    }
    local_30 = 0;
    local_2c[0] = 0;
    if (uVar6 < 0xc) {
      uVar6 = (uint)(byte)(&DAT_002a4ec4)[uVar6];
      iVar7 = *(int *)(param_1 + 0x48);
      if (*(int *)(param_1 + 0x30) == 3) {
        iVar16 = *(int *)(param_1 + 0x50);
        iVar7 = *(int *)(param_1 + 0x40) + iVar7 * -3;
      }
      else {
        iVar16 = *(int *)(param_1 + 0x50);
      }
      *(int *)(param_1 + 0x50) = iVar7 * iVar9 + iVar16;
      FUN_00253c50(*(undefined4 *)(param_1 + 0x50),*(undefined4 *)(param_1 + 0x4c),uVar6,&local_30,
                   local_2c);
      sVar1 = (short)local_30;
      sVar3 = (short)local_2c[0];
      iVar7 = __aeabi_uidiv((uVar6 - 1) * local_30 * local_2c[0],uVar6);
      uVar6 = (int)sVar3 * (int)sVar1 - *(int *)(param_1 + 0x50);
      iVar7 = iVar7 - *(int *)(param_1 + 0x4c);
      if (-1 < iVar7) {
        uVar6 = uVar6 - iVar7;
      }
      *(short *)(param_1 + 0x66) = (short)uVar6;
      if ((uVar6 & 0x8000) != 0) {
        *(undefined2 *)(param_1 + 0x66) = 0;
      }
      iVar7 = *(int *)(param_1 + 0x30);
      if (iVar7 != 4) {
        *(int *)(param_1 + 0x30) = iVar7 + 1;
      }
      else {
        *(undefined4 *)(param_1 + 0x30) = 1;
        iVar9 = *(int *)(param_1 + 0x34) + iVar9;
      }
      if (iVar7 == 4) {
        *(int *)(param_1 + 0x34) = iVar9;
      }
      printk("\t\t%s: (re)afactor:%d\n","mt_engine_recalc_phy_info",*(undefined4 *)(param_1 + 0x30))
      ;
      FUN_00253b54(param_1,param_4,param_5);
    }
  }
  return 0;
}

