// module: switch.ko
// function: cspplatspeed_to_sw_ztespeed @ 0x17458
// size: 80 bytes
//

undefined4
cspplatspeed_to_sw_ztespeed(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_1 == 2) {
    return 1;
  }
  if (param_1 != 3) {
    if (param_1 != 1) {
      printk("%s undefined speed=%d\n","cspplatspeed_to_sw_ztespeed",param_1,param_4,param_4);
      return 0;
    }
    return 0;
  }
  return 2;
}

