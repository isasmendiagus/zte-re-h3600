// module: tm.ko
// function: cla_acl_hash_addr_gen @ 0x16cdc
// size: 1204 bytes
//

undefined4 cla_acl_hash_addr_gen(uint param_1,byte *param_2,uint *param_3)

{
  undefined4 uVar1;
  byte *pbVar2;
  byte *pbVar3;
  uint uVar4;
  uint uVar5;
  byte abStack_55 [49];
  
  memset(abStack_55,0,0x2d);
  if ((6 < g_tm_debug_level) &&
     (printk("[TM][cla_acl_hash_addr_gen]input: \n"), 6 < g_tm_debug_level)) {
    uVar4 = (uint)param_2[2];
    uVar5 = (uVar4 << 0x1a) >> 0x1e;
    printk("hash_mode = %d,outport = %d , inport = %d,tag_level = %d,l2_type = %d \n",param_1,
           *param_2 & 0x1f,(uint)param_2[1] << 3 | (uint)(*param_2 >> 5) | (uVar4 & 1) << 0xb,
           (uVar4 << 0x1c) >> 0x1d,uVar5);
    if (((6 < g_tm_debug_level) &&
        (((printk("  pppoe_flag = %d,ex_rule_id = %d,ex_rule_mode = %d,direct = %d\n",
                  ((uint)param_2[2] << 0x19) >> 0x1f,param_2[3] << 1 | param_2[2] >> 7,
                  param_2[3] >> 7,param_2[4] & 1,uVar5), 6 < g_tm_debug_level &&
          (printk("extra_data0 = %d, extra_data1 = %d, extra_data2 = %d, extra_data3 = %d, extra_data4 = %d\n"
                  ,(uint)param_2[5] << 7 | (uint)(param_2[4] >> 1) | (param_2[6] & 1) << 0xf,
                  (uint)param_2[7] << 7 | (uint)(param_2[6] >> 1) | (param_2[8] & 1) << 0xf,
                  (uint)param_2[9] << 7 | (uint)(param_2[8] >> 1) | (param_2[10] & 1) << 0xf,
                  (uint)param_2[0xb] << 7 | (uint)(param_2[10] >> 1) | (param_2[0xc] & 1) << 0xf,
                  (uint)param_2[0xd] << 7 | (uint)(param_2[0xc] >> 1) | (param_2[0xe] & 1) << 0xf),
          6 < g_tm_debug_level)) &&
         (printk("extra_data5 = %d, extra_data6 = %d, extra_data7 = %d, extra_data8 = %d, extra_data9 = %d\n"
                 ,(uint)param_2[0xf] << 7 | (uint)(param_2[0xe] >> 1) | (param_2[0x10] & 1) << 0xf,
                 (uint)param_2[0x11] << 7 | (uint)(param_2[0x10] >> 1) | (param_2[0x12] & 1) << 0xf,
                 (uint)param_2[0x13] << 7 | (uint)(param_2[0x12] >> 1) | (param_2[0x14] & 1) << 0xf,
                 (uint)param_2[0x15] << 7 | (uint)(param_2[0x14] >> 1) | (param_2[0x16] & 1) << 0xf,
                 (uint)param_2[0x17] << 7 | (uint)(param_2[0x16] >> 1) | (param_2[0x18] & 1) << 0xf)
         , 6 < g_tm_debug_level)))) &&
       (printk("extra_data10 = %d, extra_data11 = %d, extra_data12 = %d, extra_data13 = %d, extra_data14 = %d\n"
               ,(uint)param_2[0x19] << 7 | (uint)(param_2[0x18] >> 1) | (param_2[0x1a] & 1) << 0xf,
               (uint)param_2[0x1b] << 7 | (uint)(param_2[0x1a] >> 1) | (param_2[0x1c] & 1) << 0xf,
               (uint)param_2[0x1d] << 7 | (uint)(param_2[0x1c] >> 1) | (param_2[0x1e] & 1) << 0xf,
               (uint)param_2[0x1f] << 7 | (uint)(param_2[0x1e] >> 1) | (param_2[0x20] & 1) << 0xf,
               (uint)param_2[0x21] << 7 | (uint)(param_2[0x20] >> 1) | (param_2[0x22] & 1) << 0xf),
       6 < g_tm_debug_level)) {
      printk("extra_data15 = %d, extra_data16 = %d, extra_data17 = %d, extra_data18 = %d, extra_data19 = %d\n"
             ,(uint)param_2[0x23] << 7 | (uint)(param_2[0x22] >> 1) | (param_2[0x24] & 1) << 0xf,
             (uint)param_2[0x25] << 7 | (uint)(param_2[0x24] >> 1) | (param_2[0x26] & 1) << 0xf,
             (uint)param_2[0x27] << 7 | (uint)(param_2[0x26] >> 1) | (param_2[0x28] & 1) << 0xf,
             (uint)param_2[0x29] << 7 | (uint)(param_2[0x28] >> 1) | (param_2[0x2a] & 1) << 0xf,
             (uint)param_2[0x2b] << 7 | (uint)(param_2[0x2a] >> 1) | (param_2[0x2c] & 1) << 0xf);
    }
  }
  if (param_1 < 4) {
    pbVar3 = param_2 + -1;
    pbVar2 = abStack_55 + 0x2d;
    do {
      pbVar3 = pbVar3 + 1;
      pbVar2 = pbVar2 + -1;
      *pbVar2 = *pbVar3;
    } while (pbVar3 != param_2 + 0x2c);
    if (param_1 == 2) {
      uVar4 = 0;
      pbVar2 = abStack_55;
      do {
        pbVar3 = pbVar2 + 1;
        uVar4 = *(uint *)(crctable_F4ACFB13 + ((uint)*pbVar2 ^ uVar4 >> 0x18) * 4) ^ uVar4 << 8;
        pbVar2 = pbVar3;
      } while (pbVar3 != abStack_55 + 0x2d);
    }
    else if (param_1 == 3) {
      uVar4 = 0;
      pbVar2 = abStack_55;
      do {
        pbVar3 = pbVar2 + 1;
        uVar4 = *(uint *)(crctable_32583499 + ((uint)*pbVar2 ^ uVar4 >> 0x18) * 4) ^ uVar4 << 8;
        pbVar2 = pbVar3;
      } while (pbVar3 != abStack_55 + 0x2d);
    }
    else {
      uVar4 = 0;
      pbVar2 = abStack_55;
      if (param_1 == 1) {
        do {
          pbVar3 = pbVar2 + 1;
          uVar4 = *(uint *)(crctable_1EDC6F41 + ((uint)*pbVar2 ^ uVar4 >> 0x18) * 4) ^ uVar4 << 8;
          pbVar2 = pbVar3;
        } while (pbVar3 != abStack_55 + 0x2d);
      }
      else {
        do {
          pbVar3 = pbVar2 + 1;
          uVar4 = *(uint *)(crctable_04C11DB7 + ((uint)*pbVar2 ^ uVar4 >> 0x18) * 4) ^ uVar4 << 8;
          pbVar2 = pbVar3;
        } while (pbVar3 != abStack_55 + 0x2d);
      }
    }
    *param_3 = uVar4 & 0xffff;
    if (g_tm_debug_level < 7) {
      uVar1 = 0;
    }
    else {
      printk("[TM][cla_acl_hash_addr_gen] hash_addr = %x\n");
      uVar1 = 0;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][cla_acl_hash_addr_gen]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

