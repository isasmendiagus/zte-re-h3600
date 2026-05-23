// module: mt7915.ko
// function: RtmpOSNetDevGetByName @ 0x24424c
// size: 12 bytes
//

void RtmpOSNetDevGetByName(void)

{
  dev_get_by_name(&init_net);
  return;
}

