// module: tm.ko
// function: tm_mirror_egress_ena_set @ 0x4a8f8
// size: 60 bytes
//

undefined4 tm_mirror_egress_ena_set(uint param_1)

{
  int iVar1;
  
  iVar1 = sbrg_set_egs_mirror_en((param_1 << 0x1a) >> 0x1f | (param_1 & 0x1f) << 1 | param_1 & 0xc0)
  ;
  if (iVar1 == 0) {
    return 0;
  }
  printk("tm_mirror_egress_ena_set fail\n");
  return 0xffffffff;
}

