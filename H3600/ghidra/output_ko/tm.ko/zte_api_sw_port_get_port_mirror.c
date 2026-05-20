// module: tm.ko
// function: zte_api_sw_port_get_port_mirror @ 0x608bc
// size: 676 bytes
//

undefined4
zte_api_sw_port_get_port_mirror(int param_1,undefined1 *param_2,undefined1 *param_3,char *param_4)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  char cVar7;
  int iVar8;
  
  *param_2 = 0;
  *param_3 = 2;
  *param_4 = '\0';
  if (param_1 == 5) {
    iVar3 = fpga_read_reg(0xe8131);
    uVar2 = fpga_read_reg(0xe8132);
    iVar5 = fpga_read_reg(0xe8134);
    uVar4 = fpga_read_reg(0xe8135);
    if ((uVar2 & 0x180) != 0) {
      if ((uVar4 & 0x180) == 0) {
        *param_2 = 1;
        *param_3 = 0;
        *param_4 = (byte)((uint)(iVar3 << 0x14) >> 0x1c) - 1;
        return 0;
      }
      *param_2 = 1;
      *param_3 = 2;
      *param_4 = (byte)((uint)(iVar5 << 0x14) >> 0x1c) - 1;
      return 0;
    }
    if ((uVar4 & 0x180) != 0) {
      *param_2 = 1;
      *param_3 = 1;
      *param_4 = (byte)((uint)(iVar5 << 0x14) >> 0x1c) - 1;
      return 0;
    }
  }
  else {
    uVar2 = fpga_read_reg(0xe8136);
    iVar3 = fpga_read_reg(0xe8137);
    fpga_read_reg(0xe8138);
    uVar4 = fpga_read_reg(0xe8139);
    iVar5 = fpga_read_reg(0xe813a);
    fpga_read_reg(0xe813b);
    if (param_1 - 6U < 2) {
      uVar6 = fpga_read_reg(0xe218c);
      bVar1 = (byte)uVar6;
      if (((uVar6 & 0x808000) == 0x808000) || ((uVar6 & 0x404000) == 0x404000)) {
        *param_2 = 1;
        *param_3 = 2;
        *param_4 = (bVar1 & 7) - 1;
      }
      else if ((uVar6 & 0xc00000) == 0) {
        if ((uVar6 & 0xc000) == 0) {
          *param_2 = 0;
          cVar7 = '\0';
          *param_3 = 2;
        }
        else {
          cVar7 = (bVar1 & 7) - 1;
          *param_2 = 1;
          *param_3 = 0;
        }
        *param_4 = cVar7;
      }
      else {
        *param_2 = 1;
        *param_3 = 1;
        *param_4 = (bVar1 & 7) - 1;
      }
    }
    iVar8 = (uVar4 >> 0xc) - 1;
    if ((uVar2 >> 0x10) - 1 == param_1) {
      if (param_1 == iVar8) {
        *param_2 = 1;
        *param_3 = 2;
        *param_4 = (byte)((uint)(iVar5 << 0x14) >> 0x1c) - 1;
        return 0;
      }
      *param_2 = 1;
      *param_3 = 0;
      *param_4 = (byte)((uint)(iVar3 << 0x14) >> 0x1c) - 1;
      return 0;
    }
    if (param_1 == iVar8) {
      *param_2 = 1;
      *param_3 = 1;
      *param_4 = (byte)((uint)(iVar5 << 0x14) >> 0x1c) - 1;
      return 0;
    }
  }
  *param_2 = 0;
  *param_3 = 2;
  *param_4 = '\0';
  return 0;
}

