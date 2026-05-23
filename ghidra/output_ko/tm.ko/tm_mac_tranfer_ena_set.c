// module: tm.ko
// function: tm_mac_tranfer_ena_set @ 0x50c54
// size: 112 bytes
//

undefined4 tm_mac_tranfer_ena_set(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_18 [3];
  
  iVar1 = getPort(param_1,local_18);
  if ((iVar1 == 0) && (local_18[0] != 8)) {
    iVar1 = sbrg_set_pt_transfer_en(local_18[0],param_2);
    uVar2 = 0;
    if (iVar1 != 0) {
      printk("tm_mac_tranfer_ena_set fail\n");
      uVar2 = 0xffffffff;
    }
  }
  else {
    printk("tm_mac_tranfer_ena_set fail, error port %d\n",param_1);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

