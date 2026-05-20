// module: switch.ko
// function: sw_port_set_port_floodcontrol @ 0x17964
// size: 28 bytes
//

undefined4
sw_port_set_port_floodcontrol
          (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  printk("[%s] not support now!\n","sw_port_set_port_floodcontrol",param_3,param_4,param_4);
  return 0;
}

