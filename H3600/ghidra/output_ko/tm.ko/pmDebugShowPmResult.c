// module: tm.ko
// function: pmDebugShowPmResult @ 0x6cc10
// size: 168 bytes
//

undefined4 pmDebugShowPmResult(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined1 *puVar4;
  int iVar5;
  undefined1 *puVar6;
  undefined1 auStack_98 [128];
  
  puVar4 = auStack_98;
  puVar6 = auStack_98;
  iVar5 = 0;
  do {
    iVar2 = iVar5 + 1;
    pp_pm_get_diag_ram_info(iVar5,puVar4);
    puVar4 = puVar4 + 0x20;
    iVar5 = iVar2;
  } while (iVar2 != 4);
  iVar5 = 0;
  do {
    iVar2 = 8;
    do {
      iVar2 = iVar2 + -1;
      uVar3 = 0x18;
      do {
        iVar5 = iVar5 + 1;
        uVar1 = uVar3 & 0xff;
        uVar3 = uVar3 - 8;
        printk("%02x ",*(uint *)(puVar6 + iVar2 * 4) >> uVar1 & 0xff);
        if (iVar5 == 0x10) {
          iVar5 = 0;
          printk(&_LC113);
        }
      } while (uVar3 != 0xfffffff8);
    } while (iVar2 != 0);
    puVar6 = puVar6 + 0x20;
  } while (puVar6 != &stack0xffffffe8);
  return 1;
}

