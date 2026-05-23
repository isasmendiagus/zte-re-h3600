// module: tm.ko
// function: tm_broadcst_vltrans_table_delete_set @ 0x49a44
// size: 468 bytes
//

undefined4 tm_broadcst_vltrans_table_delete_set(uint *param_1)

{
  uint uVar1;
  int iVar2;
  uint local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  int local_28;
  uint local_24;
  uint local_20;
  uint local_1c;
  uint local_18;
  uint local_14;
  uint local_10;
  uint local_c;
  
  local_1c = *param_1;
  local_14 = param_1[1];
  local_c = (uint)(*(char *)((int)param_1 + 0x11) != '\0');
  switch(param_1[2]) {
  case 0:
    local_20 = 0;
    break;
  case 1:
    local_20 = 1;
    break;
  case 2:
    local_20 = 2;
    break;
  case 3:
    local_20 = 3;
    break;
  default:
    printk("tm_broadcst_vltrans_table_delete_set fail, error vlan_action %d\n");
    return 0xffffffff;
  }
  switch(param_1[3]) {
  case 0:
    local_18 = 1;
    break;
  case 1:
    local_18 = 2;
    break;
  case 2:
    local_18 = 3;
    break;
  case 3:
    local_18 = 4;
    break;
  case 4:
    local_18 = 5;
    break;
  case 5:
    local_18 = 0;
    break;
  case 6:
    local_18 = 6;
    break;
  case 7:
    local_18 = 7;
    break;
  default:
    printk("tm_broadcst_vltrans_table_delete_set fail, error pt_id %d\n");
    return 0xffffffff;
  }
  iVar2 = 0;
  do {
    uVar1 = sbrg_get_broadcst_vltrans_table(&local_38,iVar2);
    if (uVar1 != 0) {
LAB_00049bb4:
      printk("tm_broadcst_vltrans_table_delete_set fail\n");
      return 0xffffffff;
    }
    if ((((local_28 == 1) && (local_2c == local_14)) && (local_30 == local_18)) &&
       (((local_34 == local_1c && (local_38 == local_20)) && (local_24 == local_c)))) {
      local_20 = uVar1;
      local_1c = uVar1;
      local_18 = uVar1;
      local_14 = uVar1;
      local_10 = uVar1;
      local_c = uVar1;
      iVar2 = sbrg_set_broadcst_vltrans_table(&local_20,iVar2);
      if (iVar2 == 0) {
        return 0;
      }
      goto LAB_00049bb4;
    }
    iVar2 = iVar2 + 1;
    if (iVar2 == 0x30) {
      printk("tm_broadcst_vltrans_table_delete_set fail,entry is not exsit\n");
      return 0;
    }
  } while( true );
}

