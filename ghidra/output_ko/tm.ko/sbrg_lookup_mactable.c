// module: tm.ko
// function: sbrg_lookup_mactable @ 0x2003c
// size: 1092 bytes
//

undefined4 sbrg_lookup_mactable(int param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  undefined4 local_34;
  uint local_30;
  uint local_2c;
  uint local_28;
  uint local_24;
  
  uVar8 = *(uint *)(param_1 + 0x18);
  uVar11 = *(uint *)(param_1 + 0x14);
  if ((0xffff < uVar8) || (0xfff < *(uint *)(param_1 + 0x10))) {
    if (g_tm_debug_level != 0) {
      printk("[TM][sbrg_lookup_mactable]input invalid parameter!\n");
    }
    return 1;
  }
  uVar10 = uVar11 >> 0x18;
  uVar1 = uVar8 >> 8;
  uVar8 = uVar8 & 0xff;
  if ((6 < g_tm_debug_level) &&
     (printk("[TM][sbrg_lookup_mactable]input:mac_addr=%-2x:%-2x:%-2x:%-2x:%-2x:%-2x\n",uVar1,uVar8,
             uVar10,(uVar11 << 8) >> 0x18,(uVar11 << 0x10) >> 0x18,uVar11 & 0xff),
     6 < g_tm_debug_level)) {
    printk("[TM][sbrg_lookup_mactable]input:vlan_id=%d\n",*(undefined4 *)(param_1 + 0x10));
  }
  uVar11 = sbrg_get_table_sel(&local_48);
  uVar2 = sbrg_get_macaddr_exchange_md(&local_3c);
  uVar3 = sbrg_get_hash_mode(&local_38);
  uVar3 = uVar2 | uVar11 | uVar3;
  if (uVar1 == 1) {
    if ((uVar10 != 0x5e || uVar8 != 0) && (uVar10 != 0xc2 || uVar8 != 0x80)) {
      iVar9 = 0;
      goto LAB_000200f4;
    }
    iVar9 = 1;
LAB_00020368:
    uVar8 = sbrg_get_multi_mac_vlan_mode(&local_44);
    uVar11 = sbrg_get_multi_mac_hash_mode(&local_40);
    local_3c = local_44;
    local_38 = local_40;
    uVar3 = uVar3 | uVar8 | uVar11;
  }
  else if ((uVar1 & 0xff) == 0xe0) {
    if (uVar10 == 0 && uVar8 == 0) goto LAB_000203d4;
    iVar9 = 0;
  }
  else {
    if ((uVar1 & 0xff) == 0x33 && uVar8 == 0x33) {
LAB_000203d4:
      iVar9 = 2;
      goto LAB_00020368;
    }
    iVar9 = 0;
  }
LAB_000200f4:
  if (uVar3 != 0) {
LAB_000200fc:
    if (g_tm_debug_level != 0) {
      printk("[TM][sbrg_lookup_mactable] reg read failed\n");
    }
    return 0xffffffff;
  }
  if ((local_3c == 0) || (local_38 == 0)) {
    local_34 = *(undefined4 *)(param_1 + 0x14);
    local_30 = *(uint *)(param_1 + 0x18);
  }
  else {
    local_34 = *(undefined4 *)(param_1 + 0x14);
    local_30 = *(uint *)(param_1 + 0x18) | *(int *)(param_1 + 0x10) << 0x10;
  }
  if (iVar9 == 0) {
    if (local_48 == 0) {
      uVar8 = sbrg_hash(&local_34,2,0x3c);
    }
    else if (local_48 == 1) {
      uVar8 = sbrg_hash(&local_34,2,0x3c);
      uVar8 = uVar8 & 0xff;
    }
    else {
      uVar11 = g_tm_debug_level;
      if (local_48 != 2) goto joined_r0x00020258;
      uVar8 = sbrg_hash(&local_34,2,0x3c);
      uVar8 = uVar8 & 0x1ff;
    }
  }
  else {
    uVar8 = sbrg_hash(&local_34,2,0x3c);
    uVar8 = (iVar9 + 1) * 0x100 + (uVar8 & 0xff);
  }
  iVar9 = 0;
  do {
    iVar4 = sbrg_get_indreg_wr_cfg(iVar9,uVar8,"sbrg_mactable_look");
    iVar9 = iVar9 + 1;
    iVar5 = tmOnuRegRead(0x4c,&local_2c,0,&sbragRegTable);
    iVar6 = tmOnuRegRead(0x4d,&local_28,0,&sbragRegTable);
    iVar7 = tmOnuRegRead(0x4e,&local_24,0,&sbragRegTable);
    uVar11 = g_tm_debug_level;
    if (((iVar6 != 0 || iVar5 != 0) || iVar7 != 0) || iVar4 != 0) goto LAB_000200fc;
    if ((((local_28 << 0x18 | local_2c >> 8) == *(uint *)(param_1 + 0x14)) &&
        ((local_28 << 8) >> 0x10 == *(uint *)(param_1 + 0x18))) &&
       (uVar10 = (local_24 << 0x18) >> 0x1c,
       uVar10 != 0 && ((local_24 & 0xf) << 8 | local_28 >> 0x18) == *(uint *)(param_1 + 0x10))) {
      uVar8 = (local_24 << 0x16) >> 0x1f;
      *(uint *)(param_1 + 0xc) = uVar10;
      *(uint *)(param_1 + 0x1c) = local_2c & 0xff;
      *(uint *)(param_1 + 8) = (local_24 << 0x17) >> 0x1f;
      *(uint *)(param_1 + 4) = uVar8;
      if (uVar11 < 7) {
        return 0;
      }
      printk("[TM][sbrg_lookup_mactable]output:smac_ctrl=%d\n");
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("[TM][sbrg_lookup_mactable]output:dmac_ctrl=%d\n",uVar8);
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("[TM][sbrg_lookup_mactable]output:status=%d\n",uVar10);
      if (g_tm_debug_level < 7) {
        return 0;
      }
      printk("[TM][sbrg_lookup_mactable]output:port_id=0x%x\n",local_2c & 0xff);
      return 0;
    }
  } while (iVar9 != 4);
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
joined_r0x00020258:
  if (6 < uVar11) {
    printk("[TM][sbrg_lookup_mactable]the entry is\'t exist\n");
  }
  return 0;
}

