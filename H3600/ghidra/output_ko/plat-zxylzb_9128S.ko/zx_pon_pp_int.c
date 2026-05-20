// module: plat-zxylzb_9128S.ko
// function: zx_pon_pp_int @ 0x17fc0
// size: 60 bytes
//

undefined4 zx_pon_pp_int(void)

{
  if ((*(uint *)(pp_base + 0x20000) & 1 &
      ~*(uint *)("mac learn:pbm %d vlan %d mac %.2x %.2x %.2x %.2x %.2x %.2x\n" + pp_base + 0x14))
      != 0) {
    pon_pp_brg_int();
  }
  return 1;
}

