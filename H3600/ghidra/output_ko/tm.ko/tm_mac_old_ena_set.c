// module: tm.ko
// function: tm_mac_old_ena_set @ 0x45f9c
// size: 44 bytes
//

undefined4 tm_mac_old_ena_set(int param_1)

{
  int iVar1;
  
  iVar1 = sbrg_set_macaddr_age_en(param_1 != 0);
  if (iVar1 == 0) {
    return 0;
  }
  printk("tm_mac_old_ena_set fail\n");
  return 0xffffffff;
}

