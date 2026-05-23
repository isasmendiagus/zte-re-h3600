// module: switch.ko
// function: sw_ztespeed_to_cspplatspeed @ 0x173c4
// size: 80 bytes
//

undefined4
sw_ztespeed_to_cspplatspeed(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_1 == 1) {
    return 2;
  }
  if (param_1 != 0) {
    if (param_1 == 2) {
      return 3;
    }
    printk("%s undefined speed=%d\n","sw_ztespeed_to_cspplatspeed",param_1,param_4,param_4);
    return 0;
  }
  return 1;
}

