// module: mt7915.ko
// function: mtf_ate_ipg_cr_restore @ 0x17209c
// size: 212 bytes
//

undefined4 mtf_ate_ipg_cr_restore(undefined4 param_1,int param_2)

{
  if (param_2 != 0) {
    MtTestModeRestoreCr(param_1,0x820f20f0);
    MtTestModeRestoreCr(param_1,0x820f20f4);
    MtTestModeRestoreCr(param_1,0x820f409c);
    MtTestModeRestoreCr(param_1,0x820f40a4);
    MtTestModeRestoreCr(param_1,0x820f3194);
    MtTestModeRestoreCr(param_1,0x820f3198);
    return 0;
  }
  MtTestModeRestoreCr(param_1,0x820e20f0);
  MtTestModeRestoreCr(param_1,0x820e20f4);
  MtTestModeRestoreCr(param_1,0x820e409c);
  MtTestModeRestoreCr(param_1,0x820e40a4);
  MtTestModeRestoreCr(param_1,0x820e3194);
  MtTestModeRestoreCr(param_1,0x820e3198);
  return 0;
}

