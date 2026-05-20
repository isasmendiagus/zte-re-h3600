// module: mt7915.ko
// function: unregister_fw_cmd_notifier @ 0x1a4054
// size: 16 bytes
//

void unregister_fw_cmd_notifier(int param_1)

{
  mt_notify_chain_unregister(param_1 + 0xa78620);
  return;
}

