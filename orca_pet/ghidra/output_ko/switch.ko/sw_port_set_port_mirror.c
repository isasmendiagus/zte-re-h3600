// module: switch.ko
// function: sw_port_set_port_mirror @ 0x17e94
// size: 352 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sw_port_set_port_mirror(uint *param_1)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  uint unaff_r6;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  
  uVar7 = *param_1;
  uVar4 = uVar7 - 5;
  if (uVar4 < 3) {
    unaff_r6 = uVar7 & 0xff;
  }
  uVar5 = param_1[2];
  uVar1 = uVar4;
  if (2 < uVar4) {
    uVar1 = (int)&g_sw_cap + uVar7;
  }
  uVar6 = param_1[3];
  if (2 < uVar4) {
    unaff_r6 = (uint)*(byte *)(uVar1 + 0xc);
  }
  uVar4 = (uint)(byte)tm_set_p2pmode[param_1[1]];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n","sw_port_set_port_mirror",
           "Mirror.sport",uVar7,"Mirror.enable",uVar5,"Mirror.direct",uVar6,"Mirror.dport",
           param_1[1]);
  }
  if (((_eth_type_trans & 1 << (unaff_r6 & 0xff)) == 0) || ((_eth_type_trans & 1 << uVar4) == 0)) {
    if (g_switch_debug_level == 0) {
      uVar2 = 0xffffffff;
    }
    else {
      printk("[%s] input invalid port!\n","sw_port_set_port_mirror");
      uVar2 = 0xffffffff;
    }
  }
  else {
    uVar6 = uVar6 & 0xff;
    iVar3 = zte_api_sw_port_set_port_mirror(unaff_r6,0,uVar6,uVar4);
    if (iVar3 == 0) {
      iVar3 = zte_api_sw_port_set_port_mirror(unaff_r6,uVar5 & 0xff,uVar6,uVar4);
      uVar2 = 0;
      if (iVar3 != 0) {
        printk("[%s] L%d tm sdk failed!\n","sw_port_set_port_mirror",0x240);
        uVar2 = 0xffffffff;
      }
    }
    else {
      printk("[%s] L%d tm sdk disable mirror failed!\n","sw_port_set_port_mirror",0x23a);
      uVar2 = 0xffffffff;
    }
  }
  return uVar2;
}

