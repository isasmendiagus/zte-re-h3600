// module: tm.ko
// function: tm_vlantable_print_get @ 0x4b680
// size: 36 bytes
//

undefined4 tm_vlantable_print_get(void)

{
  int iVar1;
  
  iVar1 = sbrg_print_vltbl();
  if (iVar1 == 0) {
    return 0;
  }
  printk("tm_vlantable_print_get fail\n");
  return 0xffffffff;
}

