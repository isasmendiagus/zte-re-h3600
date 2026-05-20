// module: mt7915.ko
// function: hc_obj_init @ 0xaa684
// size: 64 bytes
//

undefined4 hc_obj_init(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)(param_1 + 8) + 0xa797a0);
  *(int *)(param_1 + 0xabc) = iVar1 + param_2 * 0x28 + 0x32e0;
  *(int *)(iVar1 + param_2 * 0x28 + 0x3304) = iVar1;
  return 0;
}

