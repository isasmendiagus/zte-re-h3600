// module: mt7915.ko
// function: AES_CCM_Decrypt @ 0x1230cc
// size: 792 bytes
//

undefined4
AES_CCM_Decrypt(int param_1,uint param_2,undefined4 param_3,int param_4,int param_5,int param_6,
               undefined4 param_7,undefined4 param_8,uint param_9,int param_10,uint *param_11)

{
  undefined4 uVar1;
  int iVar2;
  byte *pbVar3;
  byte *pbVar4;
  uint uVar5;
  uint uVar6;
  byte *pbVar7;
  uint uVar8;
  undefined4 local_6c;
  undefined1 auStack_68 [15];
  byte bStack_59;
  byte local_58 [16];
  byte local_48;
  byte local_47 [14];
  byte local_39;
  byte local_38 [20];
  
  local_6c = 0;
  if (param_4 == 0x10) {
    if (param_6 - 7U < 7) {
      if ((((param_9 & 0xfffffff5) == 4) || ((param_9 & 0xfffffffd) == 8)) || (param_9 == 0x10)) {
        uVar6 = param_2 - param_9;
        if (*param_11 < uVar6) {
          if (DebugLevel < 0) {
            uVar1 = 0xfffffffc;
          }
          else {
            printk("AES_CCM_Decrypt: The PlainTextLength is not enough.\n");
            uVar1 = 0xfffffffc;
          }
        }
        else {
          __memzero(&local_48,0x10);
          __memzero(local_38,0x10);
          pbVar3 = &local_48;
          pbVar4 = (byte *)(param_5 + -1);
          local_48 = 0xeU - (char)param_6 | local_48;
          do {
            pbVar4 = pbVar4 + 1;
            pbVar3 = pbVar3 + 1;
            *pbVar3 = *pbVar4;
          } while (pbVar4 != (byte *)(param_5 + param_6 + -1));
          local_6c = 0x10;
          RT_AES_Encrypt(&local_48,0x10,param_3,0x10,local_38,&local_6c);
          __memzero(local_58,0x10);
          if (uVar6 < param_2) {
            pbVar4 = (byte *)(param_1 + (uVar6 - 1));
            pbVar7 = &local_39;
            pbVar3 = &bStack_59;
            do {
              pbVar4 = pbVar4 + 1;
              pbVar7 = pbVar7 + 1;
              pbVar3 = pbVar3 + 1;
              *pbVar3 = *pbVar4 ^ *pbVar7;
            } while (pbVar4 != (byte *)(param_1 + (param_2 - 1)));
          }
          if (uVar6 != 0) {
            uVar5 = 0;
            do {
              local_39 = local_39 + 1;
              local_6c = 0x10;
              RT_AES_Encrypt(&local_48,0x10,param_3,0x10,local_38,&local_6c);
              uVar8 = uVar6 - uVar5;
              if (0xf < uVar8) {
                uVar8 = 0x10;
              }
              if (uVar8 != 0) {
                iVar2 = uVar5 - 1;
                pbVar7 = (byte *)(param_1 + iVar2);
                pbVar3 = &local_39;
                pbVar4 = (byte *)(param_10 + iVar2);
                do {
                  pbVar7 = pbVar7 + 1;
                  pbVar3 = pbVar3 + 1;
                  pbVar4 = pbVar4 + 1;
                  *pbVar4 = *pbVar7 ^ *pbVar3;
                } while (pbVar7 != (byte *)(param_1 + uVar8 + iVar2));
              }
              uVar5 = uVar5 + uVar8;
            } while (uVar5 < uVar6);
          }
          *param_11 = uVar6;
          AES_CCM_MAC(param_10,uVar6,param_3,0x10,param_5,param_6,param_7,param_8,param_9,auStack_68
                     );
          iVar2 = memcmp(local_58,auStack_68,param_9);
          uVar1 = 0;
          if (iVar2 != 0) {
            if (DebugLevel < 0) {
              uVar1 = 0xfffffffb;
            }
            else {
              printk("AES_CCM_Decrypt: The MIC does not match.\n");
              uVar1 = 0xfffffffb;
            }
          }
        }
      }
      else if (DebugLevel < 0) {
        uVar1 = 0xfffffffd;
      }
      else {
        printk("AES_CCM_Decrypt: The MAC length  must be 4, 6, 8, 10, 12, 14, or 16 bytes\n");
        uVar1 = 0xfffffffd;
      }
    }
    else if (DebugLevel < 0) {
      uVar1 = 0xfffffffe;
    }
    else {
      printk("AES_CCM_Decrypt: A valid nonce length is 7-13 bytes\n");
      uVar1 = 0xfffffffe;
    }
  }
  else if (DebugLevel < 0) {
    uVar1 = 0xffffffff;
  }
  else {
    printk("AES_CCM_Decrypt: The key length must be %d bytes\n",0x10);
    uVar1 = 0xffffffff;
  }
  return uVar1;
}

