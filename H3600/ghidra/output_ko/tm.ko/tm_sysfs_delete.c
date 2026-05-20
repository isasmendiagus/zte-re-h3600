// module: tm.ko
// function: tm_sysfs_delete @ 0x78070
// size: 252 bytes
//

void tm_sysfs_delete(void)

{
  int iVar1;
  
  iVar1 = bus_find_device_by_name(&platform_bus_type,0,&_LC0);
  if (iVar1 != 0) {
    iVar1 = iVar1 + 8;
    sysfs_remove_group(iVar1,cla_info_group);
    sysfs_remove_group(iVar1,cla_info_group);
    sysfs_remove_group(iVar1,&pp_pm_info_group);
    sysfs_remove_group(iVar1,&greg_info_group);
    sysfs_remove_group(iVar1,&npp_pm_info_group);
    sysfs_remove_group(iVar1,&sdet_info_group);
    sysfs_remove_group(iVar1,&spa_info_group);
    sysfs_remove_group(iVar1,&adm_info_group);
    sysfs_remove_group(iVar1,&brg_info_group);
    sysfs_remove_group(iVar1,&red_info_group);
    sysfs_remove_group(iVar1,&tm_test_group);
    printk("= TM Module SYS FS Remove ended successfully =\n");
    return;
  }
  printk("%s: cannot find tm device\n","tm_sysfs_delete");
  return;
}

