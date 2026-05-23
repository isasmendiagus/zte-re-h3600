// module: tm.ko
// function: pm_port_stat_print @ 0x6daf4
// size: 720 bytes
//

undefined4 pm_port_stat_print(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  undefined4 local_5c;
  int local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 local_48;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 local_38;
  
  iVar3 = 0;
  local_54 = 0;
  __memzero(&local_50,0x30);
  printk(
        "|------------------------------------------------------------------------------------------------------------------|\n"
        );
  printk(
        "|--------------------------------------------- pm port statistics info --------------------------------------------|\n"
        );
  printk(
        "|------------------------------------------------------------------------------------------------------------------|\n"
        );
  pcVar4 = "multi_pkts";
  printk("| %-3s| %-5s| %-5s| %-18s| %-10s| %-18s| %-10s| %-18s| %-10s|\n",&_LC45,&_LC46,"valid",
         "uni_octets","uni_pkts","multi_octets","multi_pkts","broad_octets","broad_pkts");
  printk(
        "|------------------------------------------------------------------------------------------------------------------|\n"
        );
  do {
    iVar1 = tm_pm_port_get(iVar3,&local_5c);
    iVar2 = pm_get_in_port_rule_valid(local_5c,&local_58);
    if (iVar2 != 0 || iVar1 != 0) goto LAB_0006dc08;
    pm_port_name_get(local_5c,&local_54);
    if (local_58 == 0) {
      pcVar4 = "N/A";
      printk("| %-3s| %-5s| %-5d| %-18s| %-10s| %-18s| %-10s| %-18s| %-10s|\n",&_LC56,local_54,0,
             &_LC57,&_LC57,&_LC57,&_LC57,&_LC57,&_LC57);
    }
    else {
      iVar1 = pm_get_port_statistics(0,local_5c,&local_50);
      if (iVar1 != 0) goto LAB_0006dc08;
      printk("| %-3s| %-5s| %-5d| %-18lld| %-10d| %-18lld| %-10d| %-18lld| %-10d|\n",&_LC56,local_54
             ,local_58,local_50,uStack_4c,local_48,pcVar4,local_40,uStack_3c,local_38);
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 != 8);
  iVar3 = 0;
  while( true ) {
    iVar1 = tm_pm_port_get(iVar3,&local_5c);
    iVar2 = pm_get_out_port_rule_valid(local_5c,&local_58);
    if (iVar2 != 0 || iVar1 != 0) break;
    pm_port_name_get(local_5c,&local_54);
    if (local_58 == 0) {
      pcVar4 = "N/A";
      printk("| %-3s| %-5s| %-5d| %-18s| %-10s| %-18s| %-10s| %-18s| %-10s|\n",&_LC59,local_54,0,
             &_LC57,&_LC57,&_LC57,&_LC57,&_LC57,&_LC57);
    }
    else {
      iVar1 = pm_get_port_statistics(1,local_5c,&local_50);
      if (iVar1 != 0) break;
      printk("| %-3s| %-5s| %-5d| %-18lld| %-10d| %-18lld| %-10d| %-18lld| %-10d|\n",&_LC56,local_54
             ,local_58,local_50,uStack_4c,local_48,pcVar4,local_40,uStack_3c,local_38);
    }
    iVar3 = iVar3 + 1;
    if (iVar3 == 8) {
      printk(
            "|------------------------------------------------------------------------------------------------------------------|\n"
            );
      return 0;
    }
  }
LAB_0006dc08:
  if (6 < g_tm_debug_level) {
    printk("pm_port_stat_print failed!\n");
  }
  return 0xffffffff;
}

