// module: mt7915.ko
// function: AES_CBC_Decrypt @ 0x123a9c
// size: 428 bytes
//

void AES_CBC_Decrypt(int param_1,uint param_2,undefined4 param_3,uint param_4,int param_5,
                    int param_6,int param_7,int *param_8)

{
  byte *pbVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  int local_2c [2];
  
  if ((param_2 & 0xf) == 0) {
    if ((param_4 & 0xfffffff7) == 0x10 || param_4 == 0x20) {
      iVar4 = 0;
      if (param_6 == 0x10) {
        if (param_2 < 0x10) {
          iVar2 = -1;
        }
        else {
          do {
            local_2c[0] = *param_8 - iVar4;
            RT_AES_Decrypt(param_1,0x10,param_3,param_4,param_7 + iVar4,local_2c);
            if (iVar4 == 0) {
              pbVar3 = (byte *)(param_7 + -1);
              pbVar1 = (byte *)(param_5 + -1);
              do {
                pbVar3 = pbVar3 + 1;
                pbVar1 = pbVar1 + 1;
                *pbVar3 = *pbVar3 ^ *pbVar1;
              } while (pbVar3 != (byte *)(param_7 + 0xf));
            }
            else {
              pbVar3 = (byte *)(param_7 + iVar4 + -1);
              pbVar1 = (byte *)(param_1 + -0x11);
              do {
                pbVar3 = pbVar3 + 1;
                pbVar1 = pbVar1 + 1;
                *pbVar3 = *pbVar3 ^ *pbVar1;
              } while (pbVar3 != (byte *)(param_7 + iVar4 + 0xf));
            }
            param_2 = param_2 - 0x10;
            param_1 = param_1 + 0x10;
            iVar4 = iVar4 + local_2c[0];
          } while (0xf < param_2);
          iVar2 = iVar4 + -1;
        }
        *param_8 = iVar4 - (uint)*(byte *)(param_7 + iVar2);
      }
      else if (-1 < DebugLevel) {
        printk("AES_CBC_Decrypt: IV length is %d bytes, it must be %d bytes(128bits).\n",param_6,
               0x10);
      }
    }
    else if (-1 < DebugLevel) {
      printk("AES_CBC_Decrypt: key length is %d bytes, it must be %d, %d, or %d bytes(128, 192, or 256 bits).\n"
             ,param_4,0x10,0x18,0x20);
    }
  }
  else if (-1 < DebugLevel) {
    printk("AES_CBC_Decrypt: cipher text length is %d bytes, it can\'t be divided with no remainder by block size(%d).\n"
           ,param_2,0x10);
  }
  return;
}

