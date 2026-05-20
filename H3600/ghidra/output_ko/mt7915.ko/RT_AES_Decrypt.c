// module: mt7915.ko
// function: RT_AES_Decrypt @ 0x12259c
// size: 1260 bytes
//

void RT_AES_Decrypt(int param_1,int param_2,undefined4 param_3,uint param_4,int param_5,
                   uint *param_6)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  byte bVar7;
  byte bVar8;
  byte bVar9;
  byte bVar10;
  byte bVar11;
  byte bVar12;
  byte bVar13;
  byte bVar14;
  byte bVar15;
  byte bVar16;
  byte bVar17;
  byte bVar18;
  undefined1 uVar19;
  undefined1 uVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  byte *pbVar24;
  undefined1 *puVar25;
  int iVar26;
  int iVar27;
  int iVar28;
  undefined1 *puVar29;
  undefined1 *local_2c [2];
  
  local_2c[0] = (undefined1 *)0x0;
  if (*param_6 < 0x10) {
    if (-1 < DebugLevel) {
      printk("RT_AES_Decrypt: plain block size is %d bytes, it must be %d bytes(128 bits).\n",
             *param_6,0x10);
    }
  }
  else if ((param_4 & 0xfffffff7) == 0x10 || param_4 == 0x20) {
    iVar26 = 0;
    if (param_2 == 0x10) {
      os_alloc_mem(0,local_2c,0x100);
      if (local_2c[0] == (undefined1 *)0x0) {
        if (-1 < DebugLevel) {
          printk("%s: Allocate memory fail!!!\n","RT_AES_Decrypt");
        }
      }
      else {
        do {
          iVar22 = 0;
          do {
            iVar23 = iVar22 * 4;
            iVar21 = iVar26 * 4 + iVar22;
            iVar22 = iVar22 + 1;
            local_2c[0][iVar21] = *(undefined1 *)(param_1 + iVar26 + iVar23);
          } while (iVar22 != 4);
          iVar26 = iVar26 + 1;
        } while (iVar26 != 4);
        iVar22 = 0;
        RT_AES_KeyExpansion(param_3,param_4,local_2c[0]);
        iVar26 = ((param_4 >> 2) + 6) * 4;
        do {
          iVar23 = 0;
          do {
            iVar27 = iVar22 * 4 + iVar23;
            iVar21 = iVar23 + iVar22 * 0x3c;
            iVar23 = iVar23 + 1;
            local_2c[0][iVar27] = local_2c[0][iVar26 + iVar21 + 0x10] ^ local_2c[0][iVar27];
          } while (iVar23 != 4);
          iVar22 = iVar22 + 1;
        } while (iVar22 != 4);
        iVar22 = (param_4 >> 2) + 5;
        do {
          iVar26 = iVar26 + -4;
          iVar23 = 0;
          uVar1 = local_2c[0][4];
          uVar2 = local_2c[0][5];
          uVar3 = local_2c[0][6];
          uVar4 = local_2c[0][10];
          uVar5 = local_2c[0][0xb];
          local_2c[0][4] = local_2c[0][7];
          local_2c[0][5] = uVar1;
          uVar1 = local_2c[0][0xf];
          uVar6 = local_2c[0][0xe];
          local_2c[0][6] = uVar2;
          uVar2 = local_2c[0][0xd];
          local_2c[0][7] = uVar3;
          local_2c[0][10] = local_2c[0][8];
          local_2c[0][8] = uVar4;
          local_2c[0][0xb] = local_2c[0][9];
          local_2c[0][9] = uVar5;
          local_2c[0][0xf] = local_2c[0][0xc];
          local_2c[0][0xe] = uVar1;
          local_2c[0][0xd] = uVar6;
          local_2c[0][0xc] = uVar2;
          do {
            iVar21 = 0;
            do {
              iVar27 = iVar23 * 4 + iVar21;
              iVar21 = iVar21 + 1;
              local_2c[0][iVar27] = (&DAT_002981d4)[(byte)local_2c[0][iVar27]];
            } while (iVar21 != 4);
            iVar23 = iVar23 + 1;
          } while (iVar23 != 4);
          iVar23 = 0;
          do {
            iVar21 = 0;
            do {
              iVar28 = iVar23 * 4 + iVar21;
              iVar27 = iVar21 + iVar23 * 0x3c;
              iVar21 = iVar21 + 1;
              local_2c[0][iVar28] = local_2c[0][iVar26 + iVar27 + 0x10] ^ local_2c[0][iVar28];
            } while (iVar21 != 4);
            iVar23 = iVar23 + 1;
          } while (iVar23 != 4);
          iVar23 = 0;
          do {
            pbVar24 = local_2c[0] + iVar23;
            bVar7 = *pbVar24;
            bVar8 = pbVar24[4];
            bVar9 = pbVar24[8];
            bVar10 = pbVar24[0xc];
            bVar11 = (&DAT_002983d4)[bVar8];
            bVar12 = (&DAT_002985d4)[bVar7];
            local_2c[0][iVar23] =
                 (&DAT_002983d4)[bVar7] ^ (&DAT_002982d4)[bVar8] ^ (&DAT_002984d4)[bVar9] ^
                 (&DAT_002985d4)[bVar10];
            bVar13 = (&DAT_002985d4)[bVar8];
            bVar8 = (&DAT_002984d4)[bVar8];
            bVar14 = (&DAT_002984d4)[bVar7];
            iVar21 = iVar23 + 1;
            bVar7 = (&DAT_002982d4)[bVar7];
            bVar15 = (&DAT_002983d4)[bVar9];
            bVar16 = (&DAT_002985d4)[bVar9];
            bVar17 = (&DAT_002983d4)[bVar10];
            bVar18 = (&DAT_002982d4)[bVar10];
            local_2c[0][iVar23 + 4] =
                 (&DAT_002984d4)[bVar10] ^ (&DAT_002982d4)[bVar9] ^ bVar12 ^ bVar11;
            local_2c[0][iVar23 + 0xc] = bVar16 ^ bVar7 ^ bVar8 ^ bVar17;
            local_2c[0][iVar23 + 8] = bVar14 ^ bVar13 ^ bVar15 ^ bVar18;
            iVar23 = iVar21;
          } while (iVar21 != 4);
          iVar22 = iVar22 + -1;
        } while (iVar22 != 0);
        iVar26 = 0;
        uVar1 = local_2c[0][4];
        uVar2 = local_2c[0][5];
        uVar3 = local_2c[0][6];
        uVar4 = local_2c[0][10];
        uVar5 = local_2c[0][0xb];
        uVar6 = local_2c[0][0xf];
        uVar19 = local_2c[0][0xe];
        local_2c[0][4] = local_2c[0][7];
        uVar20 = local_2c[0][0xd];
        local_2c[0][5] = uVar1;
        local_2c[0][6] = uVar2;
        local_2c[0][7] = uVar3;
        local_2c[0][10] = local_2c[0][8];
        local_2c[0][8] = uVar4;
        local_2c[0][0xb] = local_2c[0][9];
        local_2c[0][9] = uVar5;
        local_2c[0][0xf] = local_2c[0][0xc];
        local_2c[0][0xe] = uVar6;
        local_2c[0][0xd] = uVar19;
        local_2c[0][0xc] = uVar20;
        do {
          iVar22 = 0;
          do {
            iVar23 = iVar26 * 4 + iVar22;
            iVar22 = iVar22 + 1;
            local_2c[0][iVar23] = (&DAT_002981d4)[(byte)local_2c[0][iVar23]];
          } while (iVar22 != 4);
          iVar26 = iVar26 + 1;
        } while (iVar26 != 4);
        iVar26 = 0;
        do {
          iVar22 = 0;
          do {
            iVar21 = iVar26 * 4 + iVar22;
            iVar23 = iVar22 + iVar26 * 0x3c;
            iVar22 = iVar22 + 1;
            local_2c[0][iVar21] = local_2c[0][iVar21] ^ local_2c[0][iVar23 + 0x10];
          } while (iVar22 != 4);
          iVar26 = iVar26 + 1;
        } while (iVar26 != 4);
        puVar29 = local_2c[0];
        do {
          iVar26 = 0;
          puVar25 = puVar29;
          do {
            *(undefined1 *)(param_5 + iVar26 * 4) = *puVar25;
            iVar26 = iVar26 + 1;
            puVar25 = puVar25 + 1;
          } while (iVar26 != 4);
          puVar29 = puVar29 + 4;
          param_5 = param_5 + 1;
        } while (puVar29 != local_2c[0] + 0x10);
        *param_6 = 0x10;
        if (local_2c[0] != (undefined1 *)0x0) {
          os_free_mem();
        }
      }
    }
    else if (-1 < DebugLevel) {
      printk("RT_AES_Decrypt: cipher block size is %d bytes, it must be %d bytes(128 bits).\n",
             param_2,0x10);
    }
  }
  else if (-1 < DebugLevel) {
    printk("RT_AES_Decrypt: key length is %d bytes, it must be %d, %d, or %d bytes(128, 192, or 256 bits).\n"
           ,param_4,0x10,0x18,0x20);
  }
  return;
}

