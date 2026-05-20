// module: plat-zxylzb_9128S.ko
// function: netdebug_module_init @ 0x1d328
// size: 80 bytes
//

undefined4 netdebug_module_init(void)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = __register_chrdev(99,0,0x100,"netdebug_dev",&netdebug_module_fops);
  if (iVar1 < 0) {
    printk("module-netdebug: register_chrdev failed\n");
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

