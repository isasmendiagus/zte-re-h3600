// module: mt7915.ko
// function: ReceiveWNMNotifyReq @ 0x229d9c
// size: 428 bytes
//

void ReceiveWNMNotifyReq(undefined4 param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  
  uVar4 = *(int *)(param_2 + 0x908) - 0x1c;
  if (-1 < DebugLevel) {
    printk("%s MsgLen %ld MBSS %02x:%02x:%02x:%02x:%02x:%02x\n","ReceiveWNMNotifyReq",
           *(int *)(param_2 + 0x908),*(undefined1 *)(param_2 + 4),*(undefined1 *)(param_2 + 5),
           *(undefined1 *)(param_2 + 6),*(undefined1 *)(param_2 + 7),*(undefined1 *)(param_2 + 8),
           *(undefined1 *)(param_2 + 9));
  }
  if (uVar4 != 0) {
    uVar2 = 1;
    iVar3 = 0;
    do {
      iVar5 = DebugLevel;
      uVar2 = (uint)*(byte *)(param_2 + uVar2 + 0x1c);
      uVar6 = (uint)*(byte *)(param_2 + iVar3 + 0x1c);
      if (DebugLevel < 0) {
        if (uVar6 == 0xdd) {
          iVar1 = memcmp(&wfa_oui,(void *)(param_2 + iVar3 + 0x1e),3);
          if (iVar1 != 0) {
LAB_00229e28:
            if (-1 < iVar5) {
              printk("%s, %u vendor specific, but unknown OUI, please check\n","ReceiveWNMNotifyReq"
                     ,0xdbe);
            }
          }
        }
      }
      else {
        uVar7 = uVar4;
        uVar8 = uVar6;
        uVar9 = uVar2;
        printk("%s, %u pos %d OptionalElementLen %d ElementID %d ElementLen %d\n",
               "ReceiveWNMNotifyReq",0xd9d,iVar3,uVar4,uVar6,uVar2);
        if (uVar6 == 0xdd) {
          iVar1 = memcmp(&wfa_oui,(void *)(param_2 + iVar3 + 0x1e),3);
          iVar5 = DebugLevel;
          if (iVar1 != 0) goto LAB_00229e28;
          if (-1 < DebugLevel) {
            printk(&_LC80,"ReceiveWNMNotifyReq",0xdb9,iVar3 + 2,uVar7,uVar8,uVar9);
          }
        }
        else if (-1 < DebugLevel) {
          printk("%s, UNKNOWN ElementID 0x%X , break parsing\n","ReceiveWNMNotifyReq",uVar6,
                 iVar3 + 2,uVar7,uVar8,uVar9);
        }
      }
      iVar3 = iVar3 + 2 + uVar2;
      uVar2 = iVar3 + 1;
    } while (uVar2 <= uVar4);
  }
  return;
}

