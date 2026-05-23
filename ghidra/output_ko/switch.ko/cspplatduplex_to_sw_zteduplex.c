// module: switch.ko
// function: cspplatduplex_to_sw_zteduplex @ 0x173f0
// size: 64 bytes
//

undefined4
cspplatduplex_to_sw_zteduplex(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_1 == 1) {
    return 0;
  }
  if (param_1 == 2) {
    return 1;
  }
  printk("%s undefined duplex=%d\n","cspplatduplex_to_sw_zteduplex",param_1,param_4,param_4);
  return 0;
}

