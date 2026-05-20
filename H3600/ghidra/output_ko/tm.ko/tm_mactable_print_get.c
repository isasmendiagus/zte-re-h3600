// module: tm.ko
// function: tm_mactable_print_get @ 0x4b478
// size: 36 bytes
//

undefined4 tm_mactable_print_get(void)

{
  int iVar1;
  
  iVar1 = sbrg_print_mactable();
  if (iVar1 == 0) {
    return 0;
  }
  printk("tm_mactable_print_get fail\n");
  return 0xffffffff;
}

