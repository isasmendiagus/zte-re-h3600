// module: tm.ko
// function: zte_api_sw_port_init @ 0x61ce8
// size: 288 bytes
//

undefined4
zte_api_sw_port_init(undefined1 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined1 *puVar5;
  
  iVar1 = tm_vlan_check_ena_set(*param_1,0,param_1[1],param_4,param_4);
  iVar2 = tm_vlan_check_ena_set(*param_1,1,param_1[2]);
  iVar3 = tm_mac_da_look_ena_set(*param_1,param_1[8]);
  iVar4 = tm_mac_learn_mode_set(*param_1,*(undefined4 *)(param_1 + 4));
  __memzero(port_stat1_last,0x380);
  __memzero(port_stat1_total,0x380);
  __memzero(port_stat2_last,0x2c0);
  __memzero(port_stat2_total,0x2c0);
  __memzero(port_stat3_last,0x300);
  __memzero(port_stat3_total,0x300);
  __memzero(port_stat4_last,0x280);
  __memzero(port_stat4_total,0x280);
  __memzero(port_g988stat_last,0x2000);
  __memzero(port_g988stat_total,0x2000);
  puVar5 = port_g988stat_last;
  do {
    *(undefined4 *)((int)puVar5 + 0xc) = 8;
    *(undefined4 *)((int)puVar5 + 0x10) = 2;
    *(undefined4 *)puVar5 = 2;
    *(undefined4 *)((int)puVar5 + 4) = 8;
    *(undefined4 *)((int)puVar5 + 8) = 0xfff;
    puVar5 = (undefined1 *)((int)puVar5 + 0x80);
  } while (puVar5 != port_g988stat_total);
  if (((iVar2 == 0 && iVar1 == 0) && iVar3 == 0) && iVar4 == 0) {
    return 0;
  }
  printk("[%s] L%d tm sdk failed!\n","zte_api_sw_port_init",0x4ef);
  return 0xffffffff;
}

