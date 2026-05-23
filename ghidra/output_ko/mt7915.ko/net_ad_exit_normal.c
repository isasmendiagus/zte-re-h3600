// module: mt7915.ko
// function: net_ad_exit_normal @ 0x25b564
// size: 216 bytes
//

undefined4 net_ad_exit_normal(int param_1,undefined1 *param_2)

{
  undefined1 uVar1;
  int iVar2;
  
  iVar2 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar2 == 0) {
    return 0x606;
  }
  net_ad_stop_ap(param_1);
  *param_2 = *(undefined1 *)(iVar2 + 0x795071);
  *(undefined1 *)(iVar2 + 0x795071) = 0;
  param_2[1] = *(undefined1 *)(iVar2 + 0x79564e);
  *(undefined1 *)(iVar2 + 0x79564e) = 0;
  *(undefined2 *)(param_2 + 2) = *(undefined2 *)(&DAT_00794c50 + iVar2);
  *(undefined2 *)(&DAT_00794c50 + iVar2) = 0;
  uVar1 = greenap_get_capability(iVar2);
  param_2[5] = uVar1;
  greenap_set_capability(iVar2,0);
  sys_ad_move_mem(param_2 + 6,"SetPartProfileParameters" + iVar2 + 0x18,2);
  if (*(char *)(param_1 + 0x34) != '\0') {
    sys_ad_move_mem(param_2 + 8,"SetPartProfileParameters" + iVar2 + 0x1a,8);
  }
  if ((*(uint *)(iVar2 + 0x795124) & 0x10) == 0) {
    param_2[4] = 0;
  }
  else {
    param_2[4] = 1;
  }
  return 0;
}

