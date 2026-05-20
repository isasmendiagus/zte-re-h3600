// module: mt7915.ko
// function: register_fw_cmd_notifier @ 0x1a4044
// size: 16 bytes
//

void register_fw_cmd_notifier(int param_1)

{
  mt_notify_chain_register(param_1 + 0xa78620);
  return;
}

