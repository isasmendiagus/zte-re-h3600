// module: plat-zxylzb_9128S.ko
// function: pll_cfg_fractional @ 0x1beb4
// size: 440 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void pll_cfg_fractional(uint *param_1,int param_2,uint param_3,uint param_4,int param_5,uint param_6
                       )

{
  int iVar1;
  
  printk("enter pll_cfg_fractional\n");
  if (param_3 < 0x14) {
    printk("feed back divide value is %d < 20 \n",param_3);
  }
  *param_1 = *param_1 | 0x80000000;
  *param_1 = *param_1 & 0xf7ffffff;
  *param_1 = *param_1 & 0xfeffffff;
  *param_1 = *param_1 & 0xff03ffff | param_2 << 0x12;
  *param_1 = *param_1 & 0xfffc003f | param_3 << 6;
  if (param_5 != 0) {
    *param_1 = *param_1 & 0xffffffc7 | param_5 << 3;
  }
  if (param_6 != 0) {
    *param_1 = *param_1 & 0xfffffff8 | param_6;
  }
  param_1[1] = param_1[1] & 0xf7ffffff;
  param_1[1] = param_1[1] | 0x4000000;
  param_1[1] = param_1[1] & 0xfdffffff;
  param_1[1] = param_1[1] & 0xfeffffff;
  param_1[1] = param_1[1] & 0xff000000 | param_4;
  iVar1 = 100;
  do {
    (*_request_threaded_irq)(0x66665b0);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  *param_1 = *param_1 & 0x7fffffff;
  return;
}

