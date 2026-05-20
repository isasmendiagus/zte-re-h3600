// module: mt7915.ko
// function: set_vow_show_mbss @ 0x46420
// size: 148 bytes
//

undefined4 set_vow_show_mbss(int param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  uint local_c;
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  iVar2 = sscanf(param_2,"%u",&local_c);
  iVar1 = DebugLevel;
  if ((iVar2 != 0) && (local_c < 0x11)) {
    *(uint *)(param_1 + 0xa7a328) = local_c;
    if (-1 < iVar1) {
      printk("%s: show MBSS up to %d.\n","set_vow_show_mbss");
    }
    return 1;
  }
  return 0;
}

