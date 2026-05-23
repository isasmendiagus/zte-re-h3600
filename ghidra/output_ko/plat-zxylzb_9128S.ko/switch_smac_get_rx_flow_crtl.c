// module: plat-zxylzb_9128S.ko
// function: switch_smac_get_rx_flow_crtl @ 0x14468
// size: 52 bytes
//

undefined4 switch_smac_get_rx_flow_crtl(uint param_1)

{
  if (param_1 < 5) {
    return *(undefined4 *)(npp_base + param_1 * 0x40000 + 0x40090);
  }
  return 0;
}

