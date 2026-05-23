// module: plat-zxylzb_9128S.ko
// function: pon_set_mode @ 0x1b864
// size: 80 bytes
//

void pon_set_mode(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 extraout_r2;
  
  printk("before pon_mode=0x%x\n",*(undefined4 *)(pon_base + 0x40018));
  *(undefined4 *)(pon_base + 0x40018) = param_1;
  printk("after  pon_mode=0x%x\n",*(undefined4 *)(pon_base + 0x40018),extraout_r2,param_4);
  return;
}

