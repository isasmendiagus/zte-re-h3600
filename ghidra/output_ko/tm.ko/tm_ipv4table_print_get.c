// module: tm.ko
// function: tm_ipv4table_print_get @ 0x4b888
// size: 36 bytes
//

undefined4 tm_ipv4table_print_get(void)

{
  int iVar1;
  
  iVar1 = sbrg_print_ipv4table();
  if (iVar1 == 0) {
    return 0;
  }
  printk("sbrg_print_ipv4table fail\n");
  return 0xffffffff;
}

