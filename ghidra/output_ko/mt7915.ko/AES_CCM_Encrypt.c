// module: mt7915.ko
// function: AES_CCM_Encrypt @ 0x122dc0
// size: 780 bytes
//

undefined4
AES_CCM_Encrypt(int param_1,uint param_2,undefined4 param_3,int param_4,int param_5,int param_6,
               undefined4 param_7,undefined4 param_8,uint param_9,int param_10,uint *param_11)

{
  byte *pbVar1;
  int iVar2;
  byte *pbVar3;
  undefined1 *puVar4;
  byte *pbVar5;
  undefined1 *puVar6;
  uint uVar7;
  uint uVar8;
  undefined4 local_5c;
  byte local_58 [16];
  byte local_48;
  byte local_47 [14];
  byte local_39;
  byte local_38 [20];
  
  local_5c = 0;
  if (param_4 != 0x10) {
    if (-1 < DebugLevel) {
      printk("AES_CCM_Encrypt: The key length must be %d bytes\n",0x10);
      return 0xffffffff;
    }
    return 0xffffffff;
  }
  if (6 < param_6 - 7U) {
    if (-1 < DebugLevel) {
      printk("AES_CCM_Encrypt: A valid nonce length is 7-13 bytes\n");
      return 0xfffffffe;
    }
    return 0xfffffffe;
  }
  if ((((param_9 & 0xfffffff5) != 4) && ((param_9 & 0xfffffffd) != 8)) && (param_9 != 0x10)) {
    if (-1 < DebugLevel) {
      printk("AES_CCM_Encrypt: The MAC length  must be 4, 6, 8, 10, 12, 14, or 16 bytes\n");
      return 0xfffffffd;
    }
    return 0xfffffffd;
  }
  if (*param_11 < param_9 + param_2) {
    if (-1 < DebugLevel) {
      printk("AES_CCM_Encrypt: The CipherTextLength is not enough.\n");
      return 0xfffffffc;
    }
    return 0xfffffffc;
  }
  __memzero(&local_48,0x10);
  pbVar3 = &local_48;
  pbVar5 = (byte *)(param_5 + -1);
  local_48 = 0xeU - (char)param_6 | local_48;
  do {
    pbVar5 = pbVar5 + 1;
    pbVar3 = pbVar3 + 1;
    *pbVar3 = *pbVar5;
  } while (pbVar5 != (byte *)(param_5 + param_6 + -1));
  AES_CCM_MAC(param_1,param_2,param_3,0x10,param_5,param_6,param_7,param_8,param_9,local_58);
  local_5c = 0x10;
  RT_AES_Encrypt(&local_48,0x10,param_3,0x10,local_38,&local_5c);
  if (param_9 == 0) {
    if (param_2 == 0) goto LAB_00123094;
LAB_00122fd0:
    uVar7 = 0;
    do {
      local_39 = local_39 + 1;
      local_5c = 0x10;
      RT_AES_Encrypt(&local_48,0x10,param_3,0x10,local_38,&local_5c);
      uVar8 = param_2 - uVar7;
      if (0xf < uVar8) {
        uVar8 = 0x10;
      }
      if (uVar8 != 0) {
        iVar2 = uVar7 - 1;
        pbVar1 = (byte *)(param_1 + iVar2);
        pbVar3 = &local_39;
        pbVar5 = (byte *)(param_10 + iVar2);
        do {
          pbVar1 = pbVar1 + 1;
          pbVar3 = pbVar3 + 1;
          pbVar5 = pbVar5 + 1;
          *pbVar5 = *pbVar1 ^ *pbVar3;
        } while (pbVar1 != (byte *)(param_1 + uVar8 + iVar2));
      }
      uVar7 = uVar7 + uVar8;
    } while (uVar7 < param_2);
    if (param_9 == 0) goto LAB_00123094;
  }
  else {
    pbVar5 = (byte *)((int)&local_5c + 3);
    pbVar3 = local_38;
    do {
      pbVar1 = pbVar3 + 1;
      pbVar5 = pbVar5 + 1;
      *pbVar5 = *pbVar5 ^ *pbVar3;
      pbVar3 = pbVar1;
    } while (pbVar1 != local_38 + param_9);
    if (param_2 != 0) goto LAB_00122fd0;
  }
  puVar4 = (undefined1 *)((int)&local_5c + 3);
  puVar6 = (undefined1 *)(param_10 + (param_2 - 1));
  do {
    puVar4 = puVar4 + 1;
    puVar6 = puVar6 + 1;
    *puVar6 = *puVar4;
  } while (puVar6 != (undefined1 *)(param_10 + param_9 + (param_2 - 1)));
LAB_00123094:
  *param_11 = param_9 + param_2;
  return 0;
}

