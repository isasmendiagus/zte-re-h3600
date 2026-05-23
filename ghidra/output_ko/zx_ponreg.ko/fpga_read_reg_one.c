// module: zx_ponreg.ko
// function: fpga_read_reg_one @ 0x10140
// size: 20 bytes
//

undefined4 fpga_read_reg_one(int param_1)

{
  return *(undefined4 *)(pon + param_1 * 4);
}

