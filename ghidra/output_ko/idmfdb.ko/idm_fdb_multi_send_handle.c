// module: idmfdb.ko
// function: idm_fdb_multi_send_handle @ 0x11038
// size: 2300 bytes
//

undefined4 idm_fdb_multi_send_handle(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  pointer_____offset_0x940___ *ppuVar4;
  pointer_____offset_0x940___ *ppuVar5;
  ushort uVar6;
  undefined4 uVar7;
  uint uVar8;
  undefined4 *puVar9;
  pointer_____offset_0x940___ puVar10;
  ushort uVar11;
  undefined1 *puVar12;
  undefined1 *puVar13;
  undefined1 *puVar14;
  int iVar15;
  uint uVar16;
  int local_37c;
  pointer_____offset_0x940___ *local_378;
  undefined4 local_36c;
  pointer_____offset_0x940___ local_368;
  uint local_364;
  uint local_360;
  ushort local_35c;
  int local_358 [2];
  undefined1 *local_350;
  undefined4 local_34c;
  undefined4 uStack_348;
  undefined4 uStack_344;
  undefined4 uStack_340;
  undefined4 local_33c;
  undefined4 uStack_338;
  undefined4 uStack_334;
  undefined4 uStack_330;
  ushort local_32c;
  undefined1 auStack_328 [12];
  uint local_31c [190];
  
  local_36c = 0x20;
  local_368 = (pointer_____offset_0x940___)0x0;
  if (1 < param_1 || param_3 == 0) {
    if (param_3 == 0) {
      return 0;
    }
    goto LAB_0001120c;
  }
  if ((ifd_debug & 1) != 0) {
    printk("%s original pkt:from idm:%d, ssid:%d\n","idm_fdb_multi_send_handle",param_1,param_2);
    printk("skb->head:\t%p\nskb->data:\t%p\nskb->mac_head:\t%p\nskb->cloned:\t%d\nref:\t%d\n",
           *(undefined4 *)(param_3 + 200),*(undefined4 *)(param_3 + 0xcc),
           *(undefined2 *)(param_3 + 0xaa),*(byte *)(param_3 + 0x72) & 1,
           *(undefined4 *)(*(int *)(param_3 + 0xc4) + 0x20));
    if (*(int *)(param_3 + 100) != 0) {
      printk("%02x ",**(undefined1 **)(param_3 + 0xcc));
      uVar3 = 0;
      while (uVar3 = uVar3 + 1, uVar3 < *(uint *)(param_3 + 100)) {
        printk("%02x ",*(undefined1 *)(*(int *)(param_3 + 0xcc) + uVar3));
        uVar8 = uVar3 & 0x8000000f;
        if ((int)uVar8 < 0) {
          uVar8 = ~(~((uVar8 - 1) * 0x10000000) >> 0x1c) + 1;
        }
        if (uVar8 == 0xf) {
          printk(&_LC1);
        }
      }
    }
    printk(&_LC1);
  }
  if (param_4 == 1) {
    if (param_1 == 0) {
      local_37c = 4;
      local_378 = &mcast_flood_group_idm0;
    }
    else {
      if (param_1 != 1) goto LAB_0001120c;
      local_378 = &mcast_flood_group_idm1;
      local_37c = 5;
    }
    iVar2 = param_1 * 0x108;
    uVar3 = 0;
    local_358[0] = 0;
    iVar15 = *(int *)(&DAT_00014974 + iVar2) + (uint)(0xfffffffe < *(uint *)(&DAT_00014970 + iVar2))
    ;
    *(uint *)(&DAT_00014970 + iVar2) = *(uint *)(&DAT_00014970 + iVar2) + 1;
    *(int *)(&DAT_00014974 + iVar2) = iVar15;
    uVar8 = *(uint *)(&DAT_00014978 + iVar2);
    uVar16 = *(uint *)(param_3 + 100);
    *(uint *)(&DAT_00014978 + iVar2) = uVar8 + uVar16;
    *(uint *)(&DAT_0001497c + iVar2) = *(int *)(&DAT_0001497c + iVar2) + (uint)CARRY4(uVar8,uVar16);
    __memzero(g_PortMacInfo,0xf00);
    iVar2 = *(int *)(param_3 + 0xcc);
    local_350 = g_PortMacInfo;
    local_358[1] = 0x20;
    uVar6 = *(ushort *)(iVar2 + 0xc) << 8 | *(ushort *)(iVar2 + 0xc) >> 8;
    if (uVar6 == 0x8100) {
      uVar3 = (uint)*(ushort *)(iVar2 + 0x10);
      uVar8 = (uVar3 & 0xff) << 8 | (uint)(*(ushort *)(iVar2 + 0x10) >> 8);
      if (uVar3 != 0x81) {
        iVar15 = iVar2 + 0x12;
      }
      uVar11 = (*(ushort *)(iVar2 + 0xe) & 0xf) << 8 | *(ushort *)(iVar2 + 0xe) >> 8;
      if (uVar3 == 0x81) {
        uVar3 = (uint)*(ushort *)(iVar2 + 0x14);
        iVar15 = iVar2 + 0x16;
        uVar8 = (uVar3 & 0xff) << 8 | (uint)(*(ushort *)(iVar2 + 0x14) >> 8);
      }
      if ((ifd_debug & 2) != 0) goto LAB_000117d8;
LAB_0001137c:
      if (uVar8 == 0x800) goto LAB_00011498;
      if ((uVar6 == 0x86dd) || (uVar8 == 0x86dd)) {
        local_34c = *(undefined4 *)(iVar15 + 0x18);
        uStack_348 = *(undefined4 *)(iVar15 + 0x1c);
        uStack_344 = *(undefined4 *)(iVar15 + 0x20);
        uStack_340 = *(undefined4 *)(iVar15 + 0x24);
        local_33c = *(undefined4 *)(iVar15 + 8);
        uStack_338 = *(undefined4 *)(iVar15 + 0xc);
        uStack_334 = *(undefined4 *)(iVar15 + 0x10);
        uStack_330 = *(undefined4 *)(iVar15 + 0x14);
        local_32c = uVar11;
        iVar2 = br_lookup_mfd(0,&local_34c,local_358,2);
        goto LAB_000114c8;
      }
LAB_0001139c:
      iVar1 = __idm_fdb_create_items_constprop_0(local_378,local_37c,auStack_328,&local_36c);
      goto LAB_000110e8;
    }
    iVar15 = iVar2 + 0xe;
    if ((ifd_debug & 2) == 0) {
      uVar11 = 0;
      uVar3 = 0;
    }
    else {
      uVar11 = 0;
      uVar8 = 0;
LAB_000117d8:
      printk("ethh->h_proto:%x\nvlan_tagged_proto:%x\n",uVar6,uVar8);
      uVar6 = *(ushort *)(iVar2 + 0xc) << 8 | *(ushort *)(iVar2 + 0xc) >> 8;
    }
    if (uVar6 != 0x800) {
      uVar8 = (uVar3 & 0xff) << 8 | uVar3 >> 8;
      goto LAB_0001137c;
    }
LAB_00011498:
    local_35c = uVar11;
    uVar8 = *(uint *)(iVar15 + 0x10);
    uVar3 = *(uint *)(iVar15 + 0xc);
    local_364 = uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 |
                uVar8 >> 0x18;
    local_360 = uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 |
                uVar3 >> 0x18;
    iVar2 = br_lookup_mfd(&local_364,0,local_358,2);
LAB_000114c8:
    if (iVar2 == 0) {
      if (0 < local_358[0]) {
        puVar13 = auStack_328;
        iVar2 = 0;
        ppuVar4 = local_378;
        iVar15 = 0;
        do {
          ppuVar5 = ppuVar4 + 1;
          puVar10 = *ppuVar4;
          iVar1 = iVar15;
          if (((*puVar10 != '\0') &&
              (*(int *)(puVar10 + 0x14) == *(int *)(local_350 + iVar2 * 0x78 + 0x10))) &&
             (0 < *(int *)(local_350 + iVar2 * 0x78 + 0x14))) {
            puVar9 = (undefined4 *)(local_350 + iVar2 * 0x78 + 0x18);
            puVar12 = puVar13;
            do {
              *(pointer_____offset_0x940___ *)(puVar12 + 8) = puVar10;
              *(undefined4 *)(puVar12 + 0xc) = 1;
              iVar1 = iVar1 + 1;
              puVar13 = puVar12 + 0x18;
              *(undefined4 *)(puVar12 + 0x12) = *puVar9;
              *(undefined2 *)(puVar12 + 0x16) = *(undefined2 *)(puVar9 + 1);
              puVar9 = (undefined4 *)((int)puVar9 + 6);
              puVar12 = puVar13;
            } while (iVar1 - iVar15 < *(int *)(local_350 + iVar2 * 0x78 + 0x14));
          }
          ppuVar4 = ppuVar5;
          iVar15 = iVar1;
        } while ((ppuVar5 != local_378 + local_37c) ||
                (iVar2 = iVar2 + 1, ppuVar4 = local_378, iVar2 != local_358[0]));
        goto LAB_000110e8;
      }
    }
    else if (iVar2 == 1) goto LAB_0001139c;
  }
  else {
    if (param_2 == 0xff) {
      if (param_1 == 0) {
        ppuVar4 = &flood_group_idm0;
      }
      else {
        if (param_1 != 1) goto LAB_0001120c;
        ppuVar4 = &flood_group_idm1;
      }
      uVar7 = 5;
      iVar2 = param_1 * 0x108 + param_4 * 0x18;
      uVar3 = *(uint *)(&idm_flood_cnt + iVar2);
      uVar8 = *(uint *)(&DAT_00014960 + iVar2);
      *(uint *)(&idm_flood_cnt + iVar2) = uVar3 + 1;
      *(uint *)(&DAT_0001495c + iVar2) =
           *(int *)(&DAT_0001495c + iVar2) + (uint)(0xfffffffe < uVar3);
      uVar3 = *(uint *)(param_3 + 100);
      *(uint *)(&DAT_00014960 + iVar2) = uVar8 + uVar3;
      *(uint *)(&DAT_00014964 + iVar2) = *(int *)(&DAT_00014964 + iVar2) + (uint)CARRY4(uVar8,uVar3)
      ;
    }
    else {
      if (7 < param_2) goto LAB_0001120c;
      uVar7 = 1;
      local_368 = &fdb_list + (param_2 + param_1 * 8) * 0x128;
      ppuVar4 = &local_368;
    }
    iVar1 = __idm_fdb_create_items_constprop_0(ppuVar4,uVar7,auStack_328,&local_36c);
LAB_000110e8:
    if (0 < iVar1) {
      puVar12 = (undefined1 *)0x0;
      puVar13 = puVar12;
      do {
        if (puVar12 == (undefined1 *)0x0) {
          puVar14 = puVar13 + 1;
LAB_00011164:
          if (local_31c[(int)puVar13 * 6] < 2) {
            puVar12 = auStack_328 + (int)puVar13 * 0x18;
          }
          else {
            puVar12 = (undefined1 *)0x0;
          }
        }
        else {
          local_368 = *(pointer_____offset_0x940___ *)(puVar12 + 8);
          iVar15 = *(int *)(local_368 + 0x14);
          iVar2 = skb_copy(param_3,0x20);
          if (iVar2 != 0) {
            *(int *)(iVar2 + 0x18) = iVar15;
            uVar3 = ifd_debug;
            if (*(int *)(puVar12 + 0xc) == 1) {
              puVar9 = *(undefined4 **)(iVar2 + 0xcc);
              *puVar9 = *(undefined4 *)(puVar12 + 0x12);
              uVar3 = ifd_debug;
              uVar8 = ifd_debug & 2;
              *(undefined2 *)(puVar9 + 1) = *(undefined2 *)(puVar12 + 0x16);
              if (uVar8 != 0) {
                INC_MTRANS_CNT(local_368,puVar12 + 0x12,puVar9,iVar2);
                uVar3 = ifd_debug;
              }
            }
            if ((uVar3 & 1) == 0) {
              puVar14 = puVar13 + 1;
            }
            else {
              printk("%s:from idm:%d, ssid:%d, multi send to %s\n","idm_fdb_multi_send_handle",
                     local_368[1],param_2,iVar15);
              printk("skb->head:\t%p\nskb->data:\t%p\nskb->mac_head:\t%p\nskb->cloned:\t%d\nref:\t%d\n"
                     ,*(undefined4 *)(iVar2 + 200),*(undefined4 *)(iVar2 + 0xcc),
                     *(undefined2 *)(iVar2 + 0xaa),*(byte *)(iVar2 + 0x72) & 1,
                     *(undefined4 *)(*(int *)(iVar2 + 0xc4) + 0x20));
              if (*(int *)(iVar2 + 100) == 0) {
                puVar14 = (undefined1 *)0x1;
                puVar13 = (undefined1 *)0x0;
              }
              else {
                printk("%02x ",**(undefined1 **)(iVar2 + 0xcc));
                puVar14 = (undefined1 *)0x0;
                while (puVar13 = puVar14 + 1, puVar13 < *(undefined1 **)(iVar2 + 100)) {
                  printk("%02x ",puVar13[*(int *)(iVar2 + 0xcc)]);
                  uVar3 = (uint)puVar13 & 0x8000000f;
                  if ((int)uVar3 < 0) {
                    uVar3 = ~(~((uVar3 - 1) * 0x10000000) >> 0x1c) + 1;
                  }
                  puVar14 = puVar13;
                  if (uVar3 == 0xf) {
                    printk(&_LC1);
                  }
                }
                puVar14 = puVar14 + 2;
              }
              printk(&_LC1);
            }
            iVar15 = (**(code **)(*(int *)(iVar15 + 300) + 0x10))(iVar2,iVar15);
            if (iVar15 < 0) {
              uVar3 = *(uint *)(local_368 + 0xc0);
              uVar8 = *(uint *)(local_368 + 200);
              *(uint *)(local_368 + 0xc0) = uVar3 + 1;
              *(uint *)(local_368 + 0xc4) = *(int *)(local_368 + 0xc4) + (uint)(0xfffffffe < uVar3);
              uVar3 = *(uint *)(iVar2 + 100);
              *(uint *)(local_368 + 200) = uVar8 + uVar3;
              *(uint *)(local_368 + 0xcc) = *(int *)(local_368 + 0xcc) + (uint)CARRY4(uVar8,uVar3);
              __dev_kfree_skb_any(iVar2,1);
            }
            goto LAB_00011164;
          }
          puVar14 = puVar13 + 1;
        }
        puVar13 = puVar14;
      } while ((int)puVar14 < iVar1);
      if (puVar12 == (undefined1 *)0x0) {
        return 0;
      }
      local_368 = *(pointer_____offset_0x940___ *)(puVar12 + 8);
      iVar2 = *(int *)(local_368 + 0x14);
      *(int *)(param_3 + 0x18) = iVar2;
      uVar3 = ifd_debug;
      if (*(int *)(puVar12 + 0xc) == 1) {
        puVar9 = *(undefined4 **)(param_3 + 0xcc);
        *puVar9 = *(undefined4 *)(puVar12 + 0x12);
        uVar3 = ifd_debug;
        uVar8 = ifd_debug & 2;
        *(undefined2 *)(puVar9 + 1) = *(undefined2 *)(puVar12 + 0x16);
        if (uVar8 != 0) {
          INC_MTRANS_CNT(local_368,puVar12 + 0x12,puVar9,param_3);
          uVar3 = ifd_debug;
        }
      }
      if ((uVar3 & 1) != 0) {
        printk("%s:from idm:%d, ssid:%d, multi send to %s\n","idm_fdb_multi_send_handle",
               local_368[1],param_2,iVar2);
        printk("skb->head:\t%p\nskb->data:\t%p\nskb->mac_head:\t%p\nskb->cloned:\t%d\nref:\t%d\n",
               *(undefined4 *)(param_3 + 200),*(undefined4 *)(param_3 + 0xcc),
               *(undefined2 *)(param_3 + 0xaa),*(byte *)(param_3 + 0x72) & 1,
               *(undefined4 *)(*(int *)(param_3 + 0xc4) + 0x20));
        if (*(int *)(param_3 + 100) != 0) {
          uVar3 = 0;
          printk("%02x ",**(undefined1 **)(param_3 + 0xcc));
          while (uVar3 = uVar3 + 1, uVar3 < *(uint *)(param_3 + 100)) {
            printk("%02x ",*(undefined1 *)(*(int *)(param_3 + 0xcc) + uVar3));
            uVar8 = uVar3 & 0x8000000f;
            if ((int)uVar8 < 0) {
              uVar8 = ~(~((uVar8 - 1) * 0x10000000) >> 0x1c) + 1;
            }
            if (uVar8 == 0xf) {
              printk(&_LC1);
            }
          }
        }
        printk(&_LC1);
      }
      iVar2 = (**(code **)(*(int *)(iVar2 + 300) + 0x10))(param_3,iVar2);
      if (-1 < iVar2) {
        return 0;
      }
      uVar3 = *(uint *)(local_368 + 0xc0);
      uVar8 = *(uint *)(local_368 + 200);
      *(uint *)(local_368 + 0xc0) = uVar3 + 1;
      *(uint *)(local_368 + 0xc4) = *(int *)(local_368 + 0xc4) + (uint)(0xfffffffe < uVar3);
      uVar3 = *(uint *)(param_3 + 100);
      *(uint *)(local_368 + 200) = uVar8 + uVar3;
      *(uint *)(local_368 + 0xcc) = *(int *)(local_368 + 0xcc) + (uint)CARRY4(uVar8,uVar3);
      goto LAB_0001120c;
    }
  }
  if (param_2 == 0xff) {
    param_1 = param_1 * 0x108;
    uVar3 = *(uint *)(&DAT_00014a48 + param_1);
    uVar8 = *(uint *)(&DAT_00014a50 + param_1);
    *(uint *)(&DAT_00014a48 + param_1) = uVar3 + 1;
    *(uint *)(&DAT_00014a4c + param_1) =
         *(int *)(&DAT_00014a4c + param_1) + (uint)(0xfffffffe < uVar3);
    uVar3 = *(uint *)(param_3 + 100);
    *(uint *)(&DAT_00014a50 + param_1) = uVar8 + uVar3;
    *(uint *)(&DAT_00014a54 + param_1) =
         *(int *)(&DAT_00014a54 + param_1) + (uint)CARRY4(uVar8,uVar3);
  }
  else if (local_368 != (pointer_____offset_0x940___)0x0) {
    uVar3 = *(uint *)(local_368 + 0x108);
    uVar8 = *(uint *)(local_368 + 0x110);
    *(uint *)(local_368 + 0x108) = uVar3 + 1;
    *(uint *)(local_368 + 0x10c) = *(int *)(local_368 + 0x10c) + (uint)(0xfffffffe < uVar3);
    uVar3 = *(uint *)(param_3 + 100);
    *(uint *)(local_368 + 0x110) = uVar8 + uVar3;
    *(uint *)(local_368 + 0x114) = *(int *)(local_368 + 0x114) + (uint)CARRY4(uVar8,uVar3);
  }
LAB_0001120c:
  __dev_kfree_skb_any(param_3,1);
  return 0;
}

