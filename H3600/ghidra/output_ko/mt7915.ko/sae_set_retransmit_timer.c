// module: mt7915.ko
// function: sae_set_retransmit_timer @ 0x209398
// size: 164 bytes
//

void sae_set_retransmit_timer(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 extraout_r2;
  
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_set_retransmit_timer");
    param_3 = extraout_r2;
  }
  if (param_1 == 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("==> %s(), pSaeIns NULL!!\n","sae_set_retransmit_timer",param_3,param_4);
    return;
  }
  if (*(int *)(param_1 + 0x180) != 0) {
    RTMPSetTimer(param_1 + 300,*(int *)(*(int *)(param_1 + 0x180) + 0x1b920) * 1000,param_3,param_4)
    ;
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("==> %s(), RTMPSetTimer fail!!\n","sae_set_retransmit_timer",param_3,param_4);
  return;
}

