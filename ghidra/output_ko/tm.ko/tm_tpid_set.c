// module: tm.ko
// function: tm_tpid_set @ 0x45ef4
// size: 80 bytes
//

undefined4 tm_tpid_set(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  if (7 < param_1) {
    printk("tm_tpid_set fail, error num %d\n",param_1,param_3,param_1,param_4);
    return 0xffffffff;
  }
  iVar1 = pon_pp_set_tpid(param_2,param_1);
  if (iVar1 == 0) {
    return 0;
  }
  printk("tm_tpid_set fail\n");
  return 0xffffffff;
}

