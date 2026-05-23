// module: tm.ko
// function: cla_set_hash_table @ 0x15a14
// size: 1292 bytes
//

undefined4 cla_set_hash_table(uint param_1,byte *param_2)

{
  byte bVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  bool bVar6;
  int local_24 [2];
  
  local_24[0] = 0;
  if (g_tm_debug_level < 7) goto LAB_00015a40;
  printk("[TM][cla_set_hash_table]input: \n");
  if (g_tm_debug_level < 7) {
LAB_00015c14:
    if (6 < g_tm_debug_level) {
      printk("windata4= %d, windata3 = %d, windata2 = %d, windata1 = %d\n",
             *(undefined2 *)(param_2 + 0x1b),*(undefined2 *)(param_2 + 0x19),
             *(undefined2 *)(param_2 + 0x17),*(undefined2 *)(param_2 + 0x15));
      if (g_tm_debug_level < 7) goto LAB_00015a40;
      uVar4 = (uint)param_2[0x12];
      printk("windata0= %d, flow_sta_info = %d, gemport_valid = %d, tcont_high = %d\n",
             *(undefined2 *)(param_2 + 0x13),
             (uint)param_2[0x11] << 1 | (uint)(param_2[0x10] >> 7) | (uVar4 & 3) << 9,
             (uVar4 << 0x1d) >> 0x1f,(uVar4 << 0x1c) >> 0x1f);
      goto LAB_00015c8c;
    }
LAB_00015d10:
    if (6 < g_tm_debug_level) {
      uVar4 = ((uint)param_2[0xb] << 0x19) >> 0x1b;
      printk("inport = %d, outport = %d, flow_pri = %d, wan_id = %d\n",
             (param_2[0xe] & 0x3f) << 6 | (uint)(param_2[0xd] >> 2),
             (param_2[0xd] & 3) << 3 | param_2[0xc] >> 5,
             (param_2[0xc] & 0x1f) << 1 | param_2[0xb] >> 7,uVar4);
      if (g_tm_debug_level < 7) goto LAB_00015a40;
      uVar5 = (param_2[0xb] & 1) << 3;
      printk("qid_dscp_en = %d, qid_dscp_ram_idx = %d\n",((uint)param_2[0xb] << 0x1e) >> 0x1f,
             uVar5 | param_2[10] >> 5,uVar5,uVar4);
      goto LAB_00015d9c;
    }
LAB_00015e30:
    if ((g_tm_debug_level < 7) ||
       (bVar1 = param_2[5],
       printk("flow_rp_en = %d, vlan_rp_en = %d, modify_en = %d, pkt_len_changed = %d\n",
              param_2[6] & 1,bVar1 >> 7,((uint)bVar1 << 0x19) >> 0x1f,((uint)bVar1 << 0x1a) >> 0x1b)
       , g_tm_debug_level < 7)) goto LAB_00015a40;
    printk("e8_en =%d, cmd_flow_id = %d, tcnt_gpid_rp_en = %d, gemport_uni_id = %d\n",param_2[5] & 1
           ,(uint)param_2[4] << 7 | (uint)(param_2[3] >> 1),param_2[3] & 1,
           (uint)param_2[2] << 4 | (uint)(param_2[1] >> 4));
  }
  else {
    printk("hash_addr = %d, windata19 = %d, windata18 =%d ,windata17 =%d\n",param_1,
           *(undefined2 *)(param_2 + 0x39),*(undefined2 *)(param_2 + 0x37),
           *(undefined2 *)(param_2 + 0x35));
    if (g_tm_debug_level < 7) goto LAB_00015a40;
    printk("windata16 = %d, windata15 = %d, windata14 = %d, windata13 = %d\n",
           *(undefined2 *)(param_2 + 0x33),*(undefined2 *)(param_2 + 0x31),
           *(undefined2 *)(param_2 + 0x2f),*(undefined2 *)(param_2 + 0x2d));
    if (6 < g_tm_debug_level) {
      printk("windata12 = %d, windata11 = %d, windata10 = %d, windata9 = %d\n",
             *(undefined2 *)(param_2 + 0x2b),*(undefined2 *)(param_2 + 0x29),
             *(undefined2 *)(param_2 + 0x27),*(undefined2 *)(param_2 + 0x25));
      if (g_tm_debug_level < 7) goto LAB_00015a40;
      printk("windata8= %d, windata7 = %d, windata6 = %d, windata5 = %d\n",
             *(undefined2 *)(param_2 + 0x23),*(undefined2 *)(param_2 + 0x21),
             *(undefined2 *)(param_2 + 0x1f),*(undefined2 *)(param_2 + 0x1d));
      goto LAB_00015c14;
    }
LAB_00015c8c:
    if (6 < g_tm_debug_level) {
      uVar4 = (uint)param_2[0x10];
      printk("da_known= %d, valid_en = %d, direct = %d, rule_mode = %d\n",
             ((uint)param_2[0x12] << 0x1b) >> 0x1f,(uVar4 << 0x19) >> 0x1f,(uVar4 << 0x1a) >> 0x1f,
             (uVar4 << 0x1b) >> 0x1f);
      if (g_tm_debug_level < 7) goto LAB_00015a40;
      uVar4 = (uint)param_2[0xf];
      printk("extr_index= %d, pppoe_flag = %d, l2_type = %d, tag_level = %d\n",
             param_2[0x10] << 4 | param_2[0xf] >> 4,(uVar4 << 0x1c) >> 0x1f,(uVar4 << 0x1d) >> 0x1e,
             (uVar4 & 1) << 2 | (uint)(param_2[0xe] >> 6));
      goto LAB_00015d10;
    }
LAB_00015d9c:
    if (6 < g_tm_debug_level) {
      bVar1 = param_2[9];
      printk("qos_rp_en = %d, qos_id = %d, adm_bucket_rp_en = %d, bucket_info = %d\n",
             ((uint)param_2[10] << 0x1b) >> 0x1f,(param_2[10] & 0xf) << 5 | (uint)(bVar1 >> 3),
             ((uint)bVar1 << 0x1d) >> 0x1f,(bVar1 & 3) << 4 | (uint)(param_2[8] >> 4));
      if (g_tm_debug_level < 7) goto LAB_00015a40;
      bVar1 = param_2[6];
      printk("mtu_rp_en = %d, mtu_val = %d, cpu_qid_rp_en = %d, cpu_qid = %d\n",
             ((uint)param_2[8] << 0x1c) >> 0x1f,
             (uint)param_2[7] << 3 | (uint)(bVar1 >> 5) | (param_2[8] & 7) << 0xb,
             ((uint)bVar1 << 0x1b) >> 0x1f,((uint)bVar1 << 0x1c) >> 0x1d);
      goto LAB_00015e30;
    }
  }
  if (6 < g_tm_debug_level) {
    uVar4 = (uint)*param_2;
    printk("tcont_id = %d, queue_rp_en = %d,queue_id = %d, act_rp_en = %d, act_val = %d\n",
           (param_2[1] & 0xf) << 1 | *param_2 >> 7,(uVar4 << 0x19) >> 0x1f,(uVar4 << 0x1a) >> 0x1d,
           (uVar4 << 0x1d) >> 0x1f,uVar4 & 3);
  }
LAB_00015a40:
  if (param_1 < 0x208) {
    if (local_24[0] == 0) {
      uVar4 = 0;
      uVar5 = 0;
      do {
        uVar5 = uVar5 + 1;
        uVar2 = cla_get_indirect_rw_status(local_24);
        uVar4 = uVar4 | uVar2;
        bVar6 = uVar5 == 0x13;
        if (uVar5 < 0x14) {
          bVar6 = local_24[0] == 0;
        }
      } while (bVar6);
      if (0x13 < uVar5) {
        if (g_tm_debug_level == 0) {
          return 0xffffffff;
        }
        printk("[TM][cla_set_hash_table]indirect access time out\n");
        return 0xffffffff;
      }
    }
    else {
      uVar4 = 0;
    }
    if (param_1 < 0x200) {
      if (param_1 < 0x1c0) {
        if (param_1 < 0x180) {
          if (param_1 < 0x100) {
            uVar3 = 2;
          }
          else {
            param_1 = param_1 - 0x100;
            uVar3 = 3;
          }
        }
        else {
          param_1 = param_1 - 0x180;
          uVar3 = 4;
        }
      }
      else {
        param_1 = param_1 - 0x1c0;
        uVar3 = 5;
      }
    }
    else {
      param_1 = param_1 - 0x200;
      uVar3 = 6;
    }
    uVar5 = cla_set_indirect_rw_cmd(0,uVar3,param_1);
    param_2 = param_2 + 0x3c;
    uVar2 = 0xe;
    uVar5 = uVar5 | uVar4;
    do {
      param_2 = param_2 + -4;
      uVar4 = cla_set_indirect_rw_data(uVar2 & 0xff,*(undefined4 *)param_2);
      uVar2 = uVar2 - 1;
      uVar5 = uVar5 | uVar4;
    } while (uVar2 != 0xffffffff);
    if (uVar5 == 0) {
      uVar3 = 0;
    }
    else {
      if (g_tm_debug_level == 0) {
        return 0xffffffff;
      }
      printk("[TM][cla_set_hash_table]indirect access failed\n");
      uVar3 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar3 = 1;
  }
  else {
    printk("[TM][cla_set_hash_table]input invalid parameter!\n");
    uVar3 = 1;
  }
  return uVar3;
}

