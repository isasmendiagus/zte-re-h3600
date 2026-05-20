// module: tm.ko
// function: sbrg_add_ipv6table @ 0x1effc
// size: 2252 bytes
//

undefined4 sbrg_add_ipv6table(uint *param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint *puVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint *puVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  uint uVar20;
  uint uVar21;
  uint uVar22;
  bool bVar23;
  int local_e0;
  int local_b4;
  int local_b0;
  uint local_ac;
  uint local_a8;
  uint local_a4;
  uint local_a0;
  uint local_9c;
  uint local_98;
  uint local_94;
  uint local_90;
  uint local_8c;
  uint local_88;
  uint local_84;
  uint local_80;
  uint local_7c;
  uint local_78;
  uint local_74;
  uint local_70;
  uint local_6c;
  undefined4 local_68;
  uint local_64;
  uint local_60;
  undefined4 local_5c;
  uint local_58;
  uint local_54;
  int local_50;
  uint local_4c;
  uint local_48;
  int local_44;
  uint local_40;
  uint local_3c;
  uint local_34;
  uint local_30;
  
  if ((0xfff < param_1[3]) || (0xff < param_1[8])) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
LAB_0001f060:
    printk("[TM][sbrg_add_ipv6table]input invalid parameter!\n");
    return 1;
  }
  if (((1 < *param_1) || (1 < param_1[1])) || (1 < param_1[2])) {
    if (g_tm_debug_level < 7) {
      return 1;
    }
    goto LAB_0001f060;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sbrg_add_ipv6table]input:vlan_id = %d\n");
    if (6 < g_tm_debug_level) {
      printk("[TM][sbrg_add_ipv6table]input:dip = %x:%x:%x:%x\n",param_1[7],param_1[6],param_1[5],
             param_1[4]);
      if (((g_tm_debug_level < 7) ||
          (printk("[TM][sbrg_add_ipv6table]input:sip = %x:%x:%x:%x\n",param_1[0xc],param_1[0xb],
                  param_1[10],param_1[9]), g_tm_debug_level < 7)) ||
         (printk("[TM][sbrg_add_ipv6table]input:valid = %d,\n",*param_1), g_tm_debug_level < 7))
      goto LAB_0001f0a0;
      printk("[TM][sbrg_add_ipv6table]input:mode = %d\n",param_1[2]);
    }
    if ((6 < g_tm_debug_level) &&
       (printk("[TM][sbrg_add_ipv6table]input:age = %d\n",param_1[1]), 6 < g_tm_debug_level)) {
      printk("[TM][sbrg_add_ipv6table]input:pt_mask = 0x%x\n",param_1[8]);
    }
  }
LAB_0001f0a0:
  iVar1 = sbrg_get_table_sel(&local_b4);
  if ((iVar1 == 0) && (iVar2 = sbrg_get_multi_vlan_mode(&local_b0), iVar1 = local_b0, iVar2 == 0)) {
    uVar9 = param_1[0xb];
    bVar23 = local_b0 == 0;
    uVar6 = param_1[0xc];
    uVar21 = param_1[9];
    local_8c = uVar9;
    if (bVar23) {
      local_8c = param_1[3];
    }
    uVar20 = param_1[10];
    uVar18 = param_1[4];
    if (bVar23) {
      local_8c = local_8c & 0xfff;
    }
    uVar17 = param_1[5];
    uVar15 = param_1[6];
    uVar19 = param_1[7];
    if (!bVar23) {
      local_8c = 0;
    }
    local_ac = uVar21;
    local_a8 = uVar20;
    local_a4 = uVar9;
    local_a0 = uVar6;
    local_9c = uVar18;
    local_98 = uVar17;
    local_94 = uVar15;
    local_90 = uVar19;
    uVar3 = sbrg_hash(&local_ac,9,0x10c);
    if (local_b4 != 0 && local_b4 != 3) {
      if (local_b4 == 1) {
        uVar3 = (uVar3 & 0x7f) << 2 | 0x200;
      }
      else {
        uVar3 = (uVar3 & 0x3f) << 2 | 0x300;
      }
      if (iVar1 == 0) {
        uVar10 = param_1[2];
        uVar12 = param_1[1];
        uVar7 = *param_1 & 1 | uVar15 << 0xf | (param_1[3] & 0xfff) << 3;
      }
      else {
        uVar10 = param_1[2];
        uVar12 = param_1[1];
        uVar7 = *param_1 & 1 | uVar15 << 0xf;
      }
      local_80 = uVar19 >> 0x11;
      local_88 = uVar7 | (uVar10 & 1) << 2 | (uVar12 & 1) << 1;
      local_84 = uVar15 >> 0x11 | uVar19 << 0xf;
      local_7c = param_1[8] | uVar18 << 8;
      iVar1 = 0;
      local_78 = uVar18 >> 0x18 | uVar17 << 8;
      local_74 = uVar17 >> 0x18;
      local_e0 = 4;
      local_68 = 0;
      local_5c = 0;
      local_70 = uVar9;
      local_6c = uVar6;
      local_64 = uVar21;
      local_60 = uVar20;
      do {
        puVar16 = &local_58;
        uVar6 = 0;
        do {
          uVar9 = uVar6 | uVar3;
          uVar6 = uVar6 + 1;
          iVar2 = sbrg_get_indreg_wr_cfg(iVar1,uVar9,"sbrg_add_ipv6table");
          if (iVar2 != 0) goto LAB_0001f54c;
          iVar2 = tmOnuRegRead(0x4c,puVar16,0,&sbragRegTable);
          iVar4 = tmOnuRegRead(0x4d,puVar16 + 1,0,&sbragRegTable);
          puVar8 = puVar16 + 2;
          puVar16 = puVar16 + 3;
          iVar5 = tmOnuRegRead(0x4e,puVar8,0,&sbragRegTable);
          uVar19 = local_30;
          uVar17 = local_34;
          uVar15 = local_3c;
          uVar20 = local_40;
          uVar18 = local_4c;
          uVar21 = local_58;
          if ((iVar4 != 0 || iVar2 != 0) || iVar5 != 0) goto LAB_0001f0b0;
        } while (uVar6 != 4);
        uVar12 = local_4c >> 8 | local_48 << 0x18;
        uVar6 = local_58 >> 0xf | local_54 << 0x11;
        uVar22 = (local_58 << 0x11) >> 0x14;
        uVar13 = local_48 >> 8 | local_44 << 0x18;
        uVar14 = (local_58 << 0x1d) >> 0x1f;
        uVar7 = local_54 >> 0xf | local_50 << 0x11;
        uVar10 = local_58 & 1;
        if (local_b0 == 0) {
          uVar11 = 0;
          if (((uVar12 == param_1[4]) && (uVar13 == param_1[5])) &&
             ((uVar6 == param_1[6] && ((uVar7 == param_1[7] && (local_34 == param_1[9])))))) {
            if ((local_30 == param_1[10]) &&
               (((local_40 == param_1[0xb] && (local_3c == param_1[0xc])) && (uVar22 == param_1[3]))
               )) {
              uVar11 = uVar10;
              if (uVar14 != param_1[2]) {
                uVar11 = 0;
              }
            }
            else {
              uVar11 = 0;
            }
          }
        }
        else {
          uVar11 = 0;
          if ((((uVar12 == param_1[4]) && (uVar13 == param_1[5])) && (uVar6 == param_1[6])) &&
             ((uVar7 == param_1[7] && (local_34 == param_1[9])))) {
            if ((local_30 == param_1[10]) && (local_40 == param_1[0xb])) {
              if (uVar22 == 0 && local_3c == param_1[0xc]) {
                uVar11 = uVar10;
                if (uVar14 != param_1[2]) {
                  uVar11 = 0;
                }
              }
              else {
                uVar11 = 0;
              }
            }
            else {
              uVar11 = 0;
            }
          }
        }
        if (uVar11 == 1) {
          uVar6 = 0;
          puVar16 = &local_80;
          goto LAB_0001f730;
        }
        if (uVar10 == 0) {
          if (local_e0 == 4) {
            local_e0 = iVar1;
          }
        }
        else if (g_tm_debug_level < 7) {
LAB_0001f478:
          if (g_tm_debug_level < 7) goto LAB_0001f484;
          printk("[TM][sbrg_add_ipv6table]sip = %x:%x:%x:%x\n",uVar15,uVar20,uVar19,uVar17);
LAB_0001f7ec:
          if (6 < g_tm_debug_level) {
            printk("[TM][sbrg_add_ipv6table]valid = %d,\n",1);
LAB_0001f808:
            if (6 < g_tm_debug_level) {
              printk("[TM][sbrg_add_ipv6table]mode = %d\n",uVar14);
              goto LAB_0001f824;
            }
          }
        }
        else {
          printk("[TM][sbrg_add_ipv6table]mem_id = %d\n",iVar1);
          if (g_tm_debug_level < 7) goto LAB_0001f7ec;
          printk("[TM][sbrg_add_ipv6table]hash_addr = %d\n",uVar9 - 3);
          if (g_tm_debug_level < 7) goto LAB_0001f808;
          printk("[TM][sbrg_add_ipv6table]vlan_id = %d\n",uVar22);
          if (6 < g_tm_debug_level) {
            printk("[TM][sbrg_add_ipv6table]dip = %x:%x:%x:%x\n",uVar7,uVar6,uVar13,uVar12);
            goto LAB_0001f478;
          }
LAB_0001f824:
          if (6 < g_tm_debug_level) {
            printk("[TM][sbrg_add_ipv6table]age = %d\n",(uVar21 << 0x1e) >> 0x1f);
LAB_0001f484:
            if (6 < g_tm_debug_level) {
              printk("[TM][sbrg_add_ipv6table]pt_mask = 0x%x\n",uVar18 & 0xff);
            }
          }
        }
        iVar1 = iVar1 + 1;
      } while (iVar1 != 4);
      if (local_e0 == 4) {
        if (g_tm_debug_level < 7) {
          return 1;
        }
        printk("[TM][sbrg_add_ipv6table]hash collision ipv6table add failed\n");
        return 1;
      }
      uVar6 = 0;
      puVar16 = &local_80;
      do {
        uVar9 = uVar6 | uVar3;
        uVar6 = uVar6 + 1;
        iVar1 = sbrg_set_indreg_wr_cfg(local_e0,uVar9,"sbrg_add_ipv6table");
        if (iVar1 != 0) {
LAB_0001f54c:
          if (g_tm_debug_level == 0) {
            return 0xffffffff;
          }
          printk("[TM][sbrg_add_ipv6table] reg write failed\n");
          return 0xffffffff;
        }
        iVar1 = tmOnuRegWrite(0x4e,*puVar16,0,&sbragRegTable);
        iVar2 = tmOnuRegWrite(0x4d,puVar16[-1],0,&sbragRegTable);
        iVar4 = tmOnuRegWrite(0x4c,puVar16[-2],0,&sbragRegTable);
        if ((iVar2 != 0 || iVar1 != 0) || iVar4 != 0) goto LAB_0001f54c;
        puVar16 = puVar16 + 3;
      } while (uVar6 != 4);
LAB_0001f458:
      if (6 < g_tm_debug_level) {
        printk("[TM][sbrg_add_ipv6table]ipv6table add success\n");
      }
      return 0;
    }
    if (g_tm_debug_level != 0) {
      printk("[TM][sbrg_add_ipv6table] ipv6 multicast address table is zero\n");
      return 0xffffffff;
    }
  }
  else {
LAB_0001f0b0:
    if (g_tm_debug_level != 0) {
      printk("[TM][sbrg_add_ipv6table] reg read failed\n");
    }
  }
  return 0xffffffff;
  while( true ) {
    iVar2 = tmOnuRegWrite(0x4e,*puVar16,0,&sbragRegTable);
    iVar4 = tmOnuRegWrite(0x4d,puVar16[-1],0,&sbragRegTable);
    iVar5 = tmOnuRegWrite(0x4c,puVar16[-2],0,&sbragRegTable);
    if ((iVar4 != 0 || iVar2 != 0) || iVar5 != 0) goto LAB_0001f54c;
    puVar16 = puVar16 + 3;
    if (uVar6 == 4) break;
LAB_0001f730:
    uVar9 = uVar6 | uVar3;
    uVar6 = uVar6 + 1;
    iVar2 = sbrg_set_indreg_wr_cfg(iVar1,uVar9,"sbrg_add_ipv6table");
    if (iVar2 != 0) goto LAB_0001f54c;
  }
  goto LAB_0001f458;
}

