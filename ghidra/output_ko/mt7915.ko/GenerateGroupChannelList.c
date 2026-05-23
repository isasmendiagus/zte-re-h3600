// module: mt7915.ko
// function: GenerateGroupChannelList @ 0x22d9e4
// size: 280 bytes
//

void GenerateGroupChannelList(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char *pcVar1;
  char cVar2;
  char cVar3;
  int iVar4;
  byte bVar5;
  int iVar6;
  
  iVar6 = param_1 + 0xa78ad4;
  if (2 < DebugLevel) {
    printk("%s ChannelListNum=%d\n","GenerateGroupChannelList",*(undefined1 *)(param_1 + 0xa78ad1),
           DebugLevel,param_4);
  }
  os_zero_mem(param_1 + 0xa79234,0x3b0);
  cVar3 = '\0';
  *(undefined1 *)(param_1 + 0xa795e4) = 0;
  if (*(char *)(param_1 + 0xa78ad1) == '\0') {
    return;
  }
  bVar5 = 0;
  do {
    if (cVar3 == '\0') {
LAB_0022da90:
      GroupChListInsert(param_1,iVar6);
    }
    else {
      if (*(char *)(param_1 + 0xa79235) == *(char *)(iVar6 + 2)) {
        cVar2 = '\0';
      }
      else {
        cVar2 = '\0';
        iVar4 = param_1 + 0xa79234;
        do {
          cVar2 = cVar2 + '\x01';
          if (cVar2 == cVar3) goto LAB_0022da90;
          pcVar1 = (char *)(iVar4 + 0x11);
          iVar4 = iVar4 + 0x10;
        } while (*pcVar1 != *(char *)(iVar6 + 2));
        if (cVar2 == -1) goto LAB_0022da90;
      }
      GroupChListUpdate(param_1,cVar2,iVar6);
    }
    bVar5 = bVar5 + 1;
    iVar6 = iVar6 + 0x18;
    if (*(byte *)(param_1 + 0xa78ad1) <= bVar5) {
      return;
    }
    cVar3 = *(char *)(param_1 + 0xa795e4);
  } while( true );
}

