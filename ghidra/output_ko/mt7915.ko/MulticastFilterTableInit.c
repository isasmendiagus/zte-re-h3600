// module: mt7915.ko
// function: MulticastFilterTableInit @ 0x240378
// size: 220 bytes
//

void MulticastFilterTableInit(int param_1,int *param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  uVar1 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((uVar1 & 0x400) != 0) {
    return;
  }
  os_alloc_mem(0,param_2,0xf18);
  if (*param_2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s unable to alloc memory for Multicase filter table, size=%lu\n",
             "MulticastFilterTableInit",0xf18,param_4);
      return;
    }
    return;
  }
  __memzero(*param_2,0xf18);
  *(undefined4 *)(*param_2 + 0xc04) = 0;
  *(undefined4 *)(*param_2 + 0xc08) = 0;
  iVar2 = *param_2;
  *(undefined4 *)(iVar2 + 0xf10) = 0;
  *(undefined4 *)(iVar2 + 0xf0c) = 0;
  *(undefined1 *)(iVar2 + 0xf14) = 0;
  iVar2 = *param_2;
  puVar3 = (undefined4 *)(iVar2 + 0xc0c);
  do {
    *puVar3 = 0;
    if (*(undefined4 **)(iVar2 + 0xf10) == (undefined4 *)0x0) {
      *(undefined4 **)(iVar2 + 0xf0c) = puVar3;
    }
    else {
      **(undefined4 **)(iVar2 + 0xf10) = puVar3;
    }
    *(undefined4 **)(iVar2 + 0xf10) = puVar3;
    puVar3 = puVar3 + 3;
    *(char *)(iVar2 + 0xf14) = *(char *)(iVar2 + 0xf14) + '\x01';
  } while (puVar3 != (undefined4 *)(iVar2 + 0xf0c));
  return;
}

