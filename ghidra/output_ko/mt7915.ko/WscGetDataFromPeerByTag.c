// module: mt7915.ko
// function: WscGetDataFromPeerByTag @ 0x1f2954
// size: 164 bytes
//

undefined4
WscGetDataFromPeerByTag
          (undefined4 param_1,uint *param_2,int param_3,uint param_4,void *param_5,
          undefined2 *param_6)

{
  uint uVar1;
  ushort uStack_b;
  
  if (param_3 < 1) {
    return 0;
  }
  do {
    uVar1 = *param_2;
    uStack_b = (ushort)(uVar1 >> 0x10);
    if (((uVar1 & 0xff) << 8 | uVar1 >> 8 & 0xff) == param_4) {
      uVar1 = (uStack_b & 0xff) << 8 | (uint)(uStack_b >> 8);
      if (param_6 != (undefined2 *)0x0) {
        *param_6 = (short)uVar1;
      }
      memmove(param_5,param_2 + 1,uVar1);
      return 1;
    }
    uVar1 = (uStack_b & 0xff) << 8 | (uint)(uStack_b >> 8);
    param_3 = param_3 + (-4 - uVar1);
    param_2 = (uint *)((int)param_2 + uVar1 + 4);
  } while (0 < param_3);
  return 0;
}

