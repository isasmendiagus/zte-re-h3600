// module: mt7915.ko
// function: dot11_2_ra_rate @ 0x128a48
// size: 112 bytes
//

undefined4 dot11_2_ra_rate(undefined4 param_1)

{
  switch(param_1) {
  case 2:
    return 0;
  default:
    return 3;
  case 4:
    return 1;
  case 0xb:
    return 2;
  case 0xc:
    return 4;
  case 0x12:
    return 5;
  case 0x18:
    return 6;
  case 0x24:
    return 7;
  case 0x30:
    return 8;
  case 0x48:
    return 9;
  case 0x60:
    return 10;
  case 0x6c:
    return 0xb;
  }
}

