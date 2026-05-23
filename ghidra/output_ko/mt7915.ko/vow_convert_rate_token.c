// module: mt7915.ko
// function: vow_convert_rate_token @ 0x42cac
// size: 132 bytes
//

short vow_convert_rate_token(int param_1,int param_2,int param_3)

{
  uint uVar1;
  short sVar2;
  int iVar3;
  uint uVar4;
  
  iVar3 = param_1 + param_3 * 0x1c;
  uVar1 = 1 << *(sbyte *)(param_1 + 0xa7a2ee);
  if (param_2 == 1) {
    uVar4 = iVar3 + 0xa79828;
  }
  else {
    uVar4 = (uint)*(ushort *)(iVar3 + 0xa79828);
  }
  if (param_2 == 1) {
    uVar4 = (uint)*(ushort *)(uVar4 + 2);
  }
  sVar2 = (short)uVar1 * (short)uVar4;
  if (2 < DebugLevel) {
    printk("%s: period %dus, rate %u, token %u\n","vow_convert_rate_token",uVar1 & 0xffff,uVar4,
           sVar2);
  }
  return sVar2;
}

