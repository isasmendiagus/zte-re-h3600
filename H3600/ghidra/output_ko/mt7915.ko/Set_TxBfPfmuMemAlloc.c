// module: mt7915.ko
// function: Set_TxBfPfmuMemAlloc @ 0xe5c94
// size: 208 bytes
//

bool Set_TxBfPfmuMemAlloc(undefined4 param_1,char *param_2)

{
  bool bVar1;
  size_t sVar2;
  byte *__s;
  int iVar3;
  undefined2 *puVar4;
  undefined2 local_1a;
  
  local_1a = 0;
  sVar2 = strlen(param_2);
  if (sVar2 == 5) {
    __s = (byte *)rstrtok(param_2,&_LC232);
    if (__s != (byte *)0x0) {
      puVar4 = &local_1a;
      do {
        sVar2 = strlen((char *)__s);
        if (((sVar2 != 2) || (((&_ctype)[*__s] & 0x44) == 0)) || (((&_ctype)[__s[1]] & 0x44) == 0))
        goto LAB_000e5cbc;
        AtoH(__s,puVar4);
        __s = (byte *)rstrtok(0,&_LC232);
        puVar4 = (undefined2 *)((int)puVar4 + 1);
      } while (__s != (byte *)0x0);
    }
    iVar3 = CmdPfmuMemAlloc(param_1,(undefined1)local_1a,local_1a._1_1_);
    bVar1 = iVar3 == 0;
  }
  else {
LAB_000e5cbc:
    bVar1 = false;
  }
  return bVar1;
}

