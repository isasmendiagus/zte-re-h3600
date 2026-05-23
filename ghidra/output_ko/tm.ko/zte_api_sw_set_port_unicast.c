// module: tm.ko
// function: zte_api_sw_set_port_unicast @ 0x64170
// size: 120 bytes
//

undefined4
zte_api_sw_set_port_unicast
          (undefined1 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar1 = tm_port_unicast_act_set(*param_1,param_1[4],param_3,param_4,param_4);
  iVar2 = tm_port_unknwn_unicast_flood_set(*param_1,*(undefined4 *)(param_1 + 8));
  iVar3 = tm_port_unknwn_unicast_fwd_set(*param_1,param_1[0xc]);
  iVar4 = tm_port_pon_unicast_floodport_set(*param_1,param_1[0x14]);
  iVar5 = tm_port_dft_unkunicst_vltrans_set(*param_1,*(undefined4 *)(param_1 + 0x10));
  if ((((iVar2 == 0 && iVar1 == 0) && iVar3 == 0) && iVar4 == 0) && iVar5 == 0) {
    return 0;
  }
  printk("[%s] L%d tm sdk failed!\n","zte_api_sw_set_port_unicast",0x504);
  return 0xffffffff;
}

