// module: mt7915.ko
// function: register_traffic_notifier @ 0xc62f8
// size: 16 bytes
//

void register_traffic_notifier(int param_1)

{
  mt_notify_chain_register(param_1 + 0xa18fc);
  return;
}

