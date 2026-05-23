// module: plat-zxylzb_9128S.ko
// function: get_string_table.part.0.constprop.13 @ 0x11d60
// size: 108 bytes
//

void get_string_table_part_0_constprop_13
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = (uint)(ushort)Ehdr32._50_2_;
  if (uVar1 == 0) {
    return;
  }
  if (uVar1 < (ushort)Ehdr32._48_2_) {
    iVar2 = section_headers + uVar1 * 0x28;
    if (*(int *)(iVar2 + 0x14) != 0) {
      string_table = get_data(param_1,*(undefined4 *)(iVar2 + 0x10),*(int *)(iVar2 + 0x14),
                              "string table",param_4);
    }
    string_table_length = 0;
    if (string_table != 0) {
      string_table_length = *(undefined4 *)(iVar2 + 0x14);
    }
    return;
  }
  return;
}

