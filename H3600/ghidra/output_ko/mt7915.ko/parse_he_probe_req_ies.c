// module: mt7915.ko
// function: parse_he_probe_req_ies @ 0x205620
// size: 196 bytes
//

byte parse_he_probe_req_ies(int param_1,int param_2)

{
  byte bVar1;
  void *__src;
  uint uVar2;
  
  if ((*(char *)(param_1 + 2) == '#') && (bVar1 = *(char *)(param_1 + 1) - 1, 0x14 < bVar1)) {
    *(uint *)(param_2 + 0x240) = *(uint *)(param_2 + 0x240) | 0x10;
    memmove((void *)(param_2 + 0x2ba),(void *)(param_1 + 3),0x15);
    __src = (void *)(param_1 + 0x18);
    uVar2 = (uint)(*(int *)(param_2 + 0x2c0) << 0x18) >> 0x19;
    if ((uVar2 & 2) != 0) {
      if ((uVar2 & 4) == 0) {
        if ((uVar2 & 8) != 0) {
          memmove((void *)(param_2 + 0x2d3),__src,4);
        }
      }
      else if ((uVar2 & 8) == 0) {
        memmove((void *)(param_2 + 0x2cf),__src,4);
      }
      else {
        memmove((void *)(param_2 + 0x2d3),__src,4);
      }
    }
    return bVar1;
  }
  return 0;
}

