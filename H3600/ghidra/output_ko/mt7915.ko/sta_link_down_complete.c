// module: mt7915.ko
// function: sta_link_down_complete @ 0x689ac
// size: 16 bytes
//

void sta_link_down_complete(int param_1)

{
  complete(param_1 + 0x213244);
  return;
}

