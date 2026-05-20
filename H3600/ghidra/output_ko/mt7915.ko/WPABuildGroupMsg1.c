// module: mt7915.ko
// function: WPABuildGroupMsg1 @ 0x11fc68
// size: 460 bytes
//

void WPABuildGroupMsg1(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  char cVar4;
  int local_34;
  undefined4 local_2e;
  undefined2 local_2a;
  undefined4 local_28;
  undefined2 local_24;
  undefined2 local_22;
  
  if (2 < DebugLevel) {
    printk("===> %s\n","WPABuildGroupMsg1");
  }
  if (*(int *)(param_3 + 8) == 0) {
    if (-1 < DebugLevel) {
      printk("!!!%s : pEntry->wdev is NULL!!!\n","WPABuildGroupMsg1");
    }
  }
  else {
    os_alloc_mem(0,&local_34,0x5dc);
    iVar1 = local_34;
    if (local_34 == 0) {
      if (-1 < DebugLevel) {
        printk("!!!%s : no memory!!!\n","WPABuildGroupMsg1");
      }
    }
    else {
      __memzero(local_34,0x5dc);
      uVar3 = 8;
      do {
        uVar3 = uVar3 - 1 & 0xff;
        cVar4 = *(char *)(param_2 + uVar3 + 0x390) + '\x01';
        *(char *)(param_2 + uVar3 + 0x390) = cVar4;
      } while (uVar3 != 0 && cVar4 == '\0');
      AsicGetTxTsc(param_1,*(int *)(param_3 + 8),*(int *)(param_3 + 8) + 0x3c7);
      *(undefined1 *)(param_2 + 0x39a) = 5;
      WPAConstructEapolMsg(param_3,5,param_2,*(int *)(param_3 + 8) + 0x2c,iVar1);
      local_2e = *(undefined4 *)(param_2 + 0x32a);
      local_24 = *(undefined2 *)(param_2 + 0x328);
      local_2a = *(undefined2 *)(param_2 + 0x32e);
      local_28 = *(undefined4 *)(param_2 + 0x324);
      local_22 = EAPOL;
      RTMPToWirelessSta(param_1,param_3,&local_2e,0xe,iVar1,
                        CONCAT11(*(undefined1 *)(iVar1 + 2),*(undefined1 *)(iVar1 + 3)) + 4,0);
      os_free_mem(local_34);
      if (*(byte *)(param_2 + 0x3d8) < 0xb) {
        uVar2 = 1000;
      }
      else {
        uVar2 = 60000;
      }
      RTMPModTimer(param_2 + 0x3a4,uVar2);
      if (2 < DebugLevel) {
        printk("<=== %s : send out Group Message 1\n","WPABuildGroupMsg1");
      }
    }
  }
  return;
}

