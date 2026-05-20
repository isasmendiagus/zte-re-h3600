// module: plat-zxylzb_9128S.ko
// function: register_pon_int @ 0x1b800
// size: 96 bytes
//

int register_pon_int(void)

{
  int iVar1;
  
  iVar1 = request_threaded_irq(g_pon_irq,zx_pon_int,0,0x80,&_LC0,pon_int_info);
  if (iVar1 < 0) {
    printk("request pon irq failed\n");
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}

