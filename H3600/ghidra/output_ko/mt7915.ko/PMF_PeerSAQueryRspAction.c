// module: mt7915.ko
// function: PMF_PeerSAQueryRspAction @ 0x219b34
// size: 460 bytes
//

void PMF_PeerSAQueryRspAction(int param_1,int param_2)

{
  int iVar1;
  char *pcVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uStack_1b;
  short local_1a;
  
  if (*(char *)(param_2 + 0x19) != '\x01') {
    return;
  }
  if (-1 < DebugLevel) {
    printk("[PMF]%s : Receive SA Query Response\n","PMF_PeerSAQueryRspAction");
  }
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    iVar1 = MacTableLookup(param_1,param_2 + 10);
    if (*(char *)(param_1 + 0x286285) == '\0') goto LAB_002196a4;
LAB_002196b8:
    if (iVar1 != 0) {
      if (*(char *)(iVar1 + 0x562) == '\0') {
        if (DebugLevel < 0) {
          return;
        }
        uVar3 = *(undefined1 *)(param_2 + 10);
        uVar4 = *(undefined1 *)(param_2 + 0xb);
        pcVar2 = "[PMF]%s : Entry is not PMF capable, STA(%02x:%02x:%02x:%02x:%02x:%02x)\n";
      }
      else {
        local_1a = *(short *)(param_2 + 0x1a);
        if (*(short *)(iVar1 + 0x629) != local_1a) {
          if (DebugLevel < 0) {
            return;
          }
          printk("[PMF]%s - Compare TransactionID wrong, STA(%02x:%02x:%02x:%02x:%02x:%02x), AP TransactionID =%d, STA TransactionID =%d\n"
                 ,"PMF_PeerSAQueryRspAction",*(undefined1 *)(param_2 + 10),
                 *(undefined1 *)(param_2 + 0xb),*(undefined1 *)(param_2 + 0xc),
                 *(undefined1 *)(param_2 + 0xd),*(undefined1 *)(param_2 + 0xe),
                 *(undefined1 *)(param_2 + 0xf),*(short *)(iVar1 + 0x629),local_1a);
          return;
        }
        *(undefined1 *)(iVar1 + 0x628) = 0;
        RTMPCancelTimer(iVar1 + 0x5c0,&uStack_1b);
        RTMPCancelTimer(iVar1 + 0x5f4,&uStack_1b);
        if (DebugLevel < 0) {
          return;
        }
        uVar3 = *(undefined1 *)(param_2 + 10);
        uVar4 = *(undefined1 *)(param_2 + 0xb);
        pcVar2 = "[PMF]%s - Compare TransactionID correctly, STA(%02x:%02x:%02x:%02x:%02x:%02x)\n";
      }
      goto LAB_002196e8;
    }
  }
  else if (*(char *)(param_1 + 0x286285) == '\0') {
LAB_002196a4:
    iVar1 = MacTableLookup2(param_1,param_2 + 10,*(undefined4 *)(param_2 + 0x92c));
    goto LAB_002196b8;
  }
  if (DebugLevel < 0) {
    return;
  }
  uVar3 = *(undefined1 *)(param_2 + 10);
  uVar4 = *(undefined1 *)(param_2 + 0xb);
  pcVar2 = "[PMF]%s : Entry is not found, STA(%02x:%02x:%02x:%02x:%02x:%02x)\n";
LAB_002196e8:
  printk(pcVar2,"PMF_PeerSAQueryRspAction",uVar3,uVar4,*(undefined1 *)(param_2 + 0xc),
         *(undefined1 *)(param_2 + 0xd),*(undefined1 *)(param_2 + 0xe),
         *(undefined1 *)(param_2 + 0xf));
  return;
}

