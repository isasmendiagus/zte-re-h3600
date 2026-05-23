// module: mt7915.ko
// function: HQA_TxBfProfileTagSnr @ 0x27ae50
// size: 360 bytes
//

undefined4 HQA_TxBfProfileTagSnr(undefined4 param_1,undefined4 param_2,int param_3)

{
  char *pcVar1;
  undefined4 uVar2;
  uint *puVar3;
  uint *puVar4;
  uint uVar5;
  uint uVar6;
  char *local_34;
  uint local_30 [4];
  
  if (param_3 == 0) {
    if (DebugLevel < 0) {
      uVar2 = 2;
    }
    else {
      printk("%s: HqaCmdFrame is NULL\n","HQA_TxBfProfileTagSnr");
      uVar2 = 2;
    }
  }
  else {
    os_alloc_mem(param_1,&local_34,0x200);
    pcVar1 = local_34;
    if (local_34 == (char *)0x0) {
      FUN_0026cdd0(param_3,param_2,2,3);
      return 3;
    }
    uVar5 = (*(ushort *)(param_3 + 8) & 0xff) << 8 | (uint)(*(ushort *)(param_3 + 8) >> 8);
    memcpy(local_30,(void *)(param_3 + 0xc),uVar5);
    uVar5 = uVar5 >> 2;
    if (uVar5 != 0) {
      puVar3 = local_30;
      do {
        uVar6 = *puVar3;
        puVar4 = puVar3 + 1;
        *puVar3 = uVar6 << 0x18 | (uVar6 >> 8 & 0xff) << 0x10 | (uVar6 >> 0x10 & 0xff) << 8 |
                  uVar6 >> 0x18;
        puVar3 = puVar4;
      } while (puVar4 != local_30 + uVar5);
    }
    __memzero(pcVar1,0x200);
    sprintf(local_34,"%02x:%02x:%02x:%02x",local_30[0],local_30[1],local_30[2],local_30[3]);
    Set_TxBfProfileTag_SNR(param_1,local_34);
    os_free_mem(local_34);
    FUN_0026cdd0(param_3,param_2,2,0);
    if (0 < DebugLevel) {
      printk("%s: snr_sts0:%x, snr_sts1:%x, snr_sts2:%x, snr_sts3:%x,\n","HQA_TxBfProfileTagSnr",
             local_30[0],local_30[1],local_30[2],local_30[3]);
    }
    uVar2 = 0;
  }
  return uVar2;
}

