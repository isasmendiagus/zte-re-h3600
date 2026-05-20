// module: mt7915.ko
// function: show_vow_sta_conf @ 0x47054
// size: 556 bytes
//

undefined4 show_vow_sta_conf(int param_1,char *param_2)

{
  int iVar1;
  uint uVar2;
  uint local_20;
  char *apcStack_1c [4];
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  iVar1 = sscanf(param_2,"%u",&local_20);
  if (iVar1 == 0) {
    return 0;
  }
  uVar2 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  if (uVar2 <= local_20) {
    return 0;
  }
  apcStack_1c[0] = "No change.";
  apcStack_1c[1] = "To BE.";
  apcStack_1c[2] = "To BK.";
  if (-1 < DebugLevel) {
    printk("%s: ************ sta%d ***********\n","show_vow_sta_conf",local_20);
    if (-1 < DebugLevel) {
      printk("Group --> %u\n",*(undefined1 *)(param_1 + (local_20 + 0x14f33d) * 8 + 4));
      if (DebugLevel < 0) {
        return 1;
      }
      printk("Priority --> %s(%u)\n",apcStack_1c[*(byte *)(param_1 + (local_20 + 0x14f33d) * 8 + 6)]
            );
      if (DebugLevel < 0) {
        return 1;
      }
      printk("Ac0 --> %uus(%u)\n",
             (uint)*(byte *)(param_1 + (uint)*(byte *)(param_1 + (local_20 + 0x14f33d) * 8) +
                            0xa7a2f4) << 8);
      if (DebugLevel < 0) {
        return 1;
      }
      printk("Ac1 --> %uus(%u)\n",
             (uint)*(byte *)(param_1 + (uint)*(byte *)(param_1 + local_20 * 8 + 0xa799e9) + 0xa7a2f4
                            ) << 8);
    }
    if (-1 < DebugLevel) {
      printk("Ac2 --> %uus(%u)\n",
             (uint)*(byte *)(param_1 + (uint)*(byte *)(param_1 + local_20 * 8 + 0xa799ea) + 0xa7a2f4
                            ) << 8);
      if (-1 < DebugLevel) {
        printk("Ac3 --> %uus(%u)\n",
               (uint)*(byte *)(param_1 + (uint)*(byte *)(param_1 + local_20 * 8 + 0xa799eb) +
                              0xa7a2f4) << 8);
      }
    }
    return 1;
  }
  return 1;
}

