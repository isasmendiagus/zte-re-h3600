// module: mt7915.ko
// function: cleanup_module @ 0x28f454
// size: 36 bytes
//

void cleanup_module(void)

{
  pci_unregister_driver(&_LANCHOR2);
  pci_unregister_driver(&DAT_005df694);
  os_module_exit();
  return;
}

