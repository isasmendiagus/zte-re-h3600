// module: mt7915.ko
// function: init_default_ppe @ 0x20500c
// size: 168 bytes
//

void init_default_ppe(char *param_1,uint param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  os_alloc_mem(0,param_1 + 4,(int)(short)(param_3 << 1) * (int)(short)param_2 & 0xfe);
  iVar4 = *(int *)(param_1 + 4);
  if (iVar4 == 0) {
    return;
  }
  param_1[1] = (char)param_3;
  *param_1 = (char)param_2 + -1;
  if (param_2 == 0) {
    return;
  }
  uVar5 = 0;
  uVar1 = param_3 - 1U & 0xff;
  do {
    if (param_3 != 0) {
      iVar2 = iVar4 + 2;
      do {
        *(undefined1 *)(iVar2 + -2) = 0;
        iVar3 = iVar2 + 2;
        *(undefined1 *)(iVar2 + -1) = 7;
        iVar2 = iVar3;
      } while (iVar3 != iVar4 + (uVar1 + 2) * 2);
      iVar4 = iVar4 + (uVar1 + 1) * 2;
    }
    uVar5 = uVar5 + 1;
  } while ((uVar5 & 0xff) < param_2);
  return;
}

