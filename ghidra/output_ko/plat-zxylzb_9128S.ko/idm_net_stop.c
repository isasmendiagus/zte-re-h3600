// module: plat-zxylzb_9128S.ko
// function: idm_net_stop @ 0x15400
// size: 172 bytes
//

undefined4 idm_net_stop(char *param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x240) == 0) {
    warn_slowpath_null("include/linux/netdevice.h",0xa06);
    printk(&_LC36);
  }
  else {
    _set_bit(0,*(int *)(param_1 + 0x240) + 0x50);
  }
  netif_carrier_off(param_1);
  iVar1 = strcmp(param_1,"idm0");
  if (iVar1 == 0) {
    napi_disable(param_1 + 0x528);
    idm_int_mask = *(uint *)(npp_base + 0x8024) | 0x14;
    *(uint *)(npp_base + 0x8024) = idm_int_mask;
  }
  return 0;
}

