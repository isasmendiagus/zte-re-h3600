// module: tm.ko
// function: tm_pon_pp_pm_initial @ 0x4eac8
// size: 68 bytes
//

uint tm_pon_pp_pm_initial(void)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = pp_pm_cfg_padding_en_set(1);
  uVar2 = pp_pm_cfg_padding_len_set(0x1e);
  if ((uVar2 | uVar1) != 0) {
    printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x2d1);
  }
  return uVar2 | uVar1;
}

