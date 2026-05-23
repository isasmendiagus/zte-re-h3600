// module: tm.ko
// function: tm_port_dft_unkunicst_vltrans_get @ 0x50b8c
// size: 200 bytes
//

undefined4 tm_port_dft_unkunicst_vltrans_get(undefined4 param_1,int *param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_1c;
  int local_18 [3];
  
  local_1c = 0;
  if (param_2 == (int *)0x0) {
    printk("ERROR:(%s:%d)","tm_api.c",0x2586);
    printk("param pp_act is NULL\n");
    uVar2 = 0xffffffff;
  }
  else {
    iVar1 = getPort(param_1,local_18);
    if ((iVar1 == 0) && (local_18[0] != 8)) {
      iVar1 = sbrg_get_dft_unkuni_vl_trans_pktdeal(local_18[0],&local_1c);
      if (iVar1 == 0) {
        uVar2 = 0;
        if (local_1c != 1) {
          if (local_1c == 0) {
            *param_2 = 0;
            return 0;
          }
          if (local_1c != 2) {
            return 0;
          }
        }
        *param_2 = local_1c;
      }
      else {
        printk("tm_port_dft_unkunicst_vltrans_get fail\n");
        uVar2 = 0xffffffff;
      }
    }
    else {
      printk("tm_port_dft_unkunicst_vltrans_get fail, error port %d\n",param_1);
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

