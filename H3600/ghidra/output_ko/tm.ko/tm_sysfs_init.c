// module: tm.ko
// function: tm_sysfs_init @ 0x77eac
// size: 452 bytes
//

int tm_sysfs_init(void)

{
  undefined *puVar1;
  int iVar2;
  undefined *local_38;
  undefined *local_34;
  undefined1 *local_30;
  undefined4 local_2c;
  undefined *local_28;
  undefined *local_24;
  undefined *local_20;
  undefined *local_1c;
  undefined *local_18;
  undefined *local_14;
  
  puVar1 = (undefined *)bus_find_device_by_name(&platform_bus_type,0,&_LC0);
  if (puVar1 == (undefined *)0x0) {
    local_2c = 0xffffffff;
    local_30 = &_LC0;
    local_38 = puVar1;
    local_34 = puVar1;
    local_28 = puVar1;
    local_24 = puVar1;
    local_20 = puVar1;
    local_1c = puVar1;
    local_18 = puVar1;
    local_14 = puVar1;
    platform_device_register_full(&local_38);
    puVar1 = (undefined *)bus_find_device_by_name(&platform_bus_type,0,&_LC0);
    if (puVar1 == (undefined *)0x0) {
      printk("%s: cannot find tm device\n","tm_sysfs_init");
      puVar1 = &platform_bus;
    }
  }
  puVar1 = puVar1 + 8;
  iVar2 = sysfs_create_group(puVar1,&pp_pm_info_group);
  if ((((((iVar2 == 0) && (iVar2 = sysfs_create_group(puVar1,cla_info_group), iVar2 == 0)) &&
        (iVar2 = sysfs_create_group(puVar1,&greg_info_group), iVar2 == 0)) &&
       ((iVar2 = sysfs_create_group(puVar1,&npp_pm_info_group), iVar2 == 0 &&
        (iVar2 = sysfs_create_group(puVar1,&sdet_info_group), iVar2 == 0)))) &&
      ((iVar2 = sysfs_create_group(puVar1,&spa_info_group), iVar2 == 0 &&
       ((iVar2 = sysfs_create_group(puVar1,&adm_info_group), iVar2 == 0 &&
        (iVar2 = sysfs_create_group(puVar1,&brg_info_group), iVar2 == 0)))))) &&
     ((iVar2 = sysfs_create_group(puVar1,&red_info_group), iVar2 == 0 &&
      (iVar2 = sysfs_create_group(puVar1,&tm_test_group), iVar2 == 0)))) {
    printk("= TM Module SYS FS Init ended successfully =\n");
    return 0;
  }
  printk("sysfs group failed %d\n",iVar2);
  return iVar2;
}

