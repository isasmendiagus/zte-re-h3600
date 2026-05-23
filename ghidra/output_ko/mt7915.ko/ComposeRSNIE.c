// module: mt7915.ko
// function: ComposeRSNIE @ 0xb34d4
// size: 176 bytes
//

void ComposeRSNIE(undefined4 param_1,int param_2,int *param_3,int param_4)

{
  undefined1 *puVar1;
  int *piVar2;
  undefined1 *puVar3;
  int iVar4;
  int local_2c [2];
  
  iVar4 = *param_3;
  puVar1 = (undefined1 *)(param_2 + 0x5ce);
  piVar2 = (int *)(param_2 + 0x5c0);
  local_2c[0] = 0;
  puVar3 = (undefined1 *)(param_2 + 0x5d0);
  do {
    piVar2 = piVar2 + 1;
    if (*piVar2 != 0) {
      MakeOutgoingFrame(param_4 + iVar4,local_2c,1,puVar1 + -2,1,puVar1,*puVar1,puVar3,0xffffffff);
      iVar4 = iVar4 + local_2c[0];
    }
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 0xff;
  } while (puVar1 != (undefined1 *)(param_2 + 0x5d0));
  *param_3 = iVar4;
  return;
}

