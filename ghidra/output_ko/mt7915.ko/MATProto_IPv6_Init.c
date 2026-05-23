// module: mt7915.ko
// function: MATProto_IPv6_Init @ 0x7c93c
// size: 292 bytes
//

undefined4 MATProto_IPv6_Init(int param_1)

{
  undefined4 uVar1;
  undefined2 uVar2;
  int iVar3;
  char *pcVar4;
  
  pcVar4 = *(char **)(param_1 + 0xc);
  if (pcVar4 == (char *)0x0) {
    os_alloc_mem_suspend(0,param_1 + 0xc,0x110);
    pcVar4 = *(char **)(param_1 + 0xc);
    if (pcVar4 == (char *)0x0) {
      if (DebugLevel < 0) {
        return 0;
      }
      printk("IPMacTable_init(): Allocate memory for IPv6MacTable failed!\n");
      return 0;
    }
    __memzero(pcVar4,0x110);
  }
  if (*pcVar4 != '\0') {
    if (2 < DebugLevel) {
      printk("%s(): IPv6MacTable already inited!\n","IPv6MacTable_init");
      return 1;
    }
    return 1;
  }
  iVar3 = MATDBEntryAlloc(param_1,0x20);
  if (iVar3 != 0) {
    __memzero(iVar3,0x20);
    uVar2 = BROADCAST_ADDR._4_2_;
    uVar1 = (undefined4)BROADCAST_ADDR;
    *(undefined4 *)(iVar3 + 0x1c) = 0;
    *(undefined4 *)(iVar3 + 0x10) = uVar1;
    *(undefined2 *)(iVar3 + 0x14) = uVar2;
    *(int *)(pcVar4 + 0x104) = iVar3;
    *pcVar4 = '\x01';
    return 1;
  }
  if (DebugLevel < 0) {
    return 0;
  }
  printk("IPMacTable_init(): Allocate memory for IPMacTable broadcast entry failed!\n");
  return 0;
}

