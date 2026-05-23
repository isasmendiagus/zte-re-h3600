// module: switch.ko
// function: sw_other_set_wan_lan_switch @ 0x16568
// size: 656 bytes
//

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sw_other_set_wan_lan_switch(uint *param_1)

{
  code cVar1;
  byte bVar2;
  uint uVar3;
  byte bVar4;
  uint uVar5;
  byte *pbVar6;
  byte local_23;
  byte local_22;
  byte local_21;
  
  bVar4 = 0;
  local_23 = 0;
  local_22 = 0;
  local_21 = 0;
  if (param_1 == (uint *)0x0) {
    if (g_switch_debug_level != 0) {
      printk("[SW][sw_other_set_wan_lan_switch] input ERROR: ioctl_data_sweth=null\n");
      return 0xffffffff;
    }
    return 0xffffffff;
  }
  sweth_flag = 1;
  uVar5 = *param_1;
  printk("set wan lan switch mode=%d\n",uVar5);
  if (uVar5 < 2) {
    if (wanLogicPort == 0xff) {
      return 0;
    }
    bVar4 = 0;
    cVar1 = tm_set_p2pmode[wanLogicPort];
    _zte_api_sw_mac_set_port_learnlimit = (uint)(byte)cVar1;
    uVar5 = fpga_read_reg(0xe8007);
    fpga_write_reg(0xe8007,uVar5 & 0xc1ffffff);
    tm_set_p2pmode((uint)(byte)cVar1);
    wan_to_lan = 0;
    _tm_tcont_que_sch_weight_get = _tm_tcont_que_sch_weight_get | 0xf;
    printk("set wan lan switch WAN or AUTO\n");
    uVar5 = 0;
    while( true ) {
      uVar3 = uVar5 + 1;
      if (_tm_port_unknwn_multicast_floodport_set <= uVar5) break;
      cVar1 = tm_set_p2pmode[uVar5];
      zte_api_sw_port_get_port_linkstate((uint)(byte)cVar1,&local_23,&local_22,&local_21);
      uVar5 = uVar3;
      if (_zte_api_sw_mac_set_port_learnlimit != (byte)cVar1) {
        bVar4 = bVar4 | local_23;
      }
    }
  }
  else {
    if (uVar5 == 6) {
      _zte_api_sw_mac_set_port_learnlimit = 0xff;
      uVar5 = fpga_read_reg(0xe8007);
      fpga_write_reg(0xe8007,uVar5 & 0xc1ffffff);
      wan_to_lan = 1;
      _tm_tcont_que_sch_weight_get = _tm_tcont_que_sch_weight_get | 0x1f;
      printk("All port change lan\n");
      return 0;
    }
    uVar5 = uVar5 - 1 & 0xff;
    if (_tm_port_unknwn_multicast_floodport_set < uVar5) {
      printk("[%s]%d input error!\n","sw_other_set_wan_lan_switch",0xa9);
      return 0xffffffff;
    }
    cVar1 = tm_set_p2pmode[uVar5];
    _zte_api_sw_mac_set_port_learnlimit = (uint)(byte)cVar1;
    uVar3 = fpga_read_reg(0xe8007);
    fpga_write_reg(0xe8007,uVar3 & 0xc1ffffff);
    tm_set_p2pmode((uint)(byte)cVar1);
    _tm_tcont_que_sch_weight_get = _tm_tcont_que_sch_weight_get | 0x1f;
    wan_to_lan = 1;
    printk("set wan lan switch ,eth%d to WAN\n",uVar5);
    if (_tm_port_unknwn_multicast_floodport_set == 0) goto LAB_000166c0;
    pbVar6 = (byte *)((int)&proc_create_data + 3);
    uVar5 = 0;
    do {
      pbVar6 = pbVar6 + 1;
      bVar2 = *pbVar6;
      uVar5 = uVar5 + 1;
      zte_api_sw_port_get_port_linkstate((uint)bVar2,&local_23,&local_22,&local_21);
      if (_zte_api_sw_mac_set_port_learnlimit != bVar2) {
        bVar4 = bVar4 | local_23;
      }
    } while (uVar5 < _tm_port_unknwn_multicast_floodport_set);
  }
  if (bVar4 != 0) {
    return 0;
  }
LAB_000166c0:
  LedActionSet(0xb200,1);
  g_LAN_ON_Flag = 0;
  return 0;
}

