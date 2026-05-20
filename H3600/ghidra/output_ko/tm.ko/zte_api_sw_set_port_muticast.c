// module: tm.ko
// function: zte_api_sw_set_port_muticast @ 0x61c5c
// size: 136 bytes
//

undefined4 zte_api_sw_set_port_muticast(undefined1 *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = *(int *)(param_1 + 8);
  iVar1 = tm_port_multicast_act_set(*param_1,param_1[4]);
  iVar2 = tm_port_unknwn_multicast_flood_set(*param_1,param_1[5]);
  iVar3 = tm_port_unknwn_multicast_fwd_set(*param_1,param_1[6]);
  iVar5 = tm_port_dft_multicst_vltrans_set(*param_1,iVar5 != 0);
  iVar4 = tm_port_unknwn_multicast_floodport_set(*param_1,param_1[0xc],5);
  if ((((iVar2 == 0 && iVar1 == 0) && iVar3 == 0) && iVar5 == 0) && iVar4 == 0) {
    return 0;
  }
  printk("[%s] L%d tm sdk failed!\n","zte_api_sw_set_port_muticast",0x4b5);
  return 0xffffffff;
}

