// module: mt7915.ko
// function: WpaDerivePTK_KDF_384 @ 0x11c6f4
// size: 660 bytes
//

/* WARNING: Restarted to delay deadcode elimination for space: stack */

void WpaDerivePTK_KDF_384
               (undefined4 param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,
               undefined4 *param_5,undefined4 param_6,undefined2 param_7)

{
  int iVar1;
  char local_a2 [4];
  char local_9e [4];
  char local_9a [4];
  char local_96 [4];
  char local_92 [4];
  char local_8e [2];
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 local_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 local_6c;
  undefined2 local_68;
  undefined4 local_66;
  undefined2 local_62;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 local_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  
  local_a2[0] = 'P';
  local_a2[1] = 'a';
  local_a2[2] = 'i';
  local_a2[3] = 'r';
  local_9e[0] = 'w';
  local_9e[1] = 'i';
  local_9e[2] = 's';
  local_9e[3] = 'e';
  local_9a[0] = ' ';
  local_9a[1] = 'k';
  local_9a[2] = 'e';
  local_9a[3] = 'y';
  local_8e[0] = 'o';
  local_8e[1] = 'n';
  local_96[0] = ' ';
  local_96[1] = 'e';
  local_96[2] = 'x';
  local_96[3] = 'p';
  local_92[0] = 'a';
  local_92[1] = 'n';
  local_92[2] = 's';
  local_92[3] = 'i';
  __memzero(&local_8c,0x20);
  __memzero(&local_6c,0x4c);
  iVar1 = RTMPCompareMemory(param_5,param_3,6);
  if (iVar1 == 1) {
    local_6c = *param_3;
    local_68 = *(undefined2 *)(param_3 + 1);
  }
  else {
    local_6c = *param_5;
    local_68 = *(undefined2 *)(param_5 + 1);
  }
  iVar1 = RTMPCompareMemory(param_5,param_3,6);
  if (iVar1 == 1) {
    local_62 = *(undefined2 *)(param_5 + 1);
    local_66 = *param_5;
    local_8c = local_66;
  }
  else {
    local_66 = *param_3;
    local_62 = *(undefined2 *)(param_3 + 1);
    local_8c = local_66;
  }
  local_88 = CONCAT22(local_88._2_2_,local_62);
  local_66 = local_8c;
  iVar1 = RTMPCompareMemory(param_2,param_4,0x20);
  if (iVar1 == 0) {
    local_60 = local_8c;
    uStack_5c = local_88;
    uStack_58 = uStack_84;
    uStack_54 = uStack_80;
    local_50 = local_7c;
    uStack_4c = uStack_78;
    uStack_48 = uStack_74;
    uStack_44 = uStack_70;
  }
  else {
    iVar1 = RTMPCompareMemory(param_2,param_4,0x20);
    if (iVar1 == 1) {
      local_60 = *param_4;
      uStack_5c = param_4[1];
      uStack_58 = param_4[2];
      uStack_54 = param_4[3];
      local_50 = param_4[4];
      uStack_4c = param_4[5];
      uStack_48 = param_4[6];
      uStack_44 = param_4[7];
    }
    else {
      local_60 = *param_2;
      uStack_5c = param_2[1];
      uStack_58 = param_2[2];
      uStack_54 = param_2[3];
      local_50 = param_2[4];
      uStack_4c = param_2[5];
      uStack_48 = param_2[6];
      uStack_44 = param_2[7];
    }
  }
  iVar1 = RTMPCompareMemory(param_2,param_4,0x20);
  if (iVar1 == 0) {
    local_40 = local_8c;
    uStack_3c = local_88;
    uStack_38 = uStack_84;
    uStack_34 = uStack_80;
    local_30 = local_7c;
    uStack_2c = uStack_78;
    uStack_28 = uStack_74;
    uStack_24 = uStack_70;
  }
  else {
    iVar1 = RTMPCompareMemory(param_2,param_4,0x20);
    if (iVar1 == 1) {
      local_40 = *param_2;
      uStack_3c = param_2[1];
      uStack_38 = param_2[2];
      uStack_34 = param_2[3];
      local_30 = param_2[4];
      uStack_2c = param_2[5];
      uStack_28 = param_2[6];
      uStack_24 = param_2[7];
    }
    else {
      local_40 = *param_4;
      uStack_3c = param_4[1];
      uStack_38 = param_4[2];
      uStack_34 = param_4[3];
      local_30 = param_4[4];
      uStack_2c = param_4[5];
      uStack_28 = param_4[6];
      uStack_24 = param_4[7];
    }
  }
  hex_dump("[PMF]PMK",param_1,0x30);
  hex_dump("[PMF]concatenation=",&local_6c,0x4c);
  KDF_384(param_1,0x30,local_a2,0x16,&local_6c,0x4c,param_6,param_7);
  return;
}

