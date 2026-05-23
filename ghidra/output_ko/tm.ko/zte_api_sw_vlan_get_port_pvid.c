// module: tm.ko
// function: zte_api_sw_vlan_get_port_pvid @ 0x64360
// size: 88 bytes
//

undefined4 zte_api_sw_vlan_get_port_pvid(undefined4 param_1,undefined2 *param_2,undefined1 *param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_18 [4];
  undefined2 local_14 [4];
  
  iVar1 = tm_port_pvid_get(param_1,local_14,local_18);
  if (iVar1 == 0) {
    *param_2 = local_14[0];
    *param_3 = local_18[0];
    uVar2 = 0;
  }
  else {
    printk("[%s] L%d sw api get failed!\n","zte_api_sw_vlan_get_port_pvid",0x5a4);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

