// module: tm.ko
// function: zte_api_sw_vlan_get_port_inframemode @ 0x6423c
// size: 176 bytes
//

undefined4 zte_api_sw_vlan_get_port_inframemode(undefined4 param_1,undefined1 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_14 [2];
  
  iVar1 = tm_port_vlan_filter_get(param_1,local_14);
  if (iVar1 == 0) {
    if (local_14[0] == 0) {
      *param_2 = 0;
      uVar2 = 0;
    }
    else {
      uVar2 = 0;
      if (local_14[0] == 0x3f) {
        *param_2 = 1;
      }
      else if (local_14[0] == 1) {
        *param_2 = 2;
      }
      else if (local_14[0] == 0x3e) {
        *param_2 = 3;
      }
      else {
        printk("[%s] output:\n%s = discard hybrid\n","zte_api_sw_vlan_get_port_inframemode",
               "InframeMode.mode");
      }
    }
  }
  else {
    printk("[%s] L%d sw api get failed!\n","zte_api_sw_vlan_get_port_inframemode",0x56a);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

