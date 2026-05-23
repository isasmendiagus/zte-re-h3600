// module: tm.ko
// function: tm_pon_npp_spa_initial @ 0x4ed1c
// size: 456 bytes
//

uint tm_pon_npp_spa_initial(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  uint uVar8;
  undefined4 *puVar9;
  char *pcVar10;
  char *pcVar11;
  undefined4 uStack_1c0;
  undefined1 local_1ba;
  undefined1 local_1b9;
  undefined1 local_1b8;
  undefined1 local_1b7;
  undefined1 local_1b6;
  undefined1 local_1b5;
  undefined2 local_1b4;
  undefined2 local_1b2;
  undefined4 local_1b0 [12];
  undefined4 local_180 [88];
  undefined4 uStack_20;
  
  uVar8 = 0;
  iVar5 = 0;
  do {
    if (iVar5 < 0x4e) {
      uVar1 = spa_set_up_reg_pkt_en(iVar5,1);
      uVar8 = uVar8 | uVar1;
    }
    uVar1 = spa_set_dn_reg_pkt_en(iVar5,1);
    iVar5 = iVar5 + 1;
    uVar8 = uVar8 | uVar1;
  } while (iVar5 != 0x53);
  iVar5 = 1;
  do {
    uVar1 = spa_set_pt_802x_trap_en(iVar5,1);
    iVar5 = iVar5 + 1;
    uVar8 = uVar8 | uVar1;
  } while (iVar5 != 8);
  iVar5 = 0;
  uVar1 = fpga_read_reg(0x75015);
  fpga_write_reg(0x75015,uVar1 | 0x3000000);
  do {
    uVar1 = spa_set_port_dft_pri(iVar5,0);
    iVar5 = iVar5 + 1;
    uVar8 = uVar8 | uVar1;
  } while (iVar5 != 8);
  iVar5 = 0;
  do {
    uVar1 = spa_set_port_pkt_filter(iVar5,0);
    iVar5 = iVar5 + 1;
    uVar8 = uVar8 | uVar1;
  } while (iVar5 != 9);
  spa_set_match_mode(1);
  memcpy(local_180,&_LANCHOR1,0x160);
  pcVar10 = (char *)&DAT_0007ab88;
  puVar9 = &uStack_1c0;
  do {
    pcVar11 = pcVar10 + 0x10;
    uVar2 = *(undefined4 *)(pcVar10 + 4);
    uVar3 = *(undefined4 *)(pcVar10 + 8);
    uVar4 = *(undefined4 *)(pcVar10 + 0xc);
    puVar9[4] = *(undefined4 *)pcVar10;
    puVar9[5] = uVar2;
    puVar9[6] = uVar3;
    puVar9[7] = uVar4;
    pcVar10 = pcVar11;
    puVar9 = puVar9 + 4;
  } while (pcVar11 != "tm_pon_npp_initial");
  puVar9 = local_180;
  do {
    __memzero(&local_1ba,10);
    puVar6 = puVar9 + 8;
    local_1ba = (undefined1)*puVar9;
    local_1b9 = (undefined1)puVar9[1];
    local_1b8 = (undefined1)puVar9[2];
    local_1b7 = (undefined1)puVar9[3];
    local_1b6 = (undefined1)puVar9[4];
    local_1b5 = (undefined1)puVar9[5];
    local_1b4 = (undefined2)puVar9[6];
    local_1b2 = (undefined2)puVar9[7];
    spa_set_matchram(&local_1ba);
    puVar9 = puVar6;
  } while (puVar6 != &uStack_20);
  puVar9 = local_1b0;
  iVar5 = 0;
  do {
    iVar7 = iVar5 + 1;
    spa_set_hashram(iVar5,puVar9);
    puVar9 = (undefined4 *)((int)puVar9 + 6);
    iVar5 = iVar7;
  } while (iVar7 != 8);
  if (uVar8 != 0) {
    printk("ERROR:(%s:%d) reg read fail\n","tm_api.c",0x3a8);
  }
  return uVar8;
}

