// module: mt7915.ko
// function: sae_clear_retransmit_timer @ 0x209440
// size: 72 bytes
//

void sae_clear_retransmit_timer(int param_1)

{
  undefined1 uStack_9;
  
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_clear_retransmit_timer");
  }
  RTMPCancelTimer(param_1 + 300,&uStack_9);
  return;
}

