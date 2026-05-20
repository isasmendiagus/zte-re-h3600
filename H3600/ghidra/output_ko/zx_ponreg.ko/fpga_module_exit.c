// module: zx_ponreg.ko
// function: fpga_module_exit @ 0x101dc
// size: 48 bytes
//

void fpga_module_exit(void)

{
  __arm_iounmap(pon);
  __unregister_chrdev(0xde,0,0x100,&_LC3);
  return;
}

