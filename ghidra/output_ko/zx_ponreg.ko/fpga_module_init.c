// module: zx_ponreg.ko
// function: fpga_module_init @ 0x10168
// size: 116 bytes
//

undefined4 fpga_module_init(void)

{
  int iVar1;
  undefined4 uVar2;
  
  pon = 0xf4000000;
  iVar1 = __register_chrdev(0xde,0,0x100,&_LC3,&fpga_ops);
  if (iVar1 < 0) {
    printk("register fpga driver failed!\n");
    uVar2 = 0xffffffff;
  }
  else {
    printk("register fpga driver success, major=%d\n",0xde);
    uVar2 = 0;
  }
  return uVar2;
}

