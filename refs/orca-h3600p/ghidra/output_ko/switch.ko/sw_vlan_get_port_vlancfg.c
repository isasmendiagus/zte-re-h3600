// module: switch.ko
// function: sw_vlan_get_port_vlancfg @ 0x1a8dc
// size: 196 bytes
//

int sw_vlan_get_port_vlancfg(undefined4 *param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 local_18;
  undefined4 local_14;
  
  local_18 = 0;
  local_14 = 0;
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n","sw_vlan_get_port_vlancfg","Vlan.vlan",*param_1);
  }
  iVar2 = zte_api_sw_vlan_get_port_vlancfg(*(undefined2 *)param_1,&local_18,&local_14);
  uVar1 = g_switch_debug_level;
  if (iVar2 == 0) {
    param_1[1] = local_18;
    param_1[2] = local_14;
    if (2 < uVar1) {
      printk("%s = 0x%x\n%s = 0x%x\n","Vlan.mbmask",local_18,"Vlan.untagmask",local_14);
    }
  }
  else {
    printk("[%s] L%d tm sdk failed![zte_api_sw_vlan_get_port_vlancfg]\n","sw_vlan_get_port_vlancfg",
           0xda);
  }
  return iVar2;
}

