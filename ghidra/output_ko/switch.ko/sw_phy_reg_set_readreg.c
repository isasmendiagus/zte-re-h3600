// module: switch.ko
// function: sw_phy_reg_set_readreg @ 0x1a1dc
// size: 216 bytes
//

undefined4 sw_phy_reg_set_readreg(int *param_1)

{
  code cVar1;
  undefined4 uVar2;
  uint uVar3;
  ushort local_1a [3];
  
  uVar3 = param_1[2];
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  local_1a[0] = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = 0x%x\n","sw_phy_reg_set_readreg","PhyReg.port",cVar1,
           "PhyReg.addr",uVar3 & 0xffff);
  }
  if ((byte)cVar1 < 5) {
    uVar2 = zte_api_sw_phy_read(cVar1,uVar3 & 0xffff,local_1a);
    uVar3 = g_switch_debug_level;
    if (g_switch_debug_level < 3) {
      uVar2 = 0;
    }
    param_1[3] = (uint)local_1a[0];
    if (2 < uVar3) {
      printk("[%s] output:\nPhyReg.data = 0x%x\n","sw_phy_reg_set_readreg");
      uVar2 = 0;
    }
  }
  else {
    printk("sw_phy_reg_set_readreg port invalid!\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

