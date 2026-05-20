// module: mt7915.ko
// function: rt28xx_send_packets @ 0x246730
// size: 108 bytes
//

undefined4 rt28xx_send_packets(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if ((*(uint *)(param_2 + 0x138) & 1) != 0) {
    if ((*(ushort *)(param_1 + 0xbc) & 0x10) == 0) {
      os_zero_mem(param_1 + 0x2a,0x25);
    }
    g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
    idm_fdb_hook_xmit(param_1);
    uVar1 = rt28xx_packet_xmit(param_1);
    return uVar1;
  }
  RTMPFreeNdisPacket(0,param_1);
  return 0;
}

