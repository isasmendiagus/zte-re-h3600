// module: plat-zxylzb_9128S.ko
// function: zx_pon_pp_int @ 0x17bd4
// size: 60 bytes
//

undefined4 zx_pon_pp_int(void)

{
  if ((*(uint *)(pp_base + 0x20000) & 1 & ~*(uint *)("idm_status_proc failed!\n" + pp_base + 4)) !=
      0) {
    pon_pp_brg_int();
  }
  return 1;
}

