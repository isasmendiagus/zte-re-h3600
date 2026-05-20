// module: mt7915.ko
// function: MATEngineInit @ 0x7a048
// size: 332 bytes
//

undefined4 MATEngineInit(int param_1)

{
  int *piVar1;
  int iVar2;
  code *pcVar3;
  undefined4 *puVar4;
  char *pcVar5;
  int iVar6;
  undefined4 *puVar7;
  
  if (*(int *)(param_1 + 0x794b28) == 1) {
    return 1;
  }
  puVar4 = &DAT_00291860;
  iVar6 = 0;
  do {
    puVar7 = (undefined4 *)*puVar4;
    if (puVar7 == (undefined4 *)0x0) {
      printk(&_LC5,0x1a3);
      dump_stack();
    }
    pcVar3 = (code *)*puVar7;
    if (pcVar3 != (code *)0x0) {
      iVar2 = (*pcVar3)(param_1 + 0x794b28);
      if (iVar2 == 0) {
        if (-1 < DebugLevel) {
          printk("MATEngine Init Protocol (0x%x) failed, Stop the MAT Funciton initialization failed!\n"
                 ,(&_LANCHOR0)[iVar6 * 4]);
        }
        do {
          pcVar5 = "";
          while( true ) {
            piVar1 = (int *)(pcVar5 + 4);
            pcVar5 = pcVar5 + 8;
            if (((*piVar1 != 0) && (pcVar3 = *(code **)(*piVar1 + 0xc), pcVar3 != (code *)0x0)) &&
               (iVar6 = (*pcVar3)(param_1 + 0x794b28), iVar6 == 0)) break;
            if (pcVar5 == "IPMacTable_init") {
              return 0;
            }
          }
        } while( true );
      }
      if (2 < DebugLevel) {
        printk("MATEngine Init Protocol (0x%04x) success!\n",*(undefined2 *)(puVar4 + -1));
      }
    }
    iVar6 = iVar6 + 1;
    puVar4 = puVar4 + 2;
  } while (iVar6 != 5);
  *(int *)(param_1 + 0x794b48) = param_1;
  *(undefined4 *)(param_1 + 0x794b28) = 1;
  *(undefined4 *)(param_1 + 0x794b2c) = 0;
  *(undefined1 *)(param_1 + 0x794b40) = 0;
  return 1;
}

