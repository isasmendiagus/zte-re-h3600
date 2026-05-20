// module: mt7915.ko
// function: RT_AES_Encrypt @ 0x122088
// size: 1296 bytes
//

void RT_AES_Encrypt(int param_1,int param_2,undefined4 param_3,uint param_4,int param_5,
                   uint *param_6)

{
  undefined1 uVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  byte bVar7;
  byte bVar8;
  byte bVar9;
  byte bVar10;
  byte bVar11;
  byte bVar12;
  undefined1 uVar13;
  undefined1 uVar14;
  undefined1 uVar15;
  undefined1 uVar16;
  undefined1 uVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  undefined1 *puVar21;
  uint uVar22;
  int iVar23;
  int iVar24;
  undefined1 *puVar25;
  uint local_38;
  undefined1 *local_2c [2];
  
  local_2c[0] = (undefined1 *)0x0;
  if (param_2 == 0x10) {
    if ((param_4 & 0xfffffff7) == 0x10 || param_4 == 0x20) {
      iVar23 = 0;
      if (*param_6 < 0x10) {
        if (-1 < DebugLevel) {
          printk("RT_AES_Encrypt: cipher block size is %d bytes, it must be %d bytes(128 bits).\n",
                 *param_6,0x10);
        }
      }
      else {
        os_alloc_mem(0,local_2c,0x100);
        if (local_2c[0] == (undefined1 *)0x0) {
          if (-1 < DebugLevel) {
            printk("%s: Allocate memory fail!!!\n","RT_AES_Encrypt");
          }
        }
        else {
          do {
            iVar19 = 0;
            do {
              iVar20 = iVar19 * 4;
              iVar18 = iVar23 * 4 + iVar19;
              iVar19 = iVar19 + 1;
              local_2c[0][iVar18] = *(undefined1 *)(param_1 + iVar23 + iVar20);
            } while (iVar19 != 4);
            iVar23 = iVar23 + 1;
          } while (iVar23 != 4);
          iVar23 = 0;
          RT_AES_KeyExpansion(param_3,param_4,local_2c[0]);
          uVar22 = (param_4 >> 2) + 6;
          do {
            iVar19 = 0;
            do {
              iVar18 = iVar23 * 4 + iVar19;
              iVar20 = iVar19 + iVar23 * 0x3c;
              iVar19 = iVar19 + 1;
              local_2c[0][iVar18] = local_2c[0][iVar18] ^ local_2c[0][iVar20 + 0x10];
            } while (iVar19 != 4);
            iVar23 = iVar23 + 1;
          } while (iVar23 != 4);
          if (uVar22 < 2) {
            iVar23 = 4;
          }
          else {
            local_38 = 1;
            do {
              iVar23 = 0;
              do {
                iVar19 = 0;
                do {
                  iVar20 = iVar23 * 4 + iVar19;
                  iVar19 = iVar19 + 1;
                  local_2c[0][iVar20] = (&DAT_00297eb4)[(byte)local_2c[0][iVar20]];
                } while (iVar19 != 4);
                iVar23 = iVar23 + 1;
              } while (iVar23 != 4);
              uVar1 = local_2c[0][6];
              bVar2 = local_2c[0][0xf];
              bVar3 = local_2c[0][5];
              bVar4 = local_2c[0][10];
              local_2c[0][6] = local_2c[0][7];
              uVar5 = local_2c[0][0xd];
              local_2c[0][7] = local_2c[0][4];
              uVar6 = local_2c[0][9];
              local_2c[0][5] = uVar1;
              uVar1 = local_2c[0][0xe];
              local_2c[0][0xd] = local_2c[0][0xc];
              local_2c[0][0xe] = uVar5;
              local_2c[0][4] = bVar3;
              local_2c[0][10] = local_2c[0][8];
              local_2c[0][8] = bVar4;
              local_2c[0][9] = local_2c[0][0xb];
              local_2c[0][0xb] = uVar6;
              local_2c[0][0xf] = uVar1;
              local_2c[0][0xc] = bVar2;
              iVar23 = 0;
              while( true ) {
                bVar7 = local_2c[0][iVar23];
                bVar8 = (&DAT_002980c4)[bVar3];
                bVar9 = (&DAT_002980c4)[bVar2];
                local_2c[0][iVar23] =
                     (&DAT_00297fc4)[bVar3] ^ bVar2 ^ bVar4 ^ (&DAT_002980c4)[bVar7];
                bVar10 = (&DAT_002980c4)[bVar4];
                bVar11 = (&DAT_00297fc4)[bVar2];
                bVar12 = (&DAT_00297fc4)[bVar4];
                local_2c[0][iVar23 + 0xc] = (&DAT_00297fc4)[bVar7] ^ bVar3 ^ bVar4 ^ bVar9;
                local_2c[0][iVar23 + 4] = bVar2 ^ bVar7 ^ bVar8 ^ bVar12;
                local_2c[0][iVar23 + 8] = bVar11 ^ bVar7 ^ bVar3 ^ bVar10;
                if (iVar23 + 1 == 4) break;
                bVar3 = local_2c[0][iVar23 + 5];
                bVar4 = local_2c[0][iVar23 + 9];
                bVar2 = local_2c[0][iVar23 + 0xd];
                iVar23 = iVar23 + 1;
              }
              iVar23 = 0;
              do {
                iVar19 = 0;
                do {
                  iVar18 = iVar23 * 4 + iVar19;
                  iVar20 = iVar19 + iVar23 * 0x3c;
                  iVar19 = iVar19 + 1;
                  local_2c[0][iVar18] =
                       local_2c[0][local_38 * 4 + iVar20 + 0x10] ^ local_2c[0][iVar18];
                } while (iVar19 != 4);
                iVar23 = iVar23 + 1;
              } while (iVar23 != 4);
              local_38 = local_38 + 1;
            } while (uVar22 != local_38);
            iVar23 = uVar22 * 4;
          }
          iVar19 = 0;
          do {
            iVar20 = 0;
            do {
              iVar18 = iVar19 * 4 + iVar20;
              iVar20 = iVar20 + 1;
              local_2c[0][iVar18] = (&DAT_00297eb4)[(byte)local_2c[0][iVar18]];
            } while (iVar20 != 4);
            iVar19 = iVar19 + 1;
          } while (iVar19 != 4);
          iVar19 = 0;
          uVar1 = local_2c[0][8];
          uVar5 = local_2c[0][4];
          uVar6 = local_2c[0][7];
          uVar13 = local_2c[0][6];
          uVar14 = local_2c[0][9];
          uVar15 = local_2c[0][0xf];
          uVar16 = local_2c[0][0xc];
          uVar17 = local_2c[0][0xd];
          local_2c[0][8] = local_2c[0][10];
          local_2c[0][4] = local_2c[0][5];
          local_2c[0][7] = uVar5;
          local_2c[0][6] = uVar6;
          local_2c[0][5] = uVar13;
          local_2c[0][10] = uVar1;
          local_2c[0][9] = local_2c[0][0xb];
          local_2c[0][0xb] = uVar14;
          local_2c[0][0xf] = local_2c[0][0xe];
          local_2c[0][0xc] = uVar15;
          local_2c[0][0xd] = uVar16;
          local_2c[0][0xe] = uVar17;
          do {
            iVar20 = 0;
            do {
              iVar24 = iVar19 * 4 + iVar20;
              iVar18 = iVar20 + iVar19 * 0x3c;
              iVar20 = iVar20 + 1;
              local_2c[0][iVar24] = local_2c[0][iVar23 + iVar18 + 0x10] ^ local_2c[0][iVar24];
            } while (iVar20 != 4);
            iVar19 = iVar19 + 1;
          } while (iVar19 != 4);
          puVar25 = local_2c[0];
          do {
            iVar23 = 0;
            puVar21 = puVar25;
            do {
              *(undefined1 *)(param_5 + iVar23 * 4) = *puVar21;
              iVar23 = iVar23 + 1;
              puVar21 = puVar21 + 1;
            } while (iVar23 != 4);
            puVar25 = puVar25 + 4;
            param_5 = param_5 + 1;
          } while (puVar25 != local_2c[0] + 0x10);
          *param_6 = 0x10;
          if (local_2c[0] != (undefined1 *)0x0) {
            os_free_mem();
          }
        }
      }
    }
    else if (-1 < DebugLevel) {
      printk("RT_AES_Encrypt: key length is %d bytes, it must be %d, %d, or %d bytes(128, 192, or 256 bits).\n"
             ,param_4,0x10,0x18,0x20);
    }
  }
  else if (-1 < DebugLevel) {
    printk("RT_AES_Encrypt: plain block size is %d bytes, it must be %d bytes(128 bits).\n",param_2,
           0x10);
  }
  return;
}

