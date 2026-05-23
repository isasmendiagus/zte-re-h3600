// module: tm.ko
// function: zte_api_sw_port_set_port_floodcontrolmask @ 0x62040
// size: 44 bytes
//

undefined4
zte_api_sw_port_set_port_floodcontrolmask(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  switch(param_2) {
  case 0:
  case 1:
  case 4:
    uVar1 = tm_port_pon_unkuni_floodcontrolmask(param_1,param_3);
    return uVar1;
  case 2:
  case 5:
    uVar1 = tm_port_unknwn_multicast_floodcontrolmask(param_1,param_3);
    return uVar1;
  case 3:
    uVar1 = tm_port_pon_broadcast_floodcontrolmask(param_1,param_3);
    return uVar1;
  default:
    return 0xffffffff;
  }
}

