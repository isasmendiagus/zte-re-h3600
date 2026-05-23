// module: mt7915.ko
// function: APAsicEvaluateRxAnt @ 0x17a00
// size: 196 bytes
//

void APAsicEvaluateRxAnt(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  if ((*(uint *)(param_1 + 0xa3ac14) & 1) != 0) {
    return;
  }
  if ((*(int *)(param_1 + 0xa77bb4) == 1) &&
     ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) != 0)) {
    return;
  }
  bbp_set_rxpath(param_1,"SetPartProfileParameters"[param_1 + 0x18] & 0xf,
                 *(int *)(param_1 + 0xa77bb4),&UNK_00296000 + param_1,param_4);
  if ((uint)(*(int *)(param_1 + 0xa39e24) + *(int *)(param_1 + 0xa39e20) +
            *(int *)(param_1 + 0xa39e1c)) < 0x33) {
    RTMPSetTimer(param_1 + 0x829224,300);
    *(undefined1 *)(param_1 + 0x829221) = 1;
    return;
  }
  RTMPSetTimer(param_1 + 0x829224,0x14);
  *(undefined1 *)(param_1 + 0x829221) = 0;
  return;
}

