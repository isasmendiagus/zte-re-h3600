// module: mt7915.ko
// function: net_ad_set_bss_info @ 0x25d204
// size: 236 bytes
//

undefined4 net_ad_set_bss_info(int param_1,int param_2,int param_3,void *param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_135;
  undefined1 auStack_134 [4];
  undefined4 local_130;
  undefined1 local_128;
  undefined1 local_127;
  undefined1 auStack_126 [6];
  undefined2 local_120;
  undefined4 local_11c;
  undefined4 local_118;
  undefined1 local_114;
  undefined4 local_f8;
  undefined1 local_2e;
  
  local_135 = 0;
  uVar2 = *(undefined4 *)
           (param_2 + (uint)*(byte *)(param_2 + (uint)*(byte *)(param_2 + 0xc55) + 0x205) * 4 + 0x24
           );
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  sys_ad_zero_mem(auStack_134,0x114);
  uVar2 = net_ad_get_omac_idx(param_1,uVar2,&local_135);
  local_127 = *(undefined1 *)
               (*(int *)(param_3 * 0xd18 + *(int *)(iVar1 + 0xa77bb8) + 0x504) + 0x999);
  local_128 = local_135;
  os_move_mem(auStack_126,param_4,6);
  local_114 = 0;
  local_2e = (undefined1)param_3;
  local_120 = 1;
  local_118 = 0x10002;
  local_11c = 0x10000;
  local_f8 = 3;
  local_130 = 2;
  iVar1 = AsicBssInfoUpdate(iVar1,auStack_134);
  if (iVar1 != 0) {
    uVar2 = 0x100;
  }
  return uVar2;
}

