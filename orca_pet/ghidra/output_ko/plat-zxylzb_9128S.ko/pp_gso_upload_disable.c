// module: plat-zxylzb_9128S.ko
// function: pp_gso_upload_disable @ 0x198ac
// size: 124 bytes
//

void pp_gso_upload_disable(void)

{
  int iVar1;
  undefined4 in_r3;
  int iVar2;
  uint *puVar3;
  
  if (0 < pp_gso_bp_cnt) {
    puVar3 = (uint *)&pp_gso_bp_cnt;
    iVar2 = 0;
    do {
      puVar3 = puVar3 + 1;
      if (*puVar3 != 0) {
        iVar1 = pp_bmu_free_bp(*puVar3 & 0xffff,0,0,pp_gso_bp_cnt,in_r3);
        if (iVar1 < 0) {
          printk("failed to rls bp\n");
        }
        else {
          *puVar3 = 0;
        }
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < pp_gso_bp_cnt);
  }
  pp_gso_bp_cnt = 0;
  return;
}

