// module: mt7915.ko
// function: unregister_traffic_notifier @ 0xc6308
// size: 16 bytes
//

void unregister_traffic_notifier(int param_1)

{
  mt_notify_chain_unregister(param_1 + 0xa18fc);
  return;
}

