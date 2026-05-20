// module: switch.ko
// function: sw_vlan_get_port_inframemode @ 0x1a414
// size: 404 bytes
//

int sw_vlan_get_port_inframemode(int *param_1)

{
  code cVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  byte local_19 [5];
  
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  local_19[0] = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n","sw_vlan_get_port_inframemode","InframeMode.port");
  }
  iVar3 = zte_api_sw_vlan_get_port_inframemode(cVar1,local_19);
  uVar2 = g_switch_debug_level;
  if (iVar3 == 0) {
    uVar4 = (uint)local_19[0];
    param_1[1] = uVar4;
    if (uVar4 == 0) {
      iVar3 = 0;
      if (2 < uVar2) {
        printk("[%s] output:\n%s = discard none\n","sw_vlan_get_port_inframemode","InframeMode.mode"
              );
      }
    }
    else if (uVar4 == 0x3f) {
      if (uVar2 < 3) {
        return 0;
      }
      printk("[%s] output:\n%s = discard all\n","sw_vlan_get_port_inframemode","InframeMode.mode");
    }
    else if (uVar4 == 1) {
      if (uVar2 < 3) {
        return 0;
      }
      printk("[%s] output:\n%s = discard untag\n","sw_vlan_get_port_inframemode","InframeMode.mode")
      ;
    }
    else if (uVar4 == 0x3e) {
      if (uVar2 < 3) {
        return 0;
      }
      printk("[%s] output:\n%s = discard tagged\n","sw_vlan_get_port_inframemode","InframeMode.mode"
            );
    }
    else {
      if (uVar2 < 3) {
        return 0;
      }
      printk("[%s] output:\n%s = discard hybrid\n","sw_vlan_get_port_inframemode","InframeMode.mode"
            );
    }
  }
  else {
    printk("[%s] L%d tm sdk failed!\n","sw_vlan_get_port_inframemode",0x43);
  }
  return iVar3;
}

