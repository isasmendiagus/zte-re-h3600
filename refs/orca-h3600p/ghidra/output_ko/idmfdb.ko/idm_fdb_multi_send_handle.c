// module: idmfdb.ko
// function: idm_fdb_multi_send_handle @ 0x11124
// size: 2412 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 idm_fdb_multi_send_handle(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  pointer_____offset_0x940___ *ppuVar5;
  pointer_____offset_0x940___ *ppuVar6;
  ushort uVar7;
  undefined4 uVar8;
  uint uVar9;
  undefined4 *puVar10;
  pointer_____offset_0x940___ puVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  undefined1 *puVar16;
  ushort uVar17;
  int iVar18;
  pointer_____offset_0x940___ *local_80;
  undefined4 local_6c;
  pointer_____offset_0x940___ local_68;
  uint local_64;
  uint local_60;
  ushort local_5c;
  int local_58 [2];
  undefined1 *local_50;
  undefined4 local_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 local_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  ushort local_2c;
  
  local_6c = 0x20;
  local_68 = (pointer_____offset_0x940___)0x0;
  iVar1 = kmem_cache_alloc(_DAT_000190c8,0xd0);
  if (iVar1 == 0) {
    if (param_3 == 0) {
      return 0;
    }
    __dev_kfree_skb_any(param_3,1);
    return 0;
  }
  if (param_1 < 2 && param_3 != 0) {
    if ((ifd_debug & 1) != 0) {
      printk("%s original pkt:from idm:%d, ssid:%d\n","idm_fdb_multi_send_handle",param_1,param_2);
      printk("skb->head:\t%p\nskb->data:\t%p\nskb->mac_head:\t%u\nskb->cloned:\t%d\nref:\t%d\n",
             *(undefined4 *)(param_3 + 0xd0),*(undefined4 *)(param_3 + 0xd4),
             *(undefined2 *)(param_3 + 0xb2),*(byte *)(param_3 + 0x72) & 1,
             *(undefined4 *)(*(int *)(param_3 + 0xcc) + 0x20));
      if (*(int *)(param_3 + 100) != 0) {
        printk("%02x ",**(undefined1 **)(param_3 + 0xd4));
        uVar4 = 0;
        while (uVar4 = uVar4 + 1, uVar4 < *(uint *)(param_3 + 100)) {
          printk("%02x ",*(undefined1 *)(*(int *)(param_3 + 0xd4) + uVar4));
          uVar9 = uVar4 & 0x8000000f;
          if ((int)uVar9 < 0) {
            uVar9 = ~(~((uVar9 - 1) * 0x10000000) >> 0x1c) + 1;
          }
          if (uVar9 == 0xf) {
            printk(&_LC1);
          }
        }
      }
      printk(&_LC1);
    }
    __memzero(iVar1,0x300);
    if (param_4 == 1) {
      if (param_1 == 0) {
        iVar15 = 4;
        local_80 = &mcast_flood_group_idm0;
      }
      else {
        if (param_1 != 1) goto LAB_0001118c;
        iVar15 = 5;
        local_80 = &mcast_flood_group_idm1;
      }
      puVar16 = g_PortMacInfo;
      iVar13 = param_1 * 0x108;
      uVar4 = 0;
      local_58[0] = 0;
      uVar9 = *(uint *)(&DAT_00014b18 + iVar13);
      *(uint *)(&DAT_00014b18 + iVar13) = uVar9 + 1;
      *(uint *)(&DAT_00014b1c + iVar13) =
           *(int *)(&DAT_00014b1c + iVar13) + (uint)(0xfffffffe < uVar9);
      uVar9 = *(uint *)(&DAT_00014b20 + iVar13);
      uVar12 = *(uint *)(param_3 + 100);
      *(uint *)(&DAT_00014b20 + iVar13) = uVar9 + uVar12;
      *(uint *)(&DAT_00014b24 + iVar13) =
           *(int *)(&DAT_00014b24 + iVar13) + (uint)CARRY4(uVar9,uVar12);
      __memzero(g_PortMacInfo,0xf00);
      iVar13 = *(int *)(param_3 + 0xd4);
      local_50 = g_PortMacInfo;
      local_58[1] = 0x20;
      uVar7 = *(ushort *)(iVar13 + 0xc) << 8 | *(ushort *)(iVar13 + 0xc) >> 8;
      if (uVar7 == 0x8100) {
        uVar4 = (uint)*(ushort *)(iVar13 + 0x10);
        uVar9 = (uVar4 & 0xff) << 8 | (uint)(*(ushort *)(iVar13 + 0x10) >> 8);
        if (uVar4 != 0x81) {
          puVar16 = (undefined1 *)(iVar13 + 0x12);
        }
        uVar17 = (*(ushort *)(iVar13 + 0xe) & 0xf) << 8 | *(ushort *)(iVar13 + 0xe) >> 8;
        if (uVar4 == 0x81) {
          uVar4 = (uint)*(ushort *)(iVar13 + 0x14);
          puVar16 = (undefined1 *)(iVar13 + 0x16);
          uVar9 = (uVar4 & 0xff) << 8 | (uint)(*(ushort *)(iVar13 + 0x14) >> 8);
        }
        if ((ifd_debug & 2) != 0) goto LAB_00011910;
LAB_00011534:
        if (uVar9 == 0x800) goto LAB_00011570;
        if ((uVar7 == 0x86dd) || (uVar9 == 0x86dd)) {
          local_4c = *(undefined4 *)(puVar16 + 0x18);
          uStack_48 = *(undefined4 *)(puVar16 + 0x1c);
          uStack_44 = *(undefined4 *)(puVar16 + 0x20);
          uStack_40 = *(undefined4 *)(puVar16 + 0x24);
          local_3c = *(undefined4 *)(puVar16 + 8);
          uStack_38 = *(undefined4 *)(puVar16 + 0xc);
          uStack_34 = *(undefined4 *)(puVar16 + 0x10);
          uStack_30 = *(undefined4 *)(puVar16 + 0x14);
          local_2c = uVar17;
          iVar13 = br_lookup_mfd(0,&local_4c,local_58,2);
          goto LAB_000115a0;
        }
LAB_00011554:
        iVar2 = __idm_fdb_create_items_constprop_0(local_80,iVar15,iVar1,&local_6c);
        goto LAB_00011224;
      }
      puVar16 = (undefined1 *)(iVar13 + 0xe);
      if ((ifd_debug & 2) == 0) {
        uVar17 = 0;
        uVar4 = 0;
      }
      else {
        uVar17 = 0;
        uVar9 = 0;
LAB_00011910:
        printk("ethh->h_proto:%x\nvlan_tagged_proto:%x\n",uVar7,uVar9);
        uVar7 = *(ushort *)(iVar13 + 0xc) << 8 | *(ushort *)(iVar13 + 0xc) >> 8;
      }
      if (uVar7 != 0x800) {
        uVar9 = (uVar4 & 0xff) << 8 | uVar4 >> 8;
        goto LAB_00011534;
      }
LAB_00011570:
      uVar9 = *(uint *)(puVar16 + 0x10);
      uVar4 = *(uint *)(puVar16 + 0xc);
      local_64 = uVar9 << 0x18 | (uVar9 >> 8 & 0xff) << 0x10 | (uVar9 >> 0x10 & 0xff) << 8 |
                 uVar9 >> 0x18;
      local_60 = uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 |
                 uVar4 >> 0x18;
      local_5c = uVar17;
      iVar13 = br_lookup_mfd(&local_64,0,local_58,2);
LAB_000115a0:
      if (iVar13 == 0) {
        if (0 < local_58[0]) {
          iVar13 = 0;
          ppuVar5 = local_80;
          iVar14 = iVar1;
          iVar3 = 0;
          do {
            ppuVar6 = ppuVar5 + 1;
            puVar11 = *ppuVar5;
            iVar2 = iVar3;
            if (((*puVar11 != '\0') &&
                (*(int *)(puVar11 + 0x14) == *(int *)(local_50 + iVar13 * 0x78 + 0x10))) &&
               (0 < *(int *)(local_50 + iVar13 * 0x78 + 0x14))) {
              puVar10 = (undefined4 *)(local_50 + iVar13 * 0x78 + 0x18);
              iVar18 = iVar14;
              do {
                *(pointer_____offset_0x940___ *)(iVar18 + 8) = puVar11;
                *(undefined4 *)(iVar18 + 0xc) = 1;
                iVar2 = iVar2 + 1;
                iVar14 = iVar18 + 0x18;
                *(undefined4 *)(iVar18 + 0x12) = *puVar10;
                *(undefined2 *)(iVar18 + 0x16) = *(undefined2 *)(puVar10 + 1);
                puVar10 = (undefined4 *)((int)puVar10 + 6);
                iVar18 = iVar14;
              } while (iVar2 - iVar3 < *(int *)(local_50 + iVar13 * 0x78 + 0x14));
            }
            ppuVar5 = ppuVar6;
            iVar3 = iVar2;
          } while ((ppuVar6 != local_80 + iVar15) ||
                  (iVar13 = iVar13 + 1, ppuVar5 = local_80, iVar13 != local_58[0]));
          goto LAB_00011224;
        }
      }
      else if (iVar13 == 1) goto LAB_00011554;
    }
    else {
      if (param_2 == 0xff) {
        if (param_1 == 0) {
          ppuVar5 = &flood_group_idm0;
        }
        else {
          if (param_1 != 1) goto LAB_0001118c;
          ppuVar5 = &flood_group_idm1;
        }
        uVar8 = 5;
        iVar15 = param_1 * 0x108 + param_4 * 0x18;
        uVar4 = *(uint *)(&idm_flood_cnt + iVar15);
        *(uint *)(&idm_flood_cnt + iVar15) = uVar4 + 1;
        *(uint *)(&DAT_00014b04 + iVar15) =
             *(int *)(&DAT_00014b04 + iVar15) + (uint)(0xfffffffe < uVar4);
        uVar4 = *(uint *)(&DAT_00014b08 + iVar15);
        uVar9 = *(uint *)(param_3 + 100);
        *(uint *)(&DAT_00014b08 + iVar15) = uVar4 + uVar9;
        *(uint *)(&DAT_00014b0c + iVar15) =
             *(int *)(&DAT_00014b0c + iVar15) + (uint)CARRY4(uVar4,uVar9);
      }
      else {
        if (7 < param_2) goto LAB_0001118c;
        uVar8 = 1;
        local_68 = &fdb_list + (param_2 + param_1 * 8) * 0x128;
        ppuVar5 = &local_68;
      }
      iVar2 = __idm_fdb_create_items_constprop_0(ppuVar5,uVar8,iVar1,&local_6c);
LAB_00011224:
      if (0 < iVar2) {
        iVar13 = 0;
        iVar15 = 0;
        do {
          if (iVar13 == 0) {
            iVar14 = iVar15 + 1;
            iVar15 = iVar15 * 0x18;
LAB_000112b8:
            iVar13 = iVar1 + iVar15;
            if (1 < *(uint *)(iVar13 + 0xc)) {
              iVar13 = 0;
            }
          }
          else {
            local_68 = *(pointer_____offset_0x940___ *)(iVar13 + 8);
            iVar18 = *(int *)(local_68 + 0x14);
            iVar3 = skb_copy(param_3,0x20);
            if (iVar3 != 0) {
              *(int *)(iVar3 + 0x18) = iVar18;
              uVar4 = ifd_debug;
              if (*(int *)(iVar13 + 0xc) == 1) {
                puVar10 = *(undefined4 **)(iVar3 + 0xd4);
                *puVar10 = *(undefined4 *)(iVar13 + 0x12);
                uVar4 = ifd_debug;
                uVar9 = ifd_debug & 2;
                *(undefined2 *)(puVar10 + 1) = *(undefined2 *)(iVar13 + 0x16);
                if (uVar9 != 0) {
                  INC_MTRANS_CNT(local_68,(undefined4 *)(iVar13 + 0x12),puVar10,iVar3);
                  uVar4 = ifd_debug;
                }
              }
              if ((uVar4 & 1) == 0) {
                iVar14 = iVar15 + 1;
                iVar15 = iVar15 * 0x18;
              }
              else {
                printk("%s:from idm:%d, ssid:%d, multi send to %s\n","idm_fdb_multi_send_handle",
                       local_68[1],param_2,iVar18);
                printk("skb->head:\t%p\nskb->data:\t%p\nskb->mac_head:\t%u\nskb->cloned:\t%d\nref:\t%d\n"
                       ,*(undefined4 *)(iVar3 + 0xd0),*(undefined4 *)(iVar3 + 0xd4),
                       *(undefined2 *)(iVar3 + 0xb2),*(byte *)(iVar3 + 0x72) & 1,
                       *(undefined4 *)(*(int *)(iVar3 + 0xcc) + 0x20));
                if (*(int *)(iVar3 + 100) == 0) {
                  iVar14 = 1;
                  iVar15 = 0;
                }
                else {
                  printk("%02x ",**(undefined1 **)(iVar3 + 0xd4));
                  uVar4 = 0;
                  while (uVar9 = uVar4 + 1, uVar9 < *(uint *)(iVar3 + 100)) {
                    printk("%02x ",*(undefined1 *)(*(int *)(iVar3 + 0xd4) + uVar9));
                    uVar12 = uVar9 & 0x8000000f;
                    if ((int)uVar12 < 0) {
                      uVar12 = ~(~((uVar12 - 1) * 0x10000000) >> 0x1c) + 1;
                    }
                    uVar4 = uVar9;
                    if (uVar12 == 0xf) {
                      printk(&_LC1);
                    }
                  }
                  iVar14 = uVar4 + 2;
                  iVar15 = uVar9 * 0x18;
                }
                printk(&_LC1);
              }
              iVar13 = (**(code **)(*(int *)(iVar18 + 300) + 0x10))(iVar3,iVar18);
              if (iVar13 < 0) {
                uVar4 = *(uint *)(local_68 + 0xc0);
                *(uint *)(local_68 + 0xc0) = uVar4 + 1;
                *(uint *)(local_68 + 0xc4) = *(int *)(local_68 + 0xc4) + (uint)(0xfffffffe < uVar4);
                uVar4 = *(uint *)(local_68 + 200);
                uVar9 = *(uint *)(iVar3 + 100);
                *(uint *)(local_68 + 200) = uVar4 + uVar9;
                *(uint *)(local_68 + 0xcc) = *(int *)(local_68 + 0xcc) + (uint)CARRY4(uVar4,uVar9);
                __dev_kfree_skb_any(iVar3,1);
              }
              goto LAB_000112b8;
            }
            iVar14 = iVar15 + 1;
          }
          iVar15 = iVar14;
        } while (iVar14 < iVar2);
        if (iVar13 == 0) goto LAB_00011198;
        local_68 = *(pointer_____offset_0x940___ *)(iVar13 + 8);
        iVar15 = *(int *)(local_68 + 0x14);
        *(int *)(param_3 + 0x18) = iVar15;
        uVar4 = ifd_debug;
        if (*(int *)(iVar13 + 0xc) == 1) {
          puVar10 = *(undefined4 **)(param_3 + 0xd4);
          *puVar10 = *(undefined4 *)(iVar13 + 0x12);
          uVar4 = ifd_debug;
          *(undefined2 *)(puVar10 + 1) = *(undefined2 *)(iVar13 + 0x16);
          if ((uVar4 & 2) != 0) {
            INC_MTRANS_CNT(local_68,(undefined4 *)(iVar13 + 0x12),puVar10,param_3);
            uVar4 = ifd_debug;
          }
        }
        if ((uVar4 & 1) != 0) {
          printk("%s:from idm:%d, ssid:%d, multi send to %s\n","idm_fdb_multi_send_handle",
                 local_68[1],param_2,iVar15);
          printk("skb->head:\t%p\nskb->data:\t%p\nskb->mac_head:\t%u\nskb->cloned:\t%d\nref:\t%d\n",
                 *(undefined4 *)(param_3 + 0xd0),*(undefined4 *)(param_3 + 0xd4),
                 *(undefined2 *)(param_3 + 0xb2),*(byte *)(param_3 + 0x72) & 1,
                 *(undefined4 *)(*(int *)(param_3 + 0xcc) + 0x20));
          if (*(int *)(param_3 + 100) != 0) {
            uVar4 = 0;
            printk("%02x ",**(undefined1 **)(param_3 + 0xd4));
            while (uVar4 = uVar4 + 1, uVar4 < *(uint *)(param_3 + 100)) {
              printk("%02x ",*(undefined1 *)(*(int *)(param_3 + 0xd4) + uVar4));
              uVar9 = uVar4 & 0x8000000f;
              if ((int)uVar9 < 0) {
                uVar9 = ~(~((uVar9 - 1) * 0x10000000) >> 0x1c) + 1;
              }
              if (uVar9 == 0xf) {
                printk(&_LC1);
              }
            }
          }
          printk(&_LC1);
        }
        iVar15 = (**(code **)(*(int *)(iVar15 + 300) + 0x10))(param_3,iVar15);
        if (-1 < iVar15) goto LAB_00011198;
        uVar9 = *(uint *)(local_68 + 0xc0);
        uVar4 = *(uint *)(local_68 + 200);
        *(uint *)(local_68 + 0xc0) = uVar9 + 1;
        *(uint *)(local_68 + 0xc4) = *(int *)(local_68 + 0xc4) + (uint)(0xfffffffe < uVar9);
        uVar9 = *(uint *)(param_3 + 100);
        *(uint *)(local_68 + 200) = uVar4 + uVar9;
        *(uint *)(local_68 + 0xcc) = *(int *)(local_68 + 0xcc) + (uint)CARRY4(uVar4,uVar9);
        goto LAB_0001118c;
      }
    }
    if (param_2 == 0xff) {
      param_1 = param_1 * 0x108;
      uVar9 = *(uint *)(&DAT_00014bf0 + param_1);
      uVar4 = *(uint *)(&DAT_00014bf8 + param_1);
      *(uint *)(&DAT_00014bf0 + param_1) = uVar9 + 1;
      *(uint *)(&DAT_00014bf4 + param_1) =
           *(int *)(&DAT_00014bf4 + param_1) + (uint)(0xfffffffe < uVar9);
      uVar9 = *(uint *)(param_3 + 100);
      *(uint *)(&DAT_00014bf8 + param_1) = uVar4 + uVar9;
      *(uint *)(&DAT_00014bfc + param_1) =
           *(int *)(&DAT_00014bfc + param_1) + (uint)CARRY4(uVar4,uVar9);
    }
    else if (local_68 != (pointer_____offset_0x940___)0x0) {
      uVar9 = *(uint *)(local_68 + 0x108);
      uVar4 = *(uint *)(local_68 + 0x110);
      *(uint *)(local_68 + 0x108) = uVar9 + 1;
      *(uint *)(local_68 + 0x10c) = *(int *)(local_68 + 0x10c) + (uint)(0xfffffffe < uVar9);
      uVar9 = *(uint *)(param_3 + 100);
      *(uint *)(local_68 + 0x110) = uVar4 + uVar9;
      *(uint *)(local_68 + 0x114) = *(int *)(local_68 + 0x114) + (uint)CARRY4(uVar4,uVar9);
    }
  }
  else if (param_3 == 0) goto LAB_00011198;
LAB_0001118c:
  __dev_kfree_skb_any(param_3,1);
LAB_00011198:
  kfree(iVar1);
  return 0;
}

