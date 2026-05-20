// module: mt7915.ko
// function: GetRealPortQueueID @ 0x1ac9c4
// size: 84 bytes
//

undefined2 GetRealPortQueueID(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x1c);
  iVar1 = hc_get_chip_cap(*(undefined4 *)(iVar2 + 0xa797a0));
  iVar2 = hc_get_hif_type(*(undefined4 *)(iVar2 + 0xa797a0));
  if (iVar2 != 2) {
    return 2;
  }
  if (param_2 != 0xee) {
    return 0x8000;
  }
  return *(undefined2 *)(iVar1 + 0x152);
}

