// module: tm.ko
// function: sbrg_lookup_ipv6table @ 0x1eb48
// size: 1204 bytes
//

undefined4 sbrg_lookup_ipv6table(uint *param_1)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint *puVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint *puVar13;
  uint uVar14;
  uint uVar15;
  int local_84;
  int local_80;
  uint local_7c;
  uint local_78;
  uint local_74;
  uint local_70;
  uint local_6c;
  uint local_68;
  uint local_64;
  uint local_60;
  uint local_5c;
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
  
  if (param_1[3] < 0x1000) {
    if (((6 < g_tm_debug_level) &&
        (printk("[TM][sbrg_lookup_ipv6table]input:vlan_id = %d\n"), 6 < g_tm_debug_level)) &&
       (printk("[TM][sbrg_lookup_ipv6table]input:dip = %x:%x:%x:%x\n",param_1[7],param_1[6],
               param_1[5],param_1[4]), 6 < g_tm_debug_level)) {
      printk("[TM][sbrg_lookup_ipv6table]input:sip = %x:%x:%x:%x\n",param_1[0xc],param_1[0xb],
             param_1[10],param_1[9]);
    }
    iVar2 = sbrg_get_table_sel(&local_84);
    if ((iVar2 == 0) && (iVar2 = sbrg_get_multi_vlan_mode(&local_80), iVar2 == 0)) {
      local_70 = param_1[0xc];
      local_6c = param_1[4];
      local_68 = param_1[5];
      local_64 = param_1[6];
      local_60 = param_1[7];
      local_7c = param_1[9];
      local_78 = param_1[10];
      local_74 = param_1[0xb];
      if (local_80 == 0) {
        local_5c = param_1[3] & 0xfff;
      }
      else {
        local_5c = 0;
      }
      uVar3 = sbrg_hash(&local_7c,9,0x10c);
      if (local_84 == 0 || local_84 == 3) {
        if (g_tm_debug_level == 0) {
          return 0xffffffff;
        }
        printk("[TM][sbrg_lookup_ipv6table] ipv6 multicast address table is zero\n");
        uVar1 = 0xffffffff;
      }
      else {
        iVar2 = 0;
        if (local_84 == 1) {
          uVar3 = (uVar3 & 0x7f) << 2 | 0x200;
        }
        else {
          uVar3 = (uVar3 & 0x3f) << 2 | 0x300;
        }
        do {
          puVar13 = &local_58;
          uVar14 = 0;
          do {
            iVar4 = sbrg_get_indreg_wr_cfg(iVar2,uVar14 | uVar3,"sbrg_lookup_ipv6table");
            uVar14 = uVar14 + 1;
            if (iVar4 != 0) {
              if (g_tm_debug_level == 0) {
                return 0xffffffff;
              }
              printk("[TM][sbrg_lookup_ipv6table] reg write failed\n",puVar13,iVar4);
              return 0xffffffff;
            }
            iVar4 = tmOnuRegRead(0x4c,puVar13,0,&sbragRegTable);
            iVar5 = tmOnuRegRead(0x4d,puVar13 + 1,0,&sbragRegTable);
            puVar8 = puVar13 + 2;
            puVar13 = puVar13 + 3;
            iVar6 = tmOnuRegRead(0x4e,puVar8,0,&sbragRegTable);
            if ((iVar5 != 0 || iVar4 != 0) || iVar6 != 0) goto LAB_0001eba4;
          } while (uVar14 != 4);
          uVar11 = (local_58 << 0x11) >> 0x14;
          uVar12 = local_4c >> 8 | local_48 << 0x18;
          uVar9 = local_58 >> 0xf | local_54 << 0x11;
          uVar7 = local_54 >> 0xf | local_50 << 0x11;
          uVar10 = local_48 >> 8 | local_44 << 0x18;
          uVar15 = local_58 & 1;
          uVar14 = uVar15;
          if (local_80 == 0) {
            if ((((uVar12 == param_1[4]) && (uVar10 == param_1[5])) &&
                (((uVar9 == param_1[6] && ((uVar7 == param_1[7] && (local_34 == param_1[9])))) &&
                 (local_30 == param_1[10])))) &&
               ((local_40 == param_1[0xb] && (local_3c == param_1[0xc])))) {
              if (uVar11 != param_1[3]) {
                uVar14 = 0;
              }
LAB_0001eea8:
              if (uVar14 == 1) {
                *param_1 = uVar15;
                uVar3 = g_tm_debug_level;
                uVar14 = (local_58 << 0x1e) >> 0x1f;
                uVar7 = (local_58 << 0x1d) >> 0x1f;
                param_1[8] = local_4c & 0xff;
                param_1[1] = uVar14;
                param_1[2] = uVar7;
                if ((((6 < uVar3) &&
                     (printk("[TM][sbrg_lookup_ipv6table]output:valid = %d,\n",uVar15),
                     6 < g_tm_debug_level)) &&
                    (printk("[TM][sbrg_lookup_ipv6table]output:mode = %d\n",uVar7),
                    6 < g_tm_debug_level)) &&
                   (printk("[TM][sbrg_lookup_ipv6table]output:age = %d\n",uVar14),
                   6 < g_tm_debug_level)) {
                  printk("[TM][sbrg_lookup_ipv6table]output:pt_mask = 0x%x\n",local_4c & 0xff);
                }
                goto LAB_0001ed8c;
              }
            }
          }
          else if ((((uVar12 == param_1[4]) && (uVar10 == param_1[5])) &&
                   ((uVar9 == param_1[6] &&
                    (((uVar7 == param_1[7] && (local_34 == param_1[9])) && (local_30 == param_1[10])
                     ))))) && (local_40 == param_1[0xb])) {
            if (local_3c != param_1[0xc]) {
              uVar14 = 0;
            }
            if (uVar11 != 0) {
              uVar14 = 0;
            }
            goto LAB_0001eea8;
          }
          iVar2 = iVar2 + 1;
        } while (iVar2 != 4);
        uVar1 = 0;
        *param_1 = 0;
        uVar3 = g_tm_debug_level;
        param_1[1] = 0;
        param_1[2] = 0;
        param_1[8] = 0;
        if (uVar3 < 7) {
LAB_0001ed8c:
          uVar1 = 0;
        }
        else {
          printk("[TM][sbrg_lookup_ipv6table]the entry is\'t exist\n");
        }
      }
    }
    else {
LAB_0001eba4:
      if (g_tm_debug_level == 0) {
        return 0xffffffff;
      }
      printk("[TM][sbrg_lookup_ipv6table] reg read failed\n");
      uVar1 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][sbrg_lookup_ipv6table]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

