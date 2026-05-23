// module: mt7915.ko
// function: PhyStatGetRssi @ 0x1529d8
// size: 768 bytes
//

undefined4 PhyStatGetRssi(int param_1,uint param_2,int param_3,byte *param_4)

{
  longlong lVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  uint uVar6;
  uint uVar7;
  undefined1 *puVar8;
  undefined8 uVar9;
  char local_2c [8];
  
  local_2c[0] = '\0';
  local_2c[1] = '\0';
  local_2c[2] = '\0';
  local_2c[3] = '\0';
  if (param_4 == (byte *)0x0 || param_3 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: null pointer for content buffer.\n","PhyStatGetRssi");
      return 1;
    }
  }
  else if (param_2 < 2) {
    if (((*(uint *)(param_1 + 0xa3ac14) & 1) != 0) ||
       ((*(int *)(param_1 + 0xa77bb4) == 1 &&
        ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) != 0)))) {
      puVar8 = (undefined1 *)(param_3 + -1);
      *param_4 = 4;
      puVar5 = (undefined4 *)(param_1 + param_2 * 0x168 + 0xa7bf80);
      do {
        puVar5 = puVar5 + 1;
        puVar8 = puVar8 + 1;
        *puVar8 = (char)*puVar5;
      } while (puVar5 != (undefined4 *)(param_1 + param_2 * 0x168 + 0xa7bf90));
      if (3 < DebugLevel) {
        param_1 = param_2 * 0x168 + param_1;
        printk("%s: rssi: %d, %d, %d, %d.\n","PhyStatGetRssi",*(undefined4 *)(param_1 + 0xa7bf84),
               *(undefined4 *)(param_1 + 0xa7bf88),*(undefined4 *)(param_1 + 0xa7bf8c),
               *(undefined4 *)(param_1 + 0xa7bf90));
      }
      return 0;
    }
    uVar6 = 0;
    uVar2 = param_2;
    iVar4 = *(int *)(param_1 + 0xa77bb4);
    do {
      do {
        uVar7 = uVar6 & 0xffff;
        uVar9 = HcGetMaxStaNum(param_1,uVar2,iVar4);
        uVar2 = (uint)((ulonglong)uVar9 >> 0x20);
        uVar6 = uVar6 + 1;
        iVar3 = param_1 + uVar7 * 0x14c0;
        if ((uint)uVar9 <= uVar7) {
          *param_4 = 4;
          goto LAB_00152c30;
        }
        iVar4 = iVar3;
      } while ((*(int *)(iVar3 + 0xa1d20) != 0x20001) ||
              (iVar4 = *(int *)(iVar3 + 0xa1e1c), iVar4 != 2));
      lVar1 = (ulonglong)*(byte *)(iVar3 + 0xa1e04) * 0xcccccccd;
      iVar4 = (int)lVar1;
    } while ((uint)((int)((ulonglong)lVar1 >> 0x20) << 0x16) >> 0x18 != param_2);
    *param_4 = 4;
    if (param_1 + uVar7 * 0x14c0 + 0xa1d20 != 0) {
      chip_get_rssi(param_1,*(undefined2 *)(iVar3 + 0xa1e00),local_2c);
      if (*param_4 != 0) {
        uVar2 = 0;
        do {
          *(char *)(param_3 + uVar2) = local_2c[uVar2];
          uVar2 = uVar2 + 1 & 0xffff;
        } while (uVar2 < *param_4);
      }
      if (3 < DebugLevel) {
        printk("%s: wcid: %d, rssi: %d, %d, %d, %d.\n","PhyStatGetRssi",
               *(undefined2 *)(uVar7 * 0x14c0 + param_1 + 0xa1e00),(int)local_2c[0],(int)local_2c[1]
               ,(int)local_2c[2],(int)local_2c[3]);
        return 0;
      }
      return 0;
    }
LAB_00152c30:
    if (-1 < DebugLevel) {
      printk("%s: invalid entry. no station link up.\n","PhyStatGetRssi");
      return 1;
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s: invalid band index(%d).\n","PhyStatGetRssi",param_2);
  }
  return 1;
}

