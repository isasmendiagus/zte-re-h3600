// module: tm.ko
// function: tm_pon_tm_qmg_initial @ 0x4d9b8
// size: 152 bytes
//

int tm_pon_tm_qmg_initial(void)

{
  int iVar1;
  
  iVar1 = qmg_set_ext_ddr_only_enable(0);
  if (iVar1 != 0) {
    printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0xe2);
    return iVar1;
  }
  iVar1 = qmg_set_ddr_cache_enable(1);
  if (iVar1 == 0) {
    if (lan_up != 1) {
      return 0;
    }
    qmg_set_up_ram_thd(0x50);
    qmg_set_dn_ram_thd(0x1fa0);
    return 0;
  }
  printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0xe6);
  return iVar1;
}

