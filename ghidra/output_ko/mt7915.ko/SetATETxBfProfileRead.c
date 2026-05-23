// module: mt7915.ko
// function: SetATETxBfProfileRead @ 0x266cec
// size: 304 bytes
//

undefined4 SetATETxBfProfileRead(undefined4 param_1,char *param_2)

{
  size_t sVar1;
  undefined4 uVar2;
  byte *__s;
  ushort *puVar3;
  undefined4 local_48;
  char local_44 [12];
  char acStack_38 [36];
  
  local_48 = 0;
  if ((param_2 == (char *)0x0) || (sVar1 = strlen(param_2), sVar1 != 7)) {
LAB_00266d1c:
    uVar2 = 0;
  }
  else {
    __s = (byte *)rstrtok(param_2,&_LC2);
    if (__s != (byte *)0x0) {
      puVar3 = (ushort *)&local_48;
      do {
        sVar1 = strlen((char *)__s);
        if ((((sVar1 != 3) || (((&_ctype)[*__s] & 0x44) == 0)) || (((&_ctype)[__s[1]] & 0x44) == 0))
           || (((&_ctype)[__s[2]] & 0x44) == 0)) goto LAB_00266d1c;
        local_44[0] = '0';
        local_44[1] = '\0';
        strncat(local_44,(char *)__s,3);
        AtoH(local_44,puVar3,2);
        *puVar3 = *puVar3 << 8 | *puVar3 >> 8;
        __s = (byte *)rstrtok(0,&_LC2);
        puVar3 = puVar3 + 1;
      } while (__s != (byte *)0x0);
    }
    snprintf(acStack_38,0xb,"%.2x:01:%.2x:%.2x",local_48 & 0xff,(uint)(local_48._2_2_ >> 8),
             local_48._2_2_ & 0xff);
    Set_TxBfProfileDataRead(param_1,acStack_38);
    uVar2 = 1;
  }
  return uVar2;
}

