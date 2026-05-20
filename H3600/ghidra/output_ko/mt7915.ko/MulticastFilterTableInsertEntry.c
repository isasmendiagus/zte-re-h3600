// module: mt7915.ko
// function: MulticastFilterTableInsertEntry @ 0x240944
// size: 1168 bytes
//

undefined4
MulticastFilterTableInsertEntry
          (int param_1,byte *param_2,undefined4 param_3,uint param_4,void *param_5,
          undefined4 param_6)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  byte *__s1;
  byte *pbVar7;
  byte bVar8;
  uint uVar9;
  int iVar10;
  byte *local_3c;
  
  local_3c = *(byte **)(param_1 + 0xa77bc4);
  if (local_3c == (byte *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s Multicase filter table is not ready.\n","MulticastFilterTableInsertEntry");
    }
  }
  else {
    if (*local_3c < 0x40) {
      iVar2 = MulticastFilterTableLookup(local_3c,param_2,param_6);
      if (iVar2 == 0) {
        _raw_spin_lock_bh(local_3c + 0xc04);
        __s1 = local_3c + 0x214;
        iVar2 = 0;
        pbVar1 = local_3c + 0x204;
        do {
          pbVar7 = pbVar1;
          bVar8 = __s1[-0x10];
          if (bVar8 == 1) {
            if ((*(int *)(__s1 + -0xc) == 1) && ((12000 - jiffies) + *(int *)(__s1 + -8) < 0)) {
              iVar10 = *(int *)(__s1 + -4);
              uVar9 = (byte)(__s1[1] ^ pbVar7[0x10] ^ __s1[2] ^ __s1[3] ^ __s1[4] ^ __s1[5]) & 0x7f;
              iVar3 = *(int *)(local_3c + uVar9 * 4 + 4);
              if ((iVar10 == *(int *)(iVar3 + 0xc)) &&
                 (iVar5 = memcmp(__s1,(void *)(iVar3 + 0x10),6), iVar5 == 0)) {
                *(undefined4 *)(local_3c + uVar9 * 4 + 4) = *(undefined4 *)(iVar3 + 0x24);
                *local_3c = *local_3c - 1;
                if (2 < DebugLevel) {
                  printk("MCastFilterTableDeleteEntry 1 - Total= %d\n");
                }
              }
              else {
                do {
                  iVar5 = iVar3;
                  iVar3 = *(int *)(iVar5 + 0x24);
                  if (iVar3 == 0) goto LAB_00240bd8;
                } while ((iVar10 != *(int *)(iVar3 + 0xc)) ||
                        (iVar4 = memcmp(__s1,(void *)(iVar3 + 0x10),6), iVar4 != 0));
                *(undefined4 *)(iVar5 + 0x24) = *(undefined4 *)(iVar3 + 0x24);
                *local_3c = *local_3c - 1;
                if (2 < DebugLevel) {
                  printk("MCastFilterTableDeleteEntry 2 - Total= %d\n");
                }
              }
LAB_00240bd8:
              __s1[-0x10] = 0;
              FUN_0023ff78(local_3c,__s1 + 8);
              bVar8 = __s1[-0x10];
              goto LAB_00240ac4;
            }
          }
          else {
LAB_00240ac4:
            if (bVar8 == 0) {
              __memzero(pbVar7,0x28);
              iVar3 = iVar2 * 0x28;
              local_3c[iVar3 + 0x204] = 1;
              *(undefined4 *)(local_3c + iVar3 + 0x214) = *(undefined4 *)param_2;
              iVar10 = jiffies;
              *(undefined2 *)(local_3c + iVar3 + 0x218) = *(undefined2 *)(param_2 + 4);
              *(int *)(local_3c + iVar3 + 0x20c) = iVar10;
              *(uint *)(local_3c + iVar3 + 0x208) = param_4 & 0xf;
              *(undefined4 *)(local_3c + iVar3 + 0x210) = param_6;
              pbVar1 = local_3c + iVar3 + 0x220;
              pbVar1[0] = 0;
              pbVar1[1] = 0;
              pbVar1[2] = 0;
              pbVar1[3] = 0;
              pbVar1 = local_3c + iVar3 + 0x21c;
              pbVar1[0] = 0;
              pbVar1[1] = 0;
              pbVar1[2] = 0;
              pbVar1[3] = 0;
              local_3c[iVar3 + 0x224] = 0;
              if (param_5 != (void *)0x0) {
                FUN_00240208(local_3c,local_3c + iVar3 + 0x21c,param_5,param_4);
              }
              *local_3c = *local_3c + 1;
              if (2 < DebugLevel) {
                printk("MulticastFilterTableInsertEntry -IF(%s) allocate entry #%d, Total= %d\n",
                       param_6,iVar2);
              }
              goto LAB_00240cac;
            }
          }
          __s1 = __s1 + 0x28;
          iVar2 = iVar2 + 1;
          pbVar1 = pbVar7 + 0x28;
        } while (__s1 != local_3c + 0xc14);
        if (pbVar7 != (byte *)0x0) {
LAB_00240cac:
          uVar9 = (byte)(*param_2 ^ param_2[1] ^ param_2[2] ^ param_2[3] ^ param_2[4] ^ param_2[5])
                  & 0x7f;
          iVar2 = *(int *)(local_3c + uVar9 * 4 + 4);
          if (*(int *)(local_3c + uVar9 * 4 + 4) == 0) {
            *(byte **)(local_3c + uVar9 * 4 + 4) = pbVar7;
          }
          else {
            do {
              iVar3 = iVar2;
              iVar2 = *(int *)(iVar3 + 0x24);
            } while (iVar2 != 0);
            *(byte **)(iVar3 + 0x24) = pbVar7;
          }
        }
      }
      else {
        if (param_5 == (void *)0x0) {
          return 0;
        }
        for (piVar6 = *(int **)(iVar2 + 0x18); piVar6 != (int *)0x0; piVar6 = (int *)*piVar6) {
          iVar3 = memcmp(param_5,piVar6 + 1,6);
          if (iVar3 == 0) {
            if (DebugLevel < 0) {
              return 0;
            }
            printk("%s: already in Members list.\n","MulticastFilterTableInsertEntry");
            return 0;
          }
        }
        _raw_spin_lock_bh(local_3c + 0xc04);
        FUN_00240208(local_3c,iVar2 + 0x18,param_5,param_4);
      }
      local_3c = local_3c + 0xc04;
      _raw_spin_unlock_bh(local_3c);
      return 1;
    }
    if (-1 < DebugLevel) {
      printk("%s Multicase filter table full. max-entries = %d\n","MulticastFilterTableInsertEntry",
             0x40);
    }
  }
  return 0;
}

