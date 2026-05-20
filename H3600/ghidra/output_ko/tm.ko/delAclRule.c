// module: tm.ko
// function: delAclRule @ 0x58428
// size: 928 bytes
//

undefined4 delAclRule(int param_1,uint *param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int extraout_r3;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  undefined1 auStack_bc [16];
  ushort local_ac;
  undefined1 auStack_a8 [3];
  byte local_a5;
  byte local_a4;
  int local_a0;
  byte local_98;
  undefined1 auStack_6c [58];
  ushort local_32;
  
  __memzero(auStack_a8,0x3c);
  __memzero(auStack_bc,0x14);
  __memzero(auStack_6c,0x44);
  uVar9 = *(uint *)(param_1 + 0x10);
  if (0xf < uVar9) {
    printk("Extra Index Ram Addr Overflow, extIdexAddr=%d !\n",uVar9);
    return 0xfffffff4;
  }
  uVar6 = *(uint *)(param_1 + 0xc);
  uVar7 = uVar6 & 0xff;
  if ((uVar6 & 0x10000000) != 0) {
    uVar1 = uVar9 * 0x10;
    iVar4 = (uVar1 + (uVar6 & 0xf)) * 0x10;
    if (*(int *)(sa_rulesRecord + iVar4 + 0xc) != 0) {
      iVar2 = cla_get_extra_rule_table(uVar7,auStack_6c);
      if (iVar2 != 0) {
        return 0xfffffff4;
      }
      iVar3 = *(int *)(sa_rulesRecord + iVar4 + 0xc);
      uVar8 = (uint)(byte)local_32;
      iVar2 = extraout_r3;
      if (iVar3 != 1) {
        iVar2 = iVar3 + -1;
      }
      if (iVar3 != 1) {
        *(int *)(sa_rulesRecord + iVar4 + 0xc) = iVar2;
      }
      else {
        if (uVar1 + 1 == uVar7) {
          EN_V4FAST_EXTIDXTBL(1,uVar9 & 0xff,0);
          *(undefined4 *)(g_v4OutUsed + uVar9 * 4) = 0;
        }
        else {
          if (uVar9 == 10) {
            uVar5 = 3;
          }
          else {
            uVar5 = uVar1 + 3;
          }
          if (uVar5 == uVar7) {
            EN_V6FAST_EXTIDXTBL(1,uVar9 & 0xff,0);
            *(undefined4 *)(g_v6OutUsed + uVar9 * 4) = 0;
          }
          else if (uVar1 + 5 == uVar7) {
            EN_V4FAST_EXTIDXTBL(0,uVar9 & 0xff,0);
            *(undefined4 *)(g_v4OutUsed_3t + uVar9 * 4) = 0;
          }
          else {
            if (uVar9 == 10) {
              uVar5 = 7;
            }
            else {
              uVar5 = uVar1 + 7;
            }
            if (uVar5 == uVar7) {
              EN_V6FAST_EXTIDXTBL(0,uVar9 & 0xff,0);
              *(undefined4 *)(g_v6OutUsed_3t + uVar9 * 4) = 0;
            }
            else if (uVar7 != uVar1) {
              if (uVar9 == 10) {
                uVar5 = 2;
              }
              else {
                uVar5 = uVar1 + 2;
              }
              if ((uVar5 != uVar7) && (uVar1 + 4 != uVar7)) {
                if (uVar9 == 10) {
                  uVar5 = 6;
                }
                else {
                  uVar5 = uVar1 + 6;
                }
                if (uVar5 != uVar7) {
                  iVar4 = cla_get_extra_index_table(uVar9,auStack_bc);
                  if (iVar4 != 0) {
                    return 0xfffffff4;
                  }
                  local_ac = local_ac & ~(ushort)(1 << (uVar6 & 0xf));
                  iVar4 = cla_set_extra_index_table(uVar9,auStack_bc);
                  if (iVar4 != 0) {
                    return 0xfffffff4;
                  }
                }
              }
            }
          }
        }
        iVar4 = (uVar1 + (uVar6 & 0xf)) * 0x10;
        *(undefined4 *)(sa_rulesRecord + iVar4 + 8) = 0;
        *(undefined4 *)(sa_rulesRecord + iVar4 + 4) = 0;
        *(undefined4 *)(sa_rulesRecord + iVar4) = 0;
        *(undefined4 *)(sa_rulesRecord + iVar4 + 0xc) = 0;
      }
      uVar9 = *(uint *)(param_1 + 8);
      if ((uVar9 & 0x10000) == 0) {
        iVar4 = cla_get_hash_table(uVar9 & 0x7fff,auStack_a8);
        if (iVar4 != 0) {
          return 0xfffffff4;
        }
      }
      else {
        cla_get_external_hash_table(uVar9,((uint)local_32 << 0x17) >> 0x1b,auStack_a8);
      }
      if ((int)(uVar8 << 0x1c) < 0) {
        uVar9 = ((uint)(local_a0 << 0xc) >> 0x17) << 0x10 | 0x80000000;
      }
      else {
        uVar9 = (uint)local_a4 << 7 | (uint)(local_a5 >> 1);
      }
      *param_2 = uVar9;
      uVar9 = *(uint *)(param_1 + 8);
      local_98 = local_98 & 0xbf;
      if ((uVar9 & 0x10000) == 0) {
        uVar9 = uVar9 & 0x7fff;
        if (s_aclHashUsedCnt[uVar9] == '\x01') {
          iVar4 = cla_set_hash_table(uVar9,auStack_a8);
          if (iVar4 != 0) {
            return 0xfffffff4;
          }
          s_aclHashUsedCnt[*(uint *)(param_1 + 8) & 0x7fff] = 0;
        }
        else {
          s_aclHashUsedCnt[uVar9] = s_aclHashUsedCnt[uVar9] + -1;
        }
      }
      else {
        uVar9 = uVar9 & 0xffff;
        if (s_aclHashUsedCnt[uVar9 + 0x208] == '\x01') {
          *(byte *)(uVar9 * 0x40 + -0xefdffe9) = local_98;
          s_aclHashUsedCnt[*(ushort *)(param_1 + 8) + 0x208] = 0;
        }
        else {
          s_aclHashUsedCnt[uVar9 + 0x208] = s_aclHashUsedCnt[uVar9 + 0x208] + -1;
        }
      }
      if (TM_CLA_DEBUG != 0) {
        printk("delAclRule:hash addr=0x%x, rule addr=0x%x\n",*(undefined4 *)(param_1 + 8),
               *(undefined4 *)(param_1 + 4));
        printk("pp_flowId = 0x%x\n",*param_2);
        return 0;
      }
      return 0;
    }
  }
  printk("Rule to be deleted is not exist:\n");
  return 0xfffffff4;
}

