// compatible: snps,dwc3
// function: FUN_c027d568 @ 0xc027d568
// found via struct field ptr -> 0xc027d568
// total struct-refs for compat: 2
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_c027d568(int param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  int iVar5;
  undefined4 *puVar6;
  int *piVar7;
  uint uVar8;
  undefined4 uVar9;
  uint uVar10;
  ushort uVar11;
  code *pcVar12;
  uint uVar13;
  int iVar14;
  int iVar15;
  int *piVar16;
  int iVar17;
  undefined4 uVar18;
  uint uVar19;
  byte bVar20;
  uint extraout_r12;
  bool bVar21;
  byte local_2b;
  byte local_2a;
  byte local_29 [5];
  
  iVar15 = param_1 + 0x10;
  piVar16 = *(int **)(param_1 + 100);
  iVar14 = *(int *)(param_1 + 0x124);
  iVar5 = FUN_c01ed3bc(iVar15,0x37f,0x80d0);
  if (iVar5 == 0) {
    return 0xfffffff4;
  }
  uVar13 = iVar5 + 0xfU & 0xfffffff0;
  *(int *)(uVar13 + 0x334) = iVar5;
  *(int *)(uVar13 + 0x7c) = iVar15;
  puVar6 = (undefined4 *)FUN_c01eb908(param_1,0x400,0);
  if (puVar6 == (undefined4 *)0x0) {
    FUN_c01e7918(iVar15,s_missing_IRQ_c05b74f8);
    return 0xffffffed;
  }
  *(undefined4 *)(uVar13 + 0xa0) = *puVar6;
  *(undefined4 *)(uVar13 + 0xa4) = puVar6[1];
  *(undefined4 *)(uVar13 + 0xac) = puVar6[3];
  *(undefined4 *)(uVar13 + 0xa8) = puVar6[2];
  piVar7 = (int *)FUN_c01eb908(param_1,0x200,0);
  if (piVar7 == (int *)0x0) {
    FUN_c01e7918(iVar15,s_missing_memory_resource_c05b7508);
    return 0xffffffed;
  }
  iVar5 = *piVar7;
  *(int *)(uVar13 + 0x84) = iVar5;
  *(int *)(uVar13 + 0x88) = iVar5 + 0x7fff;
  *(int *)(uVar13 + 0x90) = piVar7[3];
  *(int *)(uVar13 + 0x8c) = piVar7[2];
  *piVar7 = *piVar7 + 0xc100;
  uVar8 = FUN_c01979a4(iVar15,piVar7);
  if (0xfffff000 < uVar8) goto LAB_c027dc80;
  *(uint *)(uVar13 + 0x2f4) = uVar8;
  local_2b = 0xff;
  local_2a = 1;
  *(int *)(uVar13 + 0x2f8) = (piVar7[1] + 1) - *piVar7;
  local_29[0] = 0xc;
  if (iVar14 == 0) {
    if (piVar16 == (int *)0x0) {
      iVar5 = *(int *)(uVar13 + 0x314);
      uVar10 = ((uint)*(byte *)(uVar13 + 0x368) << 0x1a) >> 0x1f;
      uVar8 = 1;
      bVar20 = 0xff;
    }
    else {
      iVar5 = *piVar16;
      *(int *)(uVar13 + 0x314) = iVar5;
      *(byte *)(uVar13 + 0x368) =
           *(byte *)(uVar13 + 0x368) & 0xef |
           (byte)((((uint)*(byte *)((int)piVar16 + 0xd) << 0x1e) >> 0x1f) << 4);
      if (*(byte *)(piVar16 + 3) != 0) {
        local_2b = *(byte *)(piVar16 + 3);
      }
      uVar10 = *(byte *)((int)piVar16 + 10) & 1;
      *(byte *)(uVar13 + 0x368) = *(byte *)(uVar13 + 0x368) & 0xdf | (byte)(uVar10 << 5);
      if (*(byte *)((int)piVar16 + 0xb) != 0) {
        local_29[0] = *(byte *)((int)piVar16 + 0xb);
      }
      bVar1 = *(byte *)(uVar13 + 0x369);
      *(byte *)(uVar13 + 0x368) = *(byte *)(uVar13 + 0x368) & 0x7f | (char)piVar16[2] << 7;
      bVar2 = *(byte *)(uVar13 + 0x36a);
      bVar20 = (*(byte *)((int)piVar16 + 9) & 1) << 4;
      *(byte *)(uVar13 + 0x369) = bVar1 & 0xef | bVar20;
      *(int *)(uVar13 + 0x2fc) = piVar16[1];
      *(byte *)(uVar13 + 0x369) = bVar1 & 0xcf | bVar20 | (*(byte *)((int)piVar16 + 0xd) & 1) << 5;
      bVar20 = *(byte *)(uVar13 + 0x369);
      bVar1 = (byte)((((uint)*(byte *)((int)piVar16 + 0xd) << 0x1d) >> 0x1f) << 6);
      *(byte *)(uVar13 + 0x369) = bVar20 & 0xbf | bVar1;
      bVar1 = bVar20 & 0x3f | bVar1 |
              (byte)((((uint)*(byte *)((int)piVar16 + 0xd) << 0x1c) >> 0x1f) << 7);
      *(byte *)(uVar13 + 0x369) = bVar1;
      bVar3 = (byte)(((uint)*(byte *)((int)piVar16 + 0xd) << 0x1b) >> 0x18);
      *(byte *)(uVar13 + 0x36a) = bVar2 & 0xfe | bVar3 >> 7;
      bVar3 = bVar3 >> 7;
      bVar20 = (byte)((((uint)*(byte *)((int)piVar16 + 0xd) << 0x1a) >> 0x1f) << 1);
      *(byte *)(uVar13 + 0x36a) = bVar2 & 0xfc | bVar3 | bVar20;
      bVar4 = (byte)((((uint)*(byte *)((int)piVar16 + 0xd) << 0x19) >> 0x1f) << 2);
      *(byte *)(uVar13 + 0x36a) = bVar2 & 0xf8 | bVar3 | bVar20 | bVar4;
      *(byte *)(uVar13 + 0x36a) =
           bVar2 & 0xf0 | bVar3 | bVar20 | bVar4 | (*(byte *)((int)piVar16 + 0xd) >> 7) << 3;
      *(byte *)(uVar13 + 0x36a) =
           *(byte *)(uVar13 + 0x36a) & 0xef | (*(byte *)((int)piVar16 + 0xe) & 1) << 4;
      bVar20 = *(byte *)(uVar13 + 0x36a);
      uVar8 = (((uint)*(byte *)((int)piVar16 + 0xe) << 0x1e) >> 0x1f) << 5;
      bVar2 = (byte)uVar8;
      *(byte *)(uVar13 + 0x36a) = bVar20 & 0xdf | bVar2;
      uVar19 = (((uint)*(byte *)((int)piVar16 + 0xe) << 0x1d) >> 0x1f) << 6;
      *(byte *)(uVar13 + 0x36a) = bVar20 & 0x9f | bVar2 | (byte)uVar19;
      uVar19 = bVar20 & 0xffffff1f | uVar8 | uVar19 |
               (((uint)*(byte *)((int)piVar16 + 0xe) << 0x1c) >> 0x1f) << 7;
      *(char *)(uVar13 + 0x36a) = (char)uVar19;
      bVar21 = (*(byte *)((int)piVar16 + 0xe) & 0x30) != 0;
      bVar20 = local_2b;
      if (bVar21) {
        uVar8 = (uint)*(byte *)((int)piVar16 + 0xe) << 0x1a;
        uVar19 = uVar8 >> 0x1e;
        local_2a = (byte)(uVar8 >> 0x1e);
        bVar20 = bVar1;
      }
      uVar8 = 1;
      if (bVar21) {
        uVar8 = uVar19;
        bVar20 = local_2b;
      }
    }
  }
  else {
    uVar9 = FUN_c02a0a8c(iVar14);
    *(undefined4 *)(uVar13 + 0x314) = uVar9;
    iVar5 = FUN_c02bb6c4(iVar14,s_snps_has_lpm_erratum_c05b7524,0);
    *(byte *)(uVar13 + 0x368) = *(byte *)(uVar13 + 0x368) & 0xef | (iVar5 != 0) << 4;
    FUN_c02bb888(iVar14,s_snps_lpm_nyet_threshold_c05b753c,&local_2b,1);
    iVar5 = FUN_c02bb6c4(iVar14,s_snps_is_utmi_l1_suspend_c05b7554,0);
    *(byte *)(uVar13 + 0x368) = *(byte *)(uVar13 + 0x368) & 0xdf | (iVar5 != 0) << 5;
    FUN_c02bb888(iVar14,s_snps_hird_threshold_c05b756c,local_29,1);
    iVar5 = FUN_c02bb6c4(iVar14,s_snps_usb3_lpm_capable_c05b7580,0);
    *(byte *)(uVar13 + 0x369) = *(byte *)(uVar13 + 0x369) & 0xef | (iVar5 != 0) << 4;
    iVar5 = FUN_c02bb6c4(iVar14,s_tx_fifo_resize_c05b7598);
    *(byte *)(uVar13 + 0x368) = *(byte *)(uVar13 + 0x368) & 0x7f | (iVar5 != 0) << 7;
    uVar9 = FUN_c02a0a24(iVar14);
    *(undefined4 *)(uVar13 + 0x2fc) = uVar9;
    iVar5 = FUN_c02bb6c4(iVar14,s_snps_disable_scramble_quirk_c05b75a8,0);
    *(byte *)(uVar13 + 0x369) = *(byte *)(uVar13 + 0x369) & 0xdf | (iVar5 != 0) << 5;
    iVar5 = FUN_c02bb6c4(iVar14,s_snps_u2exit_lfps_quirk_c05b75c4);
    *(byte *)(uVar13 + 0x369) = *(byte *)(uVar13 + 0x369) & 0xbf | (iVar5 != 0) << 6;
    iVar5 = FUN_c02bb6c4(iVar14,s_snps_u2ss_inp3_quirk_c05b75dc);
    *(byte *)(uVar13 + 0x369) = *(byte *)(uVar13 + 0x369) & 0x7f | (iVar5 != 0) << 7;
    iVar5 = FUN_c02bb6c4(iVar14,s_snps_req_p1p2p3_quirk_c05b75f4);
    *(byte *)(uVar13 + 0x36a) = *(byte *)(uVar13 + 0x36a) & 0xfe | iVar5 != 0;
    iVar5 = FUN_c02bb6c4(iVar14,s_snps_del_p1p2p3_quirk_c05b760c);
    *(byte *)(uVar13 + 0x36a) = *(byte *)(uVar13 + 0x36a) & 0xfd | (iVar5 != 0) << 1;
    iVar5 = FUN_c02bb6c4(iVar14,s_snps_del_phy_power_chg_quirk_c05b7624);
    *(byte *)(uVar13 + 0x36a) = *(byte *)(uVar13 + 0x36a) & 0xfb | (iVar5 != 0) << 2;
    iVar5 = FUN_c02bb6c4(iVar14,s_snps_lfps_filter_quirk_c05b7644);
    *(byte *)(uVar13 + 0x36a) = *(byte *)(uVar13 + 0x36a) & 0xf7 | (iVar5 != 0) << 3;
    iVar5 = FUN_c02bb6c4(iVar14,s_snps_rx_detect_poll_quirk_c05b765c);
    *(byte *)(uVar13 + 0x36a) = *(byte *)(uVar13 + 0x36a) & 0xef | (iVar5 != 0) << 4;
    iVar5 = FUN_c02bb6c4(iVar14,s_snps_dis_u3_susphy_quirk_c05b7678);
    *(byte *)(uVar13 + 0x36a) = *(byte *)(uVar13 + 0x36a) & 0xdf | (iVar5 != 0) << 5;
    iVar5 = FUN_c02bb6c4(iVar14,s_snps_dis_u2_susphy_quirk_c05b7694);
    *(byte *)(uVar13 + 0x36a) = *(byte *)(uVar13 + 0x36a) & 0xbf | (iVar5 != 0) << 6;
    iVar5 = FUN_c02bb6c4(iVar14,s_snps_tx_de_emphasis_quirk_c05b76b0);
    *(byte *)(uVar13 + 0x36a) = *(byte *)(uVar13 + 0x36a) & 0x7f | (iVar5 != 0) << 7;
    FUN_c02bb888(iVar14,s_snps_tx_de_emphasis_c05b76cc,&local_2a,1);
    iVar5 = *(int *)(uVar13 + 0x314);
    uVar10 = ((uint)*(byte *)(uVar13 + 0x368) << 0x1a) >> 0x1f;
    uVar8 = local_2a & 3;
    bVar20 = local_2b;
  }
  bVar21 = iVar5 == 0;
  *(byte *)(uVar13 + 0x366) = bVar20;
  if (bVar21) {
    iVar5 = 5;
  }
  *(byte *)(uVar13 + 0x367) = local_29[0] | (byte)(uVar10 << 4);
  if (bVar21) {
    *(int *)(uVar13 + 0x314) = iVar5;
  }
  uVar8 = *(byte *)(uVar13 + 0x36b) & 0xfffffffc | uVar8 & 3;
  *(char *)(uVar13 + 0x36b) = (char)uVar8;
  *(undefined4 *)(uVar13 + 0x2e4) = 0;
  *(undefined4 *)(uVar13 + 0x2e8) = 0;
  *(undefined4 *)(uVar13 + 0x2ec) = 0;
  *(undefined4 *)(uVar13 + 0x2f0) = 0;
  *(undefined4 *)(uVar13 + 0x78) = 0;
  *(uint *)(param_1 + 0x68) = uVar13;
  if (*(int *)(param_1 + 0xf8) == 0) {
    iVar5 = *(int *)(param_1 + 0x10);
    *(undefined4 *)(param_1 + 0xf8) = *(undefined4 *)(iVar5 + 0xe8);
    *(undefined4 *)(param_1 + 0x10c) = *(undefined4 *)(iVar5 + 0xfc);
    uVar9 = *(undefined4 *)(iVar5 + 0xf0);
    uVar18 = *(undefined4 *)(iVar5 + 0xf4);
    iVar5 = FUN_c001126c(iVar15,uVar8,uVar9,uVar18);
    if (iVar5 != 0) {
      *(undefined4 *)(param_1 + 0x100) = uVar9;
      *(undefined4 *)(param_1 + 0x104) = uVar18;
    }
  }
  FUN_c01f0c9c(iVar15);
  FUN_c01f19f4(iVar15,4);
  FUN_c01f1c44(iVar15);
  uVar9 = *(undefined4 *)(*(int *)(uVar13 + 0x2f4) + 0x40);
  DataSynchronizationBarrier(0xf);
  FUN_c027e9e0(&LAB_c027d164,s_addr__p_value__08x_c05b74cc,*(int *)(uVar13 + 0x2f4) + 0x40,uVar9);
  *(undefined4 *)(uVar13 + 0x338) = uVar9;
  uVar9 = *(undefined4 *)(*(int *)(uVar13 + 0x2f4) + 0x44);
  DataSynchronizationBarrier(0xf);
  FUN_c027e9e0(&LAB_c027d164,s_addr__p_value__08x_c05b74cc,*(int *)(uVar13 + 0x2f4) + 0x44,uVar9);
  *(undefined4 *)(uVar13 + 0x33c) = uVar9;
  uVar9 = *(undefined4 *)(*(int *)(uVar13 + 0x2f4) + 0x48);
  DataSynchronizationBarrier(0xf);
  FUN_c027e9e0(&LAB_c027d164,s_addr__p_value__08x_c05b74cc,*(int *)(uVar13 + 0x2f4) + 0x48,uVar9);
  *(undefined4 *)(uVar13 + 0x340) = uVar9;
  uVar9 = *(undefined4 *)(*(int *)(uVar13 + 0x2f4) + 0x4c);
  DataSynchronizationBarrier(0xf);
  FUN_c027e9e0(&LAB_c027d164,s_addr__p_value__08x_c05b74cc,*(int *)(uVar13 + 0x2f4) + 0x4c,uVar9);
  *(undefined4 *)(uVar13 + 0x344) = uVar9;
  uVar9 = *(undefined4 *)(*(int *)(uVar13 + 0x2f4) + 0x50);
  DataSynchronizationBarrier(0xf);
  FUN_c027e9e0(&LAB_c027d164,s_addr__p_value__08x_c05b74cc,*(int *)(uVar13 + 0x2f4) + 0x50,uVar9);
  *(undefined4 *)(uVar13 + 0x348) = uVar9;
  uVar9 = *(undefined4 *)(*(int *)(uVar13 + 0x2f4) + 0x54);
  DataSynchronizationBarrier(0xf);
  FUN_c027e9e0(&LAB_c027d164,s_addr__p_value__08x_c05b74cc,*(int *)(uVar13 + 0x2f4) + 0x54,uVar9);
  *(undefined4 *)(uVar13 + 0x34c) = uVar9;
  uVar9 = *(undefined4 *)(*(int *)(uVar13 + 0x2f4) + 0x58);
  DataSynchronizationBarrier(0xf);
  FUN_c027e9e0(&LAB_c027d164,s_addr__p_value__08x_c05b74cc,*(int *)(uVar13 + 0x2f4) + 0x58,uVar9);
  *(undefined4 *)(uVar13 + 0x350) = uVar9;
  uVar9 = *(undefined4 *)(*(int *)(uVar13 + 0x2f4) + 0x5c);
  DataSynchronizationBarrier(0xf);
  FUN_c027e9e0(&LAB_c027d164,s_addr__p_value__08x_c05b74cc,*(int *)(uVar13 + 0x2f4) + 0x5c,uVar9);
  *(undefined4 *)(uVar13 + 0x354) = uVar9;
  uVar9 = *(undefined4 *)(*(int *)(uVar13 + 0x2f4) + 0x500);
  DataSynchronizationBarrier(0xf);
  FUN_c027e9e0(&LAB_c027d164,s_addr__p_value__08x_c05b74cc,*(int *)(uVar13 + 0x2f4) + 0x500,uVar9);
  *(undefined4 *)(uVar13 + 0x358) = uVar9;
  uVar8 = (uint)(*(int *)(uVar13 + 0x33c) << 0xb) >> 0x1a;
  *(uint *)(uVar13 + 0x30c) = uVar8;
  iVar5 = FUN_c01ed3bc(*(undefined4 *)(uVar13 + 0x7c),uVar8 << 2,0x80d0);
  *(int *)(uVar13 + 0xbc) = iVar5;
  if (iVar5 != 0) {
    if (uVar8 != 0) {
      uVar10 = 0;
      do {
        piVar16 = (int *)FUN_c01ed3bc(*(undefined4 *)(uVar13 + 0x7c),0x1c,0x80d0);
        if (piVar16 == (int *)0x0) {
LAB_c027de1c:
          FUN_c01e7918(*(undefined4 *)(uVar13 + 0x7c),s_can_t_allocate_event_buffer_c05b76e0);
          goto LAB_c027de2c;
        }
        piVar16[6] = uVar13;
        piVar16[1] = 0x100;
        iVar5 = *(int *)(uVar13 + 0x7c);
        if ((iVar5 == 0) || (puVar6 = *(undefined4 **)(iVar5 + 0x10c), puVar6 == (undefined4 *)0x0))
        {
          puVar6 = &DAT_c06744c4;
        }
        iVar5 = (*(code *)*puVar6)(iVar5,0x100,piVar16 + 5,0xd0,0);
        *piVar16 = iVar5;
        if ((iVar5 == 0) || ((int *)0xfffff000 < piVar16)) goto LAB_c027de1c;
        *(int **)(*(int *)(uVar13 + 0xbc) + uVar10 * 4) = piVar16;
        uVar10 = uVar10 + 1;
      } while (uVar8 != uVar10);
    }
    iVar5 = *(int *)(uVar13 + 0x348);
    *(undefined4 *)(uVar13 + 0x2fc) = 1;
    uVar8 = *(uint *)(*(int *)(uVar13 + 0x2f4) + 0x20);
    DataSynchronizationBarrier(0xf);
    FUN_c027e9e0(&LAB_c027d164,s_addr__p_value__08x_c05b74cc,*(int *)(uVar13 + 0x2f4) + 0x20,uVar8);
    if ((uVar8 & 0xffff0000) == 0x55330000) {
LAB_c027de70:
      *(uint *)(uVar13 + 0x318) = uVar8;
      iVar14 = *(int *)(uVar13 + 0x2f4);
      DataSynchronizationBarrier(0xe);
      if (DAT_c066b2b8 != (code *)0x0) {
        (*DAT_c066b2b8)();
      }
      *(undefined4 *)(iVar14 + 0x28) = 0x40119;
      FUN_c027e9e0(&LAB_c027d168,s_addr__p_value__08x_c05b74cc,iVar14 + 0x28);
      if (((*(uint *)(uVar13 + 0x344) & 3) == 0) && (*(int *)(uVar13 + 0x314) == 5)) {
        *(undefined4 *)(uVar13 + 0x314) = 3;
      }
      iVar14 = FUN_c0056968(500);
      iVar17 = *(int *)(uVar13 + 0x2f4);
      iVar14 = iVar14 + DAT_c066a0a0;
      DataSynchronizationBarrier(0xe);
      if (DAT_c066b2b8 != (code *)0x0) {
        (*DAT_c066b2b8)();
      }
      *(undefined4 *)(iVar17 + 0x604) = 0x40000000;
      FUN_c027e9e0(&LAB_c027d168,s_addr__p_value__08x_c05b74cc);
LAB_c027df3c:
      uVar8 = *(uint *)(*(int *)(uVar13 + 0x2f4) + 0x604);
      DataSynchronizationBarrier(0xf);
      FUN_c027e9e0(&LAB_c027d164,s_addr__p_value__08x_c05b74cc,*(int *)(uVar13 + 0x2f4) + 0x604,
                   uVar8);
      if ((uVar8 & 0x40000000) != 0) goto LAB_c027df2c;
      DataSynchronizationBarrier(0xf);
      uVar8 = *(uint *)(*(int *)(uVar13 + 0x2f4) + 0x10) | 0x800;
      FUN_c027e9e0(&LAB_c027d164,s_addr__p_value__08x_c05b74cc,*(int *)(uVar13 + 0x2f4) + 0x10);
      iVar14 = *(int *)(uVar13 + 0x2f4);
      DataSynchronizationBarrier(0xe);
      if (DAT_c066b2b8 != (code *)0x0) {
        (*DAT_c066b2b8)();
      }
      *(uint *)(iVar14 + 0x10) = uVar8;
      FUN_c027e9e0(&LAB_c027d168,s_addr__p_value__08x_c05b74cc,iVar14 + 0x10,uVar8);
      DataSynchronizationBarrier(0xf);
      uVar8 = *(uint *)(*(int *)(uVar13 + 0x2f4) + 0x1c0) | 0x80000000;
      FUN_c027e9e0(&LAB_c027d164,s_addr__p_value__08x_c05b74cc,*(int *)(uVar13 + 0x2f4) + 0x1c0);
      iVar14 = *(int *)(uVar13 + 0x2f4);
      DataSynchronizationBarrier(0xe);
      if (DAT_c066b2b8 != (code *)0x0) {
        (*DAT_c066b2b8)();
      }
      *(uint *)(iVar14 + 0x1c0) = uVar8;
      FUN_c027e9e0(&LAB_c027d168,s_addr__p_value__08x_c05b74cc,iVar14 + 0x1c0,uVar8);
      DataSynchronizationBarrier(0xf);
      uVar8 = *(uint *)(*(int *)(uVar13 + 0x2f4) + 0x100) | 0x80000000;
      FUN_c027e9e0(&LAB_c027d164,s_addr__p_value__08x_c05b74cc,*(int *)(uVar13 + 0x2f4) + 0x100);
      iVar14 = *(int *)(uVar13 + 0x2f4);
      DataSynchronizationBarrier(0xe);
      if (DAT_c066b2b8 != (code *)0x0) {
        (*DAT_c066b2b8)();
      }
      *(uint *)(iVar14 + 0x100) = uVar8;
      FUN_c027e9e0(&LAB_c027d168,s_addr__p_value__08x_c05b74cc,iVar14 + 0x100,uVar8);
      if ((*(int *)(uVar13 + 0x2e4) != 0) &&
         (pcVar12 = *(code **)(*(int *)(uVar13 + 0x2e4) + 0x38), pcVar12 != (code *)0x0)) {
        (*pcVar12)();
      }
      if ((*(int *)(uVar13 + 0x2e8) != 0) &&
         (pcVar12 = *(code **)(*(int *)(uVar13 + 0x2e8) + 0x38), pcVar12 != (code *)0x0)) {
        (*pcVar12)();
      }
      if ((*(int *)(uVar13 + 0x2ec) == 0) && (*(int *)(uVar13 + 0x2f0) == 0)) {
        iVar14 = 100;
        do {
          (*DAT_c06955fc)(0x66665b0);
          iVar14 = iVar14 + -1;
        } while (iVar14 != 0);
        DataSynchronizationBarrier(0xf);
        uVar8 = *(uint *)(*(int *)(uVar13 + 0x2f4) + 0x1c0) & 0x7fffffff;
        FUN_c027e9e0(&LAB_c027d164,s_addr__p_value__08x_c05b74cc,*(int *)(uVar13 + 0x2f4) + 0x1c0);
        iVar14 = *(int *)(uVar13 + 0x2f4);
        DataSynchronizationBarrier(0xe);
        if (DAT_c066b2b8 != (code *)0x0) {
          (*DAT_c066b2b8)();
        }
        *(uint *)(iVar14 + 0x1c0) = uVar8;
        FUN_c027e9e0(&LAB_c027d168,s_addr__p_value__08x_c05b74cc,iVar14 + 0x1c0,uVar8);
        DataSynchronizationBarrier(0xf);
        uVar8 = *(uint *)(*(int *)(uVar13 + 0x2f4) + 0x100) & 0x7fffffff;
        FUN_c027e9e0(&LAB_c027d164,s_addr__p_value__08x_c05b74cc,*(int *)(uVar13 + 0x2f4) + 0x100);
        iVar14 = *(int *)(uVar13 + 0x2f4);
        DataSynchronizationBarrier(0xe);
        if (DAT_c066b2b8 != (code *)0x0) {
          (*DAT_c066b2b8)();
        }
        *(uint *)(iVar14 + 0x100) = uVar8;
        iVar17 = 100;
        FUN_c027e9e0(&LAB_c027d168,s_addr__p_value__08x_c05b74cc,iVar14 + 0x100,uVar8);
        do {
          (*DAT_c06955fc)(0x66665b0);
          iVar17 = iVar17 + -1;
        } while (iVar17 != 0);
        DataSynchronizationBarrier(0xf);
        uVar8 = *(uint *)(*(int *)(uVar13 + 0x2f4) + 0x10) & 0xfffff7ff;
        FUN_c027e9e0(&LAB_c027d164,s_addr__p_value__08x_c05b74cc,*(int *)(uVar13 + 0x2f4) + 0x10);
        iVar14 = *(int *)(uVar13 + 0x2f4);
        DataSynchronizationBarrier(0xe);
        if (DAT_c066b2b8 != (code *)0x0) {
          (*DAT_c066b2b8)();
        }
        *(uint *)(iVar14 + 0x10) = uVar8;
        FUN_c027e9e0(&LAB_c027d168,s_addr__p_value__08x_c05b74cc,iVar14 + 0x10,uVar8);
        uVar10 = *(uint *)(*(int *)(uVar13 + 0x2f4) + 0x10);
        DataSynchronizationBarrier(0xf);
        uVar19 = uVar10 & 0xffffffcf;
        FUN_c027e9e0(&LAB_c027d164,s_addr__p_value__08x_c05b74cc,*(int *)(uVar13 + 0x2f4) + 0x10,
                     uVar10);
        uVar8 = (uint)(*(int *)(uVar13 + 0x33c) << 6) >> 0x1e;
        if (uVar8 == 1) {
          if (((*(uint *)(uVar13 + 0x2fc) & 0xfffffffd) == 1) &&
             (*(int *)(uVar13 + 0x318) + 0xaaccdef6U < 0x401)) {
            uVar19 = uVar19 | 0x401;
          }
          else {
            uVar19 = uVar10 & 0xffffffce;
          }
        }
        else if (uVar8 == 2) {
          uVar19 = uVar19 | 2;
          *(uint *)(uVar13 + 0x308) = (uint)(iVar5 << 0xf) >> 0x1c;
        }
        if ((*(uint *)(uVar13 + 0x350) & 0x80) != 0) {
          *(byte *)(uVar13 + 0x368) = *(byte *)(uVar13 + 0x368) | 0x40;
        }
        uVar11 = *(ushort *)(uVar13 + 0x368) & 0x2040;
        if (uVar11 == 0x2000) {
          if (DAT_c06ad36f == '\0') {
            FUN_c001a0c0(s_drivers_usb_dwc3_core_c_c05b74e0,0x21e,
                         s_disable_scramble_cannot_be_used_o_c05b773c);
            DAT_c06ad36f = '\x01';
            uVar11 = *(ushort *)(uVar13 + 0x368) & 0x2040;
            goto LAB_c027e358;
          }
LAB_c027e364:
          uVar19 = uVar19 & 0xfffffff7;
        }
        else {
LAB_c027e358:
          if (uVar11 != 0x2040) goto LAB_c027e364;
          uVar19 = uVar19 | 8;
        }
        if ((*(byte *)(uVar13 + 0x369) & 0x40) != 0) {
          uVar19 = uVar19 | 4;
        }
        if (*(uint *)(uVar13 + 0x318) < 0x5533190a) {
          uVar19 = uVar19 | 0x10000;
        }
        bVar20 = (byte)((uint)(*(int *)(uVar13 + 0x344) << 9) >> 0x18);
        *(byte *)(uVar13 + 0x332) = bVar20 >> 3;
        *(byte *)(uVar13 + 0x331) =
             (byte)((uint)(*(int *)(uVar13 + 0x344) << 0xe) >> 0x1a) - (bVar20 >> 3);
        FUN_c027e9e0(&LAB_c027d16c,s_found__d_IN_and__d_OUT_endpoints_c05b7770);
        iVar5 = *(int *)(uVar13 + 0x2f4);
        DataSynchronizationBarrier(0xe);
        if (DAT_c066b2b8 != (code *)0x0) {
          (*DAT_c066b2b8)();
        }
        *(uint *)(iVar5 + 0x10) = uVar19;
        FUN_c027e9e0(&LAB_c027d168,s_addr__p_value__08x_c05b74cc,iVar5 + 0x10,uVar19);
        uVar8 = *(uint *)(*(int *)(uVar13 + 0x2f4) + 0x1c0);
        DataSynchronizationBarrier(0xf);
        FUN_c027e9e0(&LAB_c027d164,s_addr__p_value__08x_c05b74cc,*(int *)(uVar13 + 0x2f4) + 0x1c0,
                     uVar8);
        iVar5 = *(int *)(uVar13 + 0x2f4);
        if (0x5533194a < *(uint *)(uVar13 + 0x318)) {
          uVar8 = uVar8 | 0x20000;
        }
        bVar20 = *(byte *)(uVar13 + 0x36a);
        if ((*(byte *)(uVar13 + 0x369) & 0x80) != 0) {
          uVar8 = uVar8 | 0x20000000;
        }
        if ((bVar20 & 1) != 0) {
          uVar8 = uVar8 | 0x1000000;
        }
        if ((bVar20 & 2) != 0) {
          uVar8 = uVar8 | 0x80000;
        }
        if ((bVar20 & 4) != 0) {
          uVar8 = uVar8 | 0x40000;
        }
        if ((bVar20 & 8) != 0) {
          uVar8 = uVar8 | 0x200;
        }
        if ((bVar20 & 0x10) != 0) {
          uVar8 = uVar8 | 0x100;
        }
        if ((bVar20 & 0x80) != 0) {
          uVar8 = uVar8 | (*(byte *)(uVar13 + 0x36b) & 3) << 1;
        }
        if ((bVar20 & 0x20) != 0) {
          uVar8 = uVar8 & 0xfffdffff;
        }
        DataSynchronizationBarrier(0xe);
        if (DAT_c066b2b8 != (code *)0x0) {
          (*DAT_c066b2b8)();
        }
        *(uint *)(iVar5 + 0x1c0) = uVar8;
        iVar14 = 100;
        FUN_c027e9e0(&LAB_c027d168,s_addr__p_value__08x_c05b74cc,iVar5 + 0x1c0,uVar8);
        do {
          (*DAT_c06955fc)(0x66665b0);
          iVar14 = iVar14 + -1;
        } while (iVar14 != 0);
        uVar8 = *(uint *)(*(int *)(uVar13 + 0x2f4) + 0x100);
        DataSynchronizationBarrier(0xf);
        FUN_c027e9e0(&LAB_c027d164,s_addr__p_value__08x_c05b74cc,*(int *)(uVar13 + 0x2f4) + 0x100,
                     uVar8);
        iVar5 = *(int *)(uVar13 + 0x2f4);
        if (0x5533194a < *(uint *)(uVar13 + 0x318)) {
          uVar8 = uVar8 | 0x40;
        }
        if ((*(byte *)(uVar13 + 0x36a) & 0x40) != 0) {
          uVar8 = uVar8 & 0xffffffbf;
        }
        DataSynchronizationBarrier(0xe);
        if (DAT_c066b2b8 != (code *)0x0) {
          (*DAT_c066b2b8)();
        }
        *(uint *)(iVar5 + 0x100) = uVar8;
        iVar14 = 100;
        FUN_c027e9e0(&LAB_c027d168,s_addr__p_value__08x_c05b74cc,iVar5 + 0x100,uVar8);
        do {
          (*DAT_c06955fc)(0x66665b0);
          iVar14 = iVar14 + -1;
        } while (iVar14 != 0);
        if (((*(byte *)(uVar13 + 0x368) & 8) == 0) ||
           (uVar8 = *(uint *)(uVar13 + 0x308), uVar8 == 0)) goto LAB_c027e60c;
        if (0xfffff < uVar8) {
          *(undefined4 *)(uVar13 + 0xc) = 0;
          uVar8 = 0xfffffff4;
LAB_c027e598:
          if ((*(int *)(uVar13 + 0x2e4) != 0) &&
             (pcVar12 = *(code **)(*(int *)(uVar13 + 0x2e4) + 0x3c), pcVar12 != (code *)0x0)) {
            (*pcVar12)();
          }
          if ((*(int *)(uVar13 + 0x2e8) != 0) &&
             (pcVar12 = *(code **)(*(int *)(uVar13 + 0x2e8) + 0x3c), pcVar12 != (code *)0x0)) {
            (*pcVar12)();
          }
          goto LAB_c027dc68;
        }
        iVar5 = FUN_c00a3100(uVar8 << 0xc,0xd0);
        *(int *)(uVar13 + 0xc) = iVar5;
        if (iVar5 == 0) {
          uVar8 = 0xfffffff4;
          goto LAB_c027e598;
        }
        if (((*(byte *)(uVar13 + 0x368) & 8) != 0) && (*(int *)(uVar13 + 0x308) != 0)) {
          FUN_c001a140(s_drivers_usb_dwc3_core_c_c05b74e0,0x11f);
          iVar5 = *(int *)(uVar13 + 0x7c);
          uVar8 = extraout_r12;
          if (iVar5 == 0) {
            uVar8 = 0x44c4;
          }
          if (iVar5 == 0) {
            puVar6 = (undefined4 *)(uVar8 & 0xffff | 0xc0670000);
          }
          else {
            puVar6 = *(undefined4 **)(iVar5 + 0x10c);
            if (*(undefined4 **)(iVar5 + 0x10c) == (undefined4 *)0x0) {
              puVar6 = &DAT_c06744c4;
            }
          }
          iVar5 = (*(code *)puVar6[4])
                            (iVar5,_DAT_c06b7084 +
                                   (*(uint *)(uVar13 + 0xc) + 0x40000000 >> 0xc) * 0x20,
                             *(uint *)(uVar13 + 0xc) & 0xfff,*(int *)(uVar13 + 0x308) << 0xc,0,0);
          if (iVar5 == -1) {
            uVar8 = 0xfffffff2;
            FUN_c01e7918(*(undefined4 *)(uVar13 + 0x7c),s_failed_to_map_scratch_buffer_c05b7794);
            FUN_c027d34c(uVar13);
            goto LAB_c027e598;
          }
          *(int *)(uVar13 + 0x20) = iVar5;
        }
LAB_c027e60c:
        iVar5 = *(int *)(uVar13 + 0x2e4);
        if ((iVar5 != 0) && (*(code **)(iVar5 + 0x48) != (code *)0x0)) {
          (**(code **)(iVar5 + 0x48))(iVar5,0);
        }
        iVar5 = *(int *)(uVar13 + 0x2e8);
        if ((iVar5 != 0) && (*(code **)(iVar5 + 0x48) != (code *)0x0)) {
          (**(code **)(iVar5 + 0x48))(iVar5,0);
        }
        if ((*(int *)(uVar13 + 0x2ec) == 0) && (*(int *)(uVar13 + 0x2f0) == 0)) {
          if (*(int *)(uVar13 + 0x30c) != 0) {
            iVar5 = 0x30c;
            uVar8 = 0;
            do {
              iVar17 = *(int *)(*(int *)(uVar13 + 0xbc) + uVar8 * 4);
              *(undefined4 *)(iVar17 + 8) = 0;
              uVar9 = *(undefined4 *)(iVar17 + 0x14);
              iVar14 = *(int *)(uVar13 + 0x2f4);
              DataSynchronizationBarrier(0xe);
              if (DAT_c066b2b8 != (code *)0x0) {
                (*DAT_c066b2b8)();
              }
              *(undefined4 *)(iVar14 + iVar5 + -0xc) = uVar9;
              FUN_c027e9e0(&LAB_c027d168,s_addr__p_value__08x_c05b74cc);
              iVar14 = *(int *)(uVar13 + 0x2f4);
              DataSynchronizationBarrier(0xe);
              if (DAT_c066b2b8 != (code *)0x0) {
                (*DAT_c066b2b8)();
              }
              puVar6 = (undefined4 *)(iVar14 + iVar5 + -8);
              *puVar6 = 0;
              FUN_c027e9e0(&LAB_c027d168,s_addr__p_value__08x_c05b74cc,puVar6,0);
              uVar11 = *(ushort *)(iVar17 + 4);
              iVar14 = *(int *)(uVar13 + 0x2f4);
              DataSynchronizationBarrier(0xe);
              if (DAT_c066b2b8 != (code *)0x0) {
                (*DAT_c066b2b8)();
              }
              *(uint *)(iVar14 + iVar5 + -4) = (uint)uVar11;
              FUN_c027e9e0(&LAB_c027d168,s_addr__p_value__08x_c05b74cc);
              iVar14 = *(int *)(uVar13 + 0x2f4);
              DataSynchronizationBarrier(0xe);
              if (DAT_c066b2b8 != (code *)0x0) {
                (*DAT_c066b2b8)();
              }
              puVar6 = (undefined4 *)(iVar14 + iVar5);
              *puVar6 = 0;
              uVar8 = uVar8 + 1;
              FUN_c027e9e0(&LAB_c027d168,s_addr__p_value__08x_c05b74cc,puVar6,0);
              iVar5 = iVar5 + 0x10;
            } while (uVar8 < *(uint *)(uVar13 + 0x30c));
          }
          iVar5 = *(int *)(uVar13 + 0x2fc);
          uVar9 = *(undefined4 *)(uVar13 + 0x7c);
          if (iVar5 == 2) {
            FUN_c027d4e8(uVar13,2);
LAB_c027e868:
            uVar8 = FUN_c027eb94(uVar13);
            if (uVar8 == 0) {
              FUN_c01f1f6c(iVar15);
              return 0;
            }
            FUN_c01e7918(iVar15,s_failed_to_initialize_debugfs_c05b77f4);
            FUN_c027d2a8(uVar13);
          }
          else if ((iVar5 == 3) || (iVar5 == 1)) {
            FUN_c027d4e8(uVar13,iVar5);
            uVar8 = FUN_c027ea20(uVar13);
            if (uVar8 == 0) goto LAB_c027e868;
            FUN_c01e7918(uVar9,s_failed_to_initialize_host_c05b77b4);
          }
          else {
            uVar8 = 0xffffffea;
            FUN_c01e7918(uVar9,s_Unsupported_mode_of_operation__d_c05b77d0);
          }
          FUN_c027d170(uVar13);
        }
        else {
          uVar8 = 0xffffffda;
        }
        iVar5 = *(int *)(uVar13 + 0x2e4);
        if ((iVar5 != 0) && (*(code **)(iVar5 + 0x48) != (code *)0x0)) {
          (**(code **)(iVar5 + 0x48))(iVar5,1);
        }
        iVar5 = *(int *)(uVar13 + 0x2e8);
        if ((iVar5 != 0) && (*(code **)(iVar5 + 0x48) != (code *)0x0)) {
          (**(code **)(iVar5 + 0x48))(iVar5,1);
        }
        FUN_c027d3ec(uVar13);
        goto LAB_c027dc78;
      }
      uVar8 = 0xffffffda;
      goto LAB_c027dc68;
    }
    if ((uVar8 & 0xffff0000) == 0x33310000) {
      uVar10 = *(uint *)(*(int *)(uVar13 + 0x2f4) + 0xa0);
      DataSynchronizationBarrier(0xf);
      uVar8 = uVar10 | 0x80000000;
      FUN_c027e9e0(&LAB_c027d164,s_addr__p_value__08x_c05b74cc,*(int *)(uVar13 + 0x2f4) + 0xa0,
                   uVar10);
      goto LAB_c027de70;
    }
    uVar8 = 0xffffffed;
    FUN_c01e7918(*(undefined4 *)(uVar13 + 0x7c),s_this_is_not_a_DesignWare_USB3_DR_c05b7700);
    goto LAB_c027dc68;
  }
LAB_c027de2c:
  uVar8 = 0xfffffff4;
  FUN_c01e7918(*(undefined4 *)(uVar13 + 0x7c),s_failed_to_allocate_event_buffers_c05b7814);
LAB_c027dc78:
  FUN_c027d2c0(uVar13);
LAB_c027dc80:
  *piVar7 = *piVar7 + -0xc100;
  return uVar8;
LAB_c027df2c:
  if (iVar14 - DAT_c066a0a0 < 0) goto LAB_c027e0f0;
  goto LAB_c027df3c;
LAB_c027e0f0:
  uVar8 = 0xffffff92;
  FUN_c01e7918(*(undefined4 *)(uVar13 + 0x7c),s_Reset_Timed_Out_c05b7728);
LAB_c027dc68:
  FUN_c01e7918(iVar15,s_failed_to_initialize_core_c05b7838);
  goto LAB_c027dc78;
}

