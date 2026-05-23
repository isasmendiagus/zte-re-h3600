// module: plat-zxylzb_9128S.ko
// function: pon_pp_cls_port_mac @ 0x16798
// size: 72 bytes
//

undefined4 pon_pp_cls_port_mac(int param_1)

{
  if ((*(uint *)(pp_base + 0x8004) & 0x10000) == 0) {
    *(uint *)(pp_base + 0x8004) = *(uint *)(pp_base + 0x8004) | param_1 << 8 | 0x10000;
    return 0;
  }
  return 0xffffffff;
}

