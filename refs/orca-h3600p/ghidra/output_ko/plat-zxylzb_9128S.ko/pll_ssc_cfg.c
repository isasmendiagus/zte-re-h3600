// module: plat-zxylzb_9128S.ko
// function: pll_ssc_cfg @ 0x1c6bc
// size: 404 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void pll_ssc_cfg(uint *param_1,int param_2,int param_3,uint param_4,int param_5,uint param_6)

{
  int iVar1;
  
  *param_1 = *param_1 | 0x80000000;
  param_1[2] = param_1[2] | 0x800;
  param_1[2] = param_1[2] & 0xfffffffd;
  *param_1 = *param_1 & 0xffffffc7 | param_5 << 3;
  *param_1 = *param_1 & 0xfffffff8 | param_6;
  *param_1 = *param_1 & 0xff03ffff | param_2 << 0x12;
  *param_1 = *param_1 & 0xfffc003f | param_3 << 6;
  param_1[1] = param_1[1] & 0xff000000 | param_4;
  param_1[2] = param_1[2] & 0xffffff83 | 0x10;
  param_1[2] = param_1[2] | 1;
  *param_1 = *param_1 & 0xf7ffffff;
  param_1[1] = param_1[1] & 0xf7ffffff;
  iVar1 = 10;
  do {
    (*_request_threaded_irq)(0x66665b0);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  *param_1 = *param_1 & 0x7fffffff;
  do {
  } while ((param_1[1] & 0x10000000) == 0);
  printk("pll_ssc_cfg success!\n");
  return;
}

