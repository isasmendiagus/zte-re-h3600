// module: mt7915.ko
// function: set_txbf_he_bf_starec @ 0xe6170
// size: 788 bytes
//

undefined4 set_txbf_he_bf_starec(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 uStack_68;
  undefined4 local_64;
  undefined1 local_60;
  undefined1 local_5c;
  undefined1 local_58;
  undefined1 local_54;
  undefined1 local_50;
  undefined1 local_4c;
  undefined1 local_48;
  undefined1 local_44;
  undefined1 local_40;
  undefined1 local_3c;
  undefined1 local_38;
  undefined1 local_34;
  undefined1 local_30;
  undefined1 local_2c;
  
  memset(&local_64,0,0x3c);
  os_zero_mem(param_1 + 0xa787b8,0x14);
  iVar1 = rstrtok(param_2,&_LC232);
  if (iVar1 == 0) {
    local_48 = 0;
    local_64 = 0;
    local_2c = 0;
    local_54 = 0;
    local_58 = 0;
    local_5c = 0;
    local_60 = 0;
    local_30 = 0;
    local_4c = 0;
    local_50 = 0;
    local_44 = 0;
    local_40 = 0;
    local_3c = 0;
    local_38 = 0;
    local_34 = 0;
  }
  else {
    puVar3 = &uStack_68;
    do {
      uVar2 = os_str_toul(iVar1,0,0x10);
      puVar3 = puVar3 + 1;
      *puVar3 = uVar2;
      iVar1 = rstrtok(0,&_LC232);
    } while (iVar1 != 0);
  }
  iVar1 = DebugLevel;
  *(undefined4 *)(param_1 + 0xa787b8) = local_64;
  *(undefined1 *)(param_1 + 0xa787bc) = local_60;
  *(undefined1 *)(param_1 + 0xa787bd) = local_5c;
  *(undefined1 *)(param_1 + 0xa787c3) = local_44;
  *(undefined1 *)(param_1 + 0xa787be) = local_58;
  *(undefined1 *)(param_1 + 0xa787bf) = local_54;
  *(undefined1 *)(param_1 + 0xa787c4) = local_40;
  *(undefined1 *)(param_1 + 0xa787c0) = local_50;
  *(undefined1 *)(param_1 + 0xa787c1) = local_4c;
  *(undefined1 *)(param_1 + 0xa787c5) = local_3c;
  *(undefined1 *)(param_1 + 0xa787c2) = local_48;
  *(undefined1 *)(param_1 + 0xa787c8) = local_30;
  *(undefined1 *)(param_1 + 0xa787c6) = local_38;
  *(undefined1 *)(param_1 + 0xa787c9) = local_2c;
  *(undefined1 *)(param_1 + 0xa787c7) = local_34;
  if (((((2 < iVar1) && (printk("conf=%d\n"), 2 < DebugLevel)) &&
       (printk("conf_su_mu=%d\n",*(undefined1 *)(param_1 + 0xa787bc)), 2 < DebugLevel)) &&
      (((printk("conf_ru_start_idx=%d\n",*(undefined1 *)(param_1 + 0xa787bd)), 2 < DebugLevel &&
        (printk("conf_ru_end_idx=%d\n",*(undefined1 *)(param_1 + 0xa787be)), 2 < DebugLevel)) &&
       ((printk("conf_trigger_su=%d\n",*(undefined1 *)(param_1 + 0xa787bf)), 2 < DebugLevel &&
        ((printk("conf_trigger_mu=%d\n",*(undefined1 *)(param_1 + 0xa787c0)), 2 < DebugLevel &&
         (printk("conf_ng16_su=%d\n",*(undefined1 *)(param_1 + 0xa787c1)), 2 < DebugLevel)))))))) &&
     ((printk("conf_ng16_mu=%d\n",*(undefined1 *)(param_1 + 0xa787c2)), 2 < DebugLevel &&
      (((((printk("conf_codebook42_su=%d\n",*(undefined1 *)(param_1 + 0xa787c3)), 2 < DebugLevel &&
          (printk("conf_codebook75_mu=%d\n",*(undefined1 *)(param_1 + 0xa787c4)), 2 < DebugLevel))
         && (printk("conf_he_ltf=%d\n",*(undefined1 *)(param_1 + 0xa787c5)), 2 < DebugLevel)) &&
        ((printk("conf_ibf_ncol=%d\n",*(undefined1 *)(param_1 + 0xa787c6)), 2 < DebugLevel &&
         (printk("conf_ibf_nrow=%d\n",*(undefined1 *)(param_1 + 0xa787c7)), 2 < DebugLevel)))) &&
       (printk("conf_nr_bw160=0x%2X\n",*(undefined1 *)(param_1 + 0xa787c8)), 2 < DebugLevel)))))) {
    printk("conf_nc_bw160=0x%2X\n",*(undefined1 *)(param_1 + 0xa787c9));
  }
  return 1;
}

