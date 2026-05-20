// module: mt7915.ko
// function: ShowSCSinfo_ver2_proc @ 0x238c08
// size: 60 bytes
//

undefined4 ShowSCSinfo_ver2_proc(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0x2cc) != (code *)0x0) {
    (**(code **)(iVar1 + 0x2cc))(param_1);
    return 1;
  }
  return 0;
}

