// module: switch.ko
// function: sw_vlan_set_port_vlancfg @ 0x1a768
// size: 224 bytes
//

int sw_vlan_set_port_vlancfg(uint *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint unaff_r7;
  uint uVar5;
  uint uVar6;
  
  uVar5 = *param_1;
  uVar6 = param_1[2];
  uVar2 = uVar5 - 6;
  uVar4 = param_1[1];
  uVar3 = param_1[3];
  if (uVar2 < 2) {
    unaff_r7 = uVar5 & 0xff;
  }
  if (1 < uVar2) {
    param_2 = (int)&g_sw_cap + uVar5;
  }
  if (1 < uVar2) {
    unaff_r7 = (uint)*(byte *)(param_2 + 0xc);
  }
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n","sw_vlan_set_port_vlancfg",
           "VlanCfg.port",uVar5,"VlanCfg.minvlan",uVar6,"VlanCfg.maxvlan",uVar3,"VlanCfg.mode",uVar4
          );
  }
  iVar1 = zte_api_sw_vlan_set_port_vlancfg(unaff_r7,uVar6 & 0xffff,uVar3 & 0xffff,uVar4 & 0xff);
  if (iVar1 != 0) {
    printk("[%s] L%d tm sdk failed![zte_api_sw_vlan_set_port_vlancfg]\n","sw_vlan_set_port_vlancfg",
           199);
  }
  return iVar1;
}

