// module: mt7915.ko
// function: SetATEIBfPhaseComp @ 0x267cf0
// size: 264 bytes
//

bool SetATEIBfPhaseComp(undefined4 param_1,char *param_2)

{
  size_t sVar1;
  byte *__s;
  int iVar2;
  undefined2 *puVar3;
  undefined2 local_1e;
  undefined2 local_1c;
  undefined2 local_1a;
  
  local_1e = 0;
  local_1c = 0;
  local_1a = 0;
  if ((param_2 == (char *)0x0) || (sVar1 = strlen(param_2), sVar1 != 0xe && sVar1 != 0x11)) {
    return false;
  }
  __s = (byte *)rstrtok(param_2,&_LC2);
  if (__s != (byte *)0x0) {
    puVar3 = &local_1e;
    do {
      sVar1 = strlen((char *)__s);
      if (sVar1 != 2) {
        return false;
      }
      if (((&_ctype)[*__s] & 0x44) == 0) {
        return false;
      }
      if (((&_ctype)[__s[1]] & 0x44) == 0) {
        return false;
      }
      AtoH(__s,puVar3);
      __s = (byte *)rstrtok(0,&_LC2);
      puVar3 = (undefined2 *)((int)puVar3 + 1);
    } while (__s != (byte *)0x0);
  }
  iVar2 = CmdITxBfPhaseComp(param_1,(undefined1)local_1e,(char)local_1c == '\x01',local_1e._1_1_,
                            (char)local_1c,local_1c._1_1_,(undefined1)local_1a);
  return iVar2 == 0;
}

