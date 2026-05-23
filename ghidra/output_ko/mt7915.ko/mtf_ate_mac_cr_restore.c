// module: mt7915.ko
// function: mtf_ate_mac_cr_restore @ 0x172170
// size: 556 bytes
//

undefined4 mtf_ate_mac_cr_restore(int param_1)

{
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x6867 ||
      (*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7915) {
    MtTestModeRestoreCr(param_1,0x820e206c);
    MtTestModeRestoreCr(param_1,0x820e2070);
    MtTestModeRestoreCr(param_1,0x820e205c);
    MtTestModeRestoreCr(param_1,0x820e2060);
    MtTestModeRestoreCr(param_1,0x820e2064);
    MtTestModeRestoreCr(param_1,0x820e2068);
    MtTestModeRestoreCr(param_1,0x820e2098);
    MtTestModeRestoreCr(param_1,0x820e4000);
    MtTestModeRestoreCr(param_1,0x820e41e0);
    MtTestModeRestoreCr(param_1,0x820e20f0);
    MtTestModeRestoreCr(param_1,0x820e20f4);
    MtTestModeRestoreCr(param_1,0x820e409c);
    MtTestModeRestoreCr(param_1,0x820e40a4);
    MtTestModeRestoreCr(param_1,0x820e3194);
    MtTestModeRestoreCr(param_1,0x820e3198);
    if (*(char *)(param_1 + 0x79504d) != '\0') {
      MtTestModeRestoreCr(param_1,0x820f206c);
      MtTestModeRestoreCr(param_1,0x820f2070);
      MtTestModeRestoreCr(param_1,0x820f205c);
      MtTestModeRestoreCr(param_1,0x820f2060);
      MtTestModeRestoreCr(param_1,0x820f2064);
      MtTestModeRestoreCr(param_1,0x820f2068);
      MtTestModeRestoreCr(param_1,0x820f2098);
      MtTestModeRestoreCr(param_1,0x820f4000);
      MtTestModeRestoreCr(param_1,0x820f41e0);
      MtTestModeRestoreCr(param_1,0x820f20f0);
      MtTestModeRestoreCr(param_1,0x820f20f4);
      MtTestModeRestoreCr(param_1,0x820f409c);
      MtTestModeRestoreCr(param_1,0x820f40a4);
      MtTestModeRestoreCr(param_1,0x820f3194);
      MtTestModeRestoreCr(param_1,0x820f3198);
      return 0;
    }
  }
  return 0;
}

