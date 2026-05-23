// module: zx_ponreg.ko
// function: fpga_write_reg_one @ 0x10154
// size: 20 bytes
//

void fpga_write_reg_one(int param_1,undefined4 param_2)

{
  *(undefined4 *)(pon + param_1 * 4) = param_2;
  return;
}

