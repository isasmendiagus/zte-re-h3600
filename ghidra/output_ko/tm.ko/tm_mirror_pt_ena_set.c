// module: tm.ko
// function: tm_mirror_pt_ena_set @ 0x4a960
// size: 44 bytes
//

undefined4 tm_mirror_pt_ena_set(int param_1)

{
  int iVar1;
  
  iVar1 = sbrg_set_pt_mirror_en(param_1 != 0);
  if (iVar1 == 0) {
    return 0;
  }
  printk("tm_mirror_pt_ena_set fail\n");
  return 0xffffffff;
}

