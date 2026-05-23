// module: tm.ko
// function: sbrg_delete_ipv6table @ 0x1f8c8
// size: 1252 bytes
//

undefined4 sbrg_delete_ipv6table(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint *puVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint *puVar11;
  undefined4 *puVar12;
  uint uVar13;
  uint uVar14;
  int local_b4;
  int local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  uint local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  uint local_58;
  uint local_54;
  int local_50;
  uint local_4c;
  uint local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_34;
  int local_30;
  
  if (0xfff < *(uint *)(param_1 + 0xc)) {
    if (g_tm_debug_level == 0) {
      return 1;
    }
    printk("[TM][sbrg_delete_ipv6table]input invalid parameter!\n");
    return 1;
  }
  if (((6 < g_tm_debug_level) &&
      (printk("[TM][sbrg_delete_ipv6table]input:vlan_id = %d\n"), 6 < g_tm_debug_level)) &&
     (printk("[TM][sbrg_delete_ipv6table]input:dip = %x:%x:%x:%x\n",*(undefined4 *)(param_1 + 0x1c),
             *(undefined4 *)(param_1 + 0x18),*(undefined4 *)(param_1 + 0x14),
             *(undefined4 *)(param_1 + 0x10)), 6 < g_tm_debug_level)) {
    printk("[TM][sbrg_delete_ipv6table]input:sip = %x:%x:%x:%x\n",*(undefined4 *)(param_1 + 0x30),
           *(undefined4 *)(param_1 + 0x2c),*(undefined4 *)(param_1 + 0x28),
           *(undefined4 *)(param_1 + 0x24));
  }
  iVar1 = sbrg_get_table_sel(&local_b4);
  if ((iVar1 != 0) || (iVar1 = sbrg_get_multi_vlan_mode(&local_b0), iVar1 != 0)) {
LAB_0001f924:
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[TM][sbrg_delete_ipv6table] reg read failed\n");
    return 0xffffffff;
  }
  local_a0 = *(undefined4 *)(param_1 + 0x30);
  local_9c = *(undefined4 *)(param_1 + 0x10);
  local_98 = *(undefined4 *)(param_1 + 0x14);
  local_94 = *(undefined4 *)(param_1 + 0x18);
  local_90 = *(undefined4 *)(param_1 + 0x1c);
  local_ac = *(undefined4 *)(param_1 + 0x24);
  local_a8 = *(undefined4 *)(param_1 + 0x28);
  local_a4 = *(undefined4 *)(param_1 + 0x2c);
  if (local_b0 == 0) {
    local_8c = *(uint *)(param_1 + 0xc) & 0xfff;
  }
  else {
    local_8c = 0;
  }
  uVar2 = sbrg_hash(&local_ac,9,0x10c);
  if (local_b4 == 0 || local_b4 == 3) {
    if (g_tm_debug_level == 0) {
      return 0xffffffff;
    }
    printk("[TM][sbrg_delete_ipv6table] ipv6 multicast address table is zero\n");
    return 0xffffffff;
  }
  if (local_b4 == 1) {
    uVar2 = (uVar2 & 0x7f) << 2 | 0x200;
  }
  else {
    uVar2 = (uVar2 & 0x3f) << 2 | 0x300;
  }
  local_88 = 0;
  iVar1 = 0;
  local_84 = 0;
  local_80 = 0;
  local_7c = 0;
  local_78 = 0;
  local_74 = 0;
  local_70 = 0;
  local_6c = 0;
  local_68 = 0;
  local_64 = 0;
  local_60 = 0;
  local_5c = 0;
  do {
    puVar11 = &local_58;
    uVar13 = 0;
    do {
      iVar3 = sbrg_get_indreg_wr_cfg(iVar1,uVar13 | uVar2,"sbrg_delete_ipv6table");
      uVar13 = uVar13 + 1;
      if (iVar3 != 0) goto LAB_0001fd6c;
      iVar3 = tmOnuRegRead(0x4c,puVar11,0,&sbragRegTable);
      iVar4 = tmOnuRegRead(0x4d,puVar11 + 1,0,&sbragRegTable);
      puVar6 = puVar11 + 2;
      puVar11 = puVar11 + 3;
      iVar5 = tmOnuRegRead(0x4e,puVar6,0,&sbragRegTable);
      if ((iVar4 != 0 || iVar3 != 0) || iVar5 != 0) goto LAB_0001f924;
    } while (uVar13 != 4);
    uVar9 = (local_58 << 0x11) >> 0x14;
    uVar7 = local_58 >> 0xf | local_54 << 0x11;
    uVar13 = local_54 >> 0xf | local_50 << 0x11;
    uVar10 = local_4c >> 8 | local_48 << 0x18;
    uVar8 = local_48 >> 8 | local_44 << 0x18;
    uVar14 = local_58 & 1;
    if (local_b0 == 0) {
      if (((uVar10 == *(uint *)(param_1 + 0x10)) &&
          ((uVar8 == *(uint *)(param_1 + 0x14) && (uVar7 == *(uint *)(param_1 + 0x18))))) &&
         (((uVar13 == *(uint *)(param_1 + 0x1c) &&
           (((local_34 == *(int *)(param_1 + 0x24) && (local_30 == *(int *)(param_1 + 0x28))) &&
            (local_40 == *(int *)(param_1 + 0x2c))))) &&
          ((local_3c == *(int *)(param_1 + 0x30) && (uVar9 == *(uint *)(param_1 + 0xc))))))) {
LAB_0001fc38:
        if ((local_58 << 0x1d) >> 0x1f != *(uint *)(param_1 + 8)) {
          uVar14 = 0;
        }
        if (uVar14 == 1) {
          uVar13 = 0;
          puVar12 = &local_88;
          break;
        }
      }
    }
    else if (((uVar10 == *(uint *)(param_1 + 0x10)) && (uVar8 == *(uint *)(param_1 + 0x14))) &&
            ((uVar7 == *(uint *)(param_1 + 0x18) &&
             ((((uVar13 == *(uint *)(param_1 + 0x1c) && (local_34 == *(int *)(param_1 + 0x24))) &&
               (local_30 == *(int *)(param_1 + 0x28))) &&
              ((local_40 == *(int *)(param_1 + 0x2c) &&
               (uVar9 == 0 && local_3c == *(int *)(param_1 + 0x30))))))))) goto LAB_0001fc38;
    iVar1 = iVar1 + 1;
    if (iVar1 == 4) {
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("[TM][sbrg_delete_ipv6table]the entry is\'t exist\n");
      return 0;
    }
  } while( true );
LAB_0001fc58:
  iVar3 = sbrg_set_indreg_wr_cfg(iVar1,uVar13 | uVar2,"sbrg_delete_ipv6table");
  uVar13 = uVar13 + 1;
  if (iVar3 != 0) {
LAB_0001fd6c:
    if (g_tm_debug_level != 0) {
      printk("[TM][sbrg_delete_ipv6table] reg write failed\n");
    }
    return 0xffffffff;
  }
  iVar3 = tmOnuRegWrite(0x4e,puVar12[2],0,&sbragRegTable);
  iVar4 = tmOnuRegWrite(0x4d,puVar12[1],0,&sbragRegTable);
  iVar5 = tmOnuRegWrite(0x4c,*puVar12,0,&sbragRegTable);
  if ((iVar4 != 0 || iVar3 != 0) || iVar5 != 0) goto LAB_0001fd6c;
  puVar12 = puVar12 + 3;
  if (uVar13 == 4) {
    if (g_tm_debug_level < 7) {
      return 0;
    }
    printk("[TM][sbrg_add_ipv6table]ipv6table delete success\n");
    return 0;
  }
  goto LAB_0001fc58;
}

