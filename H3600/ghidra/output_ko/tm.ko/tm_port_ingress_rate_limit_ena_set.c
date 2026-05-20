// module: tm.ko
// function: tm_port_ingress_rate_limit_ena_set @ 0x45f44
// size: 44 bytes
//

undefined4 tm_port_ingress_rate_limit_ena_set(int param_1)

{
  int iVar1;
  
  iVar1 = sadm_set_adm_en(param_1 != 0);
  if (iVar1 == 0) {
    return 0;
  }
  printk("tm_port_ingress_rate_limit_ena_set fail\n");
  return 0xffffffff;
}

