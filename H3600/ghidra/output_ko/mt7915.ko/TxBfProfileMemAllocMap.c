// module: mt7915.ko
// function: TxBfProfileMemAllocMap @ 0x886e0
// size: 236 bytes
//

void TxBfProfileMemAllocMap(void *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  bool bVar5;
  undefined1 local_318 [768];
  
  puVar4 = local_318;
  memcpy(local_318,param_1,0x300);
  iVar3 = 0;
  do {
    if (0 < DebugLevel) {
      printk("========= PFMU memory allocation map =========\n");
      if (0 < DebugLevel) {
        printk("%3d :",iVar3);
      }
    }
    iVar2 = 0;
    iVar1 = DebugLevel;
    do {
      while (0 < iVar1) {
        printk("%4d |",*(undefined2 *)(puVar4 + iVar2));
        bVar5 = iVar2 == 10;
        iVar2 = iVar2 + 2;
        iVar1 = DebugLevel;
        if (bVar5) goto LAB_00088754;
      }
      bVar5 = iVar2 != 10;
      iVar2 = iVar2 + 2;
    } while (bVar5);
LAB_00088754:
    if (0 < iVar1) {
      printk(&_LC32);
      iVar1 = DebugLevel;
    }
    if (0 < iVar1) {
      printk("==============================================\n");
    }
    iVar3 = iVar3 + 1;
    puVar4 = puVar4 + 0xc;
    if (iVar3 == 0x40) {
      return;
    }
  } while( true );
}

