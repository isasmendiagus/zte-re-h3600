// module: tm.ko
// function: tm_set_sbrg_pri_qtab_pon @ 0x55680
// size: 144 bytes
//

undefined4 tm_set_sbrg_pri_qtab_pon(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  int local_18 [2];
  
  iVar1 = getPort(param_1,local_18);
  if (iVar1 == -1 || local_18[0] == 8) {
    printk("tm_set_sbrg_pri_qtab_pon fail, error port %d\n",param_1);
    uVar2 = 0xffffffff;
  }
  else {
    iVar1 = sbrg_set_sbrg_pri_qtab_pon(local_18[0],param_2,param_3);
    uVar2 = 0;
    if (iVar1 != 0) {
      printk("ERROR:(%s:%d)","tm_api.c",0x4ff5);
      printk("tm_set_sbrg_pri_qtab_pon fail\n");
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

