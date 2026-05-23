// module: tm.ko
// function: tmOnuRegReadNoCheck @ 0x45c8c
// size: 68 bytes
//

undefined4 tmOnuRegReadNoCheck(int param_1,uint *param_2,int param_3,int param_4)

{
  uint uVar1;
  
  param_4 = param_4 + param_1 * 0x1c;
  *(int *)(param_4 + 0x18) = *(int *)(param_4 + 0x18) + 1;
  uVar1 = fpga_read_reg(*(int *)(param_4 + 0x14) * param_3 + *(int *)(param_4 + 8));
  *param_2 = *(uint *)(param_4 + 0xc) & uVar1 >> (*(ushort *)(param_4 + 0x10) & 0xff);
  return 0;
}

