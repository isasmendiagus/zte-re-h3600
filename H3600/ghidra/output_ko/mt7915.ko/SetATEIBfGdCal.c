// module: mt7915.ko
// function: SetATEIBfGdCal @ 0x266f7c
// size: 272 bytes
//

bool SetATEIBfGdCal(undefined4 param_1,char *param_2)

{
  bool bVar1;
  size_t sVar2;
  byte *__s;
  int iVar3;
  undefined4 *puVar4;
  undefined4 local_1c;
  
  local_1c = 0;
  if ((param_2 == (char *)0x0) || (sVar2 = strlen(param_2), sVar2 != 0xb)) {
LAB_00266fac:
    bVar1 = false;
  }
  else {
    __s = (byte *)rstrtok(param_2,&_LC2);
    if (__s != (byte *)0x0) {
      puVar4 = &local_1c;
      do {
        sVar2 = strlen((char *)__s);
        if (((sVar2 != 2) || (((&_ctype)[*__s] & 0x44) == 0)) || (((&_ctype)[__s[1]] & 0x44) == 0))
        goto LAB_00266fac;
        AtoH(__s,puVar4);
        __s = (byte *)rstrtok(0,&_LC2);
        puVar4 = (undefined4 *)((int)puVar4 + 1);
      } while (__s != (byte *)0x0);
    }
    if (-1 < DebugLevel) {
      printk(&_LC324,"SetATEIBfGdCal");
    }
    iVar3 = CmdITxBfPhaseCal(param_1,local_1c & 0xff,local_1c._1_1_,local_1c._2_1_,local_1c >> 0x18,
                             0);
    bVar1 = iVar3 == 0;
  }
  return bVar1;
}

