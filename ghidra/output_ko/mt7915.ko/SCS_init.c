// module: mt7915.ko
// function: SCS_init @ 0x238c44
// size: 168 bytes
//

void SCS_init(int param_1)

{
  uint local_14;
  
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),*(int *)(param_1 + 0xa7c2d0) + 0x1229c,&local_14)
  ;
  local_14 = local_14 | 0x80000;
  hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),*(int *)(param_1 + 0xa7c2d0) + 0x1229c);
  if (1 < *(byte *)(param_1 + 0xa7c240)) {
    hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),0x820fd00c,&local_14);
    local_14 = local_14 | 0x707;
    hw_io_write32(*(undefined4 *)(param_1 + 0xa797a0),0x820fd00c);
  }
  Set_SCSEnable_Proc(param_1,&_LC8);
  return;
}

