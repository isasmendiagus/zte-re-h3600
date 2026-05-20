// module: mt7915.ko
// function: mtf_txpower_sku_cfg_para @ 0x1a328c
// size: 388 bytes
//

void mtf_txpower_sku_cfg_para(int param_1)

{
  int iVar1;
  undefined1 *puVar2;
  char *pcVar3;
  char cVar4;
  char *pcVar5;
  char cVar6;
  int iVar7;
  undefined1 *puVar8;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  puVar2 = SINGLE_SKU_PARSE_TABLE_LENGTH;
  cVar4 = '\x04';
  *(undefined1 *)(param_1 + 0xa7863c) = 0;
  *(undefined1 *)(param_1 + 0xa7863d) = 0;
  pcVar5 = (char *)(param_1 + 0x285a5e);
  puVar8 = (undefined1 *)(param_1 + 0x285a7a);
  cVar6 = '\0';
  iVar7 = 1;
  *(undefined1 *)(param_1 + 0x285a6b) = 0;
  *(undefined1 *)(param_1 + 0x285a5e) = 4;
  *(undefined1 *)(param_1 + 0x285a7a) = 3;
  pcVar3 = (char *)(param_1 + 0x285a6c);
  while( true ) {
    puVar2 = puVar2 + 1;
    iVar7 = iVar7 + 1;
    pcVar5 = pcVar5 + 1;
    *pcVar5 = *puVar2;
    *pcVar3 = cVar6 + cVar4;
    puVar8 = puVar8 + 1;
    *puVar8 = 3;
    if (iVar7 == 0xd) break;
    cVar6 = *pcVar3;
    cVar4 = *puVar2;
    pcVar3 = pcVar3 + 1;
  }
  iVar7 = 0;
  puVar2 = (undefined1 *)((int)&PTR_caseD_2_00285a84 + param_1 + 2);
  do {
    puVar8 = (undefined1 *)(*(int *)(iVar1 + 0x20c) + iVar7);
    iVar7 = iVar7 + 1;
    puVar2 = puVar2 + 1;
    *puVar2 = *puVar8;
  } while (iVar7 != 0xf);
  puVar2 = BACKOFF_TABLE_BF_LENGTH;
  cVar4 = '\x04';
  pcVar5 = (char *)(param_1 + 0x285a96);
  puVar8 = (undefined1 *)(param_1 + 0x285abc);
  cVar6 = '\0';
  iVar1 = 1;
  *(undefined1 *)(param_1 + 0x285a96) = 4;
  *(undefined1 *)(param_1 + 0x285aa7) = 0;
  *(undefined1 *)(param_1 + 0x285abc) = 3;
  pcVar3 = (char *)(param_1 + 0x285aa8);
  while( true ) {
    puVar2 = puVar2 + 1;
    iVar1 = iVar1 + 1;
    pcVar5 = pcVar5 + 1;
    *pcVar5 = *puVar2;
    *pcVar3 = cVar4 + cVar6;
    puVar8 = puVar8 + 1;
    *puVar8 = 3;
    if (iVar1 == 0x11) break;
    cVar6 = *pcVar3;
    cVar4 = *puVar2;
    pcVar3 = pcVar3 + 1;
  }
  pcVar3 = "";
  pcVar5 = (char *)(param_1 + 0x285acc);
  do {
    pcVar3 = pcVar3 + 1;
    pcVar5 = pcVar5 + 1;
    *pcVar5 = *pcVar3;
  } while (pcVar5 != (char *)(param_1 + 0x285ae1));
  return;
}

