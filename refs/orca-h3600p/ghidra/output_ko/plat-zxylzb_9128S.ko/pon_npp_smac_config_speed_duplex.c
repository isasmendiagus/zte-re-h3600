// module: plat-zxylzb_9128S.ko
// function: pon_npp_smac_config_speed_duplex @ 0x143dc
// size: 12 bytes
//

void pon_npp_smac_config_speed_duplex(uint param_1)

{
  if (4 < param_1) {
    return;
  }
  pon_npp_smac_config_speed_duplex_part_0();
  return;
}

