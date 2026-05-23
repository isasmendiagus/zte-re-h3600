// module: tm.ko
// function: sbrg_add_mactable @ 0x20480
// size: 1584 bytes
//

undefined4 sbrg_add_mactable(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  int iVar15;
  uint uVar16;
  int iVar17;
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  uint local_48;
  uint local_44;
  uint local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  uint local_30;
  uint local_2c [2];
  
  uVar10 = *(uint *)(param_1 + 0x18);
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  if (((((uVar10 < 0x10000) && (*(uint *)(param_1 + 0x10) < 0x1000)) && (*(uint *)(param_1 + 8) < 2)
       ) && ((*(uint *)(param_1 + 4) < 2 && (*(uint *)(param_1 + 0xc) < 0x10)))) &&
     (*(uint *)(param_1 + 0x1c) < 0x100)) {
    uVar11 = *(uint *)(param_1 + 0x14);
    uVar16 = uVar10 & 0xff;
    uVar10 = uVar10 >> 8;
    uVar5 = uVar11 >> 0x18;
    if (6 < g_tm_debug_level) {
      printk("[TM][sbrg_add_mactable]input:mac_addr = %-2x:%-2x:%-2x:%-2x:%-2x:%-2x\n",uVar10,uVar16
             ,uVar5,(uVar11 << 8) >> 0x18,(uVar11 << 0x10) >> 0x18,uVar11 & 0xff);
      if (6 < g_tm_debug_level) {
        printk("[TM][sbrg_add_mactable]input: vlan_id = %d\n",*(undefined4 *)(param_1 + 0x10));
        if (((g_tm_debug_level < 7) ||
            (printk("[TM][sbrg_add_mactable]input:smac_ctrl = %d\n",*(undefined4 *)(param_1 + 8)),
            g_tm_debug_level < 7)) ||
           (printk("[TM][sbrg_add_mactable]input:dmac_ctrl = %d\n",*(undefined4 *)(param_1 + 4)),
           g_tm_debug_level < 7)) goto LAB_0002052c;
        printk("[TM][sbrg_add_mactable]input:  status = %d\n",*(undefined4 *)(param_1 + 0xc));
      }
      if (6 < g_tm_debug_level) {
        printk("[TM][sbrg_add_mactable]input: port_id = 0x%x\n",*(undefined4 *)(param_1 + 0x1c));
      }
    }
LAB_0002052c:
    uVar11 = sbrg_get_table_sel(&local_5c);
    bVar1 = uVar10 == 1;
    uVar3 = sbrg_get_macaddr_exchange_md(&local_50);
    uVar4 = sbrg_get_hash_mode(&local_4c);
    uVar4 = uVar3 | uVar11 | uVar4;
    if ((((uVar5 == 0x5e && (bVar1 && uVar16 == 0)) || (uVar5 == 0xc2 && (uVar16 == 0x80 && bVar1)))
        || (uVar5 == 0 && (uVar10 == 0xe0 && uVar16 == 0))) || (uVar10 == 0x33 && uVar16 == 0x33)) {
      uVar10 = sbrg_get_multi_mac_vlan_mode(&local_58);
      uVar5 = sbrg_get_multi_mac_hash_mode(&local_54);
      if (bVar1) {
        iVar15 = 1;
      }
      else {
        iVar15 = 2;
      }
      uVar4 = uVar4 | uVar10 | uVar5;
      local_50 = local_58;
      local_4c = local_54;
    }
    else {
      iVar15 = 0;
    }
    if (uVar4 != 0) {
LAB_000205fc:
      if (g_tm_debug_level == 0) {
        return 0xffffffff;
      }
      printk("[TM][sbrg_add_mactable] reg read failed\n");
      return 0xffffffff;
    }
    if ((local_50 == 0) || (local_4c == 0)) {
      uVar10 = *(uint *)(param_1 + 0x14);
      uVar5 = *(uint *)(param_1 + 0x18);
      local_44 = uVar5;
    }
    else {
      uVar10 = *(uint *)(param_1 + 0x14);
      uVar5 = *(uint *)(param_1 + 0x18);
      local_44 = uVar5 | *(int *)(param_1 + 0x10) << 0x10;
    }
    local_48 = uVar10;
    if (iVar15 == 0) {
      if (local_5c == 0) {
        uVar11 = sbrg_hash(&local_48,2,0x3c);
        goto LAB_00020664;
      }
      if (local_5c == 1) {
        uVar11 = sbrg_hash(&local_48,2,0x3c);
        uVar11 = uVar11 & 0xff;
        goto LAB_00020664;
      }
      if (local_5c == 2) {
        uVar11 = sbrg_hash(&local_48,2,0x3c);
        uVar11 = uVar11 & 0x1ff;
        goto LAB_00020664;
      }
      if (6 < g_tm_debug_level) {
        printk("[TM][sbrg_lookup_mactable]the entry is\'t exist\n");
        return 0;
      }
    }
    else {
      uVar11 = sbrg_hash(&local_48,2,0x3c);
      uVar11 = (iVar15 + 1) * 0x100 + (uVar11 & 0xff);
LAB_00020664:
      iVar17 = 0;
      local_3c = uVar10 >> 0x18 | *(int *)(param_1 + 0x10) << 0x18 | (uVar5 & 0xffff) << 8;
      local_38 = (*(uint *)(param_1 + 0xc) & 0xf) << 4 |
                 (uint)(*(int *)(param_1 + 0x10) << 0x14) >> 0x1c |
                 (*(uint *)(param_1 + 8) & 1) << 8 | (*(uint *)(param_1 + 4) & 1) << 9;
      local_40 = (uint)*(byte *)(param_1 + 0x1c) | uVar10 << 8;
      iVar15 = 4;
      do {
        iVar6 = sbrg_get_indreg_wr_cfg(iVar17,uVar11,"sbrg_add_mactable");
        iVar7 = tmOnuRegRead(0x4c,&local_34,0,&sbragRegTable);
        iVar8 = tmOnuRegRead(0x4d,&local_30,0,&sbragRegTable);
        iVar9 = tmOnuRegRead(0x4e,local_2c,0,&sbragRegTable);
        uVar5 = local_2c[0];
        uVar10 = local_34;
        if (((iVar8 != 0 || iVar7 != 0) || iVar9 != 0) || iVar6 != 0) goto LAB_000205fc;
        uVar16 = (local_2c[0] << 0x18) >> 0x1c;
        uVar3 = local_30 >> 0x18 | (local_2c[0] & 0xf) << 8;
        if ((((local_34 >> 8 | local_30 << 0x18) == *(uint *)(param_1 + 0x14)) &&
            ((local_30 >> 8 & 0xffff) == *(uint *)(param_1 + 0x18))) &&
           (iVar6 = iVar17, uVar16 != 0 && uVar3 == *(uint *)(param_1 + 0x10))) goto LAB_000208c8;
        iVar6 = iVar15;
        if (uVar16 == 0) {
          if (iVar15 == 4) {
            iVar6 = iVar17;
          }
        }
        else if (6 < g_tm_debug_level) {
          uVar12 = local_34 >> 8 & 0xff;
          uVar4 = local_34 >> 0x18;
          uVar13 = local_30 & 0xff;
          uVar14 = (local_34 << 8) >> 0x18;
          printk("[TM][sbrg_add_mactable]mem_id=%d,hash_addr=%d,mac=%-2x:%-2x:%-2x:%-2x:%-2x:%-2x\n"
                 ,iVar17,uVar11,(local_30 << 8) >> 0x18,local_30 >> 8 & 0xff,uVar13,uVar4,uVar14,
                 uVar12);
          if ((6 < g_tm_debug_level) &&
             (printk("[TM][sbrg_add_mactable]vlan_id=%d,port_id=%d,status=%d,smac_ctrl=%d\n",uVar3,
                     uVar10 & 0xff,uVar16,(uVar5 << 0x17) >> 0x1f,uVar13,uVar4,uVar14,uVar12),
             6 < g_tm_debug_level)) {
            printk("[TM][sbrg_add_mactable]dmac_ctrl=%d\n",(uVar5 << 0x16) >> 0x1f);
          }
        }
        iVar17 = iVar17 + 1;
        iVar15 = iVar6;
      } while (iVar17 != 4);
      if (iVar6 == 4) {
        if (g_tm_debug_level != 0) {
          printk("[TM][sbrg_add_mactable] hash collison,mactable add failed\n");
          return 1;
        }
        goto LAB_000204c8;
      }
LAB_000208c8:
      iVar15 = sbrg_set_indreg_wr(iVar6,uVar11,"sbrg_add_mactable",&local_40);
      if (iVar15 != 0) {
        if (g_tm_debug_level != 0) {
          printk("[TM][sbrg_add_mactable] reg write failed\n");
        }
        return 0xffffffff;
      }
      if (6 < g_tm_debug_level) {
        printk("[TM][sbrg_add_mactable] mactable add successed\n");
      }
    }
    uVar2 = 0;
  }
  else {
    if (g_tm_debug_level != 0) {
      printk("[TM][sbrg_add_mactable]input invalid parameter!\n");
    }
LAB_000204c8:
    uVar2 = 1;
  }
  return uVar2;
}

