// module: mt7915.ko
// function: WPAGroupRekeyByWdev @ 0x18918
// size: 116 bytes
//

void WPAGroupRekeyByWdev(undefined4 param_1,int param_2)

{
  if ((*(uint *)(param_2 + 0x254) & 0x1f0) == 0) {
    return;
  }
  if (*(int *)(param_2 + 0x2a0) == 0) {
    return;
  }
  if (1 < *(int *)(param_2 + 0x29c) - 1U) {
    return;
  }
  *(undefined4 *)(param_2 + 0x2a4) = 0;
  RTMPSetTimer(param_2 + 0x31c,1000);
  if (DebugLevel < 3) {
    return;
  }
  printk(" %s : Group rekey method= %d , interval = 0x%lx\n","WPAGroupRekeyByWdev",
         *(undefined4 *)(param_2 + 0x29c),*(undefined4 *)(param_2 + 0x2a0));
  return;
}

