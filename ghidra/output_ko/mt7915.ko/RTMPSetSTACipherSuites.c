// module: mt7915.ko
// function: RTMPSetSTACipherSuites @ 0xef46c
// size: 60 bytes
//

void RTMPSetSTACipherSuites(undefined4 param_1,undefined4 param_2,undefined2 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = GetStaCfgByWdev();
  if (iVar1 == 0) {
    return;
  }
  uVar2 = SecEncryModeOldToNew(param_3);
  *(undefined4 *)(iVar1 + 0x2124cc) = uVar2;
  uVar2 = SecEncryModeOldToNew(param_3);
  *(undefined4 *)(iVar1 + 0x2124d0) = uVar2;
  return;
}

