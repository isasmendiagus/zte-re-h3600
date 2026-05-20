// module: mt7915.ko
// function: set_vow_sta_frr_quantum @ 0x44614
// size: 156 bytes
//

undefined4 set_vow_sta_frr_quantum(int param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  uint local_c;
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  iVar2 = sscanf(param_2,"%u",&local_c);
  iVar1 = DebugLevel;
  if ((iVar2 != 0) && (local_c < 0x100)) {
    *(char *)(param_1 + 0xa7be35) = (char)local_c;
    *(undefined1 *)(param_1 + 0xa7be36) = 0;
    if (-1 < iVar1) {
      printk("%s: set FRR quantum %d.\n","set_vow_sta_frr_quantum");
    }
    return 1;
  }
  return 0;
}

