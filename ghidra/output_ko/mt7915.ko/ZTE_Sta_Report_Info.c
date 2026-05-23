// module: mt7915.ko
// function: ZTE_Sta_Report_Info @ 0x160444
// size: 364 bytes
//

undefined4 ZTE_Sta_Report_Info(undefined4 param_1,char *param_2)

{
  undefined1 *puVar1;
  size_t sVar2;
  undefined4 uVar3;
  byte *__s;
  int iVar4;
  undefined1 auStack_6a [6];
  uint local_64;
  undefined4 local_60;
  undefined2 local_5c;
  undefined4 local_5a;
  undefined2 local_56;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_38;
  
  sVar2 = strlen(param_2);
  if (sVar2 == 0x11) {
    __s = (byte *)rstrtok(param_2,&_LC2);
    puVar1 = auStack_6a;
    while (__s != (byte *)0x0) {
      sVar2 = strlen((char *)__s);
      if (((sVar2 != 2) || (((&_ctype)[*__s] & 0x44) == 0)) || (((&_ctype)[__s[1]] & 0x44) == 0))
      goto LAB_00160464;
      AtoH(__s,puVar1);
      __s = (byte *)rstrtok(0,&_LC2);
      puVar1 = puVar1 + 1;
    }
    iVar4 = MacTableLookup(param_1,auStack_6a);
    if (iVar4 != 0) {
      __memzero(&local_64,0x3c);
      local_60 = *(undefined4 *)(iVar4 + 0xae0);
      local_5a = *(undefined4 *)(iVar4 + 0xec);
      local_64 = (uint)*(byte *)(iVar4 + 0xe5);
      local_5c = *(undefined2 *)(iVar4 + 0xae4);
      local_56 = *(undefined2 *)(iVar4 + 0xf0);
      local_48 = *(undefined4 *)(iVar4 + 0x1308);
      local_50 = *(undefined4 *)(iVar4 + 0x1318);
      local_4c = *(undefined4 *)(iVar4 + 0x1300);
      local_54 = *(undefined4 *)(iVar4 + 0x1310);
      local_44 = 0;
      local_40 = 0;
      local_38 = RTMPAvgRssi(param_1,iVar4 + 0x108);
      Kernel_ASEND("multiapd.map.slave",0xa2ba,&local_64,0x3c,0,0);
    }
    uVar3 = 1;
  }
  else {
LAB_00160464:
    uVar3 = 0;
  }
  return uVar3;
}

