// module: mt7915.ko
// function: add_vie @ 0x145b40
// size: 452 bytes
//

undefined4
add_vie(undefined4 param_1,undefined4 param_2,uint param_3,size_t param_4,size_t param_5,
       void *param_6)

{
  int iVar1;
  int iVar2;
  char cVar3;
  uint uVar4;
  uint uVar5;
  size_t *local_3c;
  void *local_38;
  size_t *local_34;
  int local_30;
  size_t local_2c;
  
  uVar4 = 0;
  local_3c = (size_t *)0x0;
  local_38 = (void *)0x0;
  do {
    uVar5 = param_3 & 1 << (uVar4 & 0xff);
    if (uVar5 != 0) {
      iVar2 = find_oui_oitype(param_2,uVar5,param_4,&local_3c);
      if (iVar2 == 1) {
        iVar2 = os_alloc_mem(param_1,&local_38,param_5);
        if (iVar2 == 1) {
          return 1;
        }
        memmove(local_38,param_6,param_5);
        *local_3c = param_5;
        if (local_3c[2] != 0) {
          os_free_mem();
        }
        local_3c[2] = (size_t)local_38;
      }
      else {
        local_34 = (size_t *)0x0;
        local_30 = 0;
        local_2c = param_4;
        iVar2 = os_alloc_mem(0,&local_34,0x10);
        if (iVar2 == 1) {
          return 1;
        }
        FUN_0014580c(param_2,&local_30,uVar5);
        if ((local_30 == 0) || (iVar2 = os_alloc_mem(0,local_34 + 2,param_5), iVar2 == 1)) {
          os_free_mem(local_34);
          return 1;
        }
        memmove((void *)local_34[2],param_6,param_5);
        *local_34 = param_5;
        local_3c = local_34;
        local_34[3] = 0;
        local_34[1] = local_2c;
        cVar3 = *(char *)(local_30 + 4);
        iVar2 = *(int *)(local_30 + 8);
        if (cVar3 == '\0') {
          *(size_t **)(local_30 + 8) = local_34;
        }
        else if (iVar2 != 0) {
          for (iVar1 = *(int *)(iVar2 + 0xc); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0xc)) {
            iVar2 = iVar1;
          }
          *(size_t **)(iVar2 + 0xc) = local_34;
          cVar3 = *(char *)(local_30 + 4);
        }
        *(char *)(local_30 + 4) = cVar3 + '\x01';
      }
    }
    uVar4 = uVar4 + 1;
    if (uVar4 == 7) {
      return 0;
    }
  } while( true );
}

