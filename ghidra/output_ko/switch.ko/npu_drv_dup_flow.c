// module: switch.ko
// function: npu_drv_dup_flow @ 0x20c78
// size: 180 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 npu_drv_dup_flow(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  if (1 < *(int *)(*(int *)(param_2 + 0x34) + 0x14) - 4U) {
    uVar4 = *(undefined4 *)(param_2 + 0x98);
    uVar1 = *(undefined4 *)(param_2 + 0x9c);
    *(undefined4 *)(param_3 + 0x94) = *(undefined4 *)(param_2 + 0x94);
    *(undefined4 *)(param_3 + 0x98) = uVar4;
    *(undefined4 *)(param_3 + 0x9c) = uVar1;
    if (*(int *)(param_2 + 0x9c) != 0) {
      puVar2 = (undefined4 *)
               kmem_cache_alloc(_CspGetPortInfo,0x80d0,param_3,&kmalloc_caches,param_4);
      if (puVar2 != (undefined4 *)0x0) {
        *(undefined4 **)(param_3 + 0x9c) = puVar2;
        puVar3 = *(undefined4 **)(param_2 + 0x9c);
        uVar1 = puVar3[1];
        uVar4 = puVar3[2];
        uVar5 = puVar3[3];
        *puVar2 = *puVar3;
        puVar2[1] = uVar1;
        puVar2[2] = uVar4;
        puVar2[3] = uVar5;
        uVar1 = puVar3[5];
        puVar2[4] = puVar3[4];
        puVar2[5] = uVar1;
        return 0;
      }
      return 0xffffffff;
    }
  }
  return 0;
}

