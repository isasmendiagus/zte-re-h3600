// module: tm.ko
// function: tm_pon_pp_brg_initial @ 0x4f298
// size: 488 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint tm_pon_pp_brg_initial(void)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  
  iVar9 = 0;
  uVar8 = 0;
  do {
    uVar1 = sbrg_set_pt_transfer_en(iVar9,1);
    uVar2 = tm_vlan_check_ena_set(iVar9,0,0);
    uVar3 = tm_vlan_check_ena_set(iVar9,1,0);
    uVar4 = sbrg_set_pt_smac_look_en(iVar9,1);
    uVar5 = sbrg_set_pt_smac_lookfail_pktdeal(iVar9,0);
    iVar9 = iVar9 + 1;
    uVar8 = uVar8 | uVar2 | uVar1 | uVar3 | uVar4 | uVar5;
  } while (iVar9 != 8);
  iVar9 = 0;
  uVar1 = sbrg_set_irq_en_mask(10);
  uVar2 = sbrg_set_globle_mirror_en(1);
  uVar3 = sbrg_set_macaddr_age_en(1);
  uVar4 = tm_mac_ramaddr_sel_set(1);
  uVar5 = sbrg_set_hash_collision_pktdeal(1);
  uVar6 = sbrg_set_multicst_md(1);
  uVar7 = sbrg_set_macaddr_exchange_md(1);
  uVar7 = uVar1 | uVar8 | uVar2 | uVar3 | uVar4 | uVar5 | uVar6 | uVar7;
  do {
    uVar8 = sbrg_set_pt_learn_mode(0,iVar9);
    iVar9 = iVar9 + 1;
    uVar7 = uVar7 | uVar8;
  } while (iVar9 != 8);
  uVar8 = tm_mac_aging_cycle_set(0);
  iVar9 = 100;
  uVar1 = sbrg_set_stat_clean_en(1);
  do {
    (*_serdes_set_check_en_open)(0x66665b0);
    iVar9 = iVar9 + -1;
  } while (iVar9 != 0);
  uVar2 = sbrg_set_stat_clean_en(0);
  uVar3 = tm_mac_aging_cycle_set(300);
  uVar3 = uVar8 | uVar7 | uVar1 | uVar2 | uVar3;
  iVar9 = 0;
  do {
    uVar8 = sbrg_set_pt_learn_mode(1,iVar9);
    uVar1 = sbrg_set_pt_da_lookup_en(iVar9,1);
    uVar2 = sbrg_set_unknown_unicst_fwd(iVar9,0);
    uVar4 = sbrg_set_unknown_multicst_fwd(iVar9,1);
    uVar5 = sbrg_set_pt_tls(iVar9,0);
    iVar9 = iVar9 + 1;
    uVar3 = uVar3 | uVar1 | uVar8 | uVar2 | uVar4 | uVar5;
  } while (iVar9 != 8);
  uVar8 = sbrg_set_unknown_unicst_fwd(0,1);
  uVar1 = sbrg_set_pt_tls(0,1);
  uVar1 = uVar8 | uVar3 | uVar1;
  if (uVar1 != 0) {
    printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x1cd);
  }
  return uVar1;
}

