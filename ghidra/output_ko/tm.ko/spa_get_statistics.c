// module: tm.ko
// function: spa_get_statistics @ 0x3b574
// size: 980 bytes
//

undefined4 spa_get_statistics(undefined4 *param_1)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  uint uVar12;
  
  uVar1 = fpga_read_reg(0x75178);
  uVar2 = fpga_read_reg(0x75173);
  uVar3 = fpga_read_reg(0x75174);
  uVar4 = fpga_read_reg(0x75175);
  uVar5 = fpga_read_reg(0x75176);
  uVar6 = fpga_read_reg(0x75177);
  uVar7 = fpga_read_reg(0x75171);
  uVar8 = fpga_read_reg(0x75172);
  uVar9 = fpga_read_reg(0x7514a);
  uVar10 = fpga_read_reg(0x7514b);
  uVar11 = fpga_read_reg(0x7514c);
  uVar12 = fpga_read_reg(0x75145);
  param_1[0x1b] = uVar9;
  *param_1 = uVar1;
  param_1[0x1c] = uVar10;
  param_1[0x1d] = uVar11;
  param_1[1] = (uVar2 << 0x10) >> 0x18;
  param_1[4] = (uVar3 << 8) >> 0x18;
  param_1[3] = uVar3 >> 0x18;
  param_1[8] = (uVar4 << 8) >> 0x18;
  param_1[5] = (uVar3 << 0x10) >> 0x18;
  param_1[0xc] = (uVar5 << 8) >> 0x18;
  param_1[7] = uVar4 >> 0x18;
  param_1[0x10] = (uVar6 << 8) >> 0x18;
  param_1[9] = (uVar4 << 0x10) >> 0x18;
  param_1[0x14] = (uVar7 << 8) >> 0x18;
  param_1[0xb] = uVar5 >> 0x18;
  param_1[0x18] = (uVar8 << 8) >> 0x18;
  param_1[0xd] = (uVar5 << 0x10) >> 0x18;
  param_1[2] = uVar2 & 0xff;
  param_1[0xf] = uVar6 >> 0x18;
  param_1[6] = uVar3 & 0xff;
  param_1[0x11] = (uVar6 << 0x10) >> 0x18;
  param_1[10] = uVar4 & 0xff;
  param_1[0x13] = uVar7 >> 0x18;
  param_1[0xe] = uVar5 & 0xff;
  param_1[0x15] = (uVar7 << 0x10) >> 0x18;
  param_1[0x12] = uVar6 & 0xff;
  param_1[0x17] = uVar8 >> 0x18;
  param_1[0x16] = uVar7 & 0xff;
  param_1[0x19] = (uVar8 << 0x10) >> 0x18;
  param_1[0x1a] = uVar8 & 0xff;
  param_1[0x1e] = uVar12 & 0xffff;
  param_1[0x1f] = uVar12 >> 0x10;
  printk("spa:rcv_omci = %u\n");
  printk("spa:rcv_pon_sop = %u\n",param_1[1]);
  printk("spa:rcv_pon_eop = %u\n",param_1[2]);
  printk("spa:rcv_uni0_sop = %u\n",param_1[3]);
  printk("spa:rcv_uni0_eop = %u\n",param_1[4]);
  printk("spa:rcv_uni1_sop = %u\n",param_1[5]);
  printk("spa:rcv_uni1_eop = %u\n",param_1[6]);
  printk("spa:rcv_uni2_sop = %u\n",param_1[7]);
  printk("spa:rcv_uni2_eop = %u\n",param_1[8]);
  printk("spa:rcv_uni3_sop = %u\n",param_1[9]);
  printk("spa:rcv_uni3_eop = %u\n",param_1[10]);
  printk("spa:rcv_uni4_sop = %u\n",param_1[0xb]);
  printk("spa:rcv_uni4_eop = %u\n",param_1[0xc]);
  printk("spa:rcv_wifi0_sop = %u\n",param_1[0xd]);
  printk("spa:rcv_wifi0_eop = %u\n",param_1[0xe]);
  printk("spa:rcv_wifi1_sop = %u\n",param_1[0xf]);
  printk("spa:rcv_wifi1_eop = %u\n",param_1[0x10]);
  printk("spa:rcv_cpu_sop = %u\n",param_1[0x11]);
  printk("spa:rcv_cpu_eop = %u\n",param_1[0x12]);
  printk("spa:before_tagflt_fwd = %u\n",param_1[0x13]);
  printk("spa:before_tagflt_drp = %u\n",param_1[0x14]);
  printk("spa:before_tagflt_cpy = %u\n",param_1[0x15]);
  printk("spa:before_tagflt_trp = %u\n",param_1[0x16]);
  printk("spa:after_tagflt_fwd = %u\n",param_1[0x17]);
  printk("spa:after_tagflt_drp = %u\n",param_1[0x18]);
  printk("spa:after_tagflt_cpy = %u\n",param_1[0x19]);
  printk("spa:after_tagflt_trp = %u\n",param_1[0x1a]);
  printk("spa:dn_mulit_cnt     = %u\n",param_1[0x1b]);
  printk("spa:dn_uncast_cnt    = %u\n",param_1[0x1c]);
  printk("spa:dn_board_cnt     = %u\n",param_1[0x1d]);
  printk("spa:smac_illegal_up  = %u\n",param_1[0x1e]);
  printk("spa:smac_illegal_dn  = %u\n",param_1[0x1f]);
  return 0;
}

