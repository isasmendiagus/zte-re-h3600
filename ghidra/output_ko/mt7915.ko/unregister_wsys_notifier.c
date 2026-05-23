// module: mt7915.ko
// function: unregister_wsys_notifier @ 0x10449c
// size: 8 bytes
//

void unregister_wsys_notifier(int param_1)

{
  mt_notify_chain_unregister(param_1 + 0x24);
  return;
}

