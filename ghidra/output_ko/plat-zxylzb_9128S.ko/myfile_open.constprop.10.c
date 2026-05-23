// module: plat-zxylzb_9128S.ko
// function: myfile_open.constprop.10 @ 0x1190c
// size: 52 bytes
//

uint myfile_open_constprop_10(undefined4 param_1)

{
  uint uVar1;
  
  uVar1 = filp_open(param_1,0,0);
  if (uVar1 < 0xfffff001) {
    return uVar1;
  }
  printk("filp_open [%s] failed.\n",param_1);
  return 0;
}

