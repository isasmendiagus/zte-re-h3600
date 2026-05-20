// module: mt7915.ko
// function: HQA_TxBfProfileTagMcsThrd @ 0x27acb8
// size: 404 bytes
//

undefined4 HQA_TxBfProfileTagMcsThrd(undefined4 param_1,undefined4 param_2,int param_3)

{
  char *pcVar1;
  undefined4 uVar2;
  uint uVar3;
  uint *puVar4;
  uint *puVar5;
  uint __n;
  char *local_44;
  uint local_40 [4];
  undefined4 local_30;
  undefined4 local_2c;
  
  if (param_3 == 0) {
    if (DebugLevel < 0) {
      uVar2 = 2;
    }
    else {
      printk("%s: HqaCmdFrame is NULL\n","HQA_TxBfProfileTagMcsThrd");
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
    __n = (*(ushort *)(param_3 + 8) & 0xff) << 8 | (uint)(*(ushort *)(param_3 + 8) >> 8);
    memcpy(local_40,(void *)(param_3 + 0xc),__n);
    if (__n >> 2 != 0) {
      puVar4 = local_40;
      do {
        uVar3 = *puVar4;
        puVar5 = puVar4 + 1;
        *puVar4 = uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 |
                  uVar3 >> 0x18;
        puVar4 = puVar5;
      } while (puVar5 != local_40 + (__n >> 2));
    }
    __memzero(pcVar1,0x200);
    sprintf(local_44,"%02x:%02x:%02x:%02x:%02x:%02x",local_40[0],local_40[1],local_40[2],local_40[3]
            ,local_30,local_2c);
    Set_TxBfProfileTag_McsThrd(param_1,local_44);
    os_free_mem(local_44);
    FUN_0026cdd0(param_3,param_2,2,0);
    if (0 < DebugLevel) {
      printk("%s: len:%x, mcs_lss0:%x, mcs_sss0:%x, mcs_lss1:%x, mcs_sss1:%x, mcs_lss2:%x, mcs_sss2:%x\n"
             ,"HQA_TxBfProfileTagMcsThrd",__n,local_40[0],local_40[1],local_40[2],local_40[3],
             local_30,local_2c);
    }
    uVar2 = 0;
  }
  return uVar2;
}

