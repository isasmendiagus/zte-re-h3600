// module: tm.ko
// function: sbrg_delete_ipv4table @ 0x1e824
// size: 804 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 sbrg_delete_ipv4table(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  int local_4c;
  int local_48 [8];
  undefined4 local_28;
  uint local_24;
  
  uVar10 = *(uint *)(param_1 + 0x10);
  uVar9 = *(uint *)(param_1 + 0xc);
  local_48[4] = 0;
  local_48[5] = 0;
  local_48[6] = 0;
  if (*(uint *)(param_1 + 0x14) < 0x1000) {
    if (((6 < g_tm_debug_level) &&
        (printk("[TM][sbrg_delete_ipv4table]input:vlan_id = %d\n"), 6 < g_tm_debug_level)) &&
       (printk("[TM][sbrg_delete_ipv4table]input:dip = %-3d.%-3d.%-3d.%-3d\n",uVar10 >> 0x18,
               (uVar10 << 8) >> 0x18,(uVar10 << 0x10) >> 0x18,uVar10 & 0xff), 6 < g_tm_debug_level))
    {
      printk("[TM][sbrg_delete_ipv4table]input:sip = %-3d.%-3d.%-3d.%-3d\n",uVar9 >> 0x18,
             (uVar9 << 8) >> 0x18,(uVar9 << 0x10) >> 0x18,uVar9 & 0xff);
    }
    iVar2 = sbrg_get_table_sel(&local_4c);
    if ((iVar2 == 0) && (iVar2 = sbrg_get_multi_vlan_mode(local_48), iVar2 == 0)) {
      local_28 = *(undefined4 *)(param_1 + 0x10);
      local_48[7] = *(undefined4 *)(param_1 + 0xc);
      if (local_48[0] == 0) {
        local_24 = *(uint *)(param_1 + 0x14) & 0xfff;
      }
      else {
        local_24 = 0;
      }
      uVar9 = sbrg_hash(local_48 + 7,3,0x4c);
      if (local_4c == 0 || local_4c == 3) {
        if (g_tm_debug_level == 0) {
          return 0xffffffff;
        }
        printk("[TM][sbrg_delete_ipv4table] ipv4 multicast address table is zero\n");
        uVar1 = 0xffffffff;
      }
      else {
        if (local_4c == 1) {
          uVar9 = uVar9 & 0xff | 0x100;
        }
        else {
          uVar9 = uVar9 & 0xff | 0x200;
        }
        iVar2 = 0;
        local_48[1] = 0;
        local_48[2] = 0;
        local_48[3] = 0;
        do {
          iVar3 = sbrg_get_indreg_wr_cfg(iVar2,uVar9,"sbrg_delete_ipv4table");
          iVar4 = tmOnuRegRead(0x4c,local_48 + 4,0,&sbragRegTable);
          iVar5 = tmOnuRegRead(0x4d,local_48 + 5,0,&sbragRegTable);
          iVar6 = tmOnuRegRead(0x4e,local_48 + 6,0,&sbragRegTable);
          if (((iVar5 != 0 || iVar4 != 0) || iVar6 != 0) || iVar3 != 0) goto LAB_0001e898;
          uVar7 = (uint)local_48[4] >> 3 | local_48[5] << 0x1d;
          uVar8 = (uint)local_48[5] >> 3 | local_48[6] << 0x1d;
          uVar11 = (uint)(local_48[6] << 0x11) >> 0x14;
          uVar10 = local_48[4] & 1;
          if (local_48[0] == 0) {
            if ((uVar8 == *(uint *)(param_1 + 0x10)) &&
               ((uVar7 == *(uint *)(param_1 + 0xc) && (uVar11 == *(uint *)(param_1 + 0x14))))) {
LAB_0001eab4:
              if ((uint)(local_48[4] << 0x1d) >> 0x1f != *(uint *)(param_1 + 8)) {
                uVar10 = 0;
              }
              if (uVar10 == 1) {
                iVar2 = sbrg_set_indreg_wr(iVar2,uVar9,"sbrg_delete_ipv4table",local_48 + 1);
                if (iVar2 != 0) {
                  if (g_tm_debug_level == 0) {
                    return 0xffffffff;
                  }
                  printk("[TM][sbrg_delete_ipv4table] reg write failed\n");
                  return 0xffffffff;
                }
                goto LAB_0001e9f8;
              }
            }
          }
          else if ((uVar8 == *(uint *)(param_1 + 0x10)) &&
                  (uVar7 == *(uint *)(param_1 + 0xc) && uVar11 == 0)) goto LAB_0001eab4;
          iVar2 = iVar2 + 1;
        } while (iVar2 != 4);
        if (6 < g_tm_debug_level) {
          printk("[TM][sbrg_delete_ipv4table]the entry is\'t exist\n");
        }
LAB_0001e9f8:
        uVar1 = 0;
      }
    }
    else {
LAB_0001e898:
      if (g_tm_debug_level == 0) {
        return 0xffffffff;
      }
      printk("[TM][sbrg_delete_ipv4table] reg read failed\n");
      uVar1 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar1 = 1;
  }
  else {
    printk("[TM][sbrg_delete_ipv4table]input invalid parameter!\n");
    uVar1 = 1;
  }
  return uVar1;
}

