// module: tm.ko
// function: tm_multicst_vltrans_table_delete_set @ 0x49204
// size: 604 bytes
//

undefined4 tm_multicst_vltrans_table_delete_set(int *param_1)

{
  undefined1 uVar1;
  char cVar2;
  undefined1 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined2 local_58;
  uint local_54;
  uint local_50;
  short local_4c;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  uint local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  undefined4 local_20;
  uint local_1c;
  
  local_2c = *param_1;
  local_24 = param_1[1];
  uVar1 = *(undefined1 *)((int)param_1 + 0x13);
  local_1c = (uint)(*(char *)((int)param_1 + 0x11) != '\0');
  cVar2 = *(char *)((int)param_1 + 0x15);
  iVar5 = param_1[5];
  uVar3 = *(undefined1 *)((int)param_1 + 0x12);
  switch(param_1[2]) {
  case 0:
    local_30 = 0;
    break;
  case 1:
    local_30 = 1;
    break;
  case 2:
    local_30 = 2;
    break;
  case 3:
    local_30 = 3;
    break;
  case 4:
    local_30 = 4;
    break;
  default:
    printk("tm_multicst_vltrans_table_delete_set fail, error vlan_action %d\n");
    return 0xffffffff;
  }
  switch(param_1[3]) {
  case 0:
    local_28 = 1;
    break;
  case 1:
    local_28 = 2;
    break;
  case 2:
    local_28 = 3;
    break;
  case 3:
    local_28 = 4;
    break;
  case 4:
    local_28 = 5;
    break;
  case 5:
    local_28 = 0;
    break;
  case 6:
    local_28 = 6;
    break;
  case 7:
    local_28 = 7;
    break;
  default:
    printk("tm_multicst_vltrans_table_delete_set fail, error pt_id %d\n");
    return 0xffffffff;
  }
  iVar6 = 0;
  do {
    iVar4 = sbrg_get_multicst_vltrans_table(&local_48,iVar6);
    if (iVar4 != 0) {
LAB_000493d4:
      printk("tm_multicst_vltrans_table_delete_set fail\n");
      return 0xffffffff;
    }
    iVar4 = sbrg_get_multicst_pritrans_table(&local_54,iVar6);
    if (iVar4 != 0) {
      printk("tm_multicst_vltrans_table_add_set fail\n");
      return 0xffffffff;
    }
    if ((((((local_38 == 1) && (local_3c == local_24)) && (local_40 == local_28)) &&
         ((local_44 == local_2c && (local_48 == local_30)))) &&
        ((local_34 == local_1c &&
         (((cVar2 != '\0') == local_54 && (((char)iVar5 != '\0') == local_50)))))) &&
       (local_58 = CONCAT11(uVar3,uVar1), local_58 == local_4c)) {
      local_28 = 0;
      local_20 = 0;
      local_24 = 0;
      local_2c = 0;
      local_30 = 0;
      local_1c = 0;
      iVar5 = sbrg_set_multicst_vltrans_table(&local_30,iVar6);
      if (iVar5 == 0) {
        return 0;
      }
      goto LAB_000493d4;
    }
    iVar6 = iVar6 + 1;
    if (iVar6 == 0x30) {
      printk("tm_multicst_vltrans_table_delete_set fail,entry is not exsit\n");
      return 0xffffffff;
    }
  } while( true );
}

