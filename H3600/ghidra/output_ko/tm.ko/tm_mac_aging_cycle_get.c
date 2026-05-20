// module: tm.ko
// function: tm_mac_aging_cycle_get @ 0x4c6f8
// size: 240 bytes
//

undefined4 tm_mac_aging_cycle_get(uint *param_1)

{
  undefined4 uVar1;
  uint local_10;
  int local_c;
  
  if (param_1 == (uint *)0x0) {
    printk("ERROR:(%s:%d)","tm_api.c",0x2b2d);
    printk("param pp_time is NULL\n");
    uVar1 = 0xffffffff;
  }
  else {
    sbrg_get_table_sel(&local_c);
    sbrg_get_srcaddr_aging_cycle(&local_10);
    if (local_c == 0) {
      *param_1 = local_10 / 0x710;
      return 0;
    }
    if (local_c == 1) {
      *param_1 = local_10 / 0x1c40;
      return 0;
    }
    if (local_c == 2) {
      uVar1 = 0;
      *param_1 = local_10 / 0xe20;
    }
    else {
      printk("Sel3 is not support\n");
      uVar1 = 0xffffffff;
    }
  }
  return uVar1;
}

