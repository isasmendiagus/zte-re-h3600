// module: plat-zxylzb_9128S.ko
// function: idm_net_open @ 0x150c0
// size: 144 bytes
//

undefined4 idm_net_open(char *param_1)

{
  code *pcVar1;
  int iVar2;
  
  _clear_bit(0,*(int *)(param_1 + 0x240) + 0x50);
  netif_carrier_on(param_1);
  iVar2 = strcmp(param_1,"idm0");
  if (iVar2 == 0) {
    if ((*(uint *)(param_1 + 0x530) & 1) == 0) {
                    /* WARNING: Does not return */
      pcVar1 = (code *)software_udf(0x12,0x15150);
      (*pcVar1)();
    }
    DataMemoryBarrier(0xb);
    _clear_bit(0,param_1 + 0x530);
    idm_int_mask = *(uint *)(npp_base + 0x8024) & 0xfffffffb;
    *(uint *)(npp_base + 0x8024) = idm_int_mask;
  }
  return 0;
}

