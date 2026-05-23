// module: tm.ko
// function: getTpidAddr @ 0x57868
// size: 96 bytes
//

undefined4 getTpidAddr(uint param_1,short *param_2)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = 0xe8046;
  *param_2 = 0;
  do {
    uVar1 = fpga_read_reg(iVar2);
    if ((uVar1 & 0xffff) == param_1) {
      *param_2 = (short)iVar2 + 0x7fba;
      return 0;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 != 0xe804d);
  return 0;
}

