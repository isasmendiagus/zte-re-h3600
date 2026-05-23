// module: tm.ko
// function: zte_api_sw_set_mac_ratelimit @ 0x635d0
// size: 480 bytes
//

undefined4 zte_api_sw_set_mac_ratelimit(byte *param_1,int param_2)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  undefined1 *__s1;
  int iVar6;
  uint uVar7;
  uint uVar8;
  
  if (param_1 == (byte *)0x0) {
    return 0xffffffff;
  }
  uVar5 = 0;
  __s1 = t_dmac_lmt + 1;
  do {
    iVar2 = memcmp(__s1,param_1,6);
    if (iVar2 == 0) goto LAB_00063614;
    uVar5 = uVar5 + 1;
    __s1 = __s1 + 0xc;
  } while (uVar5 != 0x20);
  uVar5 = 0;
  iVar2 = 0;
  do {
    pcVar1 = t_dmac_lmt + iVar2;
    iVar2 = iVar2 + 0xc;
    if (*pcVar1 == '\0') goto LAB_00063614;
    uVar5 = uVar5 + 1;
  } while (uVar5 != 0x20);
  uVar5 = 0;
  iVar6 = 0xe10f1;
  iVar2 = 0xe10f0;
  uVar8 = 0;
  uVar7 = 0x400000;
LAB_00063630:
  iVar3 = (uint)param_1[3] * 0x10000 + (uint)param_1[2] * 0x1000000 + (uint)param_1[4] * 0x100 +
          (uint)param_1[5];
  uVar4 = (uint)param_1[1] + (uint)*param_1 * 0x100;
  if (param_2 == 0) {
    fpga_write_reg(iVar2,iVar3);
    fpga_write_reg(iVar6,uVar8 | uVar4);
    fpga_write_reg(0xe1005,uVar7);
    fpga_write_reg(0xe1008,0x3e80000);
    fpga_write_reg(0xe1007,0);
    iVar2 = uVar5 * 0xc;
    t_dmac_lmt[iVar2] = 0;
    *(undefined4 *)(t_dmac_lmt + iVar2 + 8) = 0;
    __memzero(iVar2 + 0xdc379,6);
    return 0;
  }
  fpga_write_reg(iVar2,iVar3);
  fpga_write_reg(iVar6,uVar4 | 0x30000 | uVar8);
  fpga_write_reg(0xe1005,uVar7);
  fpga_write_reg(0xe1008,0x3e80000);
  fpga_write_reg(0xe1007,param_2 << 2 | 1);
  iVar2 = uVar5 * 0xc;
  *(int *)(t_dmac_lmt + iVar2 + 8) = param_2;
  t_dmac_lmt[iVar2] = 1;
  *(undefined4 *)(t_dmac_lmt + iVar2 + 1) = *(undefined4 *)param_1;
  *(undefined2 *)(t_dmac_lmt + iVar2 + 5) = *(undefined2 *)(param_1 + 4);
  return 0;
LAB_00063614:
  uVar8 = uVar5 << 0x12;
  uVar7 = uVar5 | 0x400000;
  iVar2 = (uVar5 + 0x70878) * 2;
  iVar6 = iVar2 + 1;
  goto LAB_00063630;
}

