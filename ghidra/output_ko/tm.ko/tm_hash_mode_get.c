// module: tm.ko
// function: tm_hash_mode_get @ 0x4a800
// size: 72 bytes
//

undefined4 tm_hash_mode_get(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int local_c;
  
  iVar1 = sbrg_get_hash_mode(&local_c);
  if (iVar1 == 0) {
    *(bool *)param_1 = local_c != 0;
    uVar2 = 0;
  }
  else {
    printk("tm_hash_mode_get fail\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

