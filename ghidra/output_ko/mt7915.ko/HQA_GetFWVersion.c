// module: mt7915.ko
// function: HQA_GetFWVersion @ 0x26e9ec
// size: 296 bytes
//

undefined4 HQA_GetFWVersion(int param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 *puVar4;
  
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_GetFWVersion");
  }
  if (param_1 != -0xa78548) {
    if (0 < DebugLevel) {
      printk("Built date: ");
    }
    puVar4 = (undefined1 *)(param_1 + 0xa78557);
    iVar3 = DebugLevel;
    do {
      if (0 < iVar3) {
        printk(&_LC17,*puVar4);
        iVar3 = DebugLevel;
      }
      puVar4 = puVar4 + 1;
    } while (puVar4 != (undefined1 *)(param_1 + 0xa78563));
    if (0 < iVar3) {
      printk(&_LC18);
    }
    uVar1 = *(undefined4 *)(param_1 + 0xa7855b);
    uVar2 = *(undefined4 *)(param_1 + 0xa7855f);
    *(undefined4 *)(param_3 + 0xe) = *(undefined4 *)(param_1 + 0xa78557);
    *(undefined4 *)(param_3 + 0x12) = uVar1;
    *(undefined4 *)(param_3 + 0x16) = uVar2;
  }
  FUN_0026cdd0(param_3,param_2,0xe,0);
  return 0;
}

