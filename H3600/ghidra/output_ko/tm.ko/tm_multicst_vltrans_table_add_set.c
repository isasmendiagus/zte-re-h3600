// module: tm.ko
// function: tm_multicst_vltrans_table_add_set @ 0x496f8
// size: 792 bytes
//

undefined4 tm_multicst_vltrans_table_add_set(int *param_1)

{
  int iVar1;
  int iVar2;
  uint local_58;
  uint local_54;
  undefined2 local_50;
  uint local_4c;
  uint local_48;
  short local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  uint local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  uint local_18;
  uint local_14;
  
  local_58 = (uint)(*(char *)((int)param_1 + 0x15) != '\0');
  local_1c = param_1[1];
  local_54 = (uint)((char)param_1[5] != '\0');
  local_24 = *param_1;
  local_14 = (uint)(*(char *)((int)param_1 + 0x11) != '\0');
  local_50 = CONCAT11(*(undefined1 *)((int)param_1 + 0x12),*(undefined1 *)((int)param_1 + 0x13));
  switch(param_1[3]) {
  case 0:
    local_20 = 1;
    break;
  case 1:
    local_20 = 2;
    break;
  case 2:
    local_20 = 3;
    break;
  case 3:
    local_20 = 4;
    break;
  case 4:
    local_20 = 5;
    break;
  case 5:
    local_20 = 0;
    break;
  case 6:
    local_20 = 6;
    break;
  case 7:
    local_20 = 7;
    break;
  default:
    printk("tm_multicst_vltrans_table_add_set fail, error pt_id %d\n");
    return 0xffffffff;
  }
  switch(param_1[2]) {
  case 0:
    local_28 = 0;
    break;
  case 1:
    local_28 = 1;
    break;
  case 2:
    local_28 = 2;
    break;
  case 3:
    local_28 = 3;
    break;
  case 4:
    local_28 = 4;
    break;
  default:
    printk("tm_multicst_vltrans_table_add_set fail, error vlan_action %d\n");
    return 0xffffffff;
  }
  iVar2 = 0;
  local_18 = (uint)((char)param_1[4] != '\0');
  do {
    iVar1 = sbrg_get_multicst_vltrans_table(&local_40,iVar2);
    if ((iVar1 != 0) || (iVar1 = sbrg_get_multicst_pritrans_table(&local_4c,iVar2), iVar1 != 0))
    goto LAB_00049a30;
    if ((local_30 == 1) && ((local_34 == local_1c && (local_38 == local_20)))) {
      if ((local_3c == local_24) &&
         ((((local_40 == local_28 && (local_2c == local_14)) && (local_4c == local_58)) &&
          ((local_48 == local_54 && (local_44 == local_50)))))) {
        printk("tm_multicst_vltrans_table_add_set fail,the entry is exsit\n");
        return 0;
      }
      if ((local_2c == local_14) && (local_4c == local_58)) {
        if ((char)local_44 == (char)local_50) {
          sbrg_set_multicst_vltrans_table(&local_28,iVar2);
          iVar2 = sbrg_set_multicst_pritrans_table(&local_58,iVar2);
          if (iVar2 == 0) {
            return 0;
          }
          printk("tm_multicst_vltrans_table_upd_set fail\n");
          return 0xffffffff;
        }
      }
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 != 0x30);
  iVar2 = 0;
  do {
    iVar1 = sbrg_get_multicst_vltrans_table(&local_40,iVar2);
    if (iVar1 != 0) {
LAB_00049a30:
      printk("tm_multicst_vltrans_table_add_set fail\n");
      return 0xffffffff;
    }
    if (local_30 == 0) {
      sbrg_set_multicst_vltrans_table(&local_28,iVar2);
      iVar2 = sbrg_set_multicst_pritrans_table(&local_58,iVar2);
      if (iVar2 == 0) {
        return 0;
      }
      goto LAB_00049a30;
    }
    iVar2 = iVar2 + 1;
    if (iVar2 == 0x30) {
      printk("tm_multicst_vltrans_table_add_set fail,table is full\n");
      return 1;
    }
  } while( true );
}

