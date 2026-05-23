// module: mt7915.ko
// function: sae_cn_confirm_cmm @ 0x20be08
// size: 380 bytes
//

void sae_cn_confirm_cmm(int param_1,undefined4 param_2,undefined4 param_3,void *param_4,
                       void *param_5,size_t param_6,undefined2 param_7,undefined4 param_8)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined2 *local_30;
  undefined4 local_2c [2];
  
  iVar1 = (*(int *)(param_1 + 100) + 1 + param_6) * 2;
  if (4 < DebugLevel) {
    printk("==> %s(), send_confirm = %d\n","sae_cn_confirm_cmm",param_7);
  }
  os_alloc_mem(0,&local_30,iVar1);
  if (local_30 != (undefined2 *)0x0) {
    *local_30 = param_7;
    local_2c[0] = *(undefined4 *)(param_1 + 100);
    Bignum_BI2Bin_with_pad(param_2,local_30 + 1,local_2c,local_2c[0]);
    iVar2 = *(int *)(param_1 + 100) + 2;
    iVar3 = param_6 + iVar2;
    memmove((void *)((int)local_30 + iVar2),param_4,param_6);
    local_2c[0] = *(undefined4 *)(param_1 + 100);
    Bignum_BI2Bin_with_pad(param_3,(int)local_30 + iVar3,local_2c,local_2c[0]);
    memmove((void *)((int)local_30 + iVar3 + *(int *)(param_1 + 100)),param_5,param_6);
    hex_dump_with_lvl("element_bin1:",param_4,param_6,SAE_DEBUG_LEVEL);
    hex_dump_with_lvl("element_bin2:",param_5,param_6,SAE_DEBUG_LEVEL);
    RT_HMAC_SHA256(param_1 + 0x30,0x20,local_30,iVar1,param_8,0x20);
    hex_dump_with_lvl("confirm:",param_8,0x20,SAE_DEBUG_LEVEL);
    os_free_mem(local_30);
  }
  return;
}

