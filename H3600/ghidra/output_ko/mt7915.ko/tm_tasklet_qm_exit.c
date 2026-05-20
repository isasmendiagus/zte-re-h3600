// module: mt7915.ko
// function: tm_tasklet_qm_exit @ 0x150600
// size: 164 bytes
//

undefined4 tm_tasklet_qm_exit(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(char *)(iVar1 + 0x158) == '\x01') {
    *(undefined1 *)(param_1 + 0x285bac) = 0;
    tasklet_kill(param_1 + 0x285bb0);
    *(undefined1 *)(param_1 + 0x285bad) = 0;
    tasklet_kill(param_1 + 0x285bc4);
  }
  else {
    *(undefined1 *)(param_1 + 0x285bac) = 0;
    tasklet_kill(param_1 + 0x285bb0);
  }
  if (*(char *)(iVar1 + 0x15b) == '\0') {
    tasklet_kill(param_1 + 0x285bdc);
  }
  return 0;
}

