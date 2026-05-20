// module: mt7915.ko
// function: rssi_to_rcpi @ 0x21e7e8
// size: 64 bytes
//

uint rssi_to_rcpi(int param_1)

{
  if (param_1 == 0) {
    return 0xff;
  }
  if (-0x6f < param_1) {
    if (0 < param_1) {
      return 0xdc;
    }
    return (param_1 + 0x6e) * 2 & 0xff;
  }
  return 0;
}

