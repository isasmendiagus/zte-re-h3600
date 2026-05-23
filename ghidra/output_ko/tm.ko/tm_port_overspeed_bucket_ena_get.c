// module: tm.ko
// function: tm_port_overspeed_bucket_ena_get @ 0x51264
// size: 128 bytes
//

undefined4 tm_port_overspeed_bucket_ena_get(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_1c;
  undefined1 auStack_18 [4];
  uint local_14;
  
  iVar1 = getPort(param_1,auStack_18);
  if ((iVar1 == 0) && (local_14 < 8)) {
    iVar1 = sadm_get_bucket_overspeed_en(local_14,&local_1c);
    if (iVar1 == 0) {
      *(bool *)param_2 = local_1c != 0;
      uVar2 = 0;
    }
    else {
      printk("tm_port_overspeed_bucket_ena_get fail\n");
      uVar2 = 0xffffffff;
    }
  }
  else {
    printk("tm_port_overspeed_bucket_ena_get fail, error port %d\n",param_1);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

