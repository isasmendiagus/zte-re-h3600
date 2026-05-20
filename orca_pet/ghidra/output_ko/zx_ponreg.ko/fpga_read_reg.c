// module: zx_ponreg.ko
// function: fpga_read_reg @ 0x10000
// size: 20 bytes
//

undefined4 fpga_read_reg(int param_1)

{
  return *(undefined4 *)(pon + param_1 * 4);
}

