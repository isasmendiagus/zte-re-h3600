// module: mt7915.ko
// function: HQA_TxBfProfileTagMatrix @ 0x27afbc
// size: 392 bytes
//

undefined4 HQA_TxBfProfileTagMatrix(undefined4 param_1,undefined4 param_2,int param_3)

{
  char *pcVar1;
  undefined4 uVar2;
  uint *puVar3;
  uint *puVar4;
  uint uVar5;
  uint uVar6;
  char *local_44;
  uint local_40 [4];
  undefined4 local_30;
  undefined4 local_2c;
  
  if (param_3 == 0) {
    if (DebugLevel < 0) {
      uVar2 = 2;
    }
    else {
      printk("%s: HqaCmdFrame is NULL\n","HQA_TxBfProfileTagMatrix");
      uVar2 = 2;
    }
  }
  else {
    os_alloc_mem(param_1,&local_44,0x200);
    pcVar1 = local_44;
    if (local_44 == (char *)0x0) {
      FUN_0026cdd0(param_3,param_2,2,3);
      return 3;
    }
    uVar5 = (*(ushort *)(param_3 + 8) & 0xff) << 8 | (uint)(*(ushort *)(param_3 + 8) >> 8);
    memcpy(local_40,(void *)(param_3 + 0xc),uVar5);
    uVar5 = uVar5 >> 2;
    if (uVar5 != 0) {
      puVar3 = local_40;
      do {
        uVar6 = *puVar3;
        puVar4 = puVar3 + 1;
        *puVar3 = uVar6 << 0x18 | (uVar6 >> 8 & 0xff) << 0x10 | (uVar6 >> 0x10 & 0xff) << 8 |
                  uVar6 >> 0x18;
        puVar3 = puVar4;
      } while (puVar4 != local_40 + uVar5);
    }
    __memzero(pcVar1,0x200);
    sprintf(local_44,"%02x:%02x:%02x:%02x:%02x:%02x",local_40[0],local_40[1],local_40[2],local_40[3]
            ,local_30,local_2c);
    Set_TxBfProfileTag_Matrix(param_1,local_44);
    os_free_mem(local_44);
    FUN_0026cdd0(param_3,param_2,2,0);
    if (0 < DebugLevel) {
      printk("%s: nrow:%x, ncol:%x, ngroup:%x, LM:%x, code_book:%x, htc:%x\n",
             "HQA_TxBfProfileTagMatrix",local_40[0],local_40[1],local_40[2],local_40[3],local_30,
             local_2c);
    }
    uVar2 = 0;
  }
  return uVar2;
}

