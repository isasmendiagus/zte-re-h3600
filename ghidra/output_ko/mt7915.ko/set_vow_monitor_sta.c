// module: mt7915.ko
// function: set_vow_monitor_sta @ 0x46018
// size: 152 bytes
//

undefined4 set_vow_monitor_sta(int param_1,char *param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint local_c;
  
  if (param_2 != (char *)0x0) {
    iVar1 = sscanf(param_2,"%u",&local_c);
    if ((iVar1 == 0) ||
       (uVar3 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0)), iVar1 = DebugLevel,
       uVar3 <= local_c)) {
      uVar2 = 0;
    }
    else {
      *(char *)(param_1 + 0xa7a31c) = (char)local_c;
      if (iVar1 < 0) {
        uVar2 = 1;
      }
      else {
        printk("%s: monitor sta%d.\n","set_vow_monitor_sta");
        uVar2 = 1;
      }
    }
    return uVar2;
  }
  return 0;
}

