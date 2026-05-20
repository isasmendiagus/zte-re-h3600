// module: plat-zxylzb_9128S.ko
// function: pon_pp_brg_init @ 0x177b8
// size: 360 bytes
//

undefined4 pon_pp_brg_init(void)

{
  uint uVar1;
  uint uVar2;
  
  *(char **)(pp_base + 0x8004) = " %u\n";
  *(undefined4 *)(pp_base + 0x8340) = 0xff5555ff;
  *(undefined4 *)(pp_base + 0x8344) = 0x1e;
  *(undefined4 *)(pp_base + 0x8380) = 0x1f;
  *(undefined4 *)(pp_base + 0x863c) = 0xaaaaaaaa;
  *(undefined4 *)(pp_base + 0x81c0) = 0xff;
  *(undefined4 *)(pp_base + 0x81c4) = 0x5555;
  *(undefined4 *)(pp_base + 0x8188) = 0x13f434;
  *(undefined4 *)(pp_base + 0x82c0) = 0xff;
  *(undefined4 *)(pp_base + 0x8300) = 0xffff;
  *(undefined4 *)(pp_base + 0x8304) = 0x1e;
  *(undefined4 *)(pp_base + 0x8050) = 0xfffffffa;
  *(undefined4 *)(pp_base + 0x8008) = 0xff00;
  uVar1 = 0;
  do {
    uVar2 = uVar1 & 0xff;
    uVar1 = uVar1 + 1;
    pon_pp_add_port_to_vlan(0,uVar2,3);
    pon_pp_add_port_to_vlan(1,uVar2,3);
  } while (uVar1 != 8);
  pon_pp_port_isolate_part_1(6,0xdf);
  pon_pp_port_isolate_part_1(7,0xdf);
  return 0;
}

