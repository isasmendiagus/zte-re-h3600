// module: tm.ko
// function: tm_broadcst_vltrans_table_lookup_get @ 0x49eec
// size: 572 bytes
//

undefined4 tm_broadcst_vltrans_table_lookup_get(int *param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 local_4c;
  undefined4 local_48;
  undefined1 local_44;
  undefined1 local_43;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  uint local_2c;
  
  iVar5 = param_1[1];
  iVar7 = *param_1;
  cVar1 = *(char *)((int)param_1 + 0x11);
  switch(param_1[2]) {
  case 0:
    iVar8 = 0;
    break;
  case 1:
    iVar8 = 1;
    break;
  case 2:
    iVar8 = 2;
    break;
  case 3:
    iVar8 = 3;
    break;
  default:
    printk("tm_broadcst_vltrans_table_lookup_get fail, error vlan_action %d\n");
    return 0xffffffff;
  }
  switch(param_1[3]) {
  case 0:
    iVar6 = 1;
    break;
  case 1:
    iVar6 = 2;
    break;
  case 2:
    iVar6 = 3;
    break;
  case 3:
    iVar6 = 4;
    break;
  case 4:
    iVar6 = 5;
    break;
  case 5:
    iVar6 = 0;
    break;
  case 6:
    iVar6 = 6;
    break;
  case 7:
    iVar6 = 7;
    break;
  default:
    printk("tm_broadcst_vltrans_table_lookup_get fail, error pt_id %d\n");
    return 0xffffffff;
  }
  iVar3 = 0;
  while( true ) {
    iVar2 = sbrg_get_broadcst_vltrans_table(&local_40,iVar3);
    iVar4 = iVar3 + 1;
    iVar3 = sbrg_get_broadcst_pritrans_table(&local_4c,iVar3);
    if (iVar3 != 0 || iVar2 != 0) {
      printk("tm_broadcst_vltrans_table_lookup_get fail\n");
      return 0xffffffff;
    }
    if ((((local_30 == 1) && (iVar5 == local_34)) && (iVar6 == local_38)) &&
       (((iVar7 == local_3c && (iVar8 == local_40)) && ((cVar1 != '\0') == local_2c)))) break;
    iVar3 = iVar4;
    if (iVar4 == 0x30) {
      *(undefined1 *)(param_1 + 4) = 0;
      return 0;
    }
  }
  printk("[TM][tm_broadcst_vltrans_table_lookup_get]output:en = %d\n");
  printk("[TM][tm_broadcst_vltrans_table_lookup_get]output:vlan_action = %d,uni_vlan = %d\n",
         local_40,local_3c);
  printk("[TM][tm_broadcst_vltrans_table_lookup_get]output:output_pt_id = %d,pon_vlan = %d,valid = %d\n"
         ,local_38,local_34,local_30);
  printk("[TM][tm_broadcst_vltrans_table_lookup_get]output:pon_pri = %d,pri_en = %d\n",local_44,
         local_4c);
  printk("[TM][tm_broadcst_vltrans_table_lookup_get]output:pri_use = %d,uni_pri = %d\n",local_48,
         local_43);
  *param_1 = local_3c;
  *(bool *)(param_1 + 4) = local_30 != 0;
  switch(local_40) {
  case 0:
    param_1[2] = 0;
    return 0;
  case 1:
    param_1[2] = 1;
    break;
  case 2:
    param_1[2] = 2;
    return 0;
  case 3:
    param_1[2] = 3;
    return 0;
  default:
  }
  return 0;
}

