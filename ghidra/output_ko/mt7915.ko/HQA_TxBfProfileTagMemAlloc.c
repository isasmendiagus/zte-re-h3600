// module: mt7915.ko
// function: HQA_TxBfProfileTagMemAlloc @ 0x273870
// size: 492 bytes
//

undefined4 HQA_TxBfProfileTagMemAlloc(undefined4 param_1,undefined4 param_2,int param_3)

{
  char *pcVar1;
  uint *puVar2;
  uint *puVar3;
  uint __n;
  uint uVar4;
  char *local_44;
  uint local_40 [4];
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  local_44 = (char *)0x0;
  if (param_3 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: HqaCmdFrame is NULL\n","HQA_TxBfProfileTagMemAlloc");
      return 2;
    }
  }
  else {
    os_alloc_mem(param_1,&local_44,0x200);
    pcVar1 = local_44;
    if (local_44 == (char *)0x0) {
      FUN_0026cdd0(param_3,param_2,2,3);
      return 3;
    }
    __n = (*(ushort *)(param_3 + 8) & 0xff) << 8 | (uint)(*(ushort *)(param_3 + 8) >> 8);
    if (__n < 0x21) {
      memcpy(local_40,(void *)(param_3 + 0xc),__n);
      if (__n >> 2 != 0) {
        puVar2 = local_40;
        do {
          uVar4 = *puVar2;
          puVar3 = puVar2 + 1;
          *puVar2 = uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 |
                    uVar4 >> 0x18;
          puVar2 = puVar3;
        } while (puVar3 != local_40 + (__n >> 2));
      }
      __memzero(pcVar1,0x200);
      sprintf(local_44,"%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x",local_40[0],local_40[1],local_40[2]
              ,local_40[3],local_30,local_2c,local_28,local_24);
      Set_TxBfProfileTag_Mem(param_1,local_44);
      if (local_44 == (char *)0x0) {
        FUN_0026cdd0(param_3,param_2,2);
      }
      else {
        os_free_mem(local_44);
        FUN_0026cdd0(param_3,param_2,2,0);
      }
      if (0 < DebugLevel) {
        printk("%s: col0/row0:%x/%x, col1/row1:%x/%x, col2/row2:%x/%x, col3/row3:%x/%x\n",
               "HQA_TxBfProfileTagMemAlloc",local_40[0],local_40[1],local_40[2],local_40[3],local_30
               ,local_2c,local_28,local_24);
        return 0;
      }
      return 0;
    }
    os_free_mem(local_44);
    FUN_0026cdd0(param_3,param_2,2,2);
  }
  return 2;
}

