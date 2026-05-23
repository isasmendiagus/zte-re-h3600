// module: mt7915.ko
// function: AES_CMAC @ 0x123530
// size: 580 bytes
//

void AES_CMAC(int param_1,uint param_2,undefined4 param_3,int param_4,undefined4 param_5,
             uint *param_6)

{
  byte *pbVar1;
  byte *pbVar2;
  byte *pbVar3;
  uint uVar4;
  int iVar5;
  byte *pbVar6;
  byte *pbVar7;
  byte *local_74;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  byte local_58 [16];
  byte local_48 [15];
  byte bStack_39;
  byte local_38 [20];
  
  if (*param_6 < 0x10) {
    if (-1 < DebugLevel) {
      printk("AES_CMAC: MAC text length is less than %d bytes).\n",0x10);
    }
  }
  else if (param_4 == 0x10) {
    __memzero(local_48,0x10);
    __memzero(local_38,0x10);
    AES_CMAC_GenerateSubKey(param_3,0x10,local_48,local_38);
    local_68 = _LANCHOR1;
    uStack_64 = DAT_005f366c;
    uStack_60 = DAT_005f3670;
    uStack_5c = DAT_005f3674;
    if (param_2 < 0x11) {
      iVar5 = 0;
    }
    else {
      pbVar6 = (byte *)(param_1 + -1);
      pbVar7 = (byte *)((int)&uStack_5c + 3);
      pbVar3 = pbVar7;
      pbVar2 = (byte *)((int)&local_6c + 3);
      pbVar1 = pbVar6;
      uVar4 = param_2;
      do {
        do {
          pbVar2 = pbVar2 + 1;
          pbVar6 = pbVar6 + 1;
          pbVar3[1] = *pbVar6 ^ *pbVar2;
          pbVar3 = pbVar3 + 1;
        } while (pbVar2 != pbVar7);
        uVar4 = uVar4 - 0x10;
        local_6c = param_4;
        RT_AES_Encrypt(local_58,0x10,param_3,0x10,&local_68,&local_6c);
        pbVar6 = pbVar1 + 0x10;
        pbVar3 = pbVar7;
        pbVar2 = (byte *)((int)&local_6c + 3);
        pbVar1 = pbVar6;
      } while (0x10 < uVar4);
      uVar4 = param_2 - 0x11 >> 4;
      param_2 = (param_2 - 0x10) + uVar4 * -0x10;
      iVar5 = (uVar4 + 1) * 0x10;
    }
    local_74 = local_58;
    pbVar2 = (byte *)((int)&local_6c + 3);
    pbVar3 = (byte *)((int)&uStack_5c + 3);
    if (param_2 == 0x10) {
      pbVar6 = local_58 + 0xf;
      pbVar7 = (byte *)(param_1 + iVar5 + -1);
      pbVar1 = pbVar3;
      do {
        pbVar2 = pbVar2 + 1;
        pbVar7 = pbVar7 + 1;
        pbVar6 = pbVar6 + 1;
        pbVar1 = pbVar1 + 1;
        *pbVar1 = *pbVar7 ^ *pbVar2 ^ *pbVar6;
      } while (pbVar2 != pbVar3);
    }
    else {
      __memzero(local_74,0x10);
      memcpy(local_74,(void *)(param_1 + iVar5),param_2);
      pbVar1 = &bStack_39;
      local_58[param_2] = 0x80;
      do {
        pbVar3 = pbVar3 + 1;
        pbVar2 = pbVar2 + 1;
        pbVar1 = pbVar1 + 1;
        *pbVar3 = *pbVar3 ^ *pbVar2 ^ *pbVar1;
      } while (pbVar3 != local_58 + 0xf);
    }
    RT_AES_Encrypt(local_74,0x10,param_3,0x10,param_5,param_6);
  }
  else if (-1 < DebugLevel) {
    printk("AES_CMAC: key length is %d bytes, it must be %d bytes(128 bits).\n",param_4,0x10);
  }
  return;
}

