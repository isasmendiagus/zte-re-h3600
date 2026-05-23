// module: tm.ko
// function: tm_tpid_get @ 0x48500
// size: 104 bytes
//

undefined4 tm_tpid_get(uint param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_c;
  
  if (param_1 < 8) {
    iVar1 = pon_pp_get_tpid(&local_c,param_1);
    if (iVar1 == 0) {
      *param_2 = local_c;
      uVar2 = 0;
    }
    else {
      printk("tm_tpid_get fail\n");
      uVar2 = 0xffffffff;
    }
  }
  else {
    printk("tm_tpid_get fail, error num %d\n",param_1);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

