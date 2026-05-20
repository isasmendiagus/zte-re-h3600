// module: mt7915.ko
// function: WscStaShowPeerList @ 0x1ee6fc
// size: 252 bytes
//

undefined4 WscStaShowPeerList(int param_1)

{
  int *piVar1;
  char *pcVar2;
  
  pcVar2 = s_TotalTimeForDump_0x_x____d_secs__00371a28 + param_1 + 0x14;
  _raw_spin_lock_bh(pcVar2);
  if (s_TotalTimeForDump_0x_x____d_secs__00371a28[param_1 + 0x20] != '\0') {
    _raw_spin_unlock_bh(pcVar2);
    WscMaintainPeerList(param_1,&DAT_0036ee3c + param_1);
    _raw_spin_lock_bh(pcVar2);
    for (piVar1 = *(int **)(s_TotalTimeForDump_0x_x____d_secs__00371a28 + param_1 + 0x18);
        piVar1 != (int *)0x0; piVar1 = (int *)*piVar1) {
      if (2 < DebugLevel) {
        printk("MAC:%02x:%02x:%02x:%02x:%02x:%02x\tReveive Time:%lu\n",*(undefined1 *)(piVar1 + 2),
               *(undefined1 *)((int)piVar1 + 9),*(undefined1 *)((int)piVar1 + 10),
               *(undefined1 *)((int)piVar1 + 0xb),*(undefined1 *)(piVar1 + 3),
               *(undefined1 *)((int)piVar1 + 0xd),piVar1[1]);
      }
    }
  }
  _raw_spin_unlock_bh(pcVar2);
  if (2 < DebugLevel) {
    printk(&_LC13);
  }
  return 1;
}

