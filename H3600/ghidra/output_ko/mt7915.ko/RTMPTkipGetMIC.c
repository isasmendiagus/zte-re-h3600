// module: mt7915.ko
// function: RTMPTkipGetMIC @ 0x1174fc
// size: 132 bytes
//

void RTMPTkipGetMIC(int *param_1)

{
  uint uVar1;
  int *piVar2;
  int *piVar3;
  
  RTMPTkipAppendByte(param_1,0x5a);
  RTMPTkipAppendByte(param_1,0);
  RTMPTkipAppendByte(param_1,0);
  RTMPTkipAppendByte(param_1,0);
  do {
    RTMPTkipAppendByte(param_1,0);
  } while (*param_1 != 0);
  uVar1 = param_1[5];
  piVar3 = param_1 + 0xc;
  do {
    piVar2 = (int *)((int)piVar3 + 1);
    *(char *)piVar3 = (char)uVar1;
    uVar1 = uVar1 >> 8;
    piVar3 = piVar2;
  } while (piVar2 != param_1 + 0xd);
  uVar1 = param_1[6];
  do {
    piVar3 = (int *)((int)piVar2 + 1);
    *(char *)piVar2 = (char)uVar1;
    uVar1 = uVar1 >> 8;
    piVar2 = piVar3;
  } while (piVar3 != param_1 + 0xe);
  return;
}

