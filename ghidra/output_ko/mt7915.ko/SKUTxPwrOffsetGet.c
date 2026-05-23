// module: mt7915.ko
// function: SKUTxPwrOffsetGet @ 0x1521e0
// size: 532 bytes
//

int SKUTxPwrOffsetGet(int param_1,int param_2,int param_3,int param_4,byte param_5,byte param_6,
                     byte param_7)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  char cVar4;
  uint uVar5;
  byte local_1c [4];
  
  local_1c[0] = 0;
  local_1c[1] = 7;
  local_1c[2] = 0xe;
  local_1c[3] = 0x15;
  uVar5 = (uint)param_5;
  uVar3 = (uint)param_6;
  uVar2 = (uint)param_7;
  if (param_4 - 2U < 2) {
    uVar5 = uVar5 & 7;
    uVar3 = (param_5 >> 3) + 1;
    uVar1 = (uint)local_1c[param_3];
    switch(uVar5) {
    case 1:
    case 2:
      uVar1 = uVar1 + 9 & 0xff;
      break;
    case 3:
    case 4:
      uVar1 = uVar1 + 10 & 0xff;
      break;
    case 5:
      uVar1 = uVar1 + 0xb & 0xff;
      break;
    case 6:
      uVar1 = uVar1 + 0xc & 0xff;
      break;
    case 7:
      uVar1 = uVar1 + 0xd & 0xff;
      break;
    default:
      uVar1 = uVar1 + 7 & 0xff;
    }
  }
  else if (param_4 == 1) {
    if (uVar5 < 8) {
      uVar1 = (uint)(byte)(&DAT_0029a37c)[uVar5];
    }
    else {
      uVar1 = 2;
    }
  }
  else if (param_4 == 0) {
    uVar1 = (uint)(uVar5 - 2 < 2);
  }
  else if (param_4 == 4) {
    uVar1 = (uint)local_1c[param_3];
    switch(uVar5) {
    case 1:
    case 2:
      uVar1 = uVar1 + 0x16 & 0xff;
      break;
    case 3:
    case 4:
      uVar1 = uVar1 + 0x17 & 0xff;
      break;
    case 5:
    case 6:
      uVar1 = uVar1 + 0x18 & 0xff;
      break;
    case 7:
      uVar1 = uVar1 + 0x19 & 0xff;
      break;
    case 8:
      uVar1 = uVar1 + 0x1a & 0xff;
      break;
    case 9:
      uVar1 = uVar1 + 0x1b & 0xff;
      break;
    default:
      uVar1 = uVar1 + 0x15 & 0xff;
    }
  }
  else {
    uVar1 = 0;
  }
  if (uVar2 == 0) {
    cVar4 = *(char *)(param_1 + (param_2 * 0x31 + uVar1) * 4 + 0x794eb0);
  }
  else {
    cVar4 = *(char *)(param_1 + (param_2 * 0x31 + uVar1 + 0x1e53aa) * 4 + 5);
  }
  if ((2 < DebugLevel) &&
     (printk(&_LC40,"SKUTxPwrOffsetGet",param_3,param_4,uVar5,uVar3,uVar2), 2 < DebugLevel)) {
    printk(&_LC41,"SKUTxPwrOffsetGet",(int)cVar4,(int)cVar4,uVar5,uVar3,uVar2);
  }
  if (*(char *)(param_1 + 0xa3ba8c) == '\0') {
    cVar4 = '\0';
  }
  return (int)cVar4;
}

