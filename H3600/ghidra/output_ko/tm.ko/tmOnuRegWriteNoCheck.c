// module: tm.ko
// function: tmOnuRegWriteNoCheck @ 0x45cd0
// size: 84 bytes
//

undefined4 tmOnuRegWriteNoCheck(int param_1,uint param_2,int param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  
  param_4 = param_4 + param_1 * 0x1c;
  iVar2 = *(int *)(param_4 + 0x14) * param_3 + *(int *)(param_4 + 8);
  *(int *)(param_4 + 0x18) = *(int *)(param_4 + 0x18) + 1;
  uVar1 = fpga_read_reg(iVar2);
  fpga_write_reg(iVar2,uVar1 & ~(*(uint *)(param_4 + 0xc) << (*(ushort *)(param_4 + 0x10) & 0xff)) |
                       (param_2 & *(uint *)(param_4 + 0xc)) << (*(ushort *)(param_4 + 0x10) & 0xff))
  ;
  return 0;
}

