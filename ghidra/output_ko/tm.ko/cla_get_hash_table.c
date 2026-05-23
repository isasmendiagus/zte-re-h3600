// module: tm.ko
// function: cla_get_hash_table @ 0x15f20
// size: 1472 bytes
//

undefined4 cla_get_hash_table(uint param_1,byte *param_2)

{
  byte bVar1;
  byte *pbVar2;
  undefined4 *puVar3;
  uint uVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  uint uVar8;
  int iVar9;
  byte *pbVar10;
  uint uVar11;
  undefined1 *puVar12;
  undefined4 uVar13;
  undefined4 *puVar14;
  bool bVar15;
  int local_68;
  undefined4 local_64 [12];
  undefined4 auStack_34 [2];
  undefined1 auStack_2c [8];
  
  local_68 = 0;
  memset(local_64,0,0x3c);
  if (6 < g_tm_debug_level) {
    printk("[TM][cla_get_hash_table]input: hash_addr = %d\n",param_1);
  }
  if (0x207 < param_1) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][cla_get_hash_table]input invalid parameter!\n");
    return 1;
  }
  if (param_1 < 0x200) {
    if (param_1 < 0x1c0) {
      if (param_1 < 0x180) {
        if (param_1 < 0x100) {
          uVar13 = 2;
          uVar5 = param_1;
        }
        else {
          uVar13 = 3;
          uVar5 = param_1 - 0x100;
        }
      }
      else {
        uVar13 = 4;
        uVar5 = param_1 - 0x180;
      }
    }
    else {
      uVar13 = 5;
      uVar5 = param_1 - 0x1c0;
    }
  }
  else {
    uVar13 = 6;
    uVar5 = param_1 - 0x200;
  }
  if (local_68 == 0) {
    uVar8 = 0;
    uVar11 = 0;
    do {
      uVar8 = uVar8 + 1;
      uVar4 = cla_get_indirect_rw_status(&local_68);
      uVar11 = uVar11 | uVar4;
      bVar15 = uVar8 == 0x13;
      if (uVar8 < 0x14) {
        bVar15 = local_68 == 0;
      }
    } while (bVar15);
    if (0x13 < uVar8) goto LAB_00016000;
  }
  else {
    uVar11 = 0;
  }
  uVar5 = cla_set_indirect_rw_cmd(1,uVar13,uVar5);
  uVar5 = uVar5 | uVar11;
  if (local_68 == 0) {
    iVar9 = 0;
    do {
      iVar9 = iVar9 + 1;
      uVar11 = cla_get_indirect_rw_status(&local_68);
      uVar5 = uVar5 | uVar11;
      if (local_68 != 0) {
        if (iVar9 != 0x14) goto LAB_0001606c;
        break;
      }
    } while (iVar9 != 0x14);
LAB_00016000:
    if (g_tm_debug_level != 0) {
      printk("[TM][cla_get_hash_table]indirect access time out\n");
    }
    return 0xffffffff;
  }
LAB_0001606c:
  puVar12 = auStack_2c;
  uVar11 = 0xe;
  do {
    uVar8 = cla_get_indirect_rw_data(uVar11 & 0xff,puVar12);
    uVar11 = uVar11 - 1;
    puVar12 = puVar12 + -4;
    uVar5 = uVar5 | uVar8;
  } while (uVar11 != 0xffffffff);
  if (uVar5 != 0) {
    if (g_tm_debug_level != 0) {
      printk("[TM][cla_get_hash_table]indirect access failed\n");
      return 0xffffffff;
    }
    return 0xffffffff;
  }
  pbVar2 = param_2;
  puVar3 = local_64;
  do {
    puVar14 = puVar3;
    pbVar10 = pbVar2;
    uVar13 = puVar14[1];
    uVar6 = puVar14[2];
    uVar7 = puVar14[3];
    *(undefined4 *)pbVar10 = *puVar14;
    *(undefined4 *)(pbVar10 + 4) = uVar13;
    *(undefined4 *)(pbVar10 + 8) = uVar6;
    *(undefined4 *)(pbVar10 + 0xc) = uVar7;
    pbVar2 = pbVar10 + 0x10;
    puVar3 = puVar14 + 4;
  } while (puVar14 + 4 != auStack_34);
  uVar13 = puVar14[5];
  uVar6 = puVar14[6];
  *(undefined4 *)(pbVar10 + 0x10) = puVar14[4];
  *(undefined4 *)(pbVar10 + 0x14) = uVar13;
  *(undefined4 *)(pbVar10 + 0x18) = uVar6;
  if (g_tm_debug_level < 7) {
    return 0;
  }
  uVar5 = (uint)*(ushort *)(param_2 + 0x35);
  printk("hash_addr = %d, windata19 = %d, windata18 =%d ,windata17 =%d\n",param_1,
         *(undefined2 *)(param_2 + 0x39),*(undefined2 *)(param_2 + 0x37),uVar5);
  if (g_tm_debug_level < 7) {
LAB_00016224:
    if (6 < g_tm_debug_level) {
      uVar5 = (uint)param_2[0x12];
      printk("windata0= %d, flow_sta_info = %d, gemport_valid = %d, tcont_high = %d\n",
             *(undefined2 *)(param_2 + 0x13),
             (uint)param_2[0x11] << 1 | (uint)(param_2[0x10] >> 7) | (uVar5 & 3) << 9,
             (uVar5 << 0x1d) >> 0x1f,(uVar5 << 0x1c) >> 0x1f);
      if (g_tm_debug_level < 7) {
        return 0;
      }
      uVar5 = (uint)param_2[0x10];
      printk("da_known= %d, valid_en = %d, direct = %d, rule_mode = %d\n",
             ((uint)param_2[0x12] << 0x1b) >> 0x1f,(uVar5 << 0x19) >> 0x1f,(uVar5 << 0x1a) >> 0x1f,
             (uVar5 << 0x1b) >> 0x1f);
      goto LAB_000162a4;
    }
LAB_00016348:
    if (g_tm_debug_level < 7) goto LAB_00016448;
    uVar11 = (param_2[0xb] & 1) << 3;
    printk("qid_dscp_en = %d, qid_dscp_ram_idx = %d\n",((uint)param_2[0xb] << 0x1e) >> 0x1f,
           uVar11 | param_2[10] >> 5,uVar11,uVar5);
    if (g_tm_debug_level < 7) {
      return 0;
    }
    bVar1 = param_2[9];
    printk("qos_rp_en = %d, qos_id = %d, adm_bucket_rp_en = %d, bucket_info = %d\n",
           ((uint)param_2[10] << 0x1b) >> 0x1f,(param_2[10] & 0xf) << 5 | (uint)(bVar1 >> 3),
           ((uint)bVar1 << 0x1d) >> 0x1f,(bVar1 & 3) << 4 | (uint)(param_2[8] >> 4));
  }
  else {
    printk("windata16 = %d, windata15 = %d, windata14 = %d, windata13 = %d\n",
           *(undefined2 *)(param_2 + 0x33),*(undefined2 *)(param_2 + 0x31),
           *(undefined2 *)(param_2 + 0x2f),*(undefined2 *)(param_2 + 0x2d));
    if (g_tm_debug_level < 7) {
      return 0;
    }
    printk("windata12 = %d, windata11 = %d, windata10 = %d, windata9 = %d\n",
           *(undefined2 *)(param_2 + 0x2b),*(undefined2 *)(param_2 + 0x29),
           *(undefined2 *)(param_2 + 0x27),*(undefined2 *)(param_2 + 0x25));
    if (6 < g_tm_debug_level) {
      printk("windata8= %d, windata7 = %d, windata6 = %d, windata5 = %d\n",
             *(undefined2 *)(param_2 + 0x23),*(undefined2 *)(param_2 + 0x21),
             *(undefined2 *)(param_2 + 0x1f),*(undefined2 *)(param_2 + 0x1d));
      if (g_tm_debug_level < 7) {
        return 0;
      }
      uVar5 = (uint)*(ushort *)(param_2 + 0x15);
      printk("windata4= %d, windata3 = %d, windata2 = %d, windata1 = %d\n",
             *(undefined2 *)(param_2 + 0x1b),*(undefined2 *)(param_2 + 0x19),
             *(undefined2 *)(param_2 + 0x17),uVar5);
      goto LAB_00016224;
    }
LAB_000162a4:
    if (6 < g_tm_debug_level) {
      uVar5 = (uint)param_2[0xf];
      printk("extr_index= %d, pppoe_flag = %d, l2_type = %d, tag_level = %d\n",
             param_2[0x10] << 4 | param_2[0xf] >> 4,(uVar5 << 0x1c) >> 0x1f,(uVar5 << 0x1d) >> 0x1e,
             (uVar5 & 1) << 2 | (uint)(param_2[0xe] >> 6));
      if (g_tm_debug_level < 7) {
        return 0;
      }
      uVar5 = ((uint)param_2[0xb] << 0x19) >> 0x1b;
      printk("inport = %d, outport = %d, flow_pri = %d, wan_id = %d\n",
             (param_2[0xe] & 0x3f) << 6 | (uint)(param_2[0xd] >> 2),
             (param_2[0xd] & 3) << 3 | param_2[0xc] >> 5,
             (param_2[0xc] & 0x1f) << 1 | param_2[0xb] >> 7,uVar5);
      goto LAB_00016348;
    }
  }
  if (g_tm_debug_level < 7) {
    return 0;
  }
  bVar1 = param_2[6];
  printk("mtu_rp_en = %d, mtu_val = %d, cpu_qid_rp_en = %d, cpu_qid = %d\n",
         ((uint)param_2[8] << 0x1c) >> 0x1f,
         (uint)param_2[7] << 3 | (uint)(bVar1 >> 5) | (param_2[8] & 7) << 0xb,
         ((uint)bVar1 << 0x1b) >> 0x1f,((uint)bVar1 << 0x1c) >> 0x1d);
  if (g_tm_debug_level < 7) {
    return 0;
  }
  bVar1 = param_2[5];
  printk("flow_rp_en = %d, vlan_rp_en = %d, modify_en = %d, pkt_len_changed = %d\n",param_2[6] & 1,
         bVar1 >> 7,((uint)bVar1 << 0x19) >> 0x1f,((uint)bVar1 << 0x1a) >> 0x1b);
LAB_00016448:
  if ((6 < g_tm_debug_level) &&
     (printk("e8_en =%d, cmd_flow_id = %d, tcnt_gpid_rp_en = %d, gemport_uni_id = %d\n",
             param_2[5] & 1,(uint)param_2[4] << 7 | (uint)(param_2[3] >> 1),param_2[3] & 1,
             (uint)param_2[2] << 4 | (uint)(param_2[1] >> 4)), 6 < g_tm_debug_level)) {
    uVar5 = (uint)*param_2;
    printk("tcont_id = %d, queue_rp_en = %d,queue_id = %d, act_rp_en = %d, act_val = %d\n",
           (param_2[1] & 0xf) << 1 | *param_2 >> 7,(uVar5 << 0x19) >> 0x1f,(uVar5 << 0x1a) >> 0x1d,
           (uVar5 << 0x1d) >> 0x1f,uVar5 & 3);
  }
  return 0;
}

