// module: mt7915.ko
// function: Set_DisConnectSta_Proc @ 0x32a5c
// size: 396 bytes
//

undefined4 Set_DisConnectSta_Proc(int *param_1,char *param_2)

{
  undefined1 *puVar1;
  size_t sVar2;
  undefined4 uVar3;
  int iVar4;
  byte *__s;
  int iVar5;
  int iVar6;
  undefined1 auStack_26 [10];
  
  sVar2 = strlen(param_2);
  iVar6 = *param_1;
  if (((sVar2 == 0x11) &&
      (iVar5 = *(int *)(iVar6 + 0x3c), iVar4 = hc_get_chip_bcn_max_num(param_1[0x29e5e8]),
      iVar5 < iVar4)) && (*(int *)(iVar6 + 0x3c) < 0x20)) {
    __s = (byte *)rstrtok(param_2,&_LC162);
    puVar1 = auStack_26;
    while (__s != (byte *)0x0) {
      sVar2 = strlen((char *)__s);
      if (((sVar2 != 2) || (((&_ctype)[*__s] & 0x44) == 0)) || (((&_ctype)[__s[1]] & 0x44) == 0))
      goto LAB_00032a80;
      AtoH(__s,puVar1);
      __s = (byte *)rstrtok(0,&_LC162);
      puVar1 = puVar1 + 1;
    }
    iVar4 = memcmp(auStack_26,&BROADCAST_ADDR,6);
    if (iVar4 == 0) {
      Set_DisConnectAllSta_Proc(param_1,&_LC40);
      uVar3 = 1;
    }
    else {
      iVar4 = MacTableLookup(param_1,auStack_26);
      if (iVar4 != 0) {
        if (2 < DebugLevel) {
          printk("I/F(ra%d) Set_DisConnectSta_Proc::apidx=%d\n",*(undefined4 *)(iVar6 + 0x3c),
                 *(undefined1 *)(iVar4 + 0xe5));
        }
        if ((uint)*(byte *)(iVar4 + 0xe5) == *(uint *)(iVar6 + 0x3c)) {
          __MlmeDeAuthAction(param_1,iVar4,0xc,0,"Set_DisConnectSta_Proc",0x4829);
        }
      }
      uVar3 = 1;
    }
  }
  else {
LAB_00032a80:
    uVar3 = 0;
  }
  return uVar3;
}

