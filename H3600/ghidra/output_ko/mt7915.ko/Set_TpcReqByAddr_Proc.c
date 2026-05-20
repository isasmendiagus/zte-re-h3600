// module: mt7915.ko
// function: Set_TpcReqByAddr_Proc @ 0x140254
// size: 284 bytes
//

undefined4 Set_TpcReqByAddr_Proc(undefined4 param_1,char *param_2)

{
  undefined2 *puVar1;
  undefined4 uVar2;
  size_t sVar3;
  byte *__s;
  undefined2 local_26;
  undefined2 local_24;
  undefined2 local_22;
  
  local_26 = 0;
  local_24 = 0;
  local_22 = 0;
  uVar2 = RandomByte();
  sVar3 = strlen(param_2);
  if (sVar3 == 0x11) {
    if (2 < DebugLevel) {
      printk("%s: TpcReqToken = %d (0x%02X)\n","Set_TpcReqByAddr_Proc",uVar2,uVar2);
    }
    __s = (byte *)rstrtok(param_2,&_LC30);
    puVar1 = &local_26;
    while (__s != (byte *)0x0) {
      sVar3 = strlen((char *)__s);
      if (((sVar3 != 2) || (((&_ctype)[*__s] & 0x44) == 0)) || (((&_ctype)[__s[1]] & 0x44) == 0))
      goto LAB_0014028c;
      AtoH(__s,puVar1);
      __s = (byte *)rstrtok(0,&_LC30);
      puVar1 = (undefined2 *)((int)puVar1 + 1);
    }
    FUN_0013e0f8(param_1,uVar2);
    EnqueueTPCReq(param_1,&local_26,uVar2);
    uVar2 = 1;
  }
  else {
LAB_0014028c:
    uVar2 = 0;
  }
  return uVar2;
}

