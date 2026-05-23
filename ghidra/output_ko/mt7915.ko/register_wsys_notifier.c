// module: mt7915.ko
// function: register_wsys_notifier @ 0x104494
// size: 8 bytes
//

void register_wsys_notifier(int param_1)

{
  mt_notify_chain_register(param_1 + 0x24);
  return;
}

