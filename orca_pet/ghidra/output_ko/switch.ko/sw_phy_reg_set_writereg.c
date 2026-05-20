// module: switch.ko
// function: sw_phy_reg_set_writereg @ 0x1a348
// size: 184 bytes
//

undefined4 sw_phy_reg_set_writereg(int *param_1)

{
  code cVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar4 = param_1[2];
  uVar3 = param_1[3];
  cVar1 = tm_set_p2pmode[*param_1];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = 0x%x\n%s = 0x%x\n","sw_phy_reg_set_writereg","PhyReg.port",
           cVar1,"PhyReg.addr",uVar4 & 0xffff,"PhyReg.data",uVar3 & 0xffff);
  }
  if ((byte)cVar1 < 5) {
    zte_api_sw_phy_write(cVar1,uVar4 & 0xffff,uVar3 & 0xffff);
    uVar2 = 0;
  }
  else {
    printk("sw_phy_reg_set_readreg port invalid!\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

