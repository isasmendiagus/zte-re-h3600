// module: mt7915.ko
// function: peer_max_bw_cap @ 0x205288
// size: 44 bytes
//

uint peer_max_bw_cap(uint param_1)

{
  uint uVar1;
  
  if ((param_1 & 2) == 0) {
    return param_1 & 1;
  }
  if ((param_1 & 4) == 0) {
    uVar1 = 2;
  }
  else {
    uVar1 = 3;
  }
  if ((param_1 & 8) != 0) {
    uVar1 = 4;
  }
  return uVar1;
}

