// module: plat-zxylzb_9128S.ko
// function: usyms_lookup_name @ 0x12528
// size: 884 bytes
//

/* WARNING: Restarted to delay deadcode elimination for space: ram */

undefined8 * usyms_lookup_name(undefined4 param_1,char *param_2,char *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  size_t __n;
  char *__s2;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint local_40;
  int local_30;
  
  if (param_3 == (char *)0x0) {
    iVar1 = get_task_full_path_constprop_9();
    if (iVar1 < 1) {
      return (undefined8 *)0x0;
    }
    param_3 = &task_path;
  }
  printk("open file %s\n",param_3);
  iVar1 = myfile_open_constprop_10(param_3);
  if (iVar1 == 0) {
    return (undefined8 *)0x0;
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
    return (undefined8 *)0x0;
  }
  cur_task = param_1;
  if (is_32bit_elf == 0) {
    printk("\nIt is not 32 bit elf file\n");
  }
  else {
    iVar2 = get_32bit_section_headers_constprop_7(iVar1);
    if (-1 < iVar2) {
      if (string_table == 0) {
        get_string_table_part_0_constprop_13(iVar1);
      }
      if (Ehdr32._48_2_ != 0) {
        iVar2 = 0;
        local_40 = 0;
        iVar7 = 0;
        local_30 = -1;
        iVar11 = section_headers;
        do {
          if ((*(int *)(iVar11 + 4) == 0xb || *(int *)(iVar11 + 4) == 2) &&
             (iVar3 = get_32bit_elf_symbols(iVar1,iVar11), iVar3 != 0)) {
            uVar6 = *(uint *)(iVar11 + 0x18);
            if (uVar6 == (ushort)Ehdr32._50_2_) {
              iVar8 = __aeabi_uidiv(*(undefined4 *)(iVar11 + 0x14),*(undefined4 *)(iVar11 + 0x24));
              local_40 = string_table_length;
              iVar2 = string_table;
              if (0 < iVar8) goto LAB_000126e4;
            }
            else {
              if ((uVar6 < (ushort)Ehdr32._48_2_) &&
                 (iVar8 = uVar6 * 0x28 + section_headers, *(int *)(iVar8 + 4) == 3)) {
                iVar2 = get_data(iVar1,*(undefined4 *)(iVar8 + 0x10),*(undefined4 *)(iVar8 + 0x14),
                                 "string table");
                if (iVar2 == 0) {
                  local_40 = 0;
                }
                else {
                  local_40 = *(uint *)(iVar8 + 0x14);
                }
              }
              iVar8 = __aeabi_uidiv(*(undefined4 *)(iVar11 + 0x14),*(undefined4 *)(iVar11 + 0x24));
              if (0 < iVar8) {
LAB_000126e4:
                iVar9 = 0;
                iVar10 = iVar3;
                do {
                  uVar6 = *(byte *)(iVar10 + 0xc) & 0xf;
                  if ((iVar2 != 0) && (uVar6 - 1 < 2)) {
                    __s2 = "<corrupt>";
                    uVar4 = *(uint *)(iVar3 + iVar9 * 0x10);
                    if (uVar4 < local_40) {
                      __s2 = (char *)(iVar2 + uVar4);
                    }
                    iVar5 = strcmp(param_2,__s2);
                    if (iVar5 == 0) {
                      sym_info._0_4_ = *(undefined4 *)(iVar10 + 4);
                      sym_info._4_2_ = (undefined2)uVar6;
                      sym_info._6_2_ = (undefined2)*(undefined4 *)(iVar10 + 8);
                      local_30 = 0;
                      break;
                    }
                  }
                  iVar9 = iVar9 + 1;
                  iVar10 = iVar10 + 0x10;
                } while (iVar9 < iVar8);
              }
              if (iVar2 != string_table) {
                kfree(iVar2);
                iVar2 = 0;
              }
            }
            kfree(iVar3);
          }
          iVar7 = iVar7 + 1;
          iVar11 = iVar11 + 0x28;
        } while (iVar7 < (int)(uint)(ushort)Ehdr32._48_2_);
        if (local_30 != -1) {
          filp_close(iVar1,0);
          __n = strlen(param_3);
          if (0x7e < (int)__n) {
            __n = 0x7f;
          }
          memcpy(last_task_path,param_3,__n);
          last_task_path[0x7f] = 0;
          return &sym_info;
        }
      }
    }
  }
  filp_close(iVar1,0);
  last_task_path[0] = 0;
  return (undefined8 *)0x0;
}

