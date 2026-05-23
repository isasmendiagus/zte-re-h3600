// module: tm.ko
// function: aclGetAvailableHashAddr.constprop.13 @ 0x5bbe4
// size: 1724 bytes
//

undefined4 aclGetAvailableHashAddr_constprop_13(int param_1,byte *param_2,int param_3,uint *param_4)

{
  int iVar1;
  char *pcVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  undefined4 *puVar8;
  uint uVar9;
  uint local_2c [2];
  
  uVar6 = 0;
  local_2c[0] = 0;
  if (param_1 == 1) {
    cla_get_outspace_cfg(&ACL_OUT_HASH_NUM,&ACL_OUT_SPACE_SEL);
    uVar4 = 1 << (2U - ACL_OUT_HASH_NUM & 0xff);
    uVar5 = 6 - ACL_OUT_SPACE_SEL;
    if (uVar4 != 0) {
      puVar8 = (undefined4 *)(param_3 + 0xc);
      do {
        puVar8 = puVar8 + 1;
        iVar7 = cla_acl_hash_addr_gen(*puVar8,param_2,local_2c);
        if (iVar7 != 0) {
          uVar3 = 0x717;
          goto LAB_0005be68;
        }
        if (TM_CLA_DEBUG != 0) {
          printk("l_tmpHashAddr:0x%x\n",local_2c[0]);
          printk("outport:          0x%x\n",*param_2 & 0x1f);
          printk("inport:           0x%x\n",
                 (uint)param_2[1] << 3 | (uint)(*param_2 >> 5) | (param_2[2] & 1) << 0xb);
          printk("tag_level:        0x%x\n",((uint)param_2[2] << 0x1c) >> 0x1d);
          printk("l2_type:          0x%x\n",((uint)param_2[2] << 0x1a) >> 0x1e);
          printk("pppoe_flag:       0x%x\n",((uint)param_2[2] << 0x19) >> 0x1f);
          printk("ex_rule_id:       0x%x\n",param_2[3] << 1 | param_2[2] >> 7);
          printk("ex_rule_mode:     0x%x\n",param_2[3] >> 7);
          printk("direct:           0x%x\n",param_2[4] & 1);
          printk("extra_data0:      0x%x\n",
                 (uint)param_2[5] << 7 | (uint)(param_2[4] >> 1) | (param_2[6] & 1) << 0xf);
          printk("extra_data1:      0x%x\n",
                 (uint)param_2[7] << 7 | (uint)(param_2[6] >> 1) | (param_2[8] & 1) << 0xf);
          printk("extra_data2:      0x%x\n",
                 (uint)param_2[9] << 7 | (uint)(param_2[8] >> 1) | (param_2[10] & 1) << 0xf);
          printk("extra_data3:      0x%x\n",
                 (uint)param_2[0xb] << 7 | (uint)(param_2[10] >> 1) | (param_2[0xc] & 1) << 0xf);
          printk("extra_data4:      0x%x\n",
                 (uint)param_2[0xd] << 7 | (uint)(param_2[0xc] >> 1) | (param_2[0xe] & 1) << 0xf);
          printk("extra_data5:      0x%x\n",
                 (uint)param_2[0xf] << 7 | (uint)(param_2[0xe] >> 1) | (param_2[0x10] & 1) << 0xf);
          printk("extra_data6:      0x%x\n",
                 (uint)param_2[0x11] << 7 | (uint)(param_2[0x10] >> 1) | (param_2[0x12] & 1) << 0xf)
          ;
          printk("extra_data7:      0x%x\n",
                 (uint)param_2[0x13] << 7 | (uint)(param_2[0x12] >> 1) | (param_2[0x14] & 1) << 0xf)
          ;
          printk("extra_data8:      0x%x\n",
                 (uint)param_2[0x15] << 7 | (uint)(param_2[0x14] >> 1) | (param_2[0x16] & 1) << 0xf)
          ;
          printk("extra_data9:      0x%x\n",
                 (uint)param_2[0x17] << 7 | (uint)(param_2[0x16] >> 1) | (param_2[0x18] & 1) << 0xf)
          ;
          printk("extra_data10:     0x%x\n",
                 (uint)param_2[0x19] << 7 | (uint)(param_2[0x18] >> 1) | (param_2[0x1a] & 1) << 0xf)
          ;
          printk("extra_data11:     0x%x\n",
                 (uint)param_2[0x1b] << 7 | (uint)(param_2[0x1a] >> 1) | (param_2[0x1c] & 1) << 0xf)
          ;
          printk("extra_data12:     0x%x\n",
                 (uint)param_2[0x1d] << 7 | (uint)(param_2[0x1c] >> 1) | (param_2[0x1e] & 1) << 0xf)
          ;
          printk("extra_data13:     0x%x\n",
                 (uint)param_2[0x1f] << 7 | (uint)(param_2[0x1e] >> 1) | (param_2[0x20] & 1) << 0xf)
          ;
          printk("extra_data14:     0x%x\n",
                 (uint)param_2[0x21] << 7 | (uint)(param_2[0x20] >> 1) | (param_2[0x22] & 1) << 0xf)
          ;
          printk("extra_data15:     0x%x\n",
                 (uint)param_2[0x23] << 7 | (uint)(param_2[0x22] >> 1) | (param_2[0x24] & 1) << 0xf)
          ;
          printk("extra_data16:     0x%x\n",
                 (uint)param_2[0x25] << 7 | (uint)(param_2[0x24] >> 1) | (param_2[0x26] & 1) << 0xf)
          ;
          printk("extra_data17:     0x%x\n",
                 (uint)param_2[0x27] << 7 | (uint)(param_2[0x26] >> 1) | (param_2[0x28] & 1) << 0xf)
          ;
          printk("extra_data18:     0x%x\n",
                 (uint)param_2[0x29] << 7 | (uint)(param_2[0x28] >> 1) | (param_2[0x2a] & 1) << 0xf)
          ;
          printk("extra_data19:     0x%x\n",
                 (uint)param_2[0x2b] << 7 | (uint)(param_2[0x2a] >> 1) | (param_2[0x2c] & 1) << 0xf)
          ;
        }
        uVar9 = (0x400 << (uVar5 & 0xff)) - 1;
        local_2c[0] = local_2c[0] & uVar9 & uVar9 >> (2U - ACL_OUT_HASH_NUM & 0xff);
        uVar9 = uVar6 | local_2c[0] << (2U - ACL_OUT_HASH_NUM & 0xff);
        *param_4 = uVar9;
        if (s_aclHashUsedCnt[(uVar9 & 0xffff) + 0x208] == '\0') {
          *param_4 = uVar9 | 0x80010000;
          break;
        }
        uVar6 = uVar6 + 1;
      } while (uVar4 != uVar6);
    }
  }
  else {
    if (param_1 == 0) {
      puVar8 = (undefined4 *)(param_3 + -4);
      iVar7 = 1;
      do {
        puVar8 = puVar8 + 1;
        iVar1 = cla_acl_hash_addr_gen(*puVar8,param_2,local_2c);
        if (iVar1 != 0) {
          uVar3 = 0x6d4;
LAB_0005be68:
          printk("ERROR:(%s:%d)","tm_acl_v2.c",uVar3);
          printk("cla_acl_hash_addr_gen fail\n");
          return 0xfffffff4;
        }
        if (TM_CLA_DEBUG != 0) {
          printk("l_tmpHashAddr:0x%x\n",local_2c[0]);
        }
        if (uVar6 == 0) {
          *param_4 = local_2c[0] & 0xff;
LAB_0005be2c:
          uVar5 = *param_4;
          if (s_aclHashUsedCnt[uVar5 & 0x3ff] == '\0') {
LAB_0005be48:
            *param_4 = uVar5 | 0x80000000;
            goto joined_r0x0005be10;
          }
        }
        else {
          if (uVar6 == 1) {
            *param_4 = (local_2c[0] & 0x7f) + 0x100;
            goto LAB_0005be2c;
          }
          uVar4 = local_2c[0] & 0x3f;
          if (uVar6 == 2) {
            *param_4 = uVar4 + 0x180;
            goto LAB_0005be2c;
          }
          uVar5 = uVar4 + 0x1c0;
          *param_4 = uVar5;
          if (s_aclHashUsedCnt[uVar4 + 0x1c0] == '\0') goto LAB_0005be48;
          if (iVar7 == 4) goto joined_r0x0005be10;
        }
        uVar6 = uVar6 + 1;
        iVar7 = iVar7 + 1;
      } while( true );
    }
    if (param_1 != 2) {
      printk("ERROR:(%s:%d)","tm_acl_v2.c",0x770);
      printk("Invalid Hash Type!\n");
      return 0xfffffff4;
    }
    uVar6 = 0x200;
    pcVar2 = s_aclHashUsedCnt + 0x200;
    do {
      *param_4 = uVar6;
      if (*pcVar2 == '\0') {
        *param_4 = uVar6 | 0x80000000;
        break;
      }
      uVar6 = uVar6 + 1;
      pcVar2 = pcVar2 + 1;
    } while (uVar6 != 0x208);
  }
joined_r0x0005be10:
  if (TM_CLA_DEBUG != 0) {
    printk("aclGetAvailableHashAddr:0x%x \n",*param_4);
  }
  return 0;
}

