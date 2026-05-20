// module: mt7915.ko
// function: GetCfgBw2RawBw @ 0x1af788
// size: 36 bytes
//

undefined1 GetCfgBw2RawBw(int param_1)

{
  undefined1 uVar1;
  uint uVar2;
  
  uVar2 = param_1 - 1U & 0xff;
  if (uVar2 < 6) {
    uVar1 = (&DAT_0029ecd0)[uVar2];
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

