// module: mt7915.ko
// function: hc_get_channel_ctrl @ 0xaa740
// size: 20 bytes
//

int hc_get_channel_ctrl(int param_1,int param_2)

{
  return param_1 + param_2 * 0x4e0 + 0x38;
}

