// module: mt7915.ko
// function: sta_send_data_pkt @ 0x534a0
// size: 148 bytes
//

undefined4 sta_send_data_pkt(int param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined1 uVar1;
  undefined1 uVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  
  uVar3 = *(ushort *)(param_3 + 0x42);
  iVar4 = *(int *)(param_2 + 0x904);
  iVar5 = *(int *)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14);
  GetStaCfgByWdev();
  uVar1 = *(undefined1 *)(param_3 + 0x2a);
  uVar2 = *(undefined1 *)(param_3 + 0x4d);
  (**(code **)(iVar4 + 0x84))(param_1,param_2,uVar1,1,param_4);
  *(undefined1 *)(param_3 + 0x2a) = uVar1;
  (**(code **)(iVar5 + 0x24))(param_1,param_2,param_3,uVar2);
  ba_ori_session_start(param_1,param_1 + (uint)uVar3 * 0x620 + 0x2f6a0,uVar1);
  return 0;
}

