// module: mt7915.ko
// function: MsgTypeSubst @ 0x12de38
// size: 528 bytes
//

int MsgTypeSubst(int param_1,byte *param_2,undefined4 *param_3,uint *param_4)

{
  int iVar1;
  
  if ((*param_2 & 0xc) == 8) {
    if (4 < *(int *)(&DAT_0036ee4c + param_1)) {
      *param_3 = 0x11;
      iVar1 = WscMsgTypeSubst(param_2[0x21],param_2[0x24],param_4);
      if (iVar1 != 0) {
        return iVar1;
      }
    }
    *param_3 = 0x17;
    iVar1 = WpaMsgTypeSubst(param_2[0x21],param_4);
    return iVar1;
  }
  switch(*param_2 >> 4) {
  case 0:
    iVar1 = 1;
    *param_3 = 1;
    *param_4 = 4;
    break;
  case 1:
    iVar1 = 1;
    *param_3 = 1;
    *param_4 = 5;
    break;
  case 2:
    iVar1 = 1;
    *param_3 = 1;
    *param_4 = 6;
    break;
  case 3:
    iVar1 = 1;
    *param_3 = 1;
    *param_4 = 7;
    break;
  case 4:
    iVar1 = 1;
    *param_3 = 4;
    *param_4 = 4;
    break;
  case 5:
    *param_3 = 4;
    iVar1 = 1;
    *param_4 = 5;
    break;
  case 8:
    *param_3 = 4;
    iVar1 = 1;
    *param_4 = 6;
    break;
  case 10:
    iVar1 = 1;
    *param_3 = 1;
    *param_4 = 3;
    break;
  case 0xb:
    if (*(ushort *)(param_2 + 0x18) == 3) {
      *param_3 = 2;
      *param_4 = 9;
      return 1;
    }
    if ((*(ushort *)(param_2 + 0x1a) & 0xfffd) == 1) {
      *param_3 = 2;
      *param_4 = 2;
      return 1;
    }
    if ((*(ushort *)(param_2 + 0x1a) - 2 & 0xfffd) == 0) {
      if (*(ushort *)(param_2 + 0x18) < 2) {
        *param_3 = 2;
        *param_4 = 1;
        return 1;
      }
      return 1;
    }
  default:
    iVar1 = 0;
    break;
  case 0xc:
    *param_3 = 2;
    iVar1 = 1;
    *param_4 = 4;
    break;
  case 0xd:
  case 0xe:
    *param_3 = 9;
    if ((param_2[0x18] & 0x7f) < 0x17) {
      *param_4 = param_2[0x18] & 0x7f;
    }
    else {
      *param_4 = 0x1f;
    }
    iVar1 = 1;
  }
  return iVar1;
}

