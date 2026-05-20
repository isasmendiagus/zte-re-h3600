// module: tm.ko
// function: sbrg_delete_mactable @ 0x20ab0
// size: 1064 bytes
//

undefined4 sbrg_delete_mactable(int param_1)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_44;
  undefined4 local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  uint local_28;
  uint local_24;
  
  uVar5 = *(uint *)(param_1 + 0x18);
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  if ((0xffff < uVar5) || (0xfff < *(uint *)(param_1 + 0x10))) {
    if (g_tm_debug_level != 0) {
      printk("[TM][sbrg_delete_mactable]input invalid parameter!\n");
    }
    return 1;
  }
  uVar6 = *(uint *)(param_1 + 0x14);
  uVar8 = uVar5 & 0xff;
  uVar5 = uVar5 >> 8;
  uVar4 = uVar6 >> 0x18;
  if ((6 < g_tm_debug_level) &&
     (printk("[TM][sbrg_delete_mactable]input:mac_addr=%-2x:%-2x:%-2x:%-2x:%-2x:%-2x\n",uVar5,uVar8,
             uVar4,(uVar6 << 8) >> 0x18,(uVar6 << 0x10) >> 0x18,uVar6 & 0xff), 6 < g_tm_debug_level)
     ) {
    printk("[TM][sbrg_delete_mactable]input:vlan_id=%d\n",*(undefined4 *)(param_1 + 0x10));
  }
  uVar6 = sbrg_get_table_sel(&local_54);
  bVar1 = uVar5 == 1;
  uVar2 = sbrg_get_macaddr_exchange_md(&local_48);
  uVar3 = sbrg_get_hash_mode(&local_44);
  uVar3 = uVar2 | uVar6 | uVar3;
  if ((((uVar4 == 0x5e && (bVar1 && uVar8 == 0)) || (uVar4 == 0xc2 && (uVar8 == 0x80 && bVar1))) ||
      (uVar4 == 0 && (uVar5 == 0xe0 && uVar8 == 0))) || (uVar5 == 0x33 && uVar8 == 0x33)) {
    uVar5 = sbrg_get_multi_mac_vlan_mode(&local_50);
    uVar4 = sbrg_get_multi_mac_hash_mode(&local_4c);
    if (bVar1) {
      iVar7 = 1;
    }
    else {
      iVar7 = 2;
    }
    uVar3 = uVar3 | uVar5 | uVar4;
    local_48 = local_50;
    local_44 = local_4c;
  }
  else {
    iVar7 = 0;
  }
  if (uVar3 == 0) {
    if ((local_48 == 0) || (local_44 == 0)) {
      local_40 = *(undefined4 *)(param_1 + 0x14);
      local_3c = *(uint *)(param_1 + 0x18);
    }
    else {
      local_40 = *(undefined4 *)(param_1 + 0x14);
      local_3c = *(uint *)(param_1 + 0x18) | *(int *)(param_1 + 0x10) << 0x10;
    }
    if (iVar7 == 0) {
      if (local_54 == 0) {
        uVar5 = sbrg_hash(&local_40,2,0x3c);
      }
      else if (local_54 == 1) {
        uVar5 = sbrg_hash(&local_40,2,0x3c);
        uVar5 = uVar5 & 0xff;
      }
      else {
        if (local_54 != 2) {
          if (6 < g_tm_debug_level) {
            printk("[TM][sbrg_lookup_mactable]the entry is\'t exist\n");
            return 0;
          }
          return 0;
        }
        uVar5 = sbrg_hash(&local_40,2,0x3c);
        uVar5 = uVar5 & 0x1ff;
      }
    }
    else {
      uVar5 = sbrg_hash(&local_40,2,0x3c);
      uVar5 = (iVar7 + 1) * 0x100 + (uVar5 & 0xff);
    }
    iVar7 = 0;
    while( true ) {
      uVar4 = sbrg_get_indreg_wr_cfg(iVar7,uVar5,"sbrg_delete_mactable");
      uVar6 = tmOnuRegRead(0x4c,&local_2c,0,&sbragRegTable);
      uVar8 = tmOnuRegRead(0x4d,&local_28,0,&sbragRegTable);
      uVar2 = tmOnuRegRead(0x4e,&local_24,0,&sbragRegTable);
      uVar4 = uVar8 | uVar6 | uVar2 | uVar4;
      if (uVar4 != 0) break;
      if ((((local_28 << 0x18 | local_2c >> 8) == *(uint *)(param_1 + 0x14)) &&
          ((local_28 << 8) >> 0x10 == *(uint *)(param_1 + 0x18))) &&
         (((local_24 & 0xf) << 8 | local_28 >> 0x18) == *(uint *)(param_1 + 0x10) &&
          (local_24 & 0xf0) != 0)) {
        local_38 = uVar4;
        local_34 = uVar4;
        local_30 = uVar4;
        iVar7 = sbrg_set_indreg_wr(iVar7,uVar5,"sbrg_delete_mactable",&local_38);
        if (iVar7 == 0) {
          return 0;
        }
        if (g_tm_debug_level != 0) {
          printk("[TM][sbrg_delete_mactable] reg write failed\n");
          return 0xffffffff;
        }
        return 0xffffffff;
      }
      iVar7 = iVar7 + 1;
      if (iVar7 == 4) {
        if (g_tm_debug_level != 0) {
          printk("[TM][sbrg_delete_mactable] the entry is\'t exist\n");
        }
        return 0;
      }
    }
  }
  if (g_tm_debug_level == 0) {
    return 0xffffffff;
  }
  printk("[TM][sbrg_delete_mactable] reg read failed\n");
  return 0xffffffff;
}

