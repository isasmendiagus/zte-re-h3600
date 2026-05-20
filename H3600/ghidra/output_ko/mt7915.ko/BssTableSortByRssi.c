// module: mt7915.ko
// function: BssTableSortByRssi @ 0x10f988
// size: 404 bytes
//

void BssTableSortByRssi(uint *param_1,int param_2)

{
  uint *puVar1;
  bool bVar2;
  uint uVar3;
  uint *__src;
  uint uVar4;
  uint uVar5;
  void *pvVar6;
  uint uVar7;
  uint *local_34;
  void *local_2c [2];
  
  local_2c[0] = (void *)0x0;
  os_alloc_mem(0,local_2c,0xaf4);
  if (local_2c[0] == (void *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s: Allocate memory fail!!!\n","BssTableSortByRssi");
    }
  }
  else {
    uVar7 = *param_1;
    pvVar6 = local_2c[0];
    if (uVar7 == 0) {
      if (2 < DebugLevel) {
        printk("%s: BssNr=%d!!!\n","BssTableSortByRssi",0);
        pvVar6 = local_2c[0];
      }
    }
    else {
      uVar3 = uVar7 - 1;
      uVar5 = 0;
      local_34 = param_1 + 2;
      if (uVar3 != 0) {
        do {
          uVar5 = uVar5 + 1;
          uVar4 = uVar5;
          puVar1 = local_34;
          if (uVar5 < uVar7) {
            do {
              __src = puVar1 + 0x2bd;
              bVar2 = param_2 == 0;
              if ((*(char *)((int)puVar1 + 0xb65) <= *(char *)((int)local_34 + 0x71)) &&
                 (bVar2 = false, param_2 != 0)) {
                bVar2 = true;
              }
              if (*(char *)((int)puVar1 + 0xb65) == *(char *)((int)local_34 + 0x71)) {
                bVar2 = false;
              }
              uVar4 = uVar4 + 1;
              if (bVar2) {
                memmove(pvVar6,__src,0xaf4);
                memmove(__src,local_34,0xaf4);
                pvVar6 = local_2c[0];
                memmove(local_34,local_2c[0],0xaf4);
                uVar7 = *param_1;
              }
              puVar1 = __src;
            } while (uVar4 < uVar7);
            uVar3 = uVar7 - 1;
          }
          local_34 = local_34 + 0x2bd;
        } while (uVar5 < uVar3);
      }
      if (pvVar6 == (void *)0x0) {
        return;
      }
    }
    os_free_mem(pvVar6);
  }
  return;
}

