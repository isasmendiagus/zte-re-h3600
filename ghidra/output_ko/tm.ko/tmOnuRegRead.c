// module: tm.ko
// function: tmOnuRegRead @ 0x45bac
// size: 104 bytes
//

int tmOnuRegRead(undefined4 param_1,uint *param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  int local_14;
  
  local_14 = 0;
  iVar1 = tmOnuGlbRegValidation(param_1,&local_14,param_3,1,param_4);
  if (iVar1 == 0) {
    uVar2 = fpga_read_reg(*(int *)(local_14 + 0x14) * param_3 + *(int *)(local_14 + 8));
    *param_2 = *(uint *)(local_14 + 0xc) & uVar2 >> (*(ushort *)(local_14 + 0x10) & 0xff);
  }
  return iVar1;
}

