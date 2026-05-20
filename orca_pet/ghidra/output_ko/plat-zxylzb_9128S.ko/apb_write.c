// module: plat-zxylzb_9128S.ko
// function: apb_write @ 0x1c2f8
// size: 24 bytes
//

void apb_write(int param_1,undefined4 param_2)

{
  *(undefined4 *)(pon_serdes_base + param_1) = param_2;
  return;
}

