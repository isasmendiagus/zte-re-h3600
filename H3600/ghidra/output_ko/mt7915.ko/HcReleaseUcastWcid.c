// module: mt7915.ko
// function: HcReleaseUcastWcid @ 0xa9ff0
// size: 20 bytes
//

void HcReleaseUcastWcid(int param_1,int param_2)

{
  WtcReleaseUcastWcid(*(undefined4 *)(param_1 + 0xa797a0),*(undefined4 *)(param_2 + 0xabc));
  return;
}

