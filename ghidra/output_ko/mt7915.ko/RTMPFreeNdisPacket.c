// module: mt7915.ko
// function: RTMPFreeNdisPacket @ 0x2435bc
// size: 68 bytes
//

void RTMPFreeNdisPacket(undefined4 param_1,int param_2)

{
  if (param_2 == 0) {
    return;
  }
  g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + -1;
  if ((*(ushort *)(param_2 + 0xbc) & 0x10) == 0) {
    if ((*(ushort *)(param_2 + 0xbc) & 0x40) == 0) {
      __dev_kfree_skb_any(param_2,1);
      return;
    }
    _idm_skb_stack_push(param_2,2);
    return;
  }
  idm_skb_stack_push();
  return;
}

