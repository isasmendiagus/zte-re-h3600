// module: switch.ko
// function: sw_mac_get_port_macfiltermode @ 0x142b8
// size: 28 bytes
//

undefined4
sw_mac_get_port_macfiltermode
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  printk("[%s] not support now!\n","sw_mac_get_port_macfiltermode",param_3,param_4,param_4);
  return 0;
}

