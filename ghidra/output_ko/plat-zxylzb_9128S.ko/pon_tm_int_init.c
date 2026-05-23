// module: plat-zxylzb_9128S.ko
// function: pon_tm_int_init @ 0x19440
// size: 124 bytes
//

int pon_tm_int_init(void)

{
  int iVar1;
  
  *(undefined4 *)(tm_base + 0x104) = 0xffffffff;
  iVar1 = request_threaded_irq(g_tm_irq,zx_pon_tm_int,0,0,"pon_tm",&pon_tm_int_info);
  if (iVar1 < 0) {
    printk("request pon_tm irq failed\n");
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}

