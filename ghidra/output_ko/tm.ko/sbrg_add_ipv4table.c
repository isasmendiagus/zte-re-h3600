// module: tm.ko
// function: sbrg_add_ipv4table @ 0x1e1bc
// size: 1640 bytes
//

undefined4 sbrg_add_ipv4table(uint *param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  int local_64;
  int local_54;
  int local_50;
  uint local_4c;
  uint local_48;
  uint local_44;
  uint local_40;
  uint local_3c;
  int local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  
  uVar9 = param_1[4];
  uVar10 = param_1[3];
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  if ((param_1[6] < 0x100) && (param_1[5] < 0x1000)) {
    if (((param_1[2] < 2) && (param_1[1] < 2)) && (*param_1 < 2)) {
      if (6 < g_tm_debug_level) {
        printk("[TM][sbrg_add_ipv4table]input:valid = %d\n");
        if (6 < g_tm_debug_level) {
          printk("[TM][sbrg_add_ipv4table]input:age = %d\n",param_1[1]);
          if (((g_tm_debug_level < 7) ||
              (printk("[TM][sbrg_add_ipv4table]input:mode = %d\n",param_1[2]), g_tm_debug_level < 7)
              ) || (printk("[TM][sbrg_add_ipv4table]input:dip = %-3d.%-3d.%-3d.%-3d\n",uVar9 >> 0x18
                           ,uVar9 >> 0x10 & 0xff,uVar9 >> 8 & 0xff,uVar9 & 0xff),
                   g_tm_debug_level < 7)) goto LAB_0001e2a4;
          printk("[TM][sbrg_add_ipv4table]input:sip = %-3d.%-3d.%-3d.%-3d\n",uVar10 >> 0x18,
                 uVar10 >> 0x10 & 0xff,uVar10 >> 8 & 0xff,uVar10 & 0xff);
        }
        if ((6 < g_tm_debug_level) &&
           (printk("[TM][sbrg_add_ipv4table]input:vlan_id = %d\n",param_1[5]), 6 < g_tm_debug_level)
           ) {
          printk("[TM][sbrg_add_ipv4table]input:port_mask = 0x%x\n",param_1[6]);
        }
      }
LAB_0001e2a4:
      iVar1 = sbrg_get_table_sel(&local_54);
      if ((iVar1 == 0) &&
         (iVar2 = sbrg_get_multi_vlan_mode(&local_50), iVar1 = local_50, iVar2 == 0)) {
        uVar13 = param_1[3];
        uVar12 = param_1[4];
        if (local_50 == 0) {
          local_2c = param_1[5] & 0xfff;
        }
        else {
          local_2c = 0;
        }
        local_34 = uVar13;
        local_30 = uVar12;
        uVar3 = sbrg_hash(&local_34,3,0x4c);
        if (local_54 == 0 || local_54 == 3) {
          if (g_tm_debug_level == 0) {
            return 0xffffffff;
          }
          printk("[TM][sbrg_add_ipv4table] ipv4 multicast address table is zero\n");
          return 0xffffffff;
        }
        if (local_54 == 1) {
          uVar3 = uVar3 & 0xff | 0x100;
        }
        else {
          uVar3 = uVar3 & 0xff | 0x200;
        }
        if (iVar1 == 0) {
          local_44 = (param_1[6] & 0xff) << 0xf | (param_1[5] & 0xfff) << 3 | uVar12 >> 0x1d;
        }
        else {
          local_44 = (param_1[6] & 0xff) << 0xf | uVar12 >> 0x1d;
        }
        local_48 = uVar12 << 3 | uVar13 >> 0x1d;
        iVar1 = 0;
        local_4c = *param_1 | uVar13 << 3 | (param_1[2] & 1) << 2 | (param_1[1] & 1) << 1;
        local_64 = 4;
        while( true ) {
          iVar4 = sbrg_get_indreg_wr_cfg(iVar1,uVar3,"sbrg_add_ipv4table");
          iVar5 = tmOnuRegRead(0x4c,&local_40,0,&sbragRegTable);
          iVar6 = tmOnuRegRead(0x4d,&local_3c,0,&sbragRegTable);
          iVar7 = tmOnuRegRead(0x4e,&local_38,0,&sbragRegTable);
          iVar2 = local_38;
          uVar12 = local_40;
          if (((iVar6 != 0 || iVar5 != 0) || iVar7 != 0) || iVar4 != 0) break;
          uVar14 = local_40 >> 3 | local_3c << 0x1d;
          uVar11 = (uint)(local_38 << 0x11) >> 0x14;
          uVar8 = (local_40 << 0x1d) >> 0x1f;
          uVar13 = local_3c >> 3 | local_38 << 0x1d;
          if (local_50 == 0) {
            if (((uVar13 == param_1[4]) && (uVar14 == param_1[3])) && (uVar11 == param_1[5])) {
LAB_0001e560:
              uVar13 = local_40 & 1;
              if (uVar8 != param_1[2]) {
                uVar13 = 0;
              }
            }
            else {
              uVar13 = 0;
            }
          }
          else if (uVar13 == param_1[4]) {
            if (uVar14 == param_1[3] && uVar11 == 0) goto LAB_0001e560;
            uVar13 = 0;
          }
          else {
            uVar13 = 0;
          }
          if (uVar13 == 1) {
            iVar1 = sbrg_set_indreg_wr(iVar1,uVar3,"sbrg_add_ipv4table",&local_4c);
            if (iVar1 == 0) {
              if (g_tm_debug_level < 7) {
                return 0;
              }
              printk("[TM][sbrg_add_ipv4table] add success\n");
              return 0;
            }
            goto LAB_0001e5b4;
          }
          if ((local_40 & 1) == 0) {
            if (local_64 == 4) {
              local_64 = iVar1;
            }
          }
          else if (g_tm_debug_level < 7) {
LAB_0001e510:
            if (g_tm_debug_level < 7) goto LAB_0001e51c;
            printk("[TM][sbrg_add_ipv4table]mode = %d\n",uVar8);
LAB_0001e744:
            if (6 < g_tm_debug_level) {
              printk("[TM][sbrg_add_ipv4table]dip = %-3d.%-3d.%-3d.%-3d\n",uVar9 >> 0x18,
                     uVar9 >> 0x10 & 0xff,uVar9 >> 8 & 0xff,uVar9 & 0xff);
LAB_0001e770:
              if (6 < g_tm_debug_level) {
                printk("[TM][sbrg_add_ipv4table]sip = %-3d.%-3d.%-3d.%-3d\n",uVar10 >> 0x18,
                       uVar10 >> 0x10 & 0xff,uVar10 >> 8 & 0xff,uVar10 & 0xff);
                goto LAB_0001e79c;
              }
            }
          }
          else {
            printk("[TM][sbrg_add_ipv4table]mem_id = %d\n",iVar1);
            if (g_tm_debug_level < 7) goto LAB_0001e744;
            printk("[TM][sbrg_add_ipv4table]hash_addr = %d\n",uVar3);
            if (g_tm_debug_level < 7) goto LAB_0001e770;
            printk("[TM][sbrg_add_ipv4table]valid = %d\n",1);
            if (6 < g_tm_debug_level) {
              printk("[TM][sbrg_add_ipv4table]age = %d\n",(uVar12 << 0x1e) >> 0x1f);
              goto LAB_0001e510;
            }
LAB_0001e79c:
            if (6 < g_tm_debug_level) {
              printk("[TM][sbrg_add_ipv4table]vlan_id = %d\n",uVar11);
LAB_0001e51c:
              if (6 < g_tm_debug_level) {
                printk("[TM][sbrg_add_ipv4table]port_mask = 0x%x\n",(uint)(iVar2 << 9) >> 0x18);
              }
            }
          }
          iVar1 = iVar1 + 1;
          if (iVar1 == 4) {
            if (local_64 == 4) {
              if (g_tm_debug_level < 7) {
                return 1;
              }
              printk("[TM][sbrg_add_ipv4table]hash collision ipv4table add failed\n");
              return 1;
            }
            iVar1 = sbrg_set_indreg_wr(local_64,uVar3,"sbrg_add_ipv4table",&local_4c);
            if (iVar1 == 0) {
              if (g_tm_debug_level < 7) {
                return 0;
              }
              printk("[TM][sbrg_add_ipv4table] ipv4table  add success\n");
              return 0;
            }
LAB_0001e5b4:
            if (g_tm_debug_level == 0) {
              return 0xffffffff;
            }
            printk("[TM][sbrg_add_ipv4table] reg write failed\n");
            return 0xffffffff;
          }
        }
      }
      if (g_tm_debug_level != 0) {
        printk("[TM][sbrg_add_ipv4table] reg read failed\n");
      }
      return 0xffffffff;
    }
    if (g_tm_debug_level < 7) {
      return 1;
    }
  }
  else if (g_tm_debug_level == 0) {
    return 1;
  }
  printk("[TM][sbrg_add_ipv4table]input invalid parameter!\n");
  return 1;
}

