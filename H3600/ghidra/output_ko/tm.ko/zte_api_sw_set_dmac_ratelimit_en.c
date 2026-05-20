// module: tm.ko
// function: zte_api_sw_set_dmac_ratelimit_en @ 0x63ce4
// size: 120 bytes
//

undefined4
zte_api_sw_set_dmac_ratelimit_en
          (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_1 != 1) {
    fpga_write_reg(0xe10a1,0,param_3,param_4,param_4);
    fpga_write_reg(0xe100d,0x1869);
    fpga_write_reg(0xe100a,5000);
    return 0;
  }
  fpga_write_reg(0xe10a1,0xc0,param_3,param_4,param_4);
  fpga_write_reg(0xe100d,0x1869);
  fpga_write_reg(0xe100a,0x2008);
  return 0;
}

