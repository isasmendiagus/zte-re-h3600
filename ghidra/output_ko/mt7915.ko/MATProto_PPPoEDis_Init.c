// module: mt7915.ko
// function: MATProto_PPPoEDis_Init @ 0x7bb6c
// size: 228 bytes
//

undefined4
MATProto_PPPoEDis_Init(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 *puVar1;
  
  puVar1 = *(undefined1 **)(param_1 + 0x14);
  if (puVar1 == (undefined1 *)0x0) {
    os_alloc_mem_suspend(0,param_1 + 0x14,0x104,param_4,param_4);
    puVar1 = *(undefined1 **)(param_1 + 0x14);
    if (puVar1 == (undefined1 *)0x0) {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("MATProto_PPPoEDis_Init(): Allocate memory for UidMacTable failed!\n");
      return 0;
    }
    __memzero(puVar1,0x104);
  }
  *puVar1 = 1;
  puVar1 = *(undefined1 **)(param_1 + 0x10);
  if (puVar1 == (undefined1 *)0x0) {
    os_alloc_mem_suspend(0,param_1 + 0x10,0x104,1,param_4);
    puVar1 = *(undefined1 **)(param_1 + 0x10);
    if (puVar1 == (undefined1 *)0x0) {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("MATProto_PPPoEDis_Init(): Allocate memory for SesMacTable failed!\n");
      return 0;
    }
    __memzero(puVar1,0x104);
  }
  *puVar1 = 1;
  return 1;
}

