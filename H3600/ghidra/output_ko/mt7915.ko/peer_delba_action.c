// module: mt7915.ko
// function: peer_delba_action @ 0xa7414
// size: 168 bytes
//

void peer_delba_action(undefined4 param_1,int param_2)

{
  int iVar1;
  
  if (2 < DebugLevel) {
    printk("%s ==>\n","peer_delba_action");
  }
  iVar1 = PeerDelBAActionSanity
                    (param_1,*(undefined2 *)(param_2 + 0x920),param_2,
                     *(undefined4 *)(param_2 + 0x908));
  if (iVar1 == 0) {
    return;
  }
  if (2 < DebugLevel) {
    printk("Initiator = %d, Reason = %d\n",((uint)*(byte *)(param_2 + 0x1b) << 0x1c) >> 0x1f,
           *(undefined2 *)(param_2 + 0x1c));
  }
  if ((*(byte *)(param_2 + 0x1b) & 8) == 0) {
    ba_ori_session_tear_down();
    return;
  }
  ba_rec_session_tear_down
            (param_1,*(undefined2 *)(param_2 + 0x920),*(byte *)(param_2 + 0x1b) >> 4,1);
  return;
}

