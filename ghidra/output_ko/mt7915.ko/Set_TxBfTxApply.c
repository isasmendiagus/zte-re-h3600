// module: mt7915.ko
// function: Set_TxBfTxApply @ 0xe5938
// size: 240 bytes
//

undefined4 Set_TxBfTxApply(undefined4 param_1,char *param_2)

{
  size_t sVar1;
  undefined4 uVar2;
  byte *__s;
  undefined1 *puVar3;
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
  sVar1 = strlen(param_2);
  if (sVar1 == 0xe) {
    __s = (byte *)rstrtok(param_2,&_LC232);
    if (__s != (byte *)0x0) {
      puVar3 = &local_1d;
      do {
        sVar1 = strlen((char *)__s);
        if (((sVar1 != 2) || (((&_ctype)[*__s] & 0x44) == 0)) || (((&_ctype)[__s[1]] & 0x44) == 0))
        goto LAB_000e5970;
        AtoH(__s,puVar3);
        __s = (byte *)rstrtok(0,&_LC232);
        puVar3 = puVar3 + 1;
      } while (__s != (byte *)0x0);
    }
    CmdTxBfTxApplyCtrl(param_1,local_1d,local_1c,local_1b,local_1a,local_19);
    uVar2 = 1;
  }
  else {
LAB_000e5970:
    uVar2 = 0;
  }
  return uVar2;
}

