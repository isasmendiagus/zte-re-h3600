// module: mt7915.ko
// function: SetATEIBfInstCal @ 0x267090
// size: 292 bytes
//

bool SetATEIBfInstCal(undefined4 param_1,char *param_2)

{
  bool bVar1;
  size_t sVar2;
  byte *__s;
  int iVar3;
  undefined1 *puVar4;
  undefined1 local_1d;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  undefined1 local_19;
  
  local_1d = 0;
  local_1c = 0;
  local_1b = 0;
  local_1a = 0;
  local_19 = 0;
  if ((param_2 == (char *)0x0) || (sVar2 = strlen(param_2), sVar2 != 0xe)) {
LAB_002670d0:
    bVar1 = false;
  }
  else {
    __s = (byte *)rstrtok(param_2,&_LC2);
    if (__s != (byte *)0x0) {
      puVar4 = &local_1d;
      do {
        sVar2 = strlen((char *)__s);
        if (((sVar2 != 2) || (((&_ctype)[*__s] & 0x44) == 0)) || (((&_ctype)[__s[1]] & 0x44) == 0))
        goto LAB_002670d0;
        AtoH(__s,puVar4);
        __s = (byte *)rstrtok(0,&_LC2);
        puVar4 = puVar4 + 1;
      } while (__s != (byte *)0x0);
    }
    if (-1 < DebugLevel) {
      printk(&_LC324,"SetATEIBfInstCal");
    }
    iVar3 = CmdITxBfPhaseCal(param_1,local_1d,local_1c,local_1b,local_1a,local_19);
    bVar1 = iVar3 == 0;
  }
  return bVar1;
}

