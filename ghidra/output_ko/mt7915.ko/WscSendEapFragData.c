// module: mt7915.ko
// function: WscSendEapFragData @ 0x2018c8
// size: 264 bytes
//

void WscSendEapFragData(int param_1,int param_2,int *param_3)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  
  if (param_3 == (int *)0x0) {
    printk(&_LC6,0x18a);
    dump_stack();
    return;
  }
  uVar2 = (uint)*(ushort *)(param_2 + 0x2bec);
  uVar3 = *(uint *)(param_2 + 0x2bf0);
  iVar4 = *(int *)(param_2 + 0x2bfc);
  *(undefined1 *)(param_2 + 0x2bf8) = 1;
  if ((int)uVar2 < (int)uVar3) {
    *(uint *)(param_2 + 0x2bf0) = uVar3 - uVar2;
    *(undefined1 *)(param_2 + 0x2bf8) = 0;
    *(uint *)(param_2 + 0x2bfc) = iVar4 + uVar2;
    uVar3 = uVar2;
  }
  else {
    *(undefined4 *)(param_2 + 0x2bfc) = 0;
    *(undefined4 *)(param_2 + 0x2bf0) = 0;
  }
  cVar1 = *(char *)(param_1 + 0x286285);
  if (cVar1 == '\x01') {
    if (*param_3 == 2) {
      uVar5 = 2;
    }
    else {
      uVar5 = 1;
    }
    WscSendMessage(param_1,4,iVar4,uVar3,param_2,*param_3 == 2,uVar5);
    cVar1 = *(char *)(param_1 + 0x286285);
  }
  if (cVar1 == '\0') {
    WscSendMessage(param_1,4,iVar4,uVar3,param_2,2,2);
  }
  return;
}

