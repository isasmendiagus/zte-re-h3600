// module: mt7915.ko
// function: RtmpOsFileIsErr @ 0x244c08
// size: 32 bytes
//

bool RtmpOsFileIsErr(uint param_1)

{
  if (param_1 == 0) {
    return true;
  }
  return 0xfffff000 < param_1;
}

