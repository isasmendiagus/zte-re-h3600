// module: mt7915.ko
// function: mtf_get_packet_type @ 0x19ee60
// size: 12 bytes
//

uint mtf_get_packet_type(undefined4 param_1,uint *param_2)

{
  return *param_2 >> 0x1b;
}

