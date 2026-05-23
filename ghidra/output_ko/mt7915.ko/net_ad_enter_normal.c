// module: mt7915.ko
// function: net_ad_enter_normal @ 0x25b490
// size: 212 bytes
//

undefined4
net_ad_enter_normal(int param_1,undefined1 *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    return 0x606;
  }
  *(undefined1 *)(iVar1 + 0x795071) = *param_2;
  *(undefined2 *)(&DAT_00794c50 + iVar1) = *(undefined2 *)(param_2 + 2);
  *(undefined4 *)(&DAT_0036db30 + iVar1) = 0;
  *(undefined4 *)(&DAT_0036db3c + iVar1) = 0;
  if (param_2[4] == '\0') {
    uVar2 = *(uint *)(iVar1 + 0x795124) & 0xffffffef;
  }
  else {
    uVar2 = *(uint *)(iVar1 + 0x795124) | 0x10;
  }
  *(uint *)(iVar1 + 0x795124) = uVar2;
  greenap_set_capability(iVar1,param_2[5],iVar1 + 0x794c00,uVar2,param_4);
  sys_ad_move_mem("SetPartProfileParameters" + iVar1 + 0x18,param_2 + 6,2);
  if (*(char *)(param_1 + 0x34) != '\0') {
    sys_ad_move_mem("SetPartProfileParameters" + iVar1 + 0x1a,param_2 + 8,8);
  }
  net_ad_startup_ap(param_1);
  *(undefined1 *)(iVar1 + 0x79564e) = param_2[1];
  return 0;
}

