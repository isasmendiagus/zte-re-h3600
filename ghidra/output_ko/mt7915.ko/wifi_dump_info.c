// module: mt7915.ko
// function: wifi_dump_info @ 0xedbb0
// size: 268 bytes
//

void wifi_dump_info(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined **ppuVar3;
  undefined *apuStack_28 [4];
  undefined4 *puVar4;
  
  apuStack_28[0] = &DAT_002dc29c;
  apuStack_28[1] = &DAT_002dc2a0;
  apuStack_28[2] = &DAT_002dc2a8;
  apuStack_28[3] = &DAT_002dc2b0;
  ppuVar3 = apuStack_28;
  if (0 < DebugLevel) {
    printk("%s--------------------\n","wifi_dump_info");
    ppuVar3 = apuStack_28;
  }
  do {
    puVar4 = ppuVar3 + 1;
    uVar2 = *ppuVar3;
    iVar1 = dev_get_by_name(&init_net,uVar2);
    if (iVar1 != 0) {
      if (0 < DebugLevel) {
        printk("--------%s--------\n",uVar2);
      }
      uVar2 = *(undefined4 *)(iVar1 + 0x4c0);
      FUN_000d64d4(uVar2,1);
      FUN_000d65e8(uVar2,1);
      show_trinfo_proc(uVar2,&_LC461);
      ShowPLEInfo(uVar2,&_LC461);
      ShowPseInfo(uVar2,&_LC461);
      Show_PSTable_Proc(uVar2,&_LC461);
      show_swqinfo(uVar2,&_LC461);
      ShowSerProc2(uVar2,&_LC461);
    }
    ppuVar3 = (undefined **)puVar4;
  } while (puVar4 != (undefined4 *)&stack0xffffffe8);
  return;
}

