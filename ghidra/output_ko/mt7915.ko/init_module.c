// module: mt7915.ko
// function: init_module @ 0x28f3e8
// size: 104 bytes
//

void init_module(void)

{
  undefined4 in_r3;
  
  if (-1 < DebugLevel) {
    printk("2020 0214 register %s\n","mt_drv");
  }
  os_module_init();
  __pci_register_driver(&_LANCHOR2,__this_module,"mt7915");
  __pci_register_driver(&DAT_005df694,__this_module,"mt7915",in_r3);
  return;
}

