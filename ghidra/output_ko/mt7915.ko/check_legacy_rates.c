// module: mt7915.ko
// function: check_legacy_rates @ 0x12f4f0
// size: 104 bytes
//

void check_legacy_rates(byte *param_1,byte *param_2,int param_3,undefined4 param_4)

{
  void *pvVar1;
  
  *param_2 = *param_1;
  pvVar1 = memmove(param_2 + 1,param_1 + 1,(uint)*param_1);
  RTMPCheckRates(pvVar1,param_2,*(undefined1 *)(param_3 + 0x18));
  param_2[0xd] = param_1[0xd];
  memmove(param_2 + 0xe,param_1 + 0xe,(uint)param_1[0xd]);
  RTMPCheckRates(param_2 + 0xe,param_2 + 0xd,*(undefined1 *)(param_3 + 0x18),param_4);
  return;
}

