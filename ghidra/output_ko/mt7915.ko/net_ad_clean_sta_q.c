// module: mt7915.ko
// function: net_ad_clean_sta_q @ 0x25d198
// size: 92 bytes
//

undefined4 net_ad_clean_sta_q(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    return 0x606;
  }
  if (*(code **)(*(int *)("Get_RBIST_Raw_Data_Proc" + iVar1 + 0x14) + 8) == (code *)0x0) {
    return 0;
  }
  iVar1 = (**(code **)(*(int *)("Get_RBIST_Raw_Data_Proc" + iVar1 + 0x14) + 8))(iVar1,param_2);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = 0x601;
  }
  return uVar2;
}

