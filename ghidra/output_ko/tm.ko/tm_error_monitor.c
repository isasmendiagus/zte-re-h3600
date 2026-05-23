// module: tm.ko
// function: tm_error_monitor @ 0x53628
// size: 1872 bytes
//

undefined4 tm_error_monitor(void)

{
  undefined1 uVar1;
  undefined2 uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  int iVar7;
  uint *puVar8;
  uint local_e0 [51];
  
  uVar3 = fpga_read_reg(0x74014);
  printk("In smct(0x%2x), sipc_err:0x%x, mult_err:0x%x, drop_err:0x%x \n",0x14,uVar3 & 1,
         (uVar3 << 0x1e) >> 0x1f,(uVar3 << 0x1d) >> 0x1f);
  iVar4 = fpga_read_reg(0x74022);
  printk("In smct(0x%2x), res_more:0x%x, dropfifo_wr_err:0x%x, res_wrong:0x%x \n",0x22,
         (uint)(iVar4 << 0x1c) >> 0x1f,(uint)(iVar4 << 0x18) >> 0x1f,(uint)(iVar4 << 0xc) >> 0x1c);
  uVar3 = fpga_read_reg(0x74035);
  local_e0[3] = (uVar3 << 0x1c) >> 0x1f;
  printk("In smct(0x%2x), link_uni_ept:0x%x, link_ful_bud:0x%x, link_ept_res:0x%x, link_ept_req:0x%x \n"
         ,0x35,uVar3 & 1,(uVar3 << 0x1e) >> 0x1f,(uVar3 << 0x1d) >> 0x1f,local_e0[3]);
  printk("In smct(0x%2x), des_err:0x%x, bud_wrong:0x%x, sipc_desc_empty_err:0x%x, sipc_desc_full_err:0x%x \n"
         ,0x35,(uVar3 << 0x1a) >> 0x1f,(uVar3 << 4) >> 0x14,(uVar3 << 3) >> 0x1f,
         (uVar3 << 2) >> 0x1f);
  uVar3 = fpga_read_reg(0x74036);
  printk("In smct(0x%2x), smct_left_pmau:0x%x\n",0x36,uVar3 & 0x3ff);
  uVar3 = fpga_read_reg(0x74040);
  local_e0[2] = (uVar3 << 0x1c) >> 0x1f;
  printk("In smct(0x%2x), dma_up_err:0x%x, uopc_err:0x%x, sopc_err:0x%x \n",0x40,uVar3 & 1,
         (uVar3 << 0x1d) >> 0x1f,local_e0[2]);
  uVar3 = fpga_read_reg(0x74054);
  local_e0[0] = uVar3 & 1;
  local_e0[1] = (uVar3 << 0x1e) >> 0x1f;
  printk("In smct(0x%2x), ppdatfifo2reg_empty_err:0x%x, ppdatfifo2reg_full_err:0x%x \n",0x54,
         local_e0[0],local_e0[1]);
  uVar1 = fpga_read_reg(0xd2030);
  printk("In bmu(0x%2x), sw_alcecnt:0x%x\n",0x30,uVar1);
  uVar1 = fpga_read_reg(0xd2031);
  printk("In bmu(0x%2x), uopc_erlscnt:0x%x \n",0x31,uVar1);
  uVar1 = fpga_read_reg(0xd2032);
  printk("In bmu(0x%2x), cpu_dn_erlscnt:0x%x \n",0x32,uVar1);
  uVar1 = fpga_read_reg(0xd2033);
  printk("In bmu(0x%2x), red_up_erlscnt:0x%x \n",0x33,uVar1);
  uVar1 = fpga_read_reg(0xd2034);
  printk("In bmu(0x%2x), opc_drop_erlscnt:0x%x \n",0x34,uVar1);
  uVar1 = fpga_read_reg(0xd2035);
  printk("In bmu(0x%2x), cpu_up_erlscnt:0x%x \n",0x35,uVar1);
  uVar1 = fpga_read_reg(0xd2036);
  printk("In bmu(0x%2x), sopc_erlscnt:0x%x \n",0x36,uVar1);
  uVar2 = fpga_read_reg(0xd2038);
  printk("In bmu(0x%2x), bmu_normal_bperr:0x%x \n",0x38,uVar2);
  uVar2 = fpga_read_reg(0xd2039);
  printk("In bmu(0x%2x), bmu_jumbo_bperr:0x%x \n",0x39,uVar2);
  uVar3 = fpga_read_reg(0xd300c);
  printk("In qmg(0x%2x), qmg_fifo_err:0x%x \n",0xc,uVar3 & 0xfff);
  iVar4 = 0;
  puVar8 = local_e0;
  do {
    uVar5 = fpga_read_reg(iVar4 + 0xd3037);
    iVar7 = iVar4 + 1;
    *puVar8 = uVar5;
    printk("In qmg(0x%2x), cache_active_%d:0x%x \n",iVar4 + 0x37,iVar4,uVar3);
    iVar4 = iVar7;
    puVar8 = puVar8 + 1;
  } while (iVar7 != 0xc);
  uVar3 = fpga_read_reg(0xd102b);
  printk("In red(0x%2x), reg_up_dbg:0x%x \n",0x2b,uVar3 & 0x7fff);
  uVar1 = fpga_read_reg(0xe0025);
  printk("In pp_ctrl(0x%2x), ram_left_cnt:0x%x \n ",0x25,uVar1);
  uVar6 = fpga_read_reg(0x760a2);
  printk("In uopc(0x%2x), uopc2smct_no_sop_err:0x%x\n",0xa2,uVar6);
  uVar6 = fpga_read_reg(0x760a3);
  printk("In uopc(0x%2x), uopc2smct_no_eop_err:0x%x\n",0xa3,uVar6);
  uVar6 = fpga_read_reg(0x760a4);
  printk("In uopc(0x%2x), uopc2dma_no_sop_err:0x%x\n",0xa4,uVar6);
  uVar6 = fpga_read_reg(0x760a5);
  printk("In uopc(0x%2x), uopc2dma_no_eop_err:0x%x\n",0xa5,uVar6);
  uVar3 = fpga_read_reg(0x760b1);
  uVar5 = 0;
  do {
    local_e0[uVar5] = uVar3 >> ((uVar5 & 0x1f) << 3) & 0xff;
    uVar5 = uVar5 + 1;
  } while (uVar5 != 4);
  printk("In uopc(0x%2x), uopc2dma_wr_no_eop_err_high:0x%x \n",0xb1,local_e0[0]);
  iVar7 = 0x76473;
  printk("In uopc(0x%2x), uopc2dma_wr_no_sop_err_high:0x%x \n",0xb1,local_e0[1]);
  printk("In uopc(0x%2x), uopc2smct_wr_no_eop_err_high:0x%x \n",0xb1,local_e0[2]);
  uVar3 = local_e0[3];
  printk("In uopc(0x%2x), uopc2smct_wr_no_sop_err_high:0x%x \n",0xb1,local_e0[3]);
  uVar5 = fpga_read_reg(0x760b2);
  printk("In uopc(0x%2x), des_fifo_wr_no_eop_err_high:0x%x \n",0xb2,uVar5 & 0xff);
  printk("In uopc(0x%2x), des_fifo_wr_no_sop_err_high:0x%x \n",0xb2,(uVar5 << 0x10) >> 0x18);
  printk("In uopc(0x%2x), fcs_no_eop_err_high:0x%x \n",0xb2,(uVar5 << 8) >> 0x18);
  printk("In uopc(0x%2x), fcs_no_sop_err_high:0x%x \n",0xb2,uVar3);
  uVar5 = fpga_read_reg(0x760b3);
  printk("In uopc(0x%2x), mac_rd_err_sync_high:0x%x \n",0xb3,uVar5 & 0xff);
  printk("In uopc(0x%2x), uopc2mac_vld_cnt_err_sync_high:0x%x \n",0xb3,(uVar5 << 0x10) >> 0x18);
  printk("In uopc(0x%2x), ides_fifo_rd_ept_high:0x%x \n",0xb3,(uVar5 << 8) >> 0x18);
  printk("In uopc(0x%2x), ides_fifo_wr_ful_high:0x%x \n",0xb3,uVar3);
  uVar6 = fpga_read_reg(0x760b4);
  printk("In uopc(0x%2x), uopc2mac_vld_cnt_err:0x%x \n",0xb4,uVar6);
  uVar6 = fpga_read_reg(0x760b6);
  printk("In uopc(0x%2x), txd_wr_ful_pre:0x%x \n",0xb6,uVar6);
  uVar3 = fpga_read_reg(0x760b7);
  printk("In uopc(0x%2x), txd_wr_ful_pre(tcont32-39):0x%x,fcs_vld_cnt_err(tcont32-39):0x%x \n",0xb7,
         uVar3 != 0,uVar3 >> 8 != 0);
  uVar6 = fpga_read_reg(0x760b8);
  printk("In uopc(0x%2x), fcs_vld_cnt_err(tcont0-31):0x%x \n",0xb8,uVar6);
  iVar4 = fpga_read_reg(0x76471);
  printk("In sopc(0x%2x), st_cur:0x%x \n",0x71,(uint)(iVar4 << 0x1b) >> 0x1d);
  do {
    uVar3 = fpga_read_reg(iVar7);
    iVar4 = iVar7 + -0x76400;
    iVar7 = iVar7 + 1;
    printk("In sopc(0x%2x), st_cur:0x%x \n",iVar4,uVar3 & 0xf);
    printk("In sopc(0x%2x), fifo_rdcnt:0x%x \n",iVar4,(uVar3 << 0x10) >> 0x17);
    printk("In sopc(0x%2x), dcfifo_rdcnt:0x%x \n",iVar4,(uVar3 << 10) >> 0x1a);
  } while (iVar7 != 0x76478);
  iVar4 = fpga_read_reg(0x76478);
  iVar7 = 0x76482;
  printk("In sopc(0x%2x), fifo_rd_ept:0x%x \n",0x78,(uint)(iVar4 << 0x1b) >> 0x1f);
  printk("In sopc(0x%2x), fifo_wr_ful:0x%x \n",0x78,(uint)(iVar4 << 0x1a) >> 0x1f);
  iVar4 = fpga_read_reg(0x76479);
  printk("In sopc(0x%2x), fifo_rd_ept:0x%x \n",0x79,(uint)(iVar4 << 0x1b) >> 0x1f);
  printk("In sopc(0x%2x), fifo_wr_ful:0x%x \n",0x79,(uint)(iVar4 << 0x1a) >> 0x1f);
  iVar4 = fpga_read_reg(0x76480);
  printk("In sopc(0x%x), cmd_fifo_ept_err:0x%x \n",0x80,(uint)(iVar4 << 0xf) >> 0x1f);
  printk("In sopc(0x%x), cmd_fifo_wr_full_err:0x%x \n",0x80,(uint)(iVar4 << 0xe) >> 0x1f);
  uVar3 = fpga_read_reg(0x76481);
  printk("In sopc(0x%2x), req_dat_dbg1:0x%x \n",0x81,uVar3 & 0xfff);
  do {
    uVar3 = fpga_read_reg(iVar7);
    iVar4 = iVar7 + -0x76400;
    iVar7 = iVar7 + 1;
    printk("In sopc(0x%2x), bit0-3:0x%x \n",iVar4,uVar3 & 0xf);
    printk("In sopc(0x%2x), bit4-7:0x%x \n",iVar4,(uVar3 << 0x18) >> 0x1c);
    printk("In sopc(0x%2x), bit8:0x%x \n",iVar4,(uVar3 << 0x17) >> 0x1f);
  } while (iVar7 != 0x76487);
  uVar1 = fpga_read_reg(0xe7027);
  printk("In pp pm(0x%2x),pm_overrun_cnt:0x%x \n",0x27,uVar1);
  return 0;
}

