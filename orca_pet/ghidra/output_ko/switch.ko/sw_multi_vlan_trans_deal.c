// module: switch.ko
// function: sw_multi_vlan_trans_deal @ 0x1f450
// size: 1008 bytes
//

undefined4 sw_multi_vlan_trans_deal(char *param_1,int param_2)

{
  byte bVar1;
  ushort uVar2;
  ushort uVar3;
  undefined1 uVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  uint uVar8;
  undefined2 *puVar9;
  uint uVar10;
  uint uVar11;
  uint local_4c;
  ushort local_48;
  ushort local_46;
  short local_44;
  undefined1 local_41;
  uint local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  undefined1 local_30;
  undefined1 local_2f;
  
  local_4c = 0;
  if (param_1 != (char *)0x0) {
    if (lg_firstTime_58570 != '\0') {
      __memzero(&g_vlanTransEntryTbl,0x140);
      lg_firstTime_58570 = '\0';
      printk("init multi vlan trans table end\n");
    }
    iVar5 = get_sw_port_from_devname(param_1,&local_4c,1);
    if (iVar5 == 0) {
      if (*param_1 == 'w') {
        if (g_switch_debug_level < 3) {
          return 0;
        }
        printk(" wifi port ,return ok\n");
        return 0;
      }
      uVar2 = *(ushort *)(param_1 + 0x12);
      uVar3 = *(ushort *)(param_1 + 0x10);
      uVar8 = uVar2 & 0xfff;
      uVar11 = uVar3 & 0xfff;
      if ((uVar2 & 0xfff) == 0) {
        uVar10 = 1;
      }
      else {
        uVar10 = 2;
      }
      if (2 < g_switch_debug_level) {
        printk("sw_multi_vlan_trans_deal ponvlan %d, univlan %d, vlanoper %d, port %d, act %d\n",
               uVar11,uVar8,param_2,local_4c,uVar10);
      }
      __memzero(&local_48,8);
      local_48 = (ushort)(((uint)uVar3 << 0x14) >> 0x14);
      local_44 = (short)local_4c;
      if (2 < g_switch_debug_level) {
        printk("sw_query_multi_vlan_trans_entry ponvlan %d, port %d\n",uVar11,local_4c & 0xffff);
      }
      iVar5 = 0;
      pcVar7 = &DAT_0002ba7e;
      do {
        uVar3 = (ushort)(((uint)uVar2 << 0x14) >> 0x14);
        uVar4 = (undefined1)uVar10;
        local_40 = uVar8;
        local_3c = uVar11;
        local_38 = uVar10;
        if (((*pcVar7 != '\0') && (*(ushort *)(pcVar7 + -6) == local_48)) &&
           (*(short *)(pcVar7 + -2) == local_44)) {
          __memzero(&local_40,0x18);
          local_34 = local_4c;
          local_2f = 1;
          local_30 = 1;
          if (param_2 != 0) {
            iVar6 = tm_multicst_vltrans_table_delete_set(&local_40);
            if (iVar6 == 0) {
              if (2 < g_switch_debug_level) {
                printk("sw_del_multi_vlan_trans_entry idx %d\n",iVar5);
              }
              (&g_vlanTransEntryTbl)[iVar5 * 4] = 0;
              (&DAT_0002ba7c)[iVar5 * 4] = 0;
              (&DAT_0002ba7a)[iVar5 * 4] = 0;
              (&DAT_0002ba7e)[iVar5 * 8] = 0;
              (&DAT_0002ba7f)[iVar5 * 8] = 0;
              return 0;
            }
            goto LAB_0001f6fc;
          }
          uVar2 = (&DAT_0002ba7a)[iVar5 * 4];
          bVar1 = (&DAT_0002ba7f)[iVar5 * 8];
          if (2 < g_switch_debug_level) {
            printk("sw_get_multi_vlan_trans_entry univlan %d, act %d, idx %d\n",(uint)uVar2,
                   (uint)bVar1,iVar5);
          }
          local_40 = (uint)uVar2;
          local_38 = (uint)bVar1;
          iVar6 = tm_multicst_vltrans_table_delete_set(&local_40);
          if (iVar6 != 0) goto LAB_0001f6fc;
          if (2 < g_switch_debug_level) {
            printk("sw_update_multi_vlan_trans_entry univlan %d, idx %d\n",uVar8,iVar5);
          }
          (&DAT_0002ba7a)[iVar5 * 4] = uVar3;
          (&DAT_0002ba7f)[iVar5 * 8] = uVar4;
          goto LAB_0001f6ac;
        }
        iVar5 = iVar5 + 1;
        pcVar7 = pcVar7 + 8;
      } while (iVar5 != 0x28);
      __memzero(&local_40,0x18);
      local_34 = local_4c;
      local_2f = 1;
      local_30 = 1;
      if (param_2 != 0) {
        iVar5 = tm_multicst_vltrans_table_delete_set(&local_40);
        if (iVar5 == 0) {
          return 0;
        }
LAB_0001f6fc:
        printk("tm multi vltrans tbl delete fail\n");
        return 0xffffffff;
      }
      local_46 = uVar3;
      local_41 = uVar4;
      if (2 < g_switch_debug_level) {
        printk("sw_set_multi_vlan_trans_entry ponvlan %d, uniVlan %d, port %d\n",local_48,uVar8,
               local_44);
      }
      iVar5 = 0;
      puVar9 = &g_vlanTransEntryTbl;
      do {
        pcVar7 = (char *)(puVar9 + 3);
        puVar9 = puVar9 + 4;
        if (*pcVar7 == '\0') {
          (&g_vlanTransEntryTbl)[iVar5 * 4] = local_48;
          (&DAT_0002ba7c)[iVar5 * 4] = local_44;
          (&DAT_0002ba7a)[iVar5 * 4] = local_46;
          (&DAT_0002ba7f)[iVar5 * 8] = local_41;
          (&DAT_0002ba7e)[iVar5 * 8] = 1;
          break;
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 != 0x28);
LAB_0001f6ac:
      local_40 = uVar8;
      local_38 = uVar10;
      tm_multicst_vltrans_table_add_set(&local_40);
      return 0;
    }
    if (g_switch_debug_level != 0) {
      printk("curPort ERROR: portname=%s\n",param_1);
      return 0xffffffff;
    }
  }
  return 0xffffffff;
}

