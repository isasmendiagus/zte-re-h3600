// module: plat-zxylzb_9128S.ko
// function: serdes_prbs_err_ok @ 0x1bdb8
// size: 24 bytes
//

uint serdes_prbs_err_ok(void)

{
  return (uint)(*(int *)(pon_serdes_base + 0x68) << 0x11) >> 0x1f;
}

