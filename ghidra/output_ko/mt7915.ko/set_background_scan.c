// module: mt7915.ko
// function: set_background_scan @ 0xea4f4
// size: 124 bytes
//

undefined4 set_background_scan(int *param_1,undefined4 param_2)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  int *piVar4;
  
  iVar3 = *param_1;
  bVar1 = os_str_tol(param_2,0,10);
  if ((*(int *)(iVar3 + 0x38) - 0x100U & 0xfffffeff) != 0) {
    return 0;
  }
  piVar4 = param_1 + (uint)*(byte *)(iVar3 + 0x3c) * 0x160d + 0xadc92;
  if (piVar4 == (int *)0x0) {
    return 0;
  }
  cVar2 = HcGetBandByWdev(piVar4);
  BackgroundScanStart(param_1,piVar4,bVar1 | cVar2 << 4);
  return 1;
}

