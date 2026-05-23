// module: plat-zxylzb_9128S.ko
// function: switch_smac_set_rx_flow_crtl @ 0x144f4
// size: 44 bytes
//

void switch_smac_set_rx_flow_crtl(uint param_1,undefined4 param_2)

{
  if (4 < param_1) {
    return;
  }
  *(undefined4 *)(npp_base + param_1 * 0x40000 + 0x40090) = param_2;
  return;
}

