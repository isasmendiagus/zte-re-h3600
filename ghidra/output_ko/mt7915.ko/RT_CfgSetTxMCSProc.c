// module: mt7915.ko
// function: RT_CfgSetTxMCSProc @ 0xb8c98
// size: 48 bytes
//

uint RT_CfgSetTxMCSProc(undefined4 param_1,undefined1 *param_2)

{
  uint uVar1;
  undefined1 extraout_r3;
  undefined1 uVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  
  uVar1 = os_str_tol(param_1,0,10);
  bVar5 = 0x1f < uVar1;
  bVar3 = uVar1 == 0x20;
  if (!bVar3) {
    bVar5 = 0x16 < uVar1;
  }
  bVar4 = uVar1 == 0x17;
  uVar2 = extraout_r3;
  if (!bVar5 || (bVar3 || bVar4)) {
    uVar2 = 0;
  }
  if (bVar5 && (!bVar3 && !bVar4)) {
    uVar2 = 1;
  }
  if (bVar5 && (!bVar3 && !bVar4)) {
    uVar1 = 0x21;
  }
  *param_2 = uVar2;
  return uVar1;
}

