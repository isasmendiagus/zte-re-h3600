// module: mt7915.ko
// function: rc_init @ 0xac8e8
// size: 44 bytes
//

undefined4 rc_init(int param_1)

{
  os_zero_mem(param_1 + 0x1360,0x354);
  os_zero_mem(param_1 + 0x16b4,0x354);
  return 0;
}

