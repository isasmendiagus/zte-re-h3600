// module: tm.ko
// function: tm_port_unknwn_multicast_flood_set @ 0x4faa4
// size: 112 bytes
//

undefined4 tm_port_unknwn_multicast_flood_set(undefined4 param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 local_18 [3];
  
  cVar1 = getPort(param_1,local_18);
  if (cVar1 == '\0') {
    cVar1 = sbrg_set_unknown_multicst_pktdeal(local_18[0],param_2 != 0);
    uVar2 = 0;
    if (cVar1 != '\0') {
      printk("tm_port_unknwn_multicast_flood_set fail\n");
      uVar2 = 0xffffffff;
    }
  }
  else {
    printk("tm_port_unknwn_multicast_flood_set fail, error port %d\n",param_1);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

