// module: tm.ko
// function: tm_sdk_init @ 0x606fc
// size: 120 bytes
//

undefined4 tm_sdk_init(void)

{
  int iVar1;
  
  printk("enter tm_sdk_init  \n");
  tm_db_init();
  if ((g_aclRamInited == '\0') && (iVar1 = aclRamInit_part_6(), iVar1 != 0)) {
    printk("ACL RAM INIT FAILED!! \n");
    return 0xfffffff4;
  }
  acl_api_busy_lock = 0;
  if (lan_up == 1) {
    g_fast_opti = 0;
  }
  return 0;
}

