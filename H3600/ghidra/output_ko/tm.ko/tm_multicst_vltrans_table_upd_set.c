// module: tm.ko
// function: tm_multicst_vltrans_table_upd_set @ 0x49494
// size: 560 bytes
//

undefined4 tm_multicst_vltrans_table_upd_set(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  uint local_58;
  uint local_54;
  char local_50;
  undefined1 local_4f;
  uint local_4c [2];
  char local_44;
  undefined1 auStack_40 [8];
  int local_38;
  int local_34;
  int local_30;
  uint local_2c;
  undefined4 local_28;
  undefined4 local_24;
  int local_20;
  int local_1c;
  uint local_18;
  uint local_14;
  
  local_50 = *(char *)((int)param_1 + 0x13);
  local_58 = (uint)(*(char *)((int)param_1 + 0x15) != '\0');
  local_4f = *(undefined1 *)((int)param_1 + 0x12);
  local_1c = param_1[1];
  local_54 = (uint)(*(char *)(param_1 + 5) != '\0');
  local_24 = *param_1;
  local_14 = (uint)(*(char *)((int)param_1 + 0x11) != '\0');
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
    printk("tm_multicst_vltrans_table_upd_set fail, error pt_id %d\n");
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
    printk("tm_multicst_vltrans_table_upd_set fail, error vlan_action %d\n");
    return 0xffffffff;
  }
  iVar2 = 0;
  local_18 = (uint)(*(char *)(param_1 + 4) != '\0');
  do {
    iVar1 = sbrg_get_multicst_vltrans_table(auStack_40,iVar2);
    if ((iVar1 != 0) || (iVar1 = sbrg_get_multicst_pritrans_table(local_4c,iVar2), iVar1 != 0)) {
LAB_00049618:
      printk("tm_multicst_vltrans_table_upd_set fail\n");
      return 0xffffffff;
    }
    if (((local_30 == 1) &&
        (((local_34 == local_1c && (local_38 == local_20)) && (local_2c == local_14)))) &&
       ((local_4c[0] == local_58 && (local_44 == local_50)))) {
      sbrg_set_multicst_vltrans_table(&local_28,iVar2);
      iVar2 = sbrg_set_multicst_pritrans_table(&local_58,iVar2);
      if (iVar2 == 0) {
        return 0;
      }
      goto LAB_00049618;
    }
    iVar2 = iVar2 + 1;
    if (iVar2 == 0x30) {
      printk("tm_multicst_vltrans_table_upd_set fail,table is full\n");
      return 1;
    }
  } while( true );
}

