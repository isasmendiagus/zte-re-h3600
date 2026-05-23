// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_giwscan @ 0x6258c
// size: 904 bytes
//

undefined4 RtmpIoctl_rt_ioctl_giwscan(int *param_1,int param_2)

{
  ushort *puVar1;
  byte bVar2;
  undefined2 uVar3;
  uint *puVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  int iVar8;
  undefined4 uVar9;
  int iVar10;
  uint *puVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  int iVar14;
  byte local_58;
  int local_50;
  byte local_48;
  
  puVar4 = (uint *)get_scan_tab_by_wdev
                             (param_1,param_1 + *(int *)(*param_1 + 0x3c) * 0x84dec + 0xdb6d6);
  *(undefined4 *)(param_2 + 4) = 0;
  uVar5 = *puVar4;
  *(uint *)(param_2 + 4) = uVar5;
  uVar9 = 0;
  if (uVar5 != 0) {
    os_alloc_mem(0,param_2 + 8,*puVar4 * 0x6c);
    local_50 = *(int *)(param_2 + 8);
    if (local_50 != 0) {
      if (*puVar4 != 0) {
        iVar10 = 0;
        uVar5 = 0;
        puVar11 = puVar4;
        while( true ) {
          iVar8 = uVar5 * 0xaf4;
          uVar5 = uVar5 + 1;
          uVar6 = (uint)*(byte *)((int)puVar4 + iVar8 + 0x3d);
          *(undefined4 *)(local_50 + iVar10) = *(undefined4 *)((int)puVar11 + 0xe);
          iVar8 = local_50 + iVar10;
          *(undefined2 *)(iVar8 + 4) = *(undefined2 *)((int)puVar11 + 0x12);
          iVar10 = iVar10 + 0x6c;
          *(char *)(iVar8 + 6) = (char)puVar11[5];
          *(char *)(iVar8 + 7) = (char)puVar11[7];
          puVar7 = puVar11 + 2;
          if ((puVar11[0x2b4] & 1) != 0) {
            *(undefined1 *)(iVar8 + 8) = 1;
          }
          uVar12 = *(undefined4 *)((int)puVar11 + 0x26);
          uVar9 = *(undefined4 *)((int)puVar11 + 0x2a);
          *(undefined4 *)(iVar8 + 9) = *(undefined4 *)((int)puVar11 + 0x22);
          *(undefined4 *)(iVar8 + 0xd) = uVar12;
          *(undefined4 *)(iVar8 + 0x11) = uVar9;
          *(undefined1 *)(iVar8 + 0x15) = *(undefined1 *)((int)puVar11 + 0x2e);
          uVar9 = *(undefined4 *)((int)puVar11 + 0x33);
          uVar12 = *(undefined4 *)((int)puVar11 + 0x37);
          *(undefined4 *)(iVar8 + 0x16) = *(undefined4 *)((int)puVar11 + 0x2f);
          *(undefined4 *)(iVar8 + 0x1a) = uVar9;
          *(undefined4 *)(iVar8 + 0x1e) = uVar12;
          *(undefined1 *)(iVar8 + 0x22) = *(undefined1 *)((int)puVar11 + 0x3b);
          *(char *)(iVar8 + 0x23) = (char)puVar11[0x27];
          uVar12 = *(undefined4 *)((int)puVar11 + 0xa1);
          uVar9 = *(undefined4 *)((int)puVar11 + 0xa5);
          uVar13 = *(undefined4 *)((int)puVar11 + 0xa9);
          *(undefined4 *)(iVar8 + 0x24) = *(undefined4 *)((int)puVar11 + 0x9d);
          *(undefined4 *)(iVar8 + 0x28) = uVar12;
          *(undefined4 *)(iVar8 + 0x2c) = uVar9;
          *(undefined4 *)(iVar8 + 0x30) = uVar13;
          uVar13 = *(undefined4 *)((int)puVar11 + 0xad);
          uVar12 = *(undefined4 *)((int)puVar11 + 0xb1);
          uVar9 = *(undefined4 *)((int)puVar11 + 0xb5);
          *(undefined4 *)(iVar8 + 0x40) = *(undefined4 *)((int)puVar11 + 0xb9);
          *(undefined4 *)(iVar8 + 0x34) = uVar13;
          *(undefined4 *)(iVar8 + 0x38) = uVar12;
          *(undefined4 *)(iVar8 + 0x3c) = uVar9;
          local_58 = (byte)((uVar6 << 0x1e) >> 0x1f);
          uVar3 = *(undefined2 *)((int)puVar11 + 0x92);
          *(byte *)(iVar8 + 0x46) = local_58;
          *(undefined2 *)(iVar8 + 0x44) = uVar3;
          local_48 = (byte)((uVar6 << 0x19) >> 0x1f);
          local_50._0_1_ = (byte)((uVar6 << 0x1a) >> 0x1f);
          *(byte *)(iVar8 + 0x47) = local_48;
          *(byte *)(iVar8 + 0x48) = (byte)local_50;
          *(undefined1 *)(iVar8 + 0x49) = *(undefined1 *)((int)puVar11 + 0x41);
          *(ushort *)(iVar8 + 0x4a) = (ushort)(byte)puVar11[0x150];
          *(int *)(iVar8 + 0x4c) = (int)puVar11 + 0x541;
          *(ushort *)(iVar8 + 0x50) = (ushort)*(byte *)((int)puVar11 + 0x5c1);
          *(int *)(iVar8 + 0x54) = (int)puVar11 + 0x5c2;
          bVar2 = *(byte *)((int)puVar11 + 0x642);
          *(int *)(iVar8 + 0x5c) = (int)puVar11 + 0x643;
          *(ushort *)(iVar8 + 0x58) = (ushort)bVar2;
          puVar1 = (ushort *)((int)puVar11 + 0x92);
          puVar11 = puVar11 + 0x2bd;
          *(byte *)(iVar8 + 0x60) = (byte)(((uint)*puVar1 << 0x1b) >> 0x1f);
          FUN_00059bdc(iVar8 + 0x61,puVar7);
          if (*puVar4 <= uVar5) break;
          local_50 = *(int *)(param_2 + 8);
        }
      }
      iVar10 = param_1[0x28ddda];
      iVar14 = param_1[0x28dddb];
      iVar8 = param_1[0x28dddc];
      *(int *)(param_2 + 0xc) = param_1[0x28ddd9];
      *(int *)(param_2 + 0x10) = iVar10;
      *(int *)(param_2 + 0x18) = iVar8;
      *(int *)(param_2 + 0x14) = iVar14;
      uVar13 = *(undefined4 *)((int)param_1 + 0xa377b1);
      uVar12 = *(undefined4 *)((int)param_1 + 0xa377b5);
      uVar9 = *(undefined4 *)((int)param_1 + 0xa377b9);
      *(undefined4 *)(param_2 + 0x1c) = *(undefined4 *)((int)param_1 + 0xa377ad);
      *(undefined4 *)(param_2 + 0x20) = uVar13;
      *(undefined4 *)(param_2 + 0x24) = uVar12;
      *(undefined4 *)(param_2 + 0x28) = uVar9;
      uVar13 = *(undefined4 *)((int)param_1 + 0xa377fa);
      uVar9 = *(undefined4 *)((int)param_1 + 0xa377fe);
      uVar12 = *(undefined4 *)((int)param_1 + 0xa37802);
      *(undefined4 *)(param_2 + 0x2c) = *(undefined4 *)((int)param_1 + 0xa377f6);
      *(undefined4 *)(param_2 + 0x30) = uVar13;
      *(undefined4 *)(param_2 + 0x34) = uVar9;
      *(undefined4 *)(param_2 + 0x38) = uVar12;
      uVar9 = *(undefined4 *)((int)param_1 + 0xa37843);
      uVar12 = *(undefined4 *)((int)param_1 + 0xa37847);
      uVar13 = *(undefined4 *)((int)param_1 + 0xa3784b);
      *(undefined4 *)(param_2 + 0x3c) = *(undefined4 *)((int)param_1 + 0xa3783f);
      *(undefined4 *)(param_2 + 0x40) = uVar9;
      *(undefined4 *)(param_2 + 0x44) = uVar12;
      *(undefined4 *)(param_2 + 0x48) = uVar13;
      return 0;
    }
    if (DebugLevel < 0) {
      uVar9 = 1;
    }
    else {
      printk("Allocate memory fail!\n");
      uVar9 = 1;
    }
  }
  return uVar9;
}

