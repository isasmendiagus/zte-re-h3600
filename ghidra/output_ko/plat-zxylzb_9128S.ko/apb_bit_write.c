// module: plat-zxylzb_9128S.ko
// function: apb_bit_write @ 0x1bcd8
// size: 56 bytes
//

void apb_bit_write(int param_1,int param_2,uint param_3,uint param_4)

{
  *(uint *)(pon_serdes_base + param_1) =
       *(uint *)(pon_serdes_base + param_1) & ~(~(-1 << (param_3 & 0xff)) << (param_4 & 0xff)) |
       param_2 << (param_4 & 0xff);
  return;
}

