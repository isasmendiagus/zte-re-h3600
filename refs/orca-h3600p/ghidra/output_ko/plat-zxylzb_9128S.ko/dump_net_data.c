// module: plat-zxylzb_9128S.ko
// function: dump_net_data @ 0x19434
// size: 120 bytes
//

void dump_net_data(undefined1 *param_1,uint param_2)

{
  uint uVar1;
  
  if (0x7f < param_2) {
    param_2 = 0x80;
  }
  if (param_2 != 0) {
    uVar1 = 0;
    printk("%.2x ",*param_1);
    while (uVar1 = uVar1 + 1, uVar1 != param_2) {
      printk("%.2x ",param_1[uVar1]);
      if ((uVar1 & 0xf) == 0xf) {
        printk(&_LC4);
      }
    }
  }
  printk(&_LC4);
  return;
}

