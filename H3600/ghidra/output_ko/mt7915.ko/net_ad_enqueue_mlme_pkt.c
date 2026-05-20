// module: mt7915.ko
// function: net_ad_enqueue_mlme_pkt @ 0x25a2a0
// size: 52 bytes
//

void net_ad_enqueue_mlme_pkt(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = *(int *)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14);
  *(byte *)(param_2 + 0x3a) = *(byte *)(param_2 + 0x3a) | 8;
                    /* WARNING: Could not recover jumptable at 0x0025a2d0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(iVar1 + 0x20))(param_1,param_3,param_2);
  return;
}

