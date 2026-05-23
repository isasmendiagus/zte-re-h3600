// module: mt7915.ko
// function: WscGenRandomKey @ 0x1e8d6c
// size: 296 bytes
//

void WscGenRandomKey(undefined4 param_1,int param_2,char *param_3,undefined2 *param_4)

{
  undefined4 uVar1;
  uint uVar2;
  char cVar3;
  char *pcVar4;
  char *pcVar5;
  undefined2 uVar6;
  uint uVar7;
  undefined2 local_23;
  
  __memzero(param_3,0x40);
  uVar7 = *(uint *)(param_2 + 0x2a1c);
  if (uVar7 == 0) {
    pcVar4 = param_3;
    do {
      __memzero(&local_23,3);
      uVar1 = RandomByte(param_1);
      snprintf((char *)&local_23,3,"%02x",uVar1);
      pcVar5 = pcVar4 + 2;
      *(undefined2 *)pcVar4 = local_23;
      pcVar4 = pcVar5;
    } while (pcVar5 != param_3 + 0x40);
    *param_4 = 0x40;
    return;
  }
  if (uVar7 == 1) {
    cVar3 = '\x15';
    uVar7 = RandomByte(param_1);
    do {
      uVar7 = uVar7 & 0x3f;
      if (7 < uVar7) goto LAB_001e8e08;
      uVar7 = RandomByte(param_1);
      cVar3 = cVar3 + -1;
    } while (cVar3 != '\0');
    uVar7 = 8;
  }
  else {
    uVar7 = uVar7 & 0xff;
    if (uVar7 == 0) {
      uVar6 = 0;
      goto LAB_001e8e4c;
    }
  }
LAB_001e8e08:
  uVar6 = (undefined2)uVar7;
  pcVar4 = param_3;
  do {
    uVar2 = RandomByte(param_1);
    pcVar5 = pcVar4 + 1;
    *pcVar4 = (char)uVar2 + (char)(uVar2 / 0x5e) * -0x5e + '!';
    pcVar4 = pcVar5;
  } while (((int)pcVar5 - (int)param_3 & 0xffU) < uVar7);
LAB_001e8e4c:
  *param_4 = uVar6;
  return;
}

