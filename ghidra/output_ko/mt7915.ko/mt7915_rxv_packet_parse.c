// module: mt7915.ko
// function: mt7915_rxv_packet_parse @ 0x17b384
// size: 2252 bytes
//

undefined4 mt7915_rxv_packet_parse(int param_1,uint *param_2)

{
  byte bVar1;
  char cVar2;
  undefined2 uVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  void *__dest;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  byte bVar12;
  uint uVar13;
  int *piVar14;
  int *piVar15;
  int *piVar16;
  byte bVar17;
  ushort *puVar18;
  uint uVar19;
  byte bVar20;
  uint *__src;
  size_t __n;
  int *piVar21;
  uint __n_00;
  int *piVar22;
  uint local_94;
  int *local_88;
  uint local_74;
  int *local_70;
  ushort local_68;
  undefined4 local_66;
  ushort local_62;
  byte local_60;
  byte local_5f;
  ushort local_5e;
  undefined1 auStack_5c [8];
  byte local_54;
  undefined2 local_52;
  void *local_50;
  undefined2 local_4c;
  byte local_4a;
  uint local_48;
  undefined1 local_44;
  byte local_43;
  byte local_42;
  byte local_41;
  byte local_40;
  undefined1 auStack_3c [8];
  undefined1 local_34;
  undefined2 local_32;
  byte local_30;
  int local_2c [2];
  
  iVar6 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  os_zero_mem(&local_62,6);
  if (param_2 == (uint *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s(): null pointer for rxv pkt.\n","mt7915_rxv_pkt_hdr_parser");
      local_94 = (uint)local_60;
      __n = (size_t)local_62;
      goto LAB_0017b3f8;
    }
LAB_0017b604:
    local_94 = (uint)local_60;
    __n = (size_t)local_62;
  }
  else {
    uVar13 = *param_2;
    local_94 = (uVar13 << 0xb) >> 0x1b;
    __n = uVar13 & 0xffff;
    local_60 = (byte)((uVar13 << 0xb) >> 0x1b);
    local_62 = (ushort)uVar13;
    local_5f = (byte)(uVar13 >> 0x1d);
    local_5e = (ushort)((param_2[1] << 4) >> 0x14);
LAB_0017b3f8:
    if (2 < DebugLevel) {
      printk("RxV Report: RxvCnt: %d, ByteCnt: %d\n",local_94,__n);
      goto LAB_0017b604;
    }
  }
  __dest = *(void **)(param_1 + 0xa7c214);
  if (__dest == (void *)0x0) {
    os_alloc_mem(param_1,param_1 + 0xa7c214,__n);
    *(ushort *)(param_1 + 0xa7c210) = (ushort)__n;
    __dest = *(void **)(param_1 + 0xa7c214);
  }
  else {
    puVar18 = (ushort *)(param_1 + 0xa7c210);
    if (__n != *puVar18) {
      os_zero_mem();
      os_free_mem(*(undefined4 *)(param_1 + 0xa7c214));
      *(undefined4 *)(param_1 + 0xa7c214) = 0;
      *puVar18 = 0;
      os_alloc_mem(param_1,param_1 + 0xa7c214,__n);
      *puVar18 = (ushort)__n;
      __dest = *(void **)(param_1 + 0xa7c214);
    }
  }
  os_move_mem(__dest,param_2,__n);
  local_66 = 0x1000001;
  local_68 = 0;
  iVar7 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (param_2 == (uint *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s(): null pointer for rxv pkt.\n","mt7915_rxv_dump_update");
    }
  }
  else if (*(char *)(param_1 + 0xa7c218) != '\0') {
    piVar21 = *(int **)(param_1 + 0xa7c220);
    bVar20 = *(byte *)(param_1 + 0xa7c21a);
    bVar1 = *(byte *)(iVar7 + 0x213);
    if (piVar21 == (int *)0x0) {
      if (-1 < DebugLevel) {
        printk("%s(): null pointer for dump entry list.\n","mt7915_rxv_dump_update");
      }
    }
    else {
      piVar14 = (int *)*piVar21;
      if (piVar21 != piVar14) {
        iVar11 = 0;
        do {
          piVar14 = (int *)*piVar14;
          iVar11 = iVar11 + 1;
        } while (piVar21 != piVar14);
        if (iVar11 != 0) {
          os_zero_mem(&local_4c,0x10);
          if (local_94 != 0) {
            __src = param_2 + bVar1;
            local_74 = 0;
            local_70 = (int *)0x0;
            local_88 = (int *)0x0;
            while( true ) {
              piVar14 = (int *)*piVar21;
              piVar22 = local_88;
              if (piVar21 != piVar14) {
                cVar2 = (char)piVar14[2];
                piVar15 = (int *)*piVar14;
                while ((piVar22 = piVar14, cVar2 != *(char *)(param_1 + 0xa7c21c) &&
                       (piVar22 = local_88, piVar21 != piVar15))) {
                  cVar2 = *(char *)(piVar15 + 2);
                  piVar14 = piVar15;
                  piVar15 = (int *)*piVar15;
                }
              }
              local_88 = piVar22;
              if (local_88 == (int *)0x0) break;
              if (__src == (uint *)0x0) {
                if (-1 < DebugLevel) {
                  printk("%s(): null pointer for rxv pkt.\n","mt7915_rxv_entry_hdr_parser");
                }
              }
              else {
                uVar13 = *__src;
                uVar19 = __src[1];
                local_44 = (undefined1)(uVar19 >> 0x10);
                local_4c = (undefined2)uVar13;
                local_48 = (uVar13 << 0x15) >> 0x17 | (uVar19 & 0xffff) << 9 |
                           (uVar19 >> 0x1c) << 0x19;
                local_4a = (byte)((uVar13 << 9) >> 0x19);
                local_42 = (byte)((uVar19 << 6) >> 0x1f);
                local_43 = (byte)((uVar19 << 7) >> 0x1f);
                local_41 = (byte)((uVar19 << 5) >> 0x1f);
                local_40 = (byte)((uVar19 << 4) >> 0x1f);
              }
              local_66 = CONCAT22(CONCAT11(local_66._3_1_,local_4a),
                                  CONCAT11(local_4a,(undefined1)local_66));
              piVar14 = (int *)local_88[3];
              bVar1 = *(byte *)(iVar7 + 0x214);
              if (piVar14 == (int *)0x0) {
                if (-1 < DebugLevel) {
                  printk("%s(): null pointer for basic dump entry list.\n","mt7915_rxv_dump_update")
                  ;
                }
                goto LAB_0017b4f4;
              }
              piVar22 = (int *)*piVar14;
              if (piVar14 != piVar22) {
                iVar11 = 0;
                piVar15 = piVar22;
                do {
                  piVar15 = (int *)*piVar15;
                  iVar11 = iVar11 + 1;
                } while (piVar14 != piVar15);
                if (iVar11 != 0) {
                  piVar15 = (int *)*piVar22;
                  while (piVar5 = piVar15, piVar14 != piVar22) {
                    piVar15 = (int *)piVar22[4];
                    if ((piVar15 != (int *)0x0) && (piVar10 = (int *)*piVar15, piVar15 != piVar10))
                    {
                      iVar11 = 0;
                      piVar16 = piVar10;
                      do {
                        piVar16 = (int *)*piVar16;
                        iVar11 = iVar11 + 1;
                      } while (piVar15 != piVar16);
                      if (iVar11 != 0) {
                        piVar16 = (int *)*piVar10;
                        while (piVar4 = piVar16, piVar15 != piVar10) {
                          iVar11 = FUN_0017b214(param_1,piVar10,0);
                          if (iVar11 != 0) goto LAB_0017b804;
                          piVar16 = (int *)*piVar4;
                          piVar10 = piVar4;
                        }
                        os_free_mem(piVar15);
                        iVar11 = FUN_0017b214(param_1,piVar22,1);
                        if (iVar11 != 0) {
LAB_0017b804:
                          if (-1 < DebugLevel) {
                            printk("%s(): remove dump basic entry list fail.\n",
                                   "mt7915_rxv_dump_update");
                          }
                          goto LAB_0017b4f4;
                        }
                      }
                    }
                    piVar15 = (int *)*piVar5;
                    piVar22 = piVar5;
                  }
                  os_free_mem(piVar14);
                }
              }
              iVar11 = os_alloc_mem(param_1,local_88 + 3,8);
              if (iVar11 != 0) {
LAB_0017bb30:
                if (-1 < DebugLevel) {
                  printk("%s(): invalid type for rxv dump link list.\n","mt7915_rxv_dump_update");
                }
                goto LAB_0017b4f4;
              }
              piVar14 = (int *)local_88[3];
              __src = __src + bVar1;
              *piVar14 = (int)piVar14;
              piVar14[1] = (int)piVar14;
              uVar13 = 0;
              do {
                mt7915_rxv_content_len(param_1,1 << (uVar13 & 0xff) & 0xff,1,&local_68);
                if ((bVar20 >> (uVar13 & 0xff) & 1) == 0) {
                  __src = __src + (uint)*(byte *)((int)&local_66 + uVar13) * (uint)local_68;
                }
                else {
                  uVar19 = (uint)local_68 << 2;
                  __n_00 = uVar19 & 0xffff;
                  os_zero_mem(auStack_3c,0x14);
                  uVar3 = (undefined2)uVar19;
                  local_32 = uVar3;
                  bVar1 = *(byte *)((int)&local_66 + uVar13);
                  local_2c[0] = 0;
                  local_34 = (undefined1)uVar13;
                  local_30 = bVar1;
                  iVar11 = os_alloc_mem(param_1,local_2c,8);
                  if (iVar11 != 0) goto LAB_0017bb30;
                  *(int *)local_2c[0] = local_2c[0];
                  *(int *)(local_2c[0] + 4) = local_2c[0];
                  iVar11 = FUN_0017ae6c(param_1,piVar14,auStack_3c,1);
                  if (iVar11 != 0) goto LAB_0017bb30;
                  piVar22 = (int *)*piVar14;
                  piVar15 = local_70;
                  if (piVar14 != piVar22) {
                    bVar12 = *(byte *)(piVar22 + 2);
                    piVar5 = (int *)*piVar22;
                    while ((piVar15 = piVar22, (uint)bVar12 != (uVar13 & 0xff) &&
                           (piVar15 = local_70, piVar14 != piVar5))) {
                      bVar12 = *(byte *)(piVar5 + 2);
                      piVar22 = piVar5;
                      piVar5 = (int *)*piVar5;
                    }
                  }
                  local_70 = piVar15;
                  iVar11 = local_70[4];
                  if (bVar1 != 0) {
                    bVar12 = 0;
                    do {
                      os_zero_mem(auStack_5c,0x10);
                      bVar17 = bVar12 + 1;
                      local_50 = (void *)0x0;
                      local_54 = bVar12;
                      local_52 = uVar3;
                      iVar9 = os_alloc_mem(param_1,&local_50,__n_00);
                      if (iVar9 != 0) {
                        if (-1 < DebugLevel) {
                          printk("%s(): allocate memory fail.\n","mt7915_rxv_dump_update");
                        }
                        goto LAB_0017b4f4;
                      }
                      os_move_mem(local_50,__src,__n_00);
                      iVar9 = FUN_0017ae6c(param_1,iVar11,auStack_5c,0);
                      if (iVar9 != 0) goto LAB_0017bb30;
                      __src = __src + local_68;
                      bVar12 = bVar17;
                    } while (bVar17 < bVar1);
                  }
                }
                uVar13 = uVar13 + 1;
              } while (uVar13 != 4);
              bVar1 = *(byte *)(param_1 + 0xa7c21d);
              bVar12 = *(char *)(param_1 + 0xa7c21c) + 1;
              *(byte *)(param_1 + 0xa7c21c) = bVar12;
              if (bVar1 <= bVar12) {
                *(byte *)(param_1 + 0xa7c21c) = bVar12 - bVar1;
              }
              if (*(byte *)(param_1 + 0xa7c21e) < bVar1) {
                *(byte *)(param_1 + 0xa7c21e) = *(byte *)(param_1 + 0xa7c21e) + 1;
              }
              local_74 = local_74 + 1;
              if (local_94 <= (local_74 & 0xff)) goto LAB_0017b4f4;
            }
            if (-1 < DebugLevel) {
              printk("%s(): null pointer for current rxv dump entry.\n","mt7915_rxv_dump_update");
            }
          }
          goto LAB_0017b4f4;
        }
      }
      if (-1 < DebugLevel) {
        printk("%s(): empty list for dump entry.\n","mt7915_rxv_dump_update");
      }
    }
  }
LAB_0017b4f4:
  param_2 = param_2 + *(byte *)(iVar6 + 0x213);
  uVar13 = (uint)*(byte *)(iVar6 + 0x213) << 2;
  if (local_60 != 0) {
    bVar20 = 0;
    do {
      uVar19 = (*param_2 << 9) >> 0x19;
      if (2 < DebugLevel) {
        printk("%s(): sta_cnt: %d\n","mt7915_rxv_packet_parse",uVar19);
      }
      if (0x10 < uVar19) {
        if (2 < DebugLevel) {
          printk("%s(): sta count is invalid(%d).\n","mt7915_rxv_packet_parse",uVar19);
        }
        goto LAB_0017b590;
      }
      chip_parse_rxv_entry(param_1,param_2);
      bVar20 = bVar20 + 1;
      uVar19 = uVar19 * ((uint)*(byte *)(iVar6 + 0x217) + (uint)*(byte *)(iVar6 + 0x218)) +
               (uint)*(byte *)(iVar6 + 0x216) +
               (uint)*(byte *)(iVar6 + 0x215) + (uint)*(byte *)(iVar6 + 0x214) & 0xffff;
      param_2 = param_2 + uVar19;
      uVar13 = uVar13 + uVar19 * 4;
    } while (bVar20 < local_60);
  }
  if (local_62 == uVar13) {
    uVar8 = 0;
  }
  else if ((DebugLevel < 0) ||
          (printk("RxV Report: byte_cnt_sum: %d, rxv_byte_cnt: %d\n",uVar13), DebugLevel < 0)) {
LAB_0017b590:
    uVar8 = 1;
  }
  else {
    printk("Received byte count not equal to rxv_entry byte count required!\n");
    uVar8 = 1;
  }
  return uVar8;
}

