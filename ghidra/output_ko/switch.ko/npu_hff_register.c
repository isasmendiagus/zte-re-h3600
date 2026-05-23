// module: switch.ko
// function: npu_hff_register @ 0x202d4
// size: 124 bytes
//

undefined4
npu_hff_register(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_1 != (undefined4 *)0x0) {
    __memzero(&npu_hff_func_tbl,0x10,param_3,param_4,param_4);
    npu_hff_func_tbl = *param_1;
    DAT_0002b90c = param_1[1];
    DAT_0002b910 = param_1[2];
    DAT_0002b914 = param_1[3];
    printk("register npu driver %d\n",0xc);
    npu_register_driver(&npu_drv);
  }
  __memzero(gMultiVlanEntry,0x420);
  g_multivlan_lock = 0;
  return 0;
}

