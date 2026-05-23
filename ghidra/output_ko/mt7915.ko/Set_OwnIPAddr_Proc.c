// module: mt7915.ko
// function: Set_OwnIPAddr_Proc @ 0x32bec
// size: 76 bytes
//

undefined4 Set_OwnIPAddr_Proc(int *param_1)

{
  if ((uint)*(byte *)((int)param_1 + 0x2b7242) <= (uint)*(byte *)(*param_1 + 0x3c)) {
    return 0;
  }
  SetWdevOwnIPAddr(param_1 + (uint)*(byte *)(*param_1 + 0x3c) * 0x160d + 0xadc9d);
  return 1;
}

