// module: mt7915.ko
// function: sae_send_auth_commit @ 0x20a1d0
// size: 572 bytes
//

undefined4 sae_send_auth_commit(undefined4 param_1,int param_2)

{
  size_t sVar1;
  undefined4 uVar2;
  void *pvVar3;
  int iVar4;
  undefined1 *puVar5;
  char *pcVar6;
  undefined4 *puVar7;
  int iVar8;
  void *local_28;
  int local_24 [2];
  
  local_28 = (void *)0x0;
  if (2 < DebugLevel) {
    printk("==> %s():\n","sae_send_auth_commit");
  }
  if (((*(int *)(param_2 + 0x50) != 0) && (*(int *)(param_2 + 0x54) != 0)) &&
     (os_alloc_mem(param_1,&local_28,0xc02), pvVar3 = local_28, local_28 != (void *)0x0)) {
    __memzero(local_28,0xc02);
    memmove(pvVar3,(void *)(param_2 + 0x2c),2);
    pvVar3 = (void *)((int)pvVar3 + 2);
    if (*(void **)(param_2 + 0x7c) != (void *)0x0) {
      memmove(pvVar3,*(void **)(param_2 + 0x7c),*(size_t *)(param_2 + 0x80));
      pvVar3 = (void *)((int)pvVar3 + *(int *)(param_2 + 0x80));
    }
    local_24[0] = *(int *)(param_2 + 100);
    Bignum_BI2Bin_with_pad(*(undefined4 *)(param_2 + 0x50),pvVar3,local_24);
    iVar4 = (int)pvVar3 + local_24[0];
    switch(*(undefined2 *)(param_2 + 0x2c)) {
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x19:
    case 0x1a:
    case 0x1b:
    case 0x1c:
    case 0x1d:
    case 0x1e:
      puVar7 = *(undefined4 **)(param_2 + 0x54);
      local_24[0] = *(int *)(param_2 + 100);
      Bignum_BI2Bin_with_pad(*puVar7,iVar4,local_24);
      iVar8 = *(int *)(param_2 + 100);
      uVar2 = puVar7[1];
      iVar4 = iVar4 + local_24[0];
      break;
    default:
      uVar2 = *(undefined4 *)(param_2 + 0x54);
      iVar8 = *(int *)(param_2 + 100);
    }
    local_24[0] = iVar8;
    Bignum_BI2Bin_with_pad(uVar2,iVar4,local_24,iVar8);
    puVar5 = (undefined1 *)(iVar4 + local_24[0]);
    if (*(int *)(param_2 + 0x88) != 0) {
      if (2 < DebugLevel) {
        pcVar6 = (char *)(*(int *)(param_2 + 0x88) + 0x49);
        sVar1 = strlen(pcVar6);
        printk("%s(): carry pwd id %s, len = %d\n","sae_send_auth_commit",pcVar6,sVar1);
      }
      *puVar5 = 0xff;
      sVar1 = strlen((char *)(*(int *)(param_2 + 0x88) + 0x49));
      puVar5[2] = 0x21;
      puVar5[1] = (char)sVar1 + '\x01';
      pcVar6 = (char *)(*(int *)(param_2 + 0x88) + 0x49);
      sVar1 = strlen(pcVar6);
      memmove(puVar5 + 3,pcVar6,sVar1);
      sVar1 = strlen((char *)(*(int *)(param_2 + 0x88) + 0x49));
      puVar5 = puVar5 + sVar1 + 3;
    }
    sae_send_auth(param_1,param_2 + 0x160,param_2 + 0x166,param_2 + 0x16c,3,1,0,local_28,
                  (int)puVar5 - (int)local_28);
    os_free_mem(local_28);
    return 1;
  }
  return 0;
}

