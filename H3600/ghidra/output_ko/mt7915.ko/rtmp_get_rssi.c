// module: mt7915.ko
// function: rtmp_get_rssi @ 0x135960
// size: 312 bytes
//

undefined4 rtmp_get_rssi(int param_1,uint param_2,void *param_3,size_t param_4)

{
  uint uVar1;
  uint uVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  uVar4 = 0;
  do {
    uVar1 = HcGetMaxStaNum(param_1);
    uVar2 = uVar4 & 0xffff;
    uVar4 = uVar4 + 1;
    iVar5 = uVar2 * 0x14c0;
    iVar6 = param_1 + iVar5;
    if (uVar1 <= uVar2) {
      return 1;
    }
    piVar3 = (int *)(param_1 + iVar5 + 0xa1d20);
  } while (((piVar3 == (int *)0x0) || (*(int *)(iVar6 + 0xa1d20) == 0)) ||
          (*(ushort *)(iVar6 + 0xa1e00) != param_2));
  if ((piVar3[2] != 0) && (iVar5 = *(int *)(piVar3[2] + 0x14), iVar5 == 2 || iVar5 == 0x100)) {
    if ((piVar3[0x4d9] == 0) && (piVar3[0x4d8] == 0)) {
      iVar5 = GetStaCfgByWdev(param_1);
      if (iVar5 == 0) {
        if (param_4 != 0) {
          memset(param_3,-0x7f,param_4);
        }
      }
      else {
        memmove(param_3,(void *)(iVar5 + 0x2137ac),param_4);
      }
    }
    else {
      memmove(param_3,piVar3 + 0x4a,param_4);
    }
  }
  if (*piVar3 != 0x20001) {
    return 0;
  }
  memmove(param_3,piVar3 + 0x4a,param_4);
  return 0;
}

