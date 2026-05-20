// module: mt7915.ko
// function: show_fgi_and_ltf_proc @ 0x29094
// size: 208 bytes
//

undefined4 show_fgi_and_ltf_proc(int *param_1)

{
  int iVar1;
  char *apcStack_20 [4];
  
  apcStack_20[0] = "Auto_GI";
  apcStack_20[1] = "GI_08_US + LTF_2x";
  apcStack_20[2] = "GI_16_US + LTF_2x";
  apcStack_20[3] = "GI_32_US + LTF_4x";
  iVar1 = *param_1;
  if (0 < DebugLevel) {
    printk("%s:: enter\n","show_fgi_and_ltf_proc");
  }
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(iVar1 + 0x3c),*(undefined4 *)(iVar1 + 0x38));
  if (iVar1 != 0) {
    if (*(byte *)(iVar1 + 0x405c) < 4) {
      if (0 < DebugLevel) {
        printk("%s(): Current_gi(%s)\n","show_fgi_and_ltf_proc",
               apcStack_20[*(byte *)(iVar1 + 0x405c)]);
        return 1;
      }
      return 1;
    }
    if (0 < DebugLevel) {
      printk("%s(): Error!!!(cur_gi(%d) is invalid!\n","show_fgi_and_ltf_proc");
      return 0xfffffff2;
    }
  }
  return 0xfffffff2;
}

