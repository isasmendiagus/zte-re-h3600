// module: tm.ko
// function: tm_pon_npp_sipc_initial @ 0x4ec1c
// size: 64 bytes
//

int tm_pon_npp_sipc_initial(void)

{
  int iVar1;
  
  sipc_set_rx_en(1);
  iVar1 = sipc_set_cpu_up_en(0);
  if (iVar1 != 0) {
    printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x31b);
  }
  return iVar1;
}

