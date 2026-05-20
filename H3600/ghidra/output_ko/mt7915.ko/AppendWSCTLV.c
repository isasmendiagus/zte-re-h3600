// module: mt7915.ko
// function: AppendWSCTLV @ 0x1f3154
// size: 192 bytes
//

int AppendWSCTLV(uint param_1,ushort *param_2,void *param_3,uint param_4)

{
  ushort uVar1;
  ushort uVar2;
  
  uVar2 = (ushort)((param_1 & 0xff) << 8) | (ushort)(param_1 >> 8) & 0xff;
  if (param_4 == 0) {
    if (0x62 < (param_1 & 0xff)) {
      *param_2 = uVar2;
      param_2[1] = 0;
      return 4;
    }
    uVar1 = *(ushort *)(&_LANCHOR0 + (param_1 & 0xff) * 2);
    param_4 = (uint)uVar1;
    *param_2 = uVar2;
    param_2[1] = (ushort)((param_4 & 0xff) << 8) | uVar1 >> 8;
    if (param_4 == 0) {
      return 4;
    }
  }
  else {
    *param_2 = uVar2;
    param_2[1] = (ushort)((param_4 & 0xff) << 8) | (ushort)(param_4 >> 8) & 0xff;
  }
  memcpy(param_2 + 2,param_3,param_4);
  return param_4 + 4;
}

