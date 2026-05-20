// module: mt7915.ko
// function: set_hnat_register @ 0xc31ac
// size: 296 bytes
//

undefined4 set_hnat_register(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  
  os_str_tol(param_2,0,10);
  if (3 < DebugLevel) {
    printk("Device Instance\n");
  }
  puVar2 = (undefined4 *)(param_1 + 0xc);
  iVar3 = 0;
  do {
    if (DebugLevel < 4) {
      puVar4 = (undefined4 *)*puVar2;
      if (puVar4 != (undefined4 *)0x0) {
LAB_000c3204:
        if ((((*(char *)(puVar4 + 10) != '\0') && (3 < DebugLevel)) &&
            (printk("\n\t\tName:%s\n",*puVar4), 3 < DebugLevel)) &&
           (printk("\t\tWdev(list) Idx:%d\n",*(undefined1 *)(puVar4 + 3)), 3 < DebugLevel)) {
          uVar1 = RtmpOsGetNetIfIndex(*puVar4);
          printk("\t\t Idx:%d\n",uVar1);
        }
      }
    }
    else {
      printk("\tWDEV %02d:",iVar3);
      puVar4 = (undefined4 *)*puVar2;
      if (puVar4 != (undefined4 *)0x0) goto LAB_000c3204;
      if (3 < DebugLevel) {
        printk(&_LC242);
      }
    }
    iVar3 = iVar3 + 1;
    puVar2 = puVar2 + 1;
    if (iVar3 == 0x68) {
      return 1;
    }
  } while( true );
}

