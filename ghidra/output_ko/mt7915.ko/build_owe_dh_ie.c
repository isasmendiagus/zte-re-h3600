// module: mt7915.ko
// function: build_owe_dh_ie @ 0x21c74c
// size: 232 bytes
//

int build_owe_dh_ie(undefined4 param_1,int param_2,undefined1 *param_3,undefined2 param_4)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  void *local_20;
  undefined4 local_1c [2];
  
  iVar3 = 0;
  iVar4 = *(int *)(param_2 + 0x940);
  puVar5 = *(undefined4 **)(param_2 + 0x94c);
  local_20 = (void *)0x0;
  local_1c[0] = 0;
  iVar1 = os_alloc_mem(0,&local_20,*(undefined4 *)(iVar4 + 8));
  if (iVar1 == 1) {
    if (-1 < DebugLevel) {
      printk("==> %s(), ecc_gen_key failed...\n","build_owe_dh_ie");
    }
  }
  else {
    Bignum_BI2Bin_with_pad(*puVar5,local_20,local_1c,*(undefined4 *)(iVar4 + 8));
    *param_3 = 0xff;
    uVar2 = *(undefined4 *)(iVar4 + 8);
    param_3[2] = 0x20;
    param_3[1] = (char)uVar2 + '\x03';
    *(undefined2 *)(param_3 + 3) = param_4;
    memmove(param_3 + 5,local_20,*(size_t *)(iVar4 + 8));
    iVar3 = *(int *)(iVar4 + 8) + 5;
    hex_dump("ECDH parameter:",param_3,iVar3);
  }
  if (local_20 != (void *)0x0) {
    os_free_mem();
  }
  return iVar3;
}

