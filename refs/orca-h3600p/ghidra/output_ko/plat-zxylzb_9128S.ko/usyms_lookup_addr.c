// module: plat-zxylzb_9128S.ko
// function: usyms_lookup_addr @ 0x128a0
// size: 748 bytes
//

undefined1 * usyms_lookup_addr(undefined4 param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  char *__src;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint *puVar8;
  int iVar9;
  int iVar10;
  int local_34;
  uint local_30;
  
  iVar1 = myfile_open_constprop_10();
  if (iVar1 != 0) {
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
      return (undefined1 *)0x0;
    }
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
          local_30 = 0;
          iVar2 = 0;
          local_34 = -1;
          iVar10 = 0;
          iVar9 = section_headers;
          do {
            if ((*(int *)(iVar9 + 4) == 0xb || *(int *)(iVar9 + 4) == 2) &&
               (puVar3 = (uint *)get_32bit_elf_symbols(iVar1,iVar9), puVar3 != (uint *)0x0)) {
              uVar6 = *(uint *)(iVar9 + 0x18);
              if (uVar6 == (ushort)Ehdr32._50_2_) {
                iVar7 = __aeabi_uidiv(*(undefined4 *)(iVar9 + 0x14),*(undefined4 *)(iVar9 + 0x24));
                local_30 = string_table_length;
                iVar2 = string_table;
                if (0 < iVar7) goto LAB_00012a00;
              }
              else {
                if ((uVar6 < (ushort)Ehdr32._48_2_) &&
                   (iVar7 = section_headers + uVar6 * 0x28, *(int *)(iVar7 + 4) == 3)) {
                  iVar2 = get_data(iVar1,*(undefined4 *)(iVar7 + 0x10),*(undefined4 *)(iVar7 + 0x14)
                                   ,"string table");
                  if (iVar2 == 0) {
                    local_30 = 0;
                  }
                  else {
                    local_30 = *(uint *)(iVar7 + 0x14);
                  }
                }
                iVar7 = __aeabi_uidiv(*(undefined4 *)(iVar9 + 0x14),*(undefined4 *)(iVar9 + 0x24));
                iVar5 = string_table;
                if (0 < iVar7) {
LAB_00012a00:
                  iVar5 = string_table;
                  iVar4 = 0;
                  puVar8 = puVar3;
                  do {
                    iVar4 = iVar4 + 1;
                    if ((((iVar2 != 0) && (((byte)puVar8[3] & 0xf) - 1 < 2)) &&
                        (puVar8[1] <= param_2)) && (param_2 < puVar8[1] + puVar8[2])) {
                      if (*puVar8 < local_30) {
                        __src = (char *)(iVar2 + *puVar8);
                      }
                      else {
                        __src = "<corrupt>";
                      }
                      local_34 = 0;
                      strncpy(sym_node + 0x14,__src,0x20);
                      sym_node._12_4_ = puVar8[1];
                      sym_node._16_4_ = puVar8[2] + puVar8[1];
                      break;
                    }
                    puVar8 = puVar8 + 4;
                  } while (iVar4 < iVar7);
                }
                if (iVar2 != iVar5) {
                  kfree(iVar2);
                  iVar2 = 0;
                }
              }
              kfree(puVar3);
            }
            iVar10 = iVar10 + 1;
            iVar9 = iVar9 + 0x28;
          } while (iVar10 < (int)(uint)(ushort)Ehdr32._48_2_);
          if (local_34 != -1) {
            filp_close(iVar1,0);
            return sym_node;
          }
        }
      }
    }
    filp_close(iVar1,0);
    last_task_path[0] = 0;
  }
  return (undefined1 *)0x0;
}

