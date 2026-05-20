// module: mt7915.ko
// function: iwprivPhyStatHelp @ 0x348ec
// size: 304 bytes
//

uint iwprivPhyStatHelp(char *param_1,int param_2)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  char acStack_7c [100];
  
  memset(acStack_7c,0,100);
  builtin_strncpy(param_1," available commands:\n",0x16);
  uVar3 = 0x15;
  _LANCHOR1 = &DAT_0032a9ec;
  uVar1 = DAT_0032a9ec;
  while( true ) {
    if (1 < uVar1) {
      if ((0 < DebugLevel) &&
         (printk("%s iwpriv ra0 phystate read(write)=Idx \n","iwprivPhyStatHelp"), 0 < DebugLevel))
      {
        printk("%s\n%s\n","iwprivPhyStatHelp",param_1);
      }
      return uVar3;
    }
    uVar2 = snprintf(acStack_7c,100,"\t%d  %s\n",(uint)uVar1,*(undefined4 *)(_LANCHOR1 + 4));
    uVar2 = uVar3 + (uVar2 & 0xffff);
    uVar3 = uVar2 & 0xffff;
    if (param_2 <= (int)uVar2) break;
    strcat(param_1,acStack_7c);
    uVar1 = _LANCHOR1[6];
    _LANCHOR1 = _LANCHOR1 + 6;
  }
  return 0;
}

