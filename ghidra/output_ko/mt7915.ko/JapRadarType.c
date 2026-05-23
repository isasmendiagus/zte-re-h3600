// module: mt7915.ko
// function: JapRadarType @ 0x100ec4
// size: 180 bytes
//

char JapRadarType(int param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined4 local_1f;
  undefined4 local_1b;
  undefined4 local_17;
  undefined2 local_13;
  undefined1 local_11;
  
  local_1f = 0x403c3834;
  local_1b = 0x706c6864;
  local_17 = 0x807c7874;
  local_13 = 0x8884;
  local_11 = 0x8c;
  iVar2 = HcIsRfSupport(param_1,2);
  uVar3 = HcGetChannelByRf(param_1,2);
  cVar1 = *(char *)(param_1 + 0x795075);
  if (cVar1 == '\x02') {
    uVar4 = 0;
    while ((iVar2 == 0 || (*(byte *)((int)&local_1f + uVar4) != uVar3))) {
      uVar4 = uVar4 + 1;
      if (uVar4 == 0xf) {
        return '\x02';
      }
    }
    if (uVar4 < 4) {
      cVar1 = '\x03';
    }
    else {
      cVar1 = '\x04';
    }
  }
  return cVar1;
}

