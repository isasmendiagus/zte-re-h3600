// module: tm.ko
// function: tm_multicst_vltrans_table_print_get @ 0x49040
// size: 420 bytes
//

undefined4 tm_multicst_vltrans_table_print_get(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 local_4c;
  undefined4 local_48;
  undefined1 local_44;
  undefined1 local_43;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  int local_30;
  undefined4 local_2c;
  
  printk("tm_multicst_vltrans_table_print_get:\n");
  iVar3 = 1;
  uVar4 = 0;
  printk("%-5s%-4s%-7s%-10s%-11s%-10s%-12s%-7s%-10s%-11s%-10s\n",&_LC128,&_LC129,"valid","pon_vlan",
         "out_pt_id","uni_vlan","vlan_action","pri_en","pri_use","pon_pri","uni_pri");
  do {
    iVar1 = sbrg_get_multicst_vltrans_table(&local_40,iVar3 + -1);
    iVar2 = sbrg_get_multicst_pritrans_table(&local_4c,iVar3 + -1);
    if (iVar2 != 0 || iVar1 != 0) {
      printk("tm_multicst_vltrans_table_print_get fail\n");
      return 0xffffffff;
    }
    if (local_30 == 1) {
      switch(local_38) {
      case 0:
        uVar4 = 5;
        break;
      case 1:
        uVar4 = 0;
        break;
      case 2:
        uVar4 = 1;
        break;
      case 3:
        uVar4 = 4;
        break;
      case 4:
        uVar4 = 2;
        break;
      case 5:
        uVar4 = 3;
        break;
      case 6:
        uVar4 = 6;
        break;
      case 7:
        uVar4 = 7;
      }
      printk("%-5d%-4d%-7d%-10d%-11d%-10d%-12d%-7d%-10d%-11d%-10d\n",iVar3,local_2c,1,local_34,uVar4
             ,local_3c,local_40,local_4c,local_48,local_44,local_43);
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 0x31);
  return 0;
}

