// module: mt7915.ko
// function: HQA_GetDumpRXV @ 0x2710dc
// size: 532 bytes
//

undefined4 HQA_GetDumpRXV(int param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  undefined4 uVar5;
  int iVar6;
  uint *puVar7;
  int local_28;
  uint *local_24;
  
  iVar2 = DebugLevel;
  uVar1 = *(uint *)(param_3 + 0xc);
  uVar4 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18;
  iVar6 = *(int *)(param_1 + 0xa39fd4);
  *(char *)(param_1 + 0xa3ae36) = (char)(uVar1 >> 0x18);
  if (0 < iVar2) {
    printk("%s: band_idx:%x, en_log:%x\n","HQA_GetDumpRXV",uVar4,*(undefined4 *)(param_1 + 0xa39ffc)
           ,uVar4,0);
  }
  if (*(int *)(iVar6 + 0x104) == 0) {
    uVar5 = 1;
    goto LAB_00271198;
  }
  local_24 = (uint *)0x0;
  local_28 = 0;
  iVar2 = os_alloc_mem(param_1,&local_24,4);
  if (iVar2 == 0) {
    os_zero_mem(local_24,4);
    *local_24 = 0x28;
    uVar1 = *local_24;
    iVar2 = os_alloc_mem(param_1,&local_28,uVar1 * 0x24);
    if (iVar2 != 0) goto LAB_00271168;
    os_zero_mem(local_28,uVar1 * 0x24);
    uVar5 = (**(code **)(iVar6 + 0x104))(param_1,local_28,local_24);
    if (-1 < DebugLevel) {
      printk("%s : pCount = %d !!\n","HQA_GetDumpRXV",*local_24);
    }
    uVar1 = *local_24;
    *(uint *)(param_3 + 0xe) =
         uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18;
    uVar1 = *local_24;
    if (uVar1 * 9 == 0) {
      iVar2 = 6;
    }
    else {
      iVar2 = 0;
      puVar3 = (uint *)(local_28 + -4);
      puVar7 = (uint *)(param_3 + 0x12);
      do {
        puVar3 = puVar3 + 1;
        uVar4 = *puVar3;
        iVar2 = iVar2 + 1;
        *puVar7 = uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 |
                  uVar4 >> 0x18;
        puVar7 = puVar7 + 1;
      } while (iVar2 != uVar1 * 9);
      iVar2 = iVar2 * 4 + 6;
    }
    FUN_0026cdd0(param_3,param_2,iVar2,uVar5);
  }
  else {
LAB_00271168:
    if (DebugLevel < 0) {
      uVar5 = 0;
    }
    else {
      uVar5 = 0;
      printk("%s : Not enough memory for dynamic allocating !!\n","HQA_GetDumpRXV");
    }
  }
  if (local_24 != (uint *)0x0) {
    os_free_mem();
  }
  if (local_28 != 0) {
    os_free_mem();
  }
LAB_00271198:
  *(undefined1 *)(param_1 + 0xa3ba97) = 0;
  *(undefined1 *)(param_1 + 0xa3ba96) = 0;
  return uVar5;
}

