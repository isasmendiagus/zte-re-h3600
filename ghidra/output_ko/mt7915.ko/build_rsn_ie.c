// module: mt7915.ko
// function: build_rsn_ie @ 0x146df0
// size: 264 bytes
//

int build_rsn_ie(undefined4 param_1,int param_2,undefined1 *param_3)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  byte *pbVar4;
  byte *__src;
  
  if (*(int *)(param_2 + 0x14) == 1) {
    iVar2 = 0;
    piVar3 = (int *)(param_2 + 0x5c4);
    iVar1 = *piVar3;
    pbVar4 = (byte *)(param_2 + 0x5ce);
    __src = (byte *)(param_2 + 0x5d0);
    while( true ) {
      if (iVar1 != 0) {
        param_3[iVar2] = pbVar4[-2];
        param_3[iVar2 + 1] = *pbVar4;
        memmove(param_3 + iVar2 + 2,__src,(uint)*pbVar4);
        iVar2 = (uint)*pbVar4 + iVar2 + 2;
      }
      pbVar4 = pbVar4 + 1;
      __src = __src + 0xff;
      if (pbVar4 == (byte *)(param_2 + 0x5d0)) break;
      piVar3 = piVar3 + 1;
      iVar1 = *piVar3;
    }
  }
  else if (*(int *)(param_2 + 0x14) == 4) {
    iVar1 = GetStaCfgByWdev();
    iVar2 = 0;
    if ((*(uint *)(param_2 + 0x2c) & 0x20) != 0) {
      *param_3 = 0xdd;
      if (iVar1 != 0) {
        param_3[1] = *(undefined1 *)(iVar1 + 0x213038);
        memmove(param_3 + 2,(void *)(iVar1 + 0x213039),(uint)*(byte *)(iVar1 + 0x213038));
        return *(byte *)(iVar1 + 0x213038) + 2;
      }
      iVar2 = 1;
    }
  }
  else {
    iVar2 = 0;
  }
  return iVar2;
}

