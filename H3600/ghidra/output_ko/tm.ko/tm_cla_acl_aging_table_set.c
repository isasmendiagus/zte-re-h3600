// module: tm.ko
// function: tm_cla_acl_aging_table_set @ 0x53e74
// size: 68 bytes
//

undefined4
tm_cla_acl_aging_table_set
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = cla_set_acl_aging_table(param_2,param_3,param_3,param_4,param_4);
  if (iVar1 == 0) {
    return 0;
  }
  printk("ERROR:(%s:%d)","tm_api.c",0x3f09);
  printk("cla_set_acl_aging_table fail\n");
  return 0xffffffff;
}

