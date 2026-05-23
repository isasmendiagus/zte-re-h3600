// module: switch.ko
// function: sw_zteduplex_to_cspplatduplex @ 0x17358
// size: 64 bytes
//

undefined4
sw_zteduplex_to_cspplatduplex(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if (param_1 == 0) {
    return 1;
  }
  if (param_1 == 1) {
    return 2;
  }
  printk("%s undefined duplex=%d\n","sw_zteduplex_to_cspplatduplex",param_1,param_4,param_4);
  return 0;
}

