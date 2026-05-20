// module: tm.ko
// function: pp_adm_onesecond @ 0x63cac
// size: 56 bytes
//

void pp_adm_onesecond(int param_1)

{
  if (param_1 == 1000) {
    fpga_write_reg(0xe5012,200000000);
    return;
  }
  if (param_1 != 10) {
    return;
  }
  fpga_write_reg(0xe5012,2000000);
  return;
}

