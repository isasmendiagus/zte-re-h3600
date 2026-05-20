// module: tm.ko
// function: tm_pon_pp_sadm_initial @ 0x4db8c
// size: 124 bytes
//

uint tm_pon_pp_sadm_initial(void)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = sadm_set_adm_en(1);
  uVar2 = sadm_set_adm_trap_en(1);
  if ((uVar2 | uVar1) != 0) {
    printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x18d);
    return uVar2 | uVar1;
  }
  uVar1 = sadm_set_one_second(200000000);
  if (uVar1 == 0) {
    return 0;
  }
  printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x191);
  return uVar1;
}

