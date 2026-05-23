// module: mt7915.ko
// function: HQA_TxBfProfileTagTimeOut @ 0x273510
// size: 212 bytes
//

undefined4 HQA_TxBfProfileTagTimeOut(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  char *local_1c [2];
  
  os_alloc_mem(param_1,local_1c,0x200,0,0);
  if (local_1c[0] == (char *)0x0) {
    uVar2 = 3;
  }
  else {
    uVar1 = *(uint *)(param_3 + 0xc);
    uVar3 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
            uVar1 >> 0x18;
    uVar1 = uVar3;
    __memzero(local_1c[0],0x200);
    sprintf(local_1c[0],"%d",uVar3);
    Set_TxBfProfileTag_TimeOut(param_1,local_1c[0]);
    if (0 < DebugLevel) {
      printk("%s: val:%x, str:%s\n","HQA_TxBfProfileTagTimeOut",uVar3,local_1c[0],uVar1);
    }
    uVar2 = 0;
    os_free_mem(local_1c[0]);
  }
  FUN_0026cdd0(param_3,param_2,2,uVar2);
  return uVar2;
}

