// module: switch.ko
// function: sw_port_get_port_mirror @ 0x17ff8
// size: 284 bytes
//

int sw_port_get_port_mirror(uint *param_1)

{
  code cVar1;
  int iVar2;
  uint uVar3;
  byte local_13;
  byte local_12;
  byte local_11;
  
  local_13 = 0;
  local_12 = 0;
  local_11 = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s], the parameters coming in as follows:\n%s = %d\n","sw_port_get_port_mirror",
           "ioctl_data_sweth->m_CommonArgs.Mirror.sport",*param_1);
  }
  uVar3 = *param_1;
  if (uVar3 - 6 < 2) {
    uVar3 = uVar3 & 0xff;
  }
  else {
    uVar3 = (uint)(byte)tm_set_p2pmode[uVar3];
  }
  iVar2 = zte_api_sw_port_get_port_mirror(uVar3,&local_13,&local_12,&local_11);
  uVar3 = g_switch_debug_level;
  if (iVar2 == 0) {
    param_1[2] = (uint)local_13;
    param_1[3] = (uint)local_12;
    cVar1 = zte_api_sw_vlan_get_port_inframemode[local_11];
    param_1[1] = (uint)(byte)cVar1;
    if (2 < uVar3) {
      printk("[%s], the result as follows:\n%s = %d\n%s = %d\n%s = %d\n","sw_port_get_port_mirror",
             "Mirror.enable",(uint)local_13,"Mirror.direct",(uint)local_12,"Mirror.dport",
             (uint)(byte)cVar1);
    }
  }
  else {
    printk("[%s] L%d tm sdk failed!\n","sw_port_get_port_mirror",0x260);
  }
  return iVar2;
}

