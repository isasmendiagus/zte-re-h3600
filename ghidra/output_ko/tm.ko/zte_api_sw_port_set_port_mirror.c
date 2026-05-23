// module: tm.ko
// function: zte_api_sw_port_set_port_mirror @ 0x61078
// size: 844 bytes
//

undefined4 zte_api_sw_port_set_port_mirror(uint param_1,int param_2,uint param_3,uint param_4)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  uVar3 = param_1;
  if (7 < param_1) {
    uVar3 = param_4;
  }
  if (7 < uVar3) {
    printk("[%s] invalid portid\n","zte_api_sw_port_set_port_mirror");
    return 0xffffffff;
  }
  if (param_1 == 5) {
    if (param_2 == 1) {
      if ((param_3 & 0xfd) == 0) {
        fpga_write_reg(0xe8131,(param_4 + 1) * 0x100 | 0x80);
        fpga_write_reg(0xe8132,0x198);
      }
      if (1 < param_3 - 1) {
        return 0;
      }
      fpga_write_reg(0xe8134,(param_4 + 1) * 0x100 | 0x40);
      fpga_write_reg(0xe8135,0x198);
      return 0;
    }
    if (param_2 != 0) {
      return 0;
    }
    if ((param_3 & 0xfd) == 0) {
      fpga_write_reg(0xe8131);
      fpga_write_reg(0xe8132,0);
    }
    if (1 < param_3 - 1) {
      return 0;
    }
    fpga_write_reg(0xe8134,0);
    fpga_write_reg(0xe8135,0);
    return 0;
  }
  if (param_2 != 1) {
    if (param_2 != 0) {
      return 0;
    }
    if ((param_3 & 0xfd) == 0) {
      fpga_write_reg(0xe8136);
      fpga_write_reg(0xe8137,0);
      fpga_write_reg(0xe8138,0);
    }
    if (param_3 - 1 < 2) {
      fpga_write_reg(0xe8139,0);
      fpga_write_reg(0xe813a,0);
      fpga_write_reg(0xe813b,0);
    }
    fpga_write_reg(0xe218c,0x80);
    return 0;
  }
  if ((param_3 & 0xfd) == 0) {
    uVar3 = param_1 - 6 & 0xff;
    if (uVar3 < 2) {
      iVar2 = param_1 << 0x10;
    }
    else {
      iVar2 = (param_1 + 1) * 0x10000;
    }
    if ((param_4 - 6 & 0xff) < 2) {
      iVar4 = param_4 << 8;
    }
    else {
      iVar4 = (param_4 + 1) * 0x100;
    }
    if (1 < uVar3) {
      fpga_write_reg(0xe8136);
      fpga_write_reg(0xe8137,iVar4);
      fpga_write_reg(0xe8138,0x191);
      if (1 < param_3 - 1) {
        return 0;
      }
LAB_000611a8:
      iVar2 = (param_1 + 1) * 0x1000;
      goto LAB_000611b0;
    }
    uVar1 = fpga_read_reg(0xe218c,iVar2);
    fpga_write_reg(0xe218c,param_4 + 1 | 0x90 | 1 << (param_1 + 8 & 0xff) | uVar1);
    if (1 < param_3 - 1) {
      return 0;
    }
  }
  else {
    if (1 < param_3 - 1) {
      return 0;
    }
    uVar3 = param_1 - 6 & 0xff;
    if (1 < uVar3) goto LAB_000611a8;
  }
  iVar2 = param_1 << 0xc;
LAB_000611b0:
  if ((param_4 - 6 & 0xff) < 2) {
    uVar1 = param_4 << 8;
  }
  else {
    uVar1 = (param_4 + 1) * 0x100;
  }
  if (uVar3 < 2) {
    uVar3 = fpga_read_reg(0xe218c,iVar2);
    fpga_write_reg(0xe218c,param_4 + 1 | 0x90 | 1 << (param_1 + 0x10 & 0xff) | uVar3);
  }
  else {
    fpga_write_reg(0xe8139);
    fpga_write_reg(0xe813a,uVar1 | 0x80000040);
    fpga_write_reg(0xe813b,400);
  }
  return 0;
}

