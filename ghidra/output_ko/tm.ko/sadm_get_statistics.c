// module: tm.ko
// function: sadm_get_statistics @ 0x25578
// size: 1064 bytes
//

undefined4 sadm_get_statistics(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  
  uVar1 = fpga_read_reg(0xe1080);
  uVar2 = fpga_read_reg(0xe1081);
  uVar3 = fpga_read_reg(0xe1082);
  uVar4 = fpga_read_reg(0xe1083);
  uVar5 = fpga_read_reg(0xe1084);
  uVar6 = fpga_read_reg(0xe1085);
  uVar7 = fpga_read_reg(0xe1086);
  uVar8 = fpga_read_reg(0xe1087);
  printk("pon      pass: %d\n",uVar1);
  printk("uni0      pass: %d\n",uVar2);
  printk("uni1      pass: %d\n",uVar3);
  printk("uni2      pass: %d\n",uVar4);
  printk("uni3      pass: %d\n",uVar5);
  printk("uni4      pass: %d\n",uVar6);
  printk("wifi0      pass: %d\n",uVar7);
  printk("wifi1      pass: %d\n",uVar8);
  uVar1 = fpga_read_reg(0xe108a);
  uVar2 = fpga_read_reg(0xe108b);
  uVar3 = fpga_read_reg(0xe108c);
  uVar4 = fpga_read_reg(0xe108d);
  uVar5 = fpga_read_reg(0xe108e);
  uVar6 = fpga_read_reg(0xe108f);
  uVar7 = fpga_read_reg(0xe1090);
  uVar8 = fpga_read_reg(0xe1091);
  printk("pon      drop: %d\n",uVar1);
  printk("uni0      drop: %d\n",uVar2);
  printk("uni1      drop: %d\n",uVar3);
  printk("uni2      drop: %d\n",uVar4);
  printk("uni3      drop: %d\n",uVar5);
  printk("uni4      drop: %d\n",uVar6);
  printk("wifi0      drop: %d\n",uVar7);
  printk("wifi1      drop: %d\n",uVar8);
  uVar9 = fpga_read_reg(0xe1094);
  uVar10 = fpga_read_reg(0xe1095);
  uVar11 = fpga_read_reg(0xe1096);
  printk("pon unsa pass: %d\n",uVar9 & 0xff);
  printk("uni0 unsa pass: %d\n",(uVar9 << 0x10) >> 0x18);
  printk("uni1 unsa pass: %d\n",(uVar9 << 8) >> 0x18);
  printk("uni2 unsa pass: %d\n",uVar9 >> 0x18);
  printk("uni3 unsa pass: %d\n",uVar10 & 0xff);
  printk("uni4 unsa pass: %d\n",uVar10 >> 0x18);
  printk("wifi0 unsa pass: %d\n",uVar11 & 0xff);
  printk("wifi1 unsa pass: %d\n",(uVar11 << 0x10) >> 0x18);
  uVar9 = fpga_read_reg(0xe1097);
  uVar10 = fpga_read_reg(0xe1098);
  uVar11 = fpga_read_reg(0xe1099);
  printk("pon unda pass: %d\n",uVar9 & 0xff);
  printk("uni0 unda pass: %d\n",(uVar9 << 0x10) >> 0x18);
  printk("uni1 unda pass: %d\n",(uVar9 << 8) >> 0x18);
  printk("uni2 unda pass: %d\n",uVar9 >> 0x18);
  printk("uni3 unda pass: %d\n",uVar10 & 0xff);
  printk("uni4 unda pass: %d\n",uVar10 >> 0x18);
  printk("wifi0 unsa pass: %d\n",uVar11 & 0xff);
  printk("wifi1 unsa pass: %d\n",(uVar11 << 0x10) >> 0x18);
  uVar9 = fpga_read_reg(0xe109c);
  uVar10 = fpga_read_reg(0xe109d);
  uVar11 = fpga_read_reg(0xe109e);
  printk("pon unmultida pass: %d\n",uVar9 & 0xff);
  printk("uni0 unmultida pass: %d\n",(uVar9 << 0x10) >> 0x18);
  printk("uni1 unmultida pass: %d\n",(uVar9 << 8) >> 0x18);
  printk("uni2 unmultida pass: %d\n",uVar9 >> 0x18);
  printk("uni3 unmultida pass: %d\n",uVar10 & 0xff);
  printk("uni4 unmultida pass: %d\n",uVar10 >> 0x18);
  printk("wifi0 unmultida pass: %d\n",uVar11 & 0xff);
  printk("wifi1 unmultida pass: %d\n",(uVar11 << 0x10) >> 0x18);
  return 0;
}

