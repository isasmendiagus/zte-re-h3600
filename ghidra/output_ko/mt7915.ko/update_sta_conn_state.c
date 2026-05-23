// module: mt7915.ko
// function: update_sta_conn_state @ 0x105218
// size: 64 bytes
//

void update_sta_conn_state(int param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  
  uVar1 = *(ushort *)(param_2 + 0xe2);
  iVar2 = *(int *)(param_1 + 8);
  FUN_0010412c();
  *(undefined1 *)(iVar2 + (uint)uVar1 * 0x620 + 0x2fa88) = 0;
  return;
}

