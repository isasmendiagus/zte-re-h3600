// module: mt7915.ko
// function: sae_cn_confirm_ffc @ 0x20c0a0
// size: 320 bytes
//

void sae_cn_confirm_ffc(int param_1,int param_2,undefined4 param_3)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int local_24;
  int local_20;
  undefined4 local_1c;
  
  uVar5 = *(undefined4 *)(param_1 + 0x54);
  uVar4 = *(undefined4 *)(param_1 + 0x58);
  local_24 = 0;
  local_20 = 0;
  if (4 < DebugLevel) {
    printk("==> %s()is_send = %d\n","sae_cn_confirm_ffc",param_2);
  }
  os_alloc_mem(0,&local_24,0x400);
  if (local_24 != 0) {
    os_alloc_mem(0,&local_20,0x400);
    if (local_20 == 0) {
      os_free_mem(local_24);
      return;
    }
    local_1c = *(undefined4 *)(param_1 + 100);
    Bignum_BI2Bin_with_pad(uVar5,local_24,&local_1c,local_1c);
    local_1c = *(undefined4 *)(param_1 + 100);
    Bignum_BI2Bin_with_pad(uVar4,local_20,&local_1c,local_1c);
    if (param_2 == 0) {
      uVar4 = *(undefined4 *)(param_1 + 0x28);
      uVar5 = *(undefined4 *)(param_1 + 0x50);
      uVar6 = *(undefined4 *)(param_1 + 100);
      uVar1 = *(undefined2 *)(param_1 + 0x84);
      iVar2 = local_20;
      iVar3 = local_24;
    }
    else {
      uVar4 = *(undefined4 *)(param_1 + 0x50);
      uVar5 = *(undefined4 *)(param_1 + 0x28);
      uVar6 = *(undefined4 *)(param_1 + 100);
      uVar1 = *(undefined2 *)(param_1 + 4);
      iVar2 = local_24;
      iVar3 = local_20;
    }
    sae_cn_confirm_cmm(param_1,uVar4,uVar5,iVar2,iVar3,uVar6,uVar1,param_3);
    os_free_mem(local_24);
    os_free_mem(local_20);
  }
  return;
}

