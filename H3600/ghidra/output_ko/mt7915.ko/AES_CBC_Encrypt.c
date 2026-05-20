// module: mt7915.ko
// function: AES_CBC_Encrypt @ 0x123774
// size: 808 bytes
//

void AES_CBC_Encrypt(void *param_1,uint param_2,undefined4 param_3,uint param_4,int param_5,
                    int param_6,int param_7,uint *param_8)

{
  uint uVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte *pbVar4;
  byte *pbVar5;
  int iVar6;
  uint uVar7;
  byte *pbVar8;
  byte *pbVar9;
  uint __n;
  int __n_00;
  byte *pbVar10;
  undefined4 *local_58;
  byte *local_54;
  undefined1 *local_50;
  undefined4 local_3c;
  undefined1 local_38 [15];
  byte abStack_29 [5];
  
  __n = param_2 & 0xf;
  __n_00 = 0x10 - __n;
  uVar7 = *param_8;
  if (uVar7 < __n_00 + param_2) {
    if (-1 < DebugLevel) {
      printk("AES_CBC_Encrypt: cipher text length is %d bytes < (plain text length %d bytes + padding size %d bytes).\n"
             ,uVar7,param_2,__n_00);
    }
  }
  else if ((param_4 & 0xfffffff7) == 0x10 || param_4 == 0x20) {
    iVar6 = 0;
    if (param_6 == 0x10) {
      if (0xf < param_2) {
        pbVar5 = (byte *)((int)&local_3c + 3);
        uVar1 = param_2 - 0x10 >> 4;
        pbVar8 = (byte *)((int)param_1 + -1);
LAB_001238a8:
        pbVar10 = (byte *)(param_5 + -1);
        pbVar3 = pbVar5;
        pbVar4 = pbVar8;
        do {
          pbVar4 = pbVar4 + 1;
          pbVar10 = pbVar10 + 1;
          pbVar3 = pbVar3 + 1;
          *pbVar3 = *pbVar4 ^ *pbVar10;
          pbVar2 = pbVar8 + 0x10;
          pbVar9 = pbVar8;
        } while (pbVar4 != pbVar8 + 0x10);
LAB_001238d4:
        pbVar8 = pbVar2;
        local_3c = uVar7 - iVar6;
        RT_AES_Encrypt(local_38,0x10,param_3,param_4,param_7 + iVar6,&local_3c);
        iVar6 = iVar6 + local_3c;
        if (pbVar9 == (byte *)((int)param_1 + uVar1 * 0x10 + -1)) {
          memmove(local_38,(void *)((int)param_1 + (uVar1 + 1) * 0x10),__n);
          memset(local_38 + __n,__n_00,__n_00);
          if (iVar6 != 0) {
            pbVar8 = (byte *)(param_7 + iVar6 + -0x11);
            do {
              pbVar5 = pbVar5 + 1;
              pbVar8 = pbVar8 + 1;
              *pbVar5 = *pbVar5 ^ *pbVar8;
            } while (pbVar5 != abStack_29);
            uVar7 = *param_8;
            goto LAB_001239c4;
          }
          uVar7 = *param_8;
          goto LAB_00123a10;
        }
        uVar7 = *param_8;
        if (iVar6 != 0) goto LAB_00123924;
        goto LAB_001238a8;
      }
      memcpy(local_38,param_1,param_2);
      memset(local_38 + __n,__n_00,__n_00);
LAB_00123a10:
      local_54 = (byte *)((int)&local_3c + 3);
      pbVar5 = (byte *)(param_5 + -1);
      do {
        local_54 = local_54 + 1;
        pbVar5 = pbVar5 + 1;
        *local_54 = *local_54 ^ *pbVar5;
      } while (local_54 != abStack_29);
      iVar6 = 0;
LAB_001239c4:
      local_50 = local_38;
      local_58 = &local_3c;
      local_3c = uVar7 - iVar6;
      RT_AES_Encrypt(local_50,0x10,param_3,param_4,param_7 + iVar6,local_58);
      *param_8 = iVar6 + local_3c;
    }
    else if (-1 < DebugLevel) {
      printk("AES_CBC_Encrypt: IV length is %d bytes, it must be %d bytes(128bits).\n",param_6,0x10)
      ;
    }
  }
  else if (-1 < DebugLevel) {
    printk("AES_CBC_Encrypt: key length is %d bytes, it must be %d, %d, or %d bytes(128, 192, or 256 bits).\n"
           ,param_4,0x10,0x18,0x20);
  }
  return;
LAB_00123924:
  pbVar10 = (byte *)(param_7 + iVar6 + -0x11);
  pbVar3 = pbVar8;
  pbVar4 = pbVar5;
  do {
    pbVar3 = pbVar3 + 1;
    pbVar10 = pbVar10 + 1;
    pbVar4 = pbVar4 + 1;
    *pbVar4 = *pbVar3 ^ *pbVar10;
    pbVar2 = pbVar8 + 0x10;
    pbVar9 = pbVar8;
  } while (pbVar3 != pbVar8 + 0x10);
  goto LAB_001238d4;
}

