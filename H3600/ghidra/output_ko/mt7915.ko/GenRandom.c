// module: mt7915.ko
// function: GenRandom @ 0x1195f8
// size: 296 bytes
//

void GenRandom(undefined4 param_1,undefined4 *param_2,undefined4 *param_3)

{
  int iVar1;
  int iVar2;
  int local_fc;
  char local_f4 [4];
  char acStack_f0 [4];
  char acStack_ec [4];
  undefined1 auStack_e8 [32];
  undefined4 local_c8;
  undefined2 local_c4;
  undefined4 local_c2;
  undefined4 local_be;
  undefined4 local_ba;
  undefined4 local_b6;
  undefined4 local_b2;
  undefined4 local_ae;
  undefined4 local_aa;
  undefined4 local_a6;
  undefined4 local_a2;
  undefined2 local_9e;
  undefined4 local_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 local_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  
  local_f4[0] = 'I';
  local_f4[1] = 'n';
  local_f4[2] = 'i';
  local_f4[3] = 't';
  acStack_f0[0] = ' ';
  acStack_f0[1] = 'C';
  acStack_f0[2] = 'o';
  acStack_f0[3] = 'u';
  acStack_ec[0] = 'n';
  acStack_ec[1] = 't';
  acStack_ec[2] = 'e';
  acStack_ec[3] = 'r';
  __memzero(&local_78,0x50,0x7265746e,auStack_e8);
  __memzero(&local_c8,0x50);
  __memzero(auStack_e8,0x20);
  local_fc = 0;
  iVar2 = 1;
  do {
    iVar1 = iVar2;
    local_c8 = *param_2;
    local_c2 = jiffies;
    local_c4 = *(undefined2 *)(param_2 + 1);
    local_be = local_78;
    local_ba = uStack_74;
    local_b6 = uStack_70;
    local_b2 = uStack_6c;
    local_ae = local_68;
    local_aa = uStack_64;
    local_a6 = uStack_60;
    local_a2 = uStack_5c;
    local_9e = (undefined2)local_fc;
    PRF(auStack_e8,0x20,local_f4,0xc,&local_c8,0x2c,&local_78,0x20);
    iVar2 = iVar1 + 1;
    local_fc = iVar1;
  } while (iVar2 != 0x21);
  *param_3 = local_78;
  param_3[1] = uStack_74;
  param_3[2] = uStack_70;
  param_3[3] = uStack_6c;
  param_3[4] = local_68;
  param_3[5] = uStack_64;
  param_3[6] = uStack_60;
  param_3[7] = uStack_5c;
  return;
}

