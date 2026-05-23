// module: plat-zxylzb_9128S.ko
// function: apb_read @ 0x1c310
// size: 24 bytes
//

undefined4 apb_read(int param_1)

{
  return *(undefined4 *)(pon_serdes_base + param_1);
}

