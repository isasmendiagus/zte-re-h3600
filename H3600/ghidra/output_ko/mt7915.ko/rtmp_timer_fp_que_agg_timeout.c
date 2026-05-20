// module: mt7915.ko
// function: rtmp_timer_fp_que_agg_timeout @ 0xd5048
// size: 120 bytes
//

void rtmp_timer_fp_que_agg_timeout
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x24);
  iVar1 = *(int *)(iVar3 + 0x54);
  uVar2 = (uint)*(byte *)(iVar3 + 0x34);
  if (*(char *)(iVar1 + uVar2 + 0x285bac) != '\0') {
    (**(code **)(*(int *)("Get_RBIST_IQ_Data" + iVar1 + 0x10) + 8))(iVar1,0);
    uVar2 = 1;
    *(undefined1 *)(iVar3 + 0x37) = 1;
    *(undefined1 *)(iVar3 + 0x35) = 0;
  }
  if (*(char *)(param_1 + 0x1f) == '\0') {
    return;
  }
  RTMP_OS_Add_Timer(param_1,*(undefined4 *)(param_1 + 0x20),uVar2,param_4);
  return;
}

