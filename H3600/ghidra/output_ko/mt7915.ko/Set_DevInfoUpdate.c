// module: mt7915.ko
// function: Set_DevInfoUpdate @ 0xe6c04
// size: 276 bytes
//

bool Set_DevInfoUpdate(undefined4 param_1,char *param_2)

{
  bool bVar1;
  size_t sVar2;
  byte *__s;
  int iVar3;
  undefined4 *puVar4;
  undefined1 local_26;
  undefined1 local_25;
  undefined1 local_24;
  undefined1 local_23;
  undefined1 local_22;
  undefined1 local_21;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_20 = 0;
  local_1c = 0;
  sVar2 = strlen(param_2);
  if (sVar2 == 0x17) {
    __s = (byte *)rstrtok(param_2,&_LC232);
    if (__s != (byte *)0x0) {
      puVar4 = &local_20;
      do {
        sVar2 = strlen((char *)__s);
        if (((sVar2 != 2) || (((&_ctype)[*__s] & 0x44) == 0)) || (((&_ctype)[__s[1]] & 0x44) == 0))
        goto LAB_000e6c30;
        AtoH(__s,puVar4);
        __s = (byte *)rstrtok(0,&_LC232);
        puVar4 = (undefined4 *)((int)puVar4 + 1);
      } while (__s != (byte *)0x0);
    }
    local_26 = local_20._1_1_;
    local_25 = local_20._2_1_;
    local_24 = local_20._3_1_;
    local_23 = (undefined1)local_1c;
    local_22 = local_1c._1_1_;
    local_21 = local_1c._2_1_;
    iVar3 = AsicDevInfoUpdate(param_1,local_20 & 0xff,&local_26,local_1c._3_1_,1,1);
    bVar1 = iVar3 == 0;
  }
  else {
LAB_000e6c30:
    bVar1 = false;
  }
  return bVar1;
}

