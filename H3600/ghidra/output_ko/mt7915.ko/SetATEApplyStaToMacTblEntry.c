// module: mt7915.ko
// function: SetATEApplyStaToMacTblEntry @ 0x2646d4
// size: 116 bytes
//

undefined4 SetATEApplyStaToMacTblEntry(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (uint)*(byte *)(param_1 + 0xa7865d) * 0x14c0;
  iVar2 = param_1 + iVar1 + 0xa2a30;
  os_move_mem((void *)(iVar2 + 4),(void *)(param_1 + 0xa78676),4);
  os_move_mem((void *)(param_1 + iVar1 + 0xa29c4),(void *)(param_1 + 0xa78674),2);
  os_move_mem((void *)(iVar2 + 8),(void *)(param_1 + 0xa7867a),8);
  return 1;
}

