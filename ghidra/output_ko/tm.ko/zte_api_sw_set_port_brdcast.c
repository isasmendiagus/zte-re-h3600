// module: tm.ko
// function: zte_api_sw_set_port_brdcast @ 0x64104
// size: 104 bytes
//

undefined4
zte_api_sw_set_port_brdcast
          (undefined1 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = tm_port_brdcast_flood_ena_set(*param_1,param_1[4],param_3,param_4,param_4);
  iVar2 = tm_port_brdcast_fwd_ena_set(*param_1,param_1[5]);
  iVar3 = tm_port_pon_broadcast_floodport_set(*param_1,param_1[0xc]);
  iVar4 = tm_port_dft_broadcst_vltrans_set(*param_1,*(undefined4 *)(param_1 + 8));
  if (((iVar2 == 0 && iVar1 == 0) && iVar3 == 0) && iVar4 == 0) {
    return 0;
  }
  printk("[%s] L%d tm sdk failed!\n","zte_api_sw_set_port_brdcast",0x4c8);
  return 0xffffffff;
}

