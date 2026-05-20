// module: mt7915.ko
// function: rtmp_ee_init_check @ 0x25f298
// size: 28 bytes
//

undefined1 rtmp_ee_init_check(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  return *(undefined1 *)(iVar1 + 0xf8);
}

