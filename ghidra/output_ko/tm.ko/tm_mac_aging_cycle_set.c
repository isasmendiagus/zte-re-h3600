// module: tm.ko
// function: tm_mac_aging_cycle_set @ 0x4a488
// size: 156 bytes
//

undefined4 tm_mac_aging_cycle_set(int param_1)

{
  int iVar1;
  int local_c;
  
  iVar1 = sbrg_get_table_sel(&local_c);
  if (iVar1 == 0) {
    if (local_c == 0) {
      param_1 = param_1 * 0x710;
    }
    else if (local_c == 1) {
      param_1 = param_1 * 0x1c40;
    }
    else {
      if (local_c != 2) {
        printk("Sel3 is not support\n");
        return 0xffffffff;
      }
      param_1 = param_1 * 0xe20;
    }
    iVar1 = sbrg_set_srcaddr_aging_cycle(param_1);
    if (iVar1 == 0) {
      return 0;
    }
  }
  printk("tm_mac_aging_cycle_set fail\n");
  return 0xffffffff;
}

