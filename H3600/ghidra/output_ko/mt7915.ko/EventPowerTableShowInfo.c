// module: mt7915.ko
// function: EventPowerTableShowInfo @ 0x1a8500
// size: 224 bytes
//

void EventPowerTableShowInfo(undefined4 param_1,int param_2)

{
  int iVar1;
  char cVar2;
  undefined1 *puVar3;
  undefined1 auStack_295 [641];
  
  memcpy(auStack_295,"CCK_1M2M    ",0x27d);
  if (((0 < DebugLevel) &&
      (printk("=============================================================================\n"),
      0 < DebugLevel)) &&
     (printk("   Phy Rate             1SS        2SS        3SS        4SS             \n"),
     0 < DebugLevel)) {
    printk("=============================================================================\n");
  }
  puVar3 = auStack_295;
  cVar2 = '\x01';
  iVar1 = DebugLevel;
  do {
    if (cVar2 != '\t') {
      if (0 < iVar1) {
        printk("%s             %2d        %2d        %2d        %2d\n",puVar3,
               (int)*(char *)(param_2 + 4),(int)*(char *)(param_2 + 5),(int)*(char *)(param_2 + 6),
               (int)*(char *)(param_2 + 7));
      }
      iVar1 = DebugLevel;
      if (cVar2 == '1') {
        return;
      }
    }
    cVar2 = cVar2 + '\x01';
    param_2 = param_2 + 4;
    puVar3 = puVar3 + 0xd;
  } while( true );
}

