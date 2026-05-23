// module: tm.ko
// function: tmOnuRegWrite @ 0x45c14
// size: 120 bytes
//

int tmOnuRegWrite(undefined4 param_1,uint param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int local_14;
  
  local_14 = 0;
  iVar1 = tmOnuGlbRegValidation(param_1,&local_14,param_3,2,param_4);
  if (iVar1 == 0) {
    iVar3 = *(int *)(local_14 + 0x14) * param_3 + *(int *)(local_14 + 8);
    uVar2 = fpga_read_reg(iVar3);
    fpga_write_reg(iVar3,uVar2 & ~(*(uint *)(local_14 + 0xc) <<
                                  (*(ushort *)(local_14 + 0x10) & 0xff)) |
                         (param_2 & *(uint *)(local_14 + 0xc)) <<
                         (*(ushort *)(local_14 + 0x10) & 0xff));
  }
  return iVar1;
}

