// module: mt7915.ko
// function: RT28xx_MSTA_Init @ 0x68538
// size: 128 bytes
//

void RT28xx_MSTA_Init(undefined4 param_1)

{
  code *local_58;
  code *local_54;
  code *local_50;
  code *local_4c;
  code *local_48;
  
  __memzero(&local_58,0x40);
  local_58 = msta_virtual_if_open;
  local_54 = msta_virtual_if_close;
  local_50 = rt28xx_send_packets;
  local_4c = rt28xx_ioctl;
  local_48 = RT28xx_get_ether_stats;
  RTMP_STA_IoctlHandle(param_1,0,41000,0,&local_58,0,0);
  return;
}

