// module: mt7915.ko
// function: RTMPIoctlGetMacTableStaInfo @ 0xdc99c
// size: 496 bytes
//

void RTMPIoctlGetMacTableStaInfo(int param_1,char *param_2)

{
  bool bVar1;
  bool bVar2;
  int *piVar3;
  undefined2 uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  undefined4 *puVar9;
  undefined1 auStack_30 [4];
  int *local_2c [2];
  
  bVar1 = false;
  local_2c[0] = (int *)0x0;
  os_alloc_mem(0,local_2c,0xbbc);
  if (local_2c[0] == (int *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s: Allocate memory fail!!!\n","RTMPIoctlGetMacTableStaInfo");
    }
  }
  else {
    __memzero(local_2c[0],0xbbc);
    puVar9 = (undefined4 *)(param_1 + 0xa1e0c);
    iVar7 = 0;
    while( true ) {
      iVar5 = HcGetMaxStaNum(param_1);
      if (iVar5 <= iVar7) break;
      if ((undefined4 *)puVar9[-0x39] != (undefined4 *)0x0) {
        iVar5 = strcmp(param_2,*(char **)puVar9[-0x39]);
        bVar1 = iVar5 == 0;
      }
      piVar3 = local_2c[0];
      if (puVar9[-0x3b] == 0x20001) {
        bVar2 = bVar1;
        if (puVar9[4] != 2) {
          bVar2 = false;
        }
        if (bVar2) {
          iVar5 = *local_2c[0];
          *(undefined1 *)(local_2c[0] + iVar5 * 10 + 1) = *(undefined1 *)(puVar9 + -2);
          *(undefined4 *)((int)local_2c[0] + iVar5 * 0x28 + 5) = *puVar9;
          *(undefined2 *)((int)local_2c[0] + iVar5 * 0x28 + 9) = *(undefined2 *)(puVar9 + 1);
          *(ushort *)(local_2c[0] + iVar5 * 10 + 3) = (ushort)*(byte *)(puVar9 + 3);
          *(undefined1 *)((int)local_2c[0] + iVar5 * 0x28 + 0xe) = *(undefined1 *)(puVar9 + 0x283);
          *(undefined1 *)((int)local_2c[0] + iVar5 * 0x28 + 0xf) = *(undefined1 *)(puVar9 + 0x309);
          *(undefined1 *)(local_2c[0] + iVar5 * 10 + 4) = *(undefined1 *)(puVar9 + 8);
          *(undefined1 *)((int)local_2c[0] + iVar5 * 0x28 + 0x11) =
               *(undefined1 *)((int)puVar9 + 0x21);
          *(undefined1 *)((int)local_2c[0] + iVar5 * 0x28 + 0x12) =
               *(undefined1 *)((int)puVar9 + 0x22);
          local_2c[0][iVar5 * 10 + 5] = puVar9[0x286];
          uVar4 = RTMPGetLastTxRate(param_1,puVar9 + -0x3b);
          *(undefined2 *)(piVar3 + iVar5 * 10 + 6) = uVar4;
          piVar3[iVar5 * 10 + 7] = puVar9[0x13];
          *local_2c[0] = *local_2c[0] + 1;
        }
      }
      puVar9 = puVar9 + 0x530;
      iVar7 = iVar7 + 1;
    }
    uVar6 = *(uint *)(param_2 + 0x10);
    param_2[0x14] = -0x44;
    param_2[0x15] = '\v';
    uVar8 = *(uint *)(((uint)auStack_30 & 0xffffe000) + 8);
    if (uVar6 < 0xfffff444 && uVar6 + 0xbbc <= uVar8) {
      uVar8 = 0;
    }
    if (((uVar8 != 0) || (iVar7 = __copy_to_user(uVar6,local_2c[0]), iVar7 != 0)) &&
       (2 < DebugLevel)) {
      printk("%s: copy_to_user() fail\n","RTMPIoctlGetMacTableStaInfo");
    }
    if (local_2c[0] != (int *)0x0) {
      os_free_mem();
    }
  }
  return;
}

