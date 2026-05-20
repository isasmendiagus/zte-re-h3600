// module: mt7915.ko
// function: wlan_dbg_save_staoffline_record @ 0x158830
// size: 432 bytes
//

void wlan_dbg_save_staoffline_record(int param_1,uint param_2,int param_3,undefined4 param_4)

{
  undefined1 uVar1;
  undefined2 uVar2;
  int iVar3;
  undefined1 *__s2;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  if ((param_1 != 0) && (*(int *)(param_1 + 8) != 0)) {
    iVar3 = HcGetBandByWdev();
    uVar4 = *(uint *)((int)&g_ulWlanOffLineIndex + iVar3 * 4);
    if (uVar4 < 0x10) {
      if (uVar4 == 0) {
        iVar5 = 0xf;
      }
      else {
        iVar5 = uVar4 - 1;
      }
      iVar6 = iVar3 * 0x380 + iVar5 * 0x38;
      __s2 = g_arrstWlanOffline + iVar6;
      iVar5 = memcmp((undefined4 *)(param_1 + 0xec),__s2,6);
      if (((iVar5 == 0) && (*(ushort *)(g_arrstWlanOffline + iVar6 + 0x1e) == param_2)) &&
         (*(int *)(g_arrstWlanOffline + iVar6 + 8) == param_3)) {
        *(int *)(g_arrstWlanOffline + iVar6 + 0x10) =
             *(int *)(g_arrstWlanOffline + iVar6 + 0x10) + 1;
      }
      else {
        iVar5 = iVar3 * 0x380 + uVar4 * 0x38;
        __s2 = g_arrstWlanOffline + iVar5;
        *(undefined4 *)(g_arrstWlanOffline + iVar5 + 0x10) = 1;
        *(undefined4 *)(g_arrstWlanOffline + iVar5) = *(undefined4 *)(param_1 + 0xec);
        uVar2 = *(undefined2 *)(param_1 + 0xf0);
        *(uint *)((int)&g_ulWlanOffLineIndex + iVar3 * 4) = uVar4 + 1 & 0xf;
        *(undefined2 *)(g_arrstWlanOffline + iVar5 + 4) = uVar2;
      }
      *(int *)(__s2 + 8) = param_3;
      *(undefined4 *)(__s2 + 0xc) = param_4;
      *(undefined4 *)(__s2 + 0x14) = *(undefined4 *)(param_1 + 0xb04);
      __s2[0x18] = *(undefined1 *)(param_1 + 0x108);
      __s2[0x19] = *(undefined1 *)(param_1 + 0x109);
      __s2[0x1a] = *(undefined1 *)(param_1 + 0x10a);
      __s2[0x1b] = *(undefined1 *)(param_1 + 0x10b);
      __s2[0x1c] = *(undefined1 *)(param_1 + 0xaf8);
      uVar1 = *(undefined1 *)(param_1 + 0xd10);
      *(short *)(__s2 + 0x1e) = (short)param_2;
      __s2[0x1d] = uVar1;
      *(undefined4 *)(__s2 + 0x20) = *(undefined4 *)(param_1 + 0x134);
      *(undefined4 *)(__s2 + 0x24) = *(undefined4 *)(param_1 + 0x138);
      *(undefined4 *)(__s2 + 0x28) = *(undefined4 *)(param_1 + 0xae8);
      *(undefined4 *)(__s2 + 0x2c) = *(undefined4 *)(param_1 + 0x1378);
      *(undefined4 *)(__s2 + 0x30) = *(undefined4 *)(param_1 + 0x1360);
      *(undefined4 *)(__s2 + 0x34) = *(undefined4 *)(param_1 + 0x1364);
    }
  }
  return;
}

