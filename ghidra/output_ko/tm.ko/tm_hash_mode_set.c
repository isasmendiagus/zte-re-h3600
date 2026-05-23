// module: tm.ko
// function: tm_hash_mode_set @ 0x4a7d4
// size: 44 bytes
//

undefined4 tm_hash_mode_set(int param_1)

{
  int iVar1;
  
  iVar1 = sbrg_set_hash_mode(param_1 != 0);
  if (iVar1 == 0) {
    return 0;
  }
  printk("tm_hash_mode_set fail\n");
  return 0xffffffff;
}

