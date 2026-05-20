// module: mt7915.ko
// function: sys_ad_free_pkt @ 0x25ea78
// size: 16 bytes
//

void sys_ad_free_pkt(int param_1)

{
  if (param_1 == 0) {
    return;
  }
  __dev_kfree_skb_any(param_1,1);
  return;
}

