// module: tm.ko
// function: prbsCounterGetHandler @ 0x6514c
// size: 52 bytes
//

void prbsCounterGetHandler(void)

{
  undefined4 uVar1;
  
  uVar1 = serdes_get_err_cnt();
  printk("%s counter after timer = %ld\n","prbsCounterGetHandler",uVar1);
  printk("ztePonGetPrbsCounters counter: %ld.\n",uVar1);
  return;
}

