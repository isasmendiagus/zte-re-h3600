// module: tm.ko
// function: tm_port_overspeed_bucket_ena_set @ 0x511e0
// size: 132 bytes
//

undefined4 tm_port_overspeed_bucket_ena_set(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined1 auStack_18 [4];
  uint local_14;
  
  iVar1 = getPort(param_1,auStack_18);
  if ((iVar1 == 0) && (local_14 < 8)) {
    iVar1 = sadm_set_bucket_overspeed_en(local_14,param_2 != 0);
    if ((iVar1 == 0) && (iVar1 = sadm_set_bucket_overspeed_threshold(5000), iVar1 == 0)) {
      return 0;
    }
    printk("tm_port_overspeed_bucket_ena_set fail\n");
  }
  else {
    printk("tm_port_overspeed_bucket_ena_set fail, error port %d\n",param_1);
  }
  return 0xffffffff;
}

