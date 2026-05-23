// module: tm.ko
// function: cla_get_external_hash_table @ 0x16578
// size: 1032 bytes
//

undefined4 cla_get_external_hash_table(uint param_1,int param_2,byte *param_3)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int unaff_r6;
  byte *pbVar7;
  int unaff_lr;
  
  iVar5 = param_2 * 2 + 0x13;
  if (iVar5 < 0) {
    iVar5 = param_2 * 2 + 0x1a;
  }
  iVar5 = iVar5 >> 3;
  iVar3 = ((param_1 & 0xffff) + 0x3c40800) * 0x40;
  if (iVar5 != -1 && -1 < iVar5 + 1) {
    iVar3 = iVar3 + 1;
    unaff_r6 = iVar5 * 8 + 7;
    unaff_lr = -1;
  }
  if (0 < iVar5 + 1) {
    do {
      iVar4 = unaff_lr + 8;
      iVar5 = iVar4;
      pbVar7 = (byte *)(iVar3 + unaff_lr);
      do {
        if (iVar5 < 0x3c) {
          param_3[iVar5] = *pbVar7;
        }
        iVar5 = iVar5 + -1;
        pbVar7 = pbVar7 + 1;
      } while (iVar5 != unaff_lr);
      unaff_lr = iVar4;
    } while (iVar4 != unaff_r6);
  }
  if ((((6 < g_tm_debug_level) &&
       (printk("hash_addr = %d, windata19 = %d, windata18 =%d ,windata17 =%d\n",param_1,
               *(undefined2 *)(param_3 + 0x39),*(undefined2 *)(param_3 + 0x37),
               *(undefined2 *)(param_3 + 0x35)), 6 < g_tm_debug_level)) &&
      (printk("windata16 = %d, windata15 = %d, windata14 = %d, windata13 = %d\n",
              *(undefined2 *)(param_3 + 0x33),*(undefined2 *)(param_3 + 0x31),
              *(undefined2 *)(param_3 + 0x2f),*(undefined2 *)(param_3 + 0x2d)), 6 < g_tm_debug_level
      )) && (((printk("windata12 = %d, windata11 = %d, windata10 = %d, windata9 = %d\n",
                      *(undefined2 *)(param_3 + 0x2b),*(undefined2 *)(param_3 + 0x29),
                      *(undefined2 *)(param_3 + 0x27),*(undefined2 *)(param_3 + 0x25)),
              6 < g_tm_debug_level &&
              (printk("windata8= %d, windata7 = %d, windata6 = %d, windata5 = %d\n",
                      *(undefined2 *)(param_3 + 0x23),*(undefined2 *)(param_3 + 0x21),
                      *(undefined2 *)(param_3 + 0x1f),*(undefined2 *)(param_3 + 0x1d)),
              6 < g_tm_debug_level)) &&
             (printk("windata4= %d, windata3 = %d, windata2 = %d, windata1 = %d\n",
                     *(undefined2 *)(param_3 + 0x1b),*(undefined2 *)(param_3 + 0x19),
                     *(undefined2 *)(param_3 + 0x17),*(undefined2 *)(param_3 + 0x15)),
             6 < g_tm_debug_level)))) {
    uVar6 = (uint)param_3[0x12];
    printk("windata0= %d, flow_sta_info = %d, gemport_valid = %d, tcont_high = %d\n",
           *(undefined2 *)(param_3 + 0x13),
           (uint)param_3[0x11] << 1 | (uint)(param_3[0x10] >> 7) | (uVar6 & 3) << 9,
           (uVar6 << 0x1d) >> 0x1f,(uVar6 << 0x1c) >> 0x1f);
    if (6 < g_tm_debug_level) {
      uVar6 = (uint)param_3[0x10];
      printk("da_known= %d, valid_en = %d, direct = %d, rule_mode = %d\n",
             ((uint)param_3[0x12] << 0x1b) >> 0x1f,(uVar6 << 0x19) >> 0x1f,(uVar6 << 0x1a) >> 0x1f,
             (uVar6 << 0x1b) >> 0x1f);
      if (6 < g_tm_debug_level) {
        uVar6 = (uint)param_3[0xf];
        printk("extr_index= %d, pppoe_flag = %d, l2_type = %d, tag_level = %d\n",
               param_3[0x10] << 4 | param_3[0xf] >> 4,(uVar6 << 0x1c) >> 0x1f,
               (uVar6 << 0x1d) >> 0x1e,(uVar6 & 1) << 2 | (uint)(param_3[0xe] >> 6));
        if (6 < g_tm_debug_level) {
          uVar6 = ((uint)param_3[0xb] << 0x19) >> 0x1b;
          printk("inport = %d, outport = %d, flow_pri = %d, wan_id = %d\n",
                 (param_3[0xe] & 0x3f) << 6 | (uint)(param_3[0xd] >> 2),
                 (param_3[0xd] & 3) << 3 | param_3[0xc] >> 5,
                 (param_3[0xc] & 0x1f) << 1 | param_3[0xb] >> 7,uVar6);
          if (((6 < g_tm_debug_level) &&
              (uVar1 = (param_3[0xb] & 1) << 3,
              printk("qid_dscp_en = %d, qid_dscp_ram_idx = %d\n",
                     ((uint)param_3[0xb] << 0x1e) >> 0x1f,uVar1 | param_3[10] >> 5,uVar1,uVar6),
              6 < g_tm_debug_level)) &&
             ((bVar2 = param_3[9],
              printk("qos_rp_en = %d, qos_id = %d, adm_bucket_rp_en = %d, bucket_info = %d\n",
                     ((uint)param_3[10] << 0x1b) >> 0x1f,
                     (param_3[10] & 0xf) << 5 | (uint)(bVar2 >> 3),((uint)bVar2 << 0x1d) >> 0x1f,
                     (bVar2 & 3) << 4 | (uint)(param_3[8] >> 4)), 6 < g_tm_debug_level &&
              (((bVar2 = param_3[6],
                printk("mtu_rp_en = %d, mtu_val = %d, cpu_qid_rp_en = %d, cpu_qid = %d\n",
                       ((uint)param_3[8] << 0x1c) >> 0x1f,
                       (uint)param_3[7] << 3 | (uint)(bVar2 >> 5) | (param_3[8] & 7) << 0xb,
                       ((uint)bVar2 << 0x1b) >> 0x1f,((uint)bVar2 << 0x1c) >> 0x1d),
                6 < g_tm_debug_level &&
                (bVar2 = param_3[5],
                printk("flow_rp_en = %d, vlan_rp_en = %d, modify_en = %d, pkt_len_changed = %d\n",
                       param_3[6] & 1,bVar2 >> 7,((uint)bVar2 << 0x19) >> 0x1f,
                       ((uint)bVar2 << 0x1a) >> 0x1b), 6 < g_tm_debug_level)) &&
               (printk("e8_en =%d, cmd_flow_id = %d, tcnt_gpid_rp_en = %d, gemport_uni_id = %d\n",
                       param_3[5] & 1,(uint)param_3[4] << 7 | (uint)(param_3[3] >> 1),param_3[3] & 1
                       ,(uint)param_3[2] << 4 | (uint)(param_3[1] >> 4)), 6 < g_tm_debug_level))))))
          {
            uVar6 = (uint)*param_3;
            printk("tcont_id = %d, queue_rp_en = %d,queue_id = %d, act_rp_en = %d, act_val = %d\n",
                   (param_3[1] & 0xf) << 1 | *param_3 >> 7,(uVar6 << 0x19) >> 0x1f,
                   (uVar6 << 0x1a) >> 0x1d,(uVar6 << 0x1d) >> 0x1f,uVar6 & 3);
          }
        }
      }
    }
  }
  return 0;
}

