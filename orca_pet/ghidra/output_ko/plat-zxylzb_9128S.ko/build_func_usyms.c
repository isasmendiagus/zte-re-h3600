// module: plat-zxylzb_9128S.ko
// function: build_func_usyms @ 0x11ec4
// size: 1628 bytes
//

/* WARNING: Restarted to delay deadcode elimination for space: ram */

void * build_func_usyms(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  void *pvVar5;
  int iVar6;
  size_t __n;
  uint uVar7;
  char *__s2;
  uint uVar8;
  uint __n_00;
  uint *puVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  char *__src;
  void *local_54;
  uint local_4c;
  uint local_48;
  int local_34;
  uint *local_30;
  
  iVar1 = get_task_full_path_constprop_9();
  if ((iVar1 < 1) || (iVar1 = myfile_open_constprop_10(&task_path), iVar1 == 0)) {
    return (void *)0x0;
  }
  if (string_table != 0) {
    kfree();
    string_table = 0;
  }
  if (section_headers != 0) {
    kfree();
    section_headers = 0;
  }
  string_table_length = 0;
  iVar2 = get_elf_header_constprop_5(iVar1);
  if (iVar2 < 0) {
    filp_close(iVar1,0);
    return (void *)0x0;
  }
  cur_task = param_1;
  if (is_32bit_elf == 0) {
    printk("\nIt is not 32 bit elf file\n");
    goto LAB_000124bc;
  }
  iVar2 = get_32bit_section_headers_constprop_7(iVar1);
  if (iVar2 < 0) goto LAB_000124bc;
  if (string_table == 0) {
    get_string_table_part_0_constprop_13(iVar1);
  }
  local_54 = (void *)kmalloc_order(0x6800,0xd0,3);
  if (Ehdr32._48_2_ == 0) {
LAB_000124d8:
    local_4c = 0x200;
LAB_000123e0:
    uVar7 = 0;
    pvVar5 = local_54;
    do {
      iVar2 = func_insert(&mytree,pvVar5);
      uVar7 = uVar7 + 1;
      pvVar5 = (void *)((int)pvVar5 + 0x34);
      if (iVar2 < 0) break;
    } while (uVar7 < local_4c);
  }
  else {
    local_34 = 0;
    local_30 = (uint *)0x0;
    iVar10 = 0;
    iVar2 = section_headers;
    do {
      if ((*(int *)(iVar2 + 4) == 9) && (iVar12 = *(int *)(iVar2 + 0x14), iVar12 != 0)) {
        iVar14 = *(int *)(iVar2 + 0x24);
        local_34 = __aeabi_uidiv(iVar12,iVar14);
        if (iVar14 == 8) {
          local_30 = (uint *)get_data(iVar1,*(undefined4 *)(iVar2 + 0x10),iVar12,"rel section");
          if (local_30 != (uint *)0x0) {
            if ((is_big_endian != 0) &&
               (iVar12 = __aeabi_uidiv(*(undefined4 *)(iVar2 + 0x14),*(undefined4 *)(iVar2 + 0x24)),
               0 < iVar12)) {
              iVar14 = 0;
              puVar9 = local_30;
              do {
                iVar14 = iVar14 + 1;
                uVar7 = *puVar9;
                uVar8 = puVar9[1];
                *puVar9 = uVar7 << 0x18 | (uVar7 >> 8 & 0xff) << 0x10 | (uVar7 >> 0x10 & 0xff) << 8
                          | uVar7 >> 0x18;
                puVar9[1] = uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 |
                            (uVar8 >> 0x10 & 0xff) << 8 | uVar8 >> 0x18;
                puVar9 = puVar9 + 2;
              } while (iVar12 != iVar14);
            }
          }
        }
        else {
          printk("Invalid entsize of section, %d, should be %d\n",iVar14,8);
          local_30 = (uint *)0x0;
        }
      }
      iVar10 = iVar10 + 1;
      iVar2 = iVar2 + 0x28;
    } while (iVar10 < (int)(uint)(ushort)Ehdr32._48_2_);
    if ((ushort)Ehdr32._48_2_ == 0) goto LAB_000124d8;
    uVar7 = 0;
    iVar10 = 0;
    local_4c = 0x200;
    iVar12 = 0;
    local_48 = 0;
    iVar2 = section_headers;
    do {
      if ((*(int *)(iVar2 + 4) == 0xb || *(int *)(iVar2 + 4) == 2) &&
         (iVar3 = get_32bit_elf_symbols(iVar1,iVar2), iVar14 = string_table, iVar3 != 0)) {
        uVar8 = *(uint *)(iVar2 + 0x18);
        if (uVar8 == (ushort)Ehdr32._50_2_) {
          local_48 = string_table_length;
          iVar4 = __aeabi_uidiv(*(undefined4 *)(iVar2 + 0x14),*(undefined4 *)(iVar2 + 0x24));
          if (0 < iVar4) goto LAB_00012158;
        }
        else {
          if ((uVar8 < (ushort)Ehdr32._48_2_) &&
             (iVar14 = section_headers + uVar8 * 0x28, *(int *)(iVar14 + 4) == 3)) {
            iVar10 = get_data(iVar1,*(undefined4 *)(iVar14 + 0x10),*(undefined4 *)(iVar14 + 0x14),
                              "string table");
            if (iVar10 == 0) {
              local_48 = 0;
            }
            else {
              local_48 = *(uint *)(iVar14 + 0x14);
            }
          }
          iVar4 = __aeabi_uidiv(*(undefined4 *)(iVar2 + 0x14),*(undefined4 *)(iVar2 + 0x24));
          iVar14 = iVar10;
          if (0 < iVar4) {
LAB_00012158:
            iVar11 = 0;
            iVar10 = iVar3 + 0x10;
            do {
              while ((((*(short *)(iVar10 + -2) == 0 && (*(int *)(iVar2 + 4) != 0xb)) ||
                      (iVar14 == 0 || (*(byte *)(iVar10 + -4) & 0xf) != 2)) ||
                     (*(uint *)(iVar10 + -8) < 8))) {
LAB_0001217c:
                iVar11 = iVar11 + 1;
                iVar10 = iVar10 + 0x10;
                if (iVar4 == iVar11) goto LAB_000122a4;
              }
              if (*(uint *)(iVar10 + -0x10) < local_48) {
                __src = (char *)(iVar14 + *(uint *)(iVar10 + -0x10));
              }
              else {
                __src = "<corrupt>";
              }
              strncpy((char *)((int)local_54 + uVar7 * 0x34 + 0x14),__src,0x20);
              if (*(int *)(iVar2 + 4) == 0xb) {
                if ((local_30 != (uint *)0x0) && (local_34 != 0)) {
                  iVar13 = 0;
                  puVar9 = local_30;
                  do {
                    __s2 = "<corrupt>";
                    iVar13 = iVar13 + 1;
                    uVar8 = *(uint *)(iVar3 + (puVar9[1] >> 8) * 0x10);
                    if (uVar8 < local_48) {
                      __s2 = (char *)(iVar14 + uVar8);
                    }
                    iVar6 = strcmp(__src,__s2);
                    if (iVar6 == 0) {
                      iVar13 = user_va2pa(cur_task,*puVar9);
                      if ((iVar13 != 0) &&
                         (uVar8 = *(uint *)(iVar13 + -0x80000000), 0x3fffffff < uVar8)) {
                        *(uint *)((int)local_54 + uVar7 * 0x34 + 0xc) = uVar8;
                        *(uint *)((int)local_54 + uVar7 * 0x34 + 0x10) =
                             uVar8 + *(int *)(iVar10 + -8);
                        goto LAB_00012224;
                      }
                      break;
                    }
                    puVar9 = puVar9 + 2;
                  } while (iVar13 != local_34);
                }
                goto LAB_0001217c;
              }
              *(undefined4 *)((int)local_54 + uVar7 * 0x34 + 0xc) = *(undefined4 *)(iVar10 + -0xc);
              *(int *)((int)local_54 + uVar7 * 0x34 + 0x10) =
                   *(int *)(iVar10 + -8) + *(int *)(iVar10 + -0xc);
LAB_00012224:
              uVar7 = uVar7 + 1;
              if (uVar7 < local_4c) goto LAB_0001217c;
              uVar8 = local_4c * 0x34;
              __n_00 = uVar8 + 0x6800;
              pvVar5 = (void *)__kmalloc(__n_00,0xd0);
              if (pvVar5 == (void *)0x0 || local_54 == (void *)0x0) {
                kfree(local_54);
                if (pvVar5 == (void *)0x0) {
                  if (iVar14 != string_table) {
                    kfree(iVar14);
                  }
                  kfree(iVar3);
                  goto LAB_000124bc;
                }
              }
              else {
                if (uVar8 <= __n_00) {
                  __n_00 = uVar8;
                }
                memcpy(pvVar5,local_54,__n_00);
                kfree(local_54);
              }
              iVar11 = iVar11 + 1;
              local_4c = local_4c + 0x200;
              iVar10 = iVar10 + 0x10;
              local_54 = pvVar5;
            } while (iVar4 != iVar11);
          }
LAB_000122a4:
          if (iVar14 != string_table) {
            kfree(iVar14);
            iVar14 = 0;
          }
        }
        kfree(iVar3);
        iVar10 = iVar14;
      }
      iVar12 = iVar12 + 1;
      iVar2 = iVar2 + 0x28;
    } while (iVar12 < (int)(uint)(ushort)Ehdr32._48_2_);
    if (local_4c != 0) goto LAB_000123e0;
  }
  if (local_54 != (void *)0x0) {
    filp_close(iVar1,0);
    __n = strlen(&task_path);
    if (0x7e < (int)__n) {
      __n = 0x7f;
    }
    memcpy(last_task_path,&task_path,__n);
    last_task_path[0x7f] = 0;
    return local_54;
  }
LAB_000124bc:
  filp_close(iVar1,0);
  last_task_path[0] = 0;
  return (void *)0x0;
}

