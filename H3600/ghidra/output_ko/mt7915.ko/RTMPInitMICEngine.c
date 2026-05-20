// module: mt7915.ko
// function: RTMPInitMICEngine @ 0x117580
// size: 160 bytes
//

void RTMPInitMICEngine(int param_1,undefined4 param_2,undefined1 *param_3,undefined1 *param_4,
                      byte param_5,undefined4 param_6)

{
  undefined1 *puVar1;
  undefined4 *puVar2;
  undefined1 *puVar3;
  undefined4 local_1c;
  
  param_1 = param_1 + 0xa39f14;
  local_1c = (uint)param_5;
  RTMPTkipSetMICKey(param_1,param_6);
  puVar1 = param_3;
  do {
    puVar3 = puVar1 + 1;
    RTMPTkipAppendByte(param_1,*puVar1);
    puVar1 = puVar3;
  } while (puVar3 != param_3 + 6);
  puVar1 = param_4;
  do {
    puVar3 = puVar1 + 1;
    RTMPTkipAppendByte(param_1,*puVar1);
    puVar1 = puVar3;
  } while (puVar3 != param_4 + 6);
  puVar2 = &local_1c;
  RTMPTkipAppendByte(param_1,param_5);
  while (puVar2 != (undefined4 *)((int)&local_1c + 3)) {
    puVar2 = (undefined4 *)((int)puVar2 + 1);
    RTMPTkipAppendByte(param_1,*(undefined1 *)puVar2);
  }
  return;
}

