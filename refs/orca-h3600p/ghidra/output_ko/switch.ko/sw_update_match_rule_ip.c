// module: switch.ko
// function: sw_update_match_rule_ip @ 0x21f48
// size: 244 bytes
//

void sw_update_match_rule_ip(uint param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  char *pcVar8;
  char *pcVar9;
  undefined4 uStack_1b8;
  undefined1 local_1b2;
  undefined1 local_1b1;
  undefined1 local_1b0;
  undefined1 local_1af;
  undefined1 local_1ae;
  undefined1 local_1ad;
  undefined2 local_1ac;
  undefined2 local_1aa;
  undefined4 auStack_1a8 [12];
  undefined4 local_178 [23];
  uint local_11c;
  uint local_fc;
  
  memcpy(local_178,&_LANCHOR0,0x160);
  pcVar8 = (char *)&DAT_00023994;
  puVar7 = &uStack_1b8;
  do {
    pcVar9 = pcVar8 + 0x10;
    uVar1 = *(undefined4 *)(pcVar8 + 4);
    uVar2 = *(undefined4 *)(pcVar8 + 8);
    uVar3 = *(undefined4 *)(pcVar8 + 0xc);
    puVar7[4] = *(undefined4 *)pcVar8;
    puVar7[5] = uVar1;
    puVar7[6] = uVar2;
    puVar7[7] = uVar3;
    pcVar8 = pcVar9;
    puVar7 = puVar7 + 4;
  } while (pcVar9 != "UNKOWN");
  local_11c = param_1 >> 0x10;
  local_fc = param_1 & 0xffff;
  puVar7 = local_178;
  do {
    __memzero(&local_1b2,10);
    puVar4 = puVar7 + 8;
    local_1b2 = (undefined1)*puVar7;
    local_1b1 = (undefined1)puVar7[1];
    local_1b0 = (undefined1)puVar7[2];
    local_1af = (undefined1)puVar7[3];
    local_1ae = (undefined1)puVar7[4];
    local_1ad = (undefined1)puVar7[5];
    local_1ac = (undefined2)puVar7[6];
    local_1aa = (undefined2)puVar7[7];
    spa_set_matchram(&local_1b2);
    puVar7 = puVar4;
  } while (puVar4 != (undefined4 *)&stack0xffffffe8);
  puVar7 = auStack_1a8;
  iVar5 = 0;
  do {
    iVar6 = iVar5 + 1;
    spa_set_hashram(iVar5,puVar7);
    puVar7 = (undefined4 *)((int)puVar7 + 6);
    iVar5 = iVar6;
  } while (iVar6 != 8);
  return;
}

