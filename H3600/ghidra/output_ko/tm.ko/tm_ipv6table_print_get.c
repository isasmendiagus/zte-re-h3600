// module: tm.ko
// function: tm_ipv6table_print_get @ 0x4b8ac
// size: 36 bytes
//

undefined4 tm_ipv6table_print_get(void)

{
  int iVar1;
  
  iVar1 = sbrg_print_ipv6table();
  if (iVar1 == 0) {
    return 0;
  }
  printk("tm_ipv6table_print_get fail\n");
  return 0xffffffff;
}

