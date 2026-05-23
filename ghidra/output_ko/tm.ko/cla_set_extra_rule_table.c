// module: tm.ko
// function: cla_set_extra_rule_table @ 0x146e0
// size: 2392 bytes
//

undefined4 cla_set_extra_rule_table(uint param_1,byte *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  int local_2c [2];
  
  local_2c[0] = 0;
  if (g_tm_debug_level < 7) goto LAB_0001470c;
  printk("[TM][cla_set_extra_rule_table]input:\n");
  if (g_tm_debug_level < 7) {
LAB_00014930:
    if (6 < g_tm_debug_level) {
      printk("winoffset14 = %d, winoffset15 = %d, winoffset16 = %d, winoffset17 = %d\n",
             (param_2[0xd] & 1) << 6 | param_2[0xc] >> 2,param_2[0xd] >> 1,param_2[0xe] & 0x7f,
             (param_2[0xf] & 0x3f) << 1 | param_2[0xe] >> 7);
      if (g_tm_debug_level < 7) goto LAB_0001470c;
      printk("winoffset18 = %d, winoffset19 = %d, winmask0 = %d, winmask1 = %d\n",
             (param_2[0x10] & 0x1f) << 2 | param_2[0xf] >> 6,
             (param_2[0x11] & 0xf) << 3 | param_2[0x10] >> 5,
             (uint)param_2[0x12] << 4 | (uint)(param_2[0x11] >> 4) | (param_2[0x13] & 0xf) << 0xc,
             (uint)param_2[0x14] << 4 | (uint)(param_2[0x13] >> 4) | (param_2[0x15] & 0xf) << 0xc);
      goto LAB_000149f4;
    }
LAB_00014b04:
    if (6 < g_tm_debug_level) {
      printk("winmask10 = %d, winmask11 = %d, winmask12 = %d, winmask13 = %d\n",
             (uint)param_2[0x26] << 4 | (uint)(param_2[0x25] >> 4) | (param_2[0x27] & 0xf) << 0xc,
             (uint)param_2[0x28] << 4 | (uint)(param_2[0x27] >> 4) | (param_2[0x29] & 0xf) << 0xc,
             (uint)param_2[0x2a] << 4 | (uint)(param_2[0x29] >> 4) | (param_2[0x2b] & 0xf) << 0xc,
             (uint)param_2[0x2c] << 4 | (uint)(param_2[0x2b] >> 4) | (param_2[0x2d] & 0xf) << 0xc);
      if (g_tm_debug_level < 7) goto LAB_0001470c;
      printk("winmask14 = %d, winmask15 = %d, winmask16 = %d, winmask17 = %d\n",
             (uint)param_2[0x2e] << 4 | (uint)(param_2[0x2d] >> 4) | (param_2[0x2f] & 0xf) << 0xc,
             (uint)param_2[0x30] << 4 | (uint)(param_2[0x2f] >> 4) | (param_2[0x31] & 0xf) << 0xc,
             (uint)param_2[0x32] << 4 | (uint)(param_2[0x31] >> 4) | (param_2[0x33] & 0xf) << 0xc,
             (uint)param_2[0x34] << 4 | (uint)(param_2[0x33] >> 4) | (param_2[0x35] & 0xf) << 0xc);
      goto LAB_00014c14;
    }
LAB_00014ca8:
    if (6 < g_tm_debug_level) {
      printk("rule_mode = %d, hash_len = %d, mem_ctrl = %d\n",((uint)param_2[0x3a] << 0x1c) >> 0x1f,
             (param_2[0x3b] & 1) << 4 | (uint)(param_2[0x3a] >> 4),
             ((uint)param_2[0x3b] << 0x1e) >> 0x1f);
      if (g_tm_debug_level < 7) goto LAB_0001470c;
      printk("cvlan_mask               :0x%x\n",((uint)param_2[0x3b] << 0x1d) >> 0x1f);
      goto LAB_00014d04;
    }
LAB_00014d4c:
    if (6 < g_tm_debug_level) {
      printk("offset2_type             :0x%x\n",(param_2[0x3d] & 1) << 2 | param_2[0x3c] >> 6);
      if (g_tm_debug_level < 7) goto LAB_0001470c;
      printk("offset3_type             :0x%x\n",((uint)param_2[0x3d] << 0x1c) >> 0x1d);
      goto LAB_00014da0;
    }
LAB_00014df4:
    if (6 < g_tm_debug_level) {
      printk("offset6_type             :0x%x\n",((uint)param_2[0x3e] << 0x1b) >> 0x1d);
      if (g_tm_debug_level < 7) goto LAB_0001470c;
      printk("offset7_type             :0x%x\n",param_2[0x3e] >> 5);
      goto LAB_00014e3c;
    }
LAB_00014e84:
    if (6 < g_tm_debug_level) {
      printk("offset10_type            :0x%x\n",(param_2[0x40] & 1) << 2 | param_2[0x3f] >> 6);
      if (g_tm_debug_level < 7) goto LAB_0001470c;
      printk("offset11_type            :0x%x\n",((uint)param_2[0x40] << 0x1c) >> 0x1d);
      goto LAB_00014ed8;
    }
LAB_00014f2c:
    if (6 < g_tm_debug_level) {
      printk("offset14_type            :0x%x\n",((uint)param_2[0x41] << 0x1b) >> 0x1d);
      if (g_tm_debug_level < 7) goto LAB_0001470c;
      printk("offset15_type            :0x%x\n",param_2[0x41] >> 5);
      goto LAB_00014f74;
    }
  }
  else {
    printk("rule_id = %d, winoffset0 = %d, winoffset1 = %d\n",param_1,*param_2 & 0x7f,
           (param_2[1] & 0x3f) << 1 | *param_2 >> 7);
    if (g_tm_debug_level < 7) goto LAB_0001470c;
    printk("winoffset2 = %d, winoffset3 = %d, winoffset4 = %d, winoffset5 = %d\n",
           (param_2[2] & 0x1f) << 2 | param_2[1] >> 6,(param_2[3] & 0xf) << 3 | param_2[2] >> 5,
           (param_2[4] & 7) << 4 | param_2[3] >> 4,(param_2[5] & 3) << 5 | param_2[4] >> 3);
    if (6 < g_tm_debug_level) {
      printk("winoffset6 = %d, winoffset7 = %d, winoffset8 = %d, winoffset9 = %d\n",
             (param_2[6] & 1) << 6 | param_2[5] >> 2,param_2[6] >> 1,param_2[7] & 0x7f,
             (param_2[8] & 0x3f) << 1 | param_2[7] >> 7);
      if (g_tm_debug_level < 7) goto LAB_0001470c;
      printk("winoffset10 = %d, winoffset11 = %d, winoffset12 = %d, winoffset13 = %d\n",
             (param_2[9] & 0x1f) << 2 | param_2[8] >> 6,(param_2[10] & 0xf) << 3 | param_2[9] >> 5,
             (param_2[0xb] & 7) << 4 | param_2[10] >> 4,(param_2[0xc] & 3) << 5 | param_2[0xb] >> 3)
      ;
      goto LAB_00014930;
    }
LAB_000149f4:
    if (6 < g_tm_debug_level) {
      printk("winmask2 = %d, winmask3 = %d, winmask4 = %d, winmask5 = %d\n",
             (uint)param_2[0x16] << 4 | (uint)(param_2[0x15] >> 4) | (param_2[0x17] & 0xf) << 0xc,
             (uint)param_2[0x18] << 4 | (uint)(param_2[0x17] >> 4) | (param_2[0x19] & 0xf) << 0xc,
             (uint)param_2[0x1a] << 4 | (uint)(param_2[0x19] >> 4) | (param_2[0x1b] & 0xf) << 0xc,
             (uint)param_2[0x1c] << 4 | (uint)(param_2[0x1b] >> 4) | (param_2[0x1d] & 0xf) << 0xc);
      if (g_tm_debug_level < 7) goto LAB_0001470c;
      printk("winmask6 = %d, winmask7 = %d, winmask8 = %d, winmask9 = %d\n",
             (uint)param_2[0x1e] << 4 | (uint)(param_2[0x1d] >> 4) | (param_2[0x1f] & 0xf) << 0xc,
             (uint)param_2[0x20] << 4 | (uint)(param_2[0x1f] >> 4) | (param_2[0x21] & 0xf) << 0xc,
             (uint)param_2[0x22] << 4 | (uint)(param_2[0x21] >> 4) | (param_2[0x23] & 0xf) << 0xc,
             (uint)param_2[0x24] << 4 | (uint)(param_2[0x23] >> 4) | (param_2[0x25] & 0xf) << 0xc);
      goto LAB_00014b04;
    }
LAB_00014c14:
    if (6 < g_tm_debug_level) {
      uVar3 = (uint)param_2[0x39];
      printk("windmask18 = %d, winmask19 = %d, outport_mask = %d,inport_mask= %d\n",
             (uint)param_2[0x36] << 4 | (uint)(param_2[0x35] >> 4) | (param_2[0x37] & 0xf) << 0xc,
             (uint)param_2[0x38] << 4 | (uint)(param_2[0x37] >> 4) | (uVar3 & 0xf) << 0xc,
             (uVar3 << 0x1b) >> 0x1f,(uVar3 << 0x1a) >> 0x1f);
      if (g_tm_debug_level < 7) goto LAB_0001470c;
      printk("taglevel_mask = %d, l2info_mask = %d, pppoe_mask= %d,no_match_act = %d\n",
             ((uint)param_2[0x39] << 0x19) >> 0x1f,param_2[0x39] >> 7,param_2[0x3a] & 1,
             ((uint)param_2[0x3a] << 0x1d) >> 0x1e);
      goto LAB_00014ca8;
    }
LAB_00014d04:
    if (6 < g_tm_debug_level) {
      printk("offset0_type             :0x%x\n",param_2[0x3c] & 7);
      if (g_tm_debug_level < 7) goto LAB_0001470c;
      printk("offset1_type             :0x%x\n",((uint)param_2[0x3c] << 0x1a) >> 0x1d);
      goto LAB_00014d4c;
    }
LAB_00014da0:
    if (6 < g_tm_debug_level) {
      printk("offset4_type             :0x%x\n",((uint)param_2[0x3d] << 0x19) >> 0x1d);
      if (g_tm_debug_level < 7) goto LAB_0001470c;
      printk("offset5_type             :0x%x\n",(param_2[0x3e] & 3) << 1 | param_2[0x3d] >> 7);
      goto LAB_00014df4;
    }
LAB_00014e3c:
    if (6 < g_tm_debug_level) {
      printk("offset8_type             :0x%x\n",param_2[0x3f] & 7);
      if (g_tm_debug_level < 7) goto LAB_0001470c;
      printk("offset9_type             :0x%x\n",((uint)param_2[0x3f] << 0x1a) >> 0x1d);
      goto LAB_00014e84;
    }
LAB_00014ed8:
    if (6 < g_tm_debug_level) {
      printk("offset12_type            :0x%x\n",((uint)param_2[0x40] << 0x19) >> 0x1d);
      if (g_tm_debug_level < 7) goto LAB_0001470c;
      printk("offset13_type            :0x%x\n",(param_2[0x41] & 3) << 1 | param_2[0x40] >> 7);
      goto LAB_00014f2c;
    }
LAB_00014f74:
    if ((g_tm_debug_level < 7) ||
       (printk("offset16_type            :0x%x\n",param_2[0x42] & 7), g_tm_debug_level < 7))
    goto LAB_0001470c;
    printk("offset17_type            :0x%x\n",((uint)param_2[0x42] << 0x1a) >> 0x1d);
  }
  if ((6 < g_tm_debug_level) &&
     (printk("offset18_type            :0x%x\n",(param_2[0x43] & 1) << 2 | param_2[0x42] >> 6),
     6 < g_tm_debug_level)) {
    printk("offset19_type            :0x%x\n",((uint)param_2[0x43] << 0x1c) >> 0x1d);
  }
LAB_0001470c:
  if (param_1 < 0xa0) {
    if (local_2c[0] == 0) {
      uVar3 = 0;
      uVar4 = 0;
      do {
        uVar4 = uVar4 + 1;
        uVar1 = cla_get_indirect_rw_status(local_2c);
        uVar3 = uVar3 | uVar1;
        bVar5 = uVar4 == 0x13;
        if (uVar4 < 0x14) {
          bVar5 = local_2c[0] == 0;
        }
      } while (bVar5);
      if (0x13 < uVar4) {
        if (g_tm_debug_level == 0) {
          return 0xffffffff;
        }
        printk("[TM][cla_set_extra_rule_table]indirect access time out\n");
        return 0xffffffff;
      }
    }
    else {
      uVar3 = 0;
    }
    param_2 = param_2 + 0x44;
    uVar4 = cla_set_indirect_rw_cmd(0,1,param_1);
    uVar1 = 0x10;
    uVar4 = uVar4 | uVar3;
    do {
      param_2 = param_2 + -4;
      uVar3 = cla_set_indirect_rw_data(uVar1 & 0xff,*(undefined4 *)param_2);
      uVar1 = uVar1 - 1;
      uVar4 = uVar4 | uVar3;
    } while (uVar1 != 0xffffffff);
    if (uVar4 == 0) {
      uVar2 = 0;
    }
    else {
      if (g_tm_debug_level == 0) {
        return 0xffffffff;
      }
      printk("[TM][cla_set_extra_rule_table]indirect access failed\n");
      uVar2 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 1;
  }
  else {
    printk("[TM][cla_set_extra_rule_table]input invalid parameter!\n");
    uVar2 = 1;
  }
  return uVar2;
}

