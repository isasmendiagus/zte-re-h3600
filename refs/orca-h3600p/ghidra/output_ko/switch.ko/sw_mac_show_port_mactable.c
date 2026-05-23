// module: switch.ko
// function: sw_mac_show_port_mactable @ 0x14bf8
// size: 28 bytes
//

undefined4
sw_mac_show_port_mactable
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  printk("[%s] not support now!\n","sw_mac_show_port_mactable",param_3,param_4,param_4);
  return 0;
}

