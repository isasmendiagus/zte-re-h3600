// module: mt7915.ko
// function: ApCliMsgTypeSubst @ 0x6978c
// size: 480 bytes
//

uint ApCliMsgTypeSubst(int param_1,byte *param_2,undefined4 *param_3,uint *param_4)

{
  byte bVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  bVar1 = *param_2;
  uVar5 = bVar1 & 0xc;
  if ((param_2[1] & 3) == 3) {
    iVar4 = 0x1e;
  }
  else {
    iVar4 = 0x18;
  }
  if (uVar5 != 8) {
    if ((bVar1 & 0xc) != 0) {
      return 0;
    }
    switch(bVar1 >> 4) {
    case 1:
      uVar5 = 1;
      *param_3 = 1;
      *param_4 = 5;
      break;
    case 3:
      uVar5 = 1;
      *param_3 = 1;
      *param_4 = 7;
      break;
    case 10:
      uVar5 = 1;
      *param_3 = 1;
      *param_4 = 3;
      break;
    case 0xb:
      if (*(short *)(param_2 + 0x18) == 3) {
        *param_3 = 2;
        uVar5 = 1;
        *param_4 = 9;
      }
      else {
        if ((*(short *)(param_2 + 0x1a) - 2U & 0xfffd) != 0) {
          return 0;
        }
        uVar5 = 1;
        *param_3 = 2;
        *param_4 = 1;
      }
      break;
    case 0xc:
      *param_3 = 2;
      uVar5 = 1;
      *param_4 = 4;
      break;
    case 0xd:
      *param_3 = 9;
      uVar5 = 1;
      uVar3 = param_2[0x18] & 0x7f;
      if (0x16 < uVar3) {
        uVar3 = 0x1f;
      }
      *param_4 = uVar3;
    }
    return uVar5;
  }
  piVar2 = (int *)MacTableLookup(param_1,param_2 + 10);
  if (((piVar2 != (int *)0x0) && (*piVar2 == 2)) &&
     (*(int *)(&DAT_0036ee3c + param_1 + (uint)*(byte *)(piVar2 + 0x39) * 0x2137b0) == 1)) {
    *param_3 = 0x11;
    uVar5 = WscMsgTypeSubst(param_2[iVar4 + 9],param_2[iVar4 + 0xc],param_4);
    if (uVar5 != 0) {
      return uVar5;
    }
  }
  *param_3 = 0x17;
  uVar5 = WpaMsgTypeSubst(param_2[iVar4 + 9],param_4);
  return uVar5;
}

