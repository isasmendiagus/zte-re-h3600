// module: tm.ko
// function: cla_get_extra_rule_table @ 0x15038
// size: 2524 bytes
//

undefined4 cla_get_extra_rule_table(uint param_1,byte *param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined1 *puVar5;
  bool bVar6;
  int local_70;
  undefined1 auStack_6c [64];
  undefined1 auStack_2c [8];
  
  local_70 = 0;
  memset(auStack_6c,0,0x44);
  if (6 < g_tm_debug_level) {
    printk("[TM][cla_get_extra_rule_table]input: rule_id = %d\n",param_1);
  }
  if (0x9f < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][cla_get_extra_rule_table]input invalid parameter!\n");
    return 1;
  }
  if (local_70 == 0) {
    uVar2 = 0;
    uVar4 = 0;
    do {
      uVar2 = uVar2 + 1;
      uVar1 = cla_get_indirect_rw_status(&local_70);
      uVar4 = uVar4 | uVar1;
      bVar6 = uVar2 == 0x13;
      if (uVar2 < 0x14) {
        bVar6 = local_70 == 0;
      }
    } while (bVar6);
    if (0x13 < uVar2) goto LAB_000150bc;
  }
  else {
    uVar4 = 0;
  }
  uVar2 = cla_set_indirect_rw_cmd(1,1,param_1);
  uVar2 = uVar2 | uVar4;
  if (local_70 == 0) {
    iVar3 = 0;
    do {
      iVar3 = iVar3 + 1;
      uVar4 = cla_get_indirect_rw_status(&local_70);
      uVar2 = uVar2 | uVar4;
      if (local_70 != 0) {
        if (iVar3 != 0x14) goto LAB_00015140;
        break;
      }
    } while (iVar3 != 0x14);
LAB_000150bc:
    if (g_tm_debug_level != 0) {
      printk("[TM][cla_get_extra_rule_table]indirect access time out\n");
    }
    return 0xffffffff;
  }
LAB_00015140:
  puVar5 = auStack_2c;
  uVar4 = 0x10;
  do {
    uVar1 = cla_get_indirect_rw_data(uVar4 & 0xff,puVar5);
    uVar4 = uVar4 - 1;
    puVar5 = puVar5 + -4;
    uVar2 = uVar2 | uVar1;
  } while (uVar4 != 0xffffffff);
  if (uVar2 != 0) {
    if (g_tm_debug_level != 0) {
      printk("[TM][cla_get_extra_rule_table]indirect access failed\n");
      return 0xffffffff;
    }
    return 0xffffffff;
  }
  memcpy(param_2,auStack_6c,0x44);
  if (g_tm_debug_level < 7) {
    return 0;
  }
  printk("[TM][cla_get_extra_rule_table]onput:\n");
  if (g_tm_debug_level < 7) {
LAB_00015340:
    if (6 < g_tm_debug_level) {
      printk("winoffset14 = %d, winoffset15 = %d, winoffset16 = %d, winoffset17 = %d\n",
             (param_2[0xd] & 1) << 6 | param_2[0xc] >> 2,param_2[0xd] >> 1,param_2[0xe] & 0x7f,
             (param_2[0xf] & 0x3f) << 1 | param_2[0xe] >> 7);
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("winoffset18 = %d, winoffset19 = %d, winmask0 = %d, winmask1 = %d\n",
             (param_2[0x10] & 0x1f) << 2 | param_2[0xf] >> 6,
             (param_2[0x11] & 0xf) << 3 | param_2[0x10] >> 5,
             (uint)param_2[0x12] << 4 | (uint)(param_2[0x11] >> 4) | (param_2[0x13] & 0xf) << 0xc,
             (uint)param_2[0x14] << 4 | (uint)(param_2[0x13] >> 4) | (param_2[0x15] & 0xf) << 0xc);
      goto LAB_00015404;
    }
LAB_0001550c:
    if (6 < g_tm_debug_level) {
      printk("winmask10 = %d, winmask11 = %d, winmask12 = %d, winmask13 = %d\n",
             (uint)param_2[0x26] << 4 | (uint)(param_2[0x25] >> 4) | (param_2[0x27] & 0xf) << 0xc,
             (uint)param_2[0x28] << 4 | (uint)(param_2[0x27] >> 4) | (param_2[0x29] & 0xf) << 0xc,
             (uint)param_2[0x2a] << 4 | (uint)(param_2[0x29] >> 4) | (param_2[0x2b] & 0xf) << 0xc,
             (uint)param_2[0x2c] << 4 | (uint)(param_2[0x2b] >> 4) | (param_2[0x2d] & 0xf) << 0xc);
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("winmask14 = %d, winmask15 = %d, winmask16 = %d, winmask17 = %d\n",
             (uint)param_2[0x2e] << 4 | (uint)(param_2[0x2d] >> 4) | (param_2[0x2f] & 0xf) << 0xc,
             (uint)param_2[0x30] << 4 | (uint)(param_2[0x2f] >> 4) | (param_2[0x31] & 0xf) << 0xc,
             (uint)param_2[0x32] << 4 | (uint)(param_2[0x31] >> 4) | (param_2[0x33] & 0xf) << 0xc,
             (uint)param_2[0x34] << 4 | (uint)(param_2[0x33] >> 4) | (param_2[0x35] & 0xf) << 0xc);
      goto LAB_00015614;
    }
LAB_000156a8:
    if (6 < g_tm_debug_level) {
      printk("rule_mode = %d, hash_len = %d, mem_ctrl = %d\n ",((uint)param_2[0x3a] << 0x1c) >> 0x1f
             ,(param_2[0x3b] & 1) << 4 | (uint)(param_2[0x3a] >> 4),
             ((uint)param_2[0x3b] << 0x1e) >> 0x1f);
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("cvlan_mask               :0x%x\n",((uint)param_2[0x3b] << 0x1d) >> 0x1f);
      goto LAB_00015704;
    }
LAB_0001574c:
    if (6 < g_tm_debug_level) {
      printk("offset2_type             :0x%x\n",(param_2[0x3d] & 1) << 2 | param_2[0x3c] >> 6);
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("offset3_type             :0x%x\n",((uint)param_2[0x3d] << 0x1c) >> 0x1d);
      goto LAB_000157a0;
    }
LAB_000157f4:
    if (6 < g_tm_debug_level) {
      printk("offset6_type             :0x%x\n",((uint)param_2[0x3e] << 0x1b) >> 0x1d);
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("offset7_type             :0x%x\n",param_2[0x3e] >> 5);
      goto LAB_0001583c;
    }
LAB_00015884:
    if (6 < g_tm_debug_level) {
      printk("offset10_type            :0x%x\n",(param_2[0x40] & 1) << 2 | param_2[0x3f] >> 6);
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("offset11_type            :0x%x\n",((uint)param_2[0x40] << 0x1c) >> 0x1d);
      goto LAB_000158d8;
    }
LAB_0001592c:
    if (g_tm_debug_level < 7) goto LAB_000159bc;
    printk("offset14_type            :0x%x\n",((uint)param_2[0x41] << 0x1b) >> 0x1d);
    if (g_tm_debug_level < 7) {
      return 0;
    }
    printk("offset15_type            :0x%x\n",param_2[0x41] >> 5);
  }
  else {
    printk("rule_id = %d, winoffset0 = %d, winoffset1 = %d\n",param_1,*param_2 & 0x7f,
           (param_2[1] & 0x3f) << 1 | *param_2 >> 7);
    if (g_tm_debug_level < 7) {
      return 0;
    }
    printk("winoffset2 = %d, winoffset3 = %d, winoffset4 = %d, winoffset5 = %d\n",
           (param_2[2] & 0x1f) << 2 | param_2[1] >> 6,(param_2[3] & 0xf) << 3 | param_2[2] >> 5,
           (param_2[4] & 7) << 4 | param_2[3] >> 4,(param_2[5] & 3) << 5 | param_2[4] >> 3);
    if (6 < g_tm_debug_level) {
      printk("winoffset6 = %d, winoffset7 = %d, winoffset8 = %d, winoffset9 = %d\n",
             (param_2[6] & 1) << 6 | param_2[5] >> 2,param_2[6] >> 1,param_2[7] & 0x7f,
             (param_2[8] & 0x3f) << 1 | param_2[7] >> 7);
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("winoffset10 = %d, winoffset11 = %d, winoffset12 = %d, winoffset13 = %d\n",
             (param_2[9] & 0x1f) << 2 | param_2[8] >> 6,(param_2[10] & 0xf) << 3 | param_2[9] >> 5,
             (param_2[0xb] & 7) << 4 | param_2[10] >> 4,(param_2[0xc] & 3) << 5 | param_2[0xb] >> 3)
      ;
      goto LAB_00015340;
    }
LAB_00015404:
    if (6 < g_tm_debug_level) {
      printk("winmask2 = %d, winmask3 = %d, winmask4 = %d, winmask5 = %d\n",
             (uint)param_2[0x16] << 4 | (uint)(param_2[0x15] >> 4) | (param_2[0x17] & 0xf) << 0xc,
             (uint)param_2[0x18] << 4 | (uint)(param_2[0x17] >> 4) | (param_2[0x19] & 0xf) << 0xc,
             (uint)param_2[0x1a] << 4 | (uint)(param_2[0x19] >> 4) | (param_2[0x1b] & 0xf) << 0xc,
             (uint)param_2[0x1c] << 4 | (uint)(param_2[0x1b] >> 4) | (param_2[0x1d] & 0xf) << 0xc);
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("winmask6 = %d, winmask7 = %d, winmask8 = %d, winmask9 = %d\n",
             (uint)param_2[0x1e] << 4 | (uint)(param_2[0x1d] >> 4) | (param_2[0x1f] & 0xf) << 0xc,
             (uint)param_2[0x20] << 4 | (uint)(param_2[0x1f] >> 4) | (param_2[0x21] & 0xf) << 0xc,
             (uint)param_2[0x22] << 4 | (uint)(param_2[0x21] >> 4) | (param_2[0x23] & 0xf) << 0xc,
             (uint)param_2[0x24] << 4 | (uint)(param_2[0x23] >> 4) | (param_2[0x25] & 0xf) << 0xc);
      goto LAB_0001550c;
    }
LAB_00015614:
    if (6 < g_tm_debug_level) {
      uVar4 = (uint)param_2[0x39];
      printk("windmask18 = %d, winmask19 = %d, outport_mask = %d,inport_mask= %d\n",
             (uint)param_2[0x36] << 4 | (uint)(param_2[0x35] >> 4) | (param_2[0x37] & 0xf) << 0xc,
             (uint)param_2[0x38] << 4 | (uint)(param_2[0x37] >> 4) | (uVar4 & 0xf) << 0xc,
             (uVar4 << 0x1b) >> 0x1f,(uVar4 << 0x1a) >> 0x1f);
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("taglevel_mask = %d, l2info_mask = %d, pppoe_mask= %d,no_match_act = %d\n",
             ((uint)param_2[0x39] << 0x19) >> 0x1f,param_2[0x39] >> 7,param_2[0x3a] & 1,
             ((uint)param_2[0x3a] << 0x1d) >> 0x1e);
      goto LAB_000156a8;
    }
LAB_00015704:
    if (6 < g_tm_debug_level) {
      printk("offset0_type             :0x%x\n",param_2[0x3c] & 7);
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("offset1_type             :0x%x\n",((uint)param_2[0x3c] << 0x1a) >> 0x1d);
      goto LAB_0001574c;
    }
LAB_000157a0:
    if (6 < g_tm_debug_level) {
      printk("offset4_type             :0x%x\n",((uint)param_2[0x3d] << 0x19) >> 0x1d);
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("offset5_type             :0x%x\n",(param_2[0x3e] & 3) << 1 | param_2[0x3d] >> 7);
      goto LAB_000157f4;
    }
LAB_0001583c:
    if (6 < g_tm_debug_level) {
      printk("offset8_type             :0x%x\n",param_2[0x3f] & 7);
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("offset9_type             :0x%x\n",((uint)param_2[0x3f] << 0x1a) >> 0x1d);
      goto LAB_00015884;
    }
LAB_000158d8:
    if (6 < g_tm_debug_level) {
      printk("offset12_type            :0x%x\n",((uint)param_2[0x40] << 0x19) >> 0x1d);
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("offset13_type            :0x%x\n",(param_2[0x41] & 3) << 1 | param_2[0x40] >> 7);
      goto LAB_0001592c;
    }
  }
  if (g_tm_debug_level < 7) {
    return 0;
  }
  printk("offset16_type            :0x%x\n",param_2[0x42] & 7);
  if (g_tm_debug_level < 7) {
    return 0;
  }
  printk("offset17_type            :0x%x\n",((uint)param_2[0x42] << 0x1a) >> 0x1d);
LAB_000159bc:
  if ((6 < g_tm_debug_level) &&
     (printk("offset18_type            :0x%x\n",(param_2[0x43] & 1) << 2 | param_2[0x42] >> 6),
     6 < g_tm_debug_level)) {
    printk("offset19_type            :0x%x\n",((uint)param_2[0x43] << 0x1c) >> 0x1d);
  }
  return 0;
}

