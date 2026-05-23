// module: mt7915.ko
// function: WpaDerivePTK_KDF_256 @ 0x11c450
// size: 672 bytes
//

/* WARNING: Restarted to delay deadcode elimination for space: stack */

void WpaDerivePTK_KDF_256
               (void *param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,
               undefined4 *param_5,undefined4 param_6,uint param_7)

{
  int iVar1;
  size_t inlen;
  char local_aa [4];
  char local_a6 [4];
  char local_a2 [4];
  char local_9e [4];
  char local_9a [4];
  char local_96 [2];
  undefined4 local_94;
  undefined4 local_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 local_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 local_74;
  undefined2 local_70;
  undefined4 local_6e;
  undefined2 local_6a;
  undefined4 local_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 local_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  
  local_aa[0] = 'P';
  local_aa[1] = 'a';
  local_aa[2] = 'i';
  local_aa[3] = 'r';
  local_a6[0] = 'w';
  local_a6[1] = 'i';
  local_a6[2] = 's';
  local_a6[3] = 'e';
  local_a2[0] = ' ';
  local_a2[1] = 'k';
  local_a2[2] = 'e';
  local_a2[3] = 'y';
  local_96[0] = 'o';
  local_96[1] = 'n';
  local_9e[0] = ' ';
  local_9e[1] = 'e';
  local_9e[2] = 'x';
  local_9e[3] = 'p';
  local_9a[0] = 'a';
  local_9a[1] = 'n';
  local_9a[2] = 's';
  local_9a[3] = 'i';
  __memzero(&local_94,0x20);
  __memzero(&local_74,0x4c);
  iVar1 = RTMPCompareMemory(param_5,param_3,6);
  if (iVar1 == 1) {
    local_74 = *param_3;
    local_70 = *(undefined2 *)(param_3 + 1);
  }
  else {
    local_74 = *param_5;
    local_70 = *(undefined2 *)(param_5 + 1);
  }
  iVar1 = RTMPCompareMemory(param_5,param_3,6);
  if (iVar1 == 1) {
    local_6a = *(undefined2 *)(param_5 + 1);
    local_6e = *param_5;
    local_94 = local_6e;
  }
  else {
    local_6e = *param_3;
    local_6a = *(undefined2 *)(param_3 + 1);
    local_94 = local_6e;
  }
  local_90 = CONCAT22(local_90._2_2_,local_6a);
  local_6e = local_94;
  iVar1 = RTMPCompareMemory(param_2,param_4,0x20);
  if (iVar1 == 0) {
    local_68 = local_94;
    uStack_64 = local_90;
    uStack_60 = uStack_8c;
    uStack_5c = uStack_88;
    local_58 = local_84;
    uStack_54 = uStack_80;
    uStack_50 = uStack_7c;
    uStack_4c = uStack_78;
  }
  else {
    iVar1 = RTMPCompareMemory(param_2,param_4,0x20);
    if (iVar1 == 1) {
      local_68 = *param_4;
      uStack_64 = param_4[1];
      uStack_60 = param_4[2];
      uStack_5c = param_4[3];
      local_58 = param_4[4];
      uStack_54 = param_4[5];
      uStack_50 = param_4[6];
      uStack_4c = param_4[7];
    }
    else {
      local_68 = *param_2;
      uStack_64 = param_2[1];
      uStack_60 = param_2[2];
      uStack_5c = param_2[3];
      local_58 = param_2[4];
      uStack_54 = param_2[5];
      uStack_50 = param_2[6];
      uStack_4c = param_2[7];
    }
  }
  iVar1 = RTMPCompareMemory(param_2,param_4,0x20);
  if (iVar1 == 0) {
    local_48 = local_94;
    uStack_44 = local_90;
    uStack_40 = uStack_8c;
    uStack_3c = uStack_88;
    local_38 = local_84;
    uStack_34 = uStack_80;
    uStack_30 = uStack_7c;
    uStack_2c = uStack_78;
  }
  else {
    iVar1 = RTMPCompareMemory(param_2,param_4,0x20);
    if (iVar1 == 1) {
      local_48 = *param_2;
      uStack_44 = param_2[1];
      uStack_40 = param_2[2];
      uStack_3c = param_2[3];
      local_38 = param_2[4];
      uStack_34 = param_2[5];
      uStack_30 = param_2[6];
      uStack_2c = param_2[7];
    }
    else {
      local_48 = *param_4;
      uStack_44 = param_4[1];
      uStack_40 = param_4[2];
      uStack_3c = param_4[3];
      local_38 = param_4[4];
      uStack_34 = param_4[5];
      uStack_30 = param_4[6];
      uStack_2c = param_4[7];
    }
  }
  hex_dump("[PMF]PMK",param_1,0x20);
  hex_dump("[PMF]concatenation=",&local_74,0x4c);
  if (param_7 < 0x31) {
    inlen = 0x20;
  }
  else {
    inlen = 0x30;
  }
  KDF(param_1,inlen,local_aa,(size_t *)0x16);
  return;
}

