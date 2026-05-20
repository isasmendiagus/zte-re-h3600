// module: plat-zxylzb_9128S.ko
// function: pon_tm_net_open @ 0x1939c
// size: 120 bytes
//

undefined4 pon_tm_net_open(char *param_1)

{
  code *pcVar1;
  int iVar2;
  
  _clear_bit(0,*(int *)(param_1 + 0x240) + 0x50);
  netif_carrier_on(param_1);
  iVar2 = strcmp(param_1,"pon");
  if (iVar2 == 0) {
    if ((*(uint *)(param_1 + 0x538) & 1) == 0) {
                    /* WARNING: Does not return */
      pcVar1 = (code *)software_udf(0x12,0x19414);
      (*pcVar1)();
    }
    DataMemoryBarrier(0xb);
    _clear_bit(0,param_1 + 0x538);
    *(uint *)(tm_base + 0x104) = *(uint *)(tm_base + 0x104) & 0xfffffffc;
  }
  return 0;
}

