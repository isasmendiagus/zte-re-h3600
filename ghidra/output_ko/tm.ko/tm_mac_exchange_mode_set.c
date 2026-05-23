// module: tm.ko
// function: tm_mac_exchange_mode_set @ 0x45ff4
// size: 44 bytes
//

undefined4 tm_mac_exchange_mode_set(int param_1)

{
  int iVar1;
  
  iVar1 = sbrg_set_macaddr_exchange_md(param_1 != 0);
  if (iVar1 == 0) {
    return 0;
  }
  printk("tm_mac_exchange_mode_set fail\n");
  return 0xffffffff;
}

