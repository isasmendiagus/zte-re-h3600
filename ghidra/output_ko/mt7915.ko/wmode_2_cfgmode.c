// module: mt7915.ko
// function: wmode_2_cfgmode @ 0xb8084
// size: 120 bytes
//

undefined2 wmode_2_cfgmode(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  ushort *puVar1;
  int iVar2;
  undefined2 *puVar3;
  
  iVar2 = 0;
  puVar3 = &DAT_002942d0;
  do {
    puVar1 = puVar3 + 1;
    puVar3 = puVar3 + 2;
    if (*puVar1 == param_1) {
      return (&DAT_002942d0)[iVar2];
    }
    iVar2 = iVar2 + 2;
  } while (iVar2 != 0x2e);
  if (DebugLevel < 0) {
    return 0;
  }
  printk("%s(): Cannot get cfgmode by wmode(%x)\n","wmode_2_cfgmode",param_1,DebugLevel,param_4);
  return 0;
}

