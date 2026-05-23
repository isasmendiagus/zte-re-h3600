// module: switch.ko
// function: sw_mac_add_port_macaddress @ 0x1489c
// size: 288 bytes
//

undefined4 sw_mac_add_port_macaddress(int *param_1)

{
  code cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int local_2e;
  undefined2 local_2a;
  
  iVar3 = param_1[4];
  cVar1 = zte_api_sw_mac_set_port_macfiltermode[*param_1];
  iVar2 = param_1[3];
  __memzero(&local_2e,6);
  local_2e = param_1[1];
  local_2a = (undefined2)param_1[2];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %d\n%s = %2x:%2x:%2x:%2x:%2x:%2x\n%s = %d\n%s = %d\n",
           "sw_mac_add_port_macaddress","MacEntry.port",*param_1,"MacEntry.mac",(char)param_1[1],
           *(undefined1 *)((int)param_1 + 5),*(undefined1 *)((int)param_1 + 6),
           *(undefined1 *)((int)param_1 + 7),(char)param_1[2],*(undefined1 *)((int)param_1 + 9),
           "MacEntry.vid",param_1[3],"MacEntry.mode",param_1[4]);
  }
  iVar3 = zte_api_sw_mac_add_port_macaddress(cVar1,&local_2e,(short)iVar2,(char)iVar3);
  uVar4 = 0;
  if (iVar3 != 0) {
    printk("[%s] L%d tm sdk failed!\n","sw_mac_add_port_macaddress",0x91);
    uVar4 = 0xffffffff;
  }
  return uVar4;
}

