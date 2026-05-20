// module: tm.ko
// function: sbrg_lookup_ipv4table @ 0x1de38
// size: 900 bytes
//

undefined4 sbrg_lookup_ipv4table(uint *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  int local_40;
  int local_3c;
  uint local_38;
  uint local_34;
  int local_30;
  uint local_2c;
  uint local_28;
  uint local_24;
  
  uVar10 = param_1[4];
  uVar8 = param_1[3];
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  if (0xfff < param_1[5]) {
    if (g_tm_debug_level != 0) {
      printk("[TM][sbrg_lookup_ipv4table]input invalid parameter!\n");
      return 1;
    }
    return 1;
  }
  if (((6 < g_tm_debug_level) &&
      (printk("[TM][sbrg_lookup_ipv4table]input:vlan_id = %d\n"), 6 < g_tm_debug_level)) &&
     (printk("[TM][sbrg_lookup_ipv4table]input:dip = %-3d.%-3d.%-3d.%-3d\n",uVar10 >> 0x18,
             (uVar10 << 8) >> 0x18,(uVar10 << 0x10) >> 0x18,uVar10 & 0xff), 6 < g_tm_debug_level)) {
    printk("[TM][sbrg_lookup_ipv4table]input:sip = %-3d.%-3d.%-3d.%-3d\n",uVar8 >> 0x18,
           (uVar8 << 8) >> 0x18,(uVar8 << 0x10) >> 0x18,uVar8 & 0xff);
  }
  iVar1 = sbrg_get_table_sel(&local_40);
  if ((iVar1 == 0) && (iVar1 = sbrg_get_multi_vlan_mode(&local_3c), iVar1 == 0)) {
    local_28 = param_1[4];
    local_2c = param_1[3];
    if (local_3c == 0) {
      local_24 = param_1[5] & 0xfff;
    }
    else {
      local_24 = 0;
    }
    uVar8 = sbrg_hash(&local_2c,3,0x4c);
    if (local_40 == 0 || local_40 == 3) {
      if (g_tm_debug_level == 0) {
        return 0xffffffff;
      }
      printk("[TM][sbrg_lookup_ipv4table] ipv4 multicast address table is zero\n");
      return 0xffffffff;
    }
    if (local_40 == 1) {
      uVar8 = uVar8 & 0xff | 0x100;
    }
    else {
      uVar8 = uVar8 & 0xff | 0x200;
    }
    iVar1 = 0;
    while( true ) {
      iVar2 = sbrg_get_indreg_wr_cfg(iVar1,uVar8,"sbrg_lookup_ipv4table");
      iVar3 = tmOnuRegRead(0x4c,&local_38,0,&sbragRegTable);
      iVar4 = tmOnuRegRead(0x4d,&local_34,0,&sbragRegTable);
      iVar5 = tmOnuRegRead(0x4e,&local_30,0,&sbragRegTable);
      if (((iVar4 != 0 || iVar3 != 0) || iVar5 != 0) || iVar2 != 0) break;
      uVar10 = local_38 >> 3 | local_34 << 0x1d;
      uVar12 = (uint)(local_30 << 0x11) >> 0x14;
      uVar6 = local_34 >> 3 | local_30 << 0x1d;
      uVar9 = local_38 & 1;
      if (local_3c == 0) {
        if ((uVar6 == param_1[4]) && (uVar10 == param_1[3])) {
          uVar7 = uVar9;
          if (uVar12 != param_1[5]) {
            uVar7 = 0;
          }
LAB_0001e0cc:
          if (uVar7 == 1) {
            *param_1 = uVar9;
            uVar8 = g_tm_debug_level;
            uVar11 = (uint)(local_30 << 9) >> 0x18;
            uVar13 = (local_38 << 0x1d) >> 0x1f;
            uVar7 = (local_38 << 0x1e) >> 0x1f;
            param_1[4] = uVar6;
            param_1[6] = uVar11;
            param_1[3] = uVar10;
            param_1[5] = uVar12;
            param_1[1] = uVar7;
            param_1[2] = uVar13;
            if (uVar8 < 7) {
              return 0;
            }
            printk("[TM][sbrg_lookup_ipv4table]output:valid  = %d\n",uVar9);
            if (g_tm_debug_level < 7) {
              return 0;
            }
            printk("[TM][sbrg_lookup_ipv4table]output:age    = %d\n",uVar7);
            if (g_tm_debug_level < 7) {
              return 0;
            }
            printk("[TM][sbrg_lookup_ipv4table]output:mode   = %d\n",uVar13);
            if (g_tm_debug_level < 7) {
              return 0;
            }
            printk("[TM][sbrg_lookup_ipv4table]output:port_mask = 0x%x\n",uVar11);
            return 0;
          }
        }
      }
      else if (uVar6 == param_1[4]) {
        uVar7 = (uVar12 == 0 && uVar10 == param_1[3]) & uVar9;
        goto LAB_0001e0cc;
      }
      iVar1 = iVar1 + 1;
      if (iVar1 == 4) {
        *param_1 = 0;
        uVar8 = g_tm_debug_level;
        param_1[1] = 0;
        param_1[2] = 0;
        param_1[6] = 0;
        if (6 < uVar8) {
          printk("[TM][sbrg_lookup_ipv4table]the entry is\'t exist\n");
        }
        return 0;
      }
    }
  }
  if (g_tm_debug_level != 0) {
    printk("[TM][sbrg_lookup_ipv4table] reg read failed\n");
    return 0xffffffff;
  }
  return 0xffffffff;
}

