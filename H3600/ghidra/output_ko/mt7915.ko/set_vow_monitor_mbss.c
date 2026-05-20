// module: mt7915.ko
// function: set_vow_monitor_mbss @ 0x4614c
// size: 148 bytes
//

undefined4 set_vow_monitor_mbss(int param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  uint local_c;
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  iVar2 = sscanf(param_2,"%u",&local_c);
  iVar1 = DebugLevel;
  if ((iVar2 != 0) && (local_c < 0x10)) {
    *(char *)(param_1 + 0xa7a31e) = (char)local_c;
    if (-1 < iVar1) {
      printk("%s: monitor mbss%d.\n","set_vow_monitor_mbss");
    }
    return 1;
  }
  return 0;
}

