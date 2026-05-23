// module: switch.ko
// function: sw_other_get_onu_mtu @ 0x167d8
// size: 28 bytes
//

undefined4
sw_other_get_onu_mtu(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  printk("[%s] not support now!\n","sw_other_get_onu_mtu",param_3,param_4,param_4);
  return 0;
}

