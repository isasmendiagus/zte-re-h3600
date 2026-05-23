// module: mt7915.ko
// function: fp_que_agg_timeout @ 0xd4ff0
// size: 88 bytes
//

void fp_que_agg_timeout(undefined4 param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_2 + 0x54);
  if (*(char *)(iVar1 + (uint)*(byte *)(param_2 + 0x34) + 0x285bac) == '\0') {
    return;
  }
  (**(code **)(*(int *)("Get_RBIST_IQ_Data" + iVar1 + 0x10) + 8))(iVar1,0);
  *(undefined1 *)(param_2 + 0x37) = 1;
  *(undefined1 *)(param_2 + 0x35) = 0;
  return;
}

