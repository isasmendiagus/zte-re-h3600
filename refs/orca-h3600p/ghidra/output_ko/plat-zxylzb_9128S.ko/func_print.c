// module: plat-zxylzb_9128S.ko
// function: func_print @ 0x11e88
// size: 60 bytes
//

void func_print(void)

{
  int iVar1;
  
  iVar1 = rb_first();
  if (iVar1 == 0) {
    return;
  }
  do {
    printk("func %s : %.8x-%.8x\n",iVar1 + 0x14,*(undefined4 *)(iVar1 + 0xc),
           *(undefined4 *)(iVar1 + 0x10));
    iVar1 = rb_next(iVar1);
  } while (iVar1 != 0);
  return;
}

