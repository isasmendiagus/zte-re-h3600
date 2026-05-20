// module: mt7915.ko
// function: UpdateMbssCliLinkMap @ 0x83084
// size: 68 bytes
//

void UpdateMbssCliLinkMap(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  _raw_spin_lock_bh(&DAT_003686a4 + param_1);
  iVar1 = param_1 + param_2 * 8;
  *(undefined4 *)(&DAT_003686a8 + iVar1) = param_4;
  *(undefined4 *)(&DAT_003686ac + iVar1) = param_3;
  _raw_spin_unlock_bh(&DAT_003686a4 + param_1);
  return;
}

