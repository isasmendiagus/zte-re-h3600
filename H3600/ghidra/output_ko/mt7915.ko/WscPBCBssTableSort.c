// module: mt7915.ko
// function: WscPBCBssTableSort @ 0x1e7ffc
// size: 756 bytes
//

void WscPBCBssTableSort(int param_1,int param_2)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  uint *puVar7;
  undefined4 *puVar8;
  uint uVar9;
  int local_2c [2];
  
  uVar6 = *(undefined4 *)(param_2 + 0x29ec);
  local_2c[0] = 0;
  puVar1 = (uint *)get_scan_tab_by_wdev(param_1,uVar6);
  iVar2 = GetStaCfgByWdev(param_1,uVar6);
  if (iVar2 == 0) {
    printk(&_LC163,0x285f);
    dump_stack();
  }
  iVar3 = HcGetBandByWdev(uVar6);
  os_alloc_mem(0,local_2c,0x1f8);
  if (local_2c[0] == 0) {
    if (-1 < DebugLevel) {
      printk("%s: Allocate memory fail!!!\n","WscPBCBssTableSort");
    }
  }
  else {
    __memzero(local_2c[0],0x3f);
    *(undefined1 *)(param_2 + 0x4c) = 0;
    uVar5 = *puVar1;
    if (uVar5 != 0) {
      puVar7 = puVar1 + 2;
      uVar9 = 0;
      do {
        if ((short)puVar7[0x3b] != 0) {
          iVar4 = RcGetBandIdxByChannel(*(undefined4 *)(param_1 + 0xa797a0),(char)puVar7[3]);
          if ((iVar3 == iVar4) && ((iVar2 == 0 || ((char)puVar7[5] == *(char *)(iVar2 + 0x4060)))))
          {
            iVar4 = WscBssWpsIESearchForPBC
                              (param_1,param_2,puVar7,local_2c[0],(short)puVar7[0x3b],
                               (int)puVar7 + 0xee);
            if (iVar4 == 0) {
              WscBssWpsIESearchForPBC
                        (param_1,param_2,puVar7,local_2c[0],*(undefined2 *)((int)puVar7 + 0x4ee),
                         puVar7[0x13c]);
            }
          }
          uVar5 = *puVar1;
        }
        uVar9 = uVar9 + 1;
        puVar7 = puVar7 + 0x2bd;
      } while (uVar9 < uVar5);
      if (*(char *)(param_2 + 0x4c) == '\x01') {
        RTMPZeroMemory(param_2 + 0x28,0x24);
        puVar8 = (undefined4 *)(param_2 + 0x4d);
        RTMPMoveMemory(param_2 + 0x2c,local_2c[0] + 0x18,*(undefined1 *)(local_2c[0] + 0x38));
        *(uint *)(param_2 + 0x28) = (uint)*(byte *)(local_2c[0] + 0x38);
        RTMPZeroMemory(puVar8,6);
        RTMPMoveMemory(puVar8,local_2c[0] + 0x10,6);
        RTMPZeroMemory(param_2 + 0x66,6);
        RTMPMoveMemory(param_2 + 0x66,local_2c[0] + 0x39,6);
        if ((iVar2 != 0) &&
           (*(undefined1 *)(iVar2 + 0x4165) = *(undefined1 *)(local_2c[0] + 0x16),
           (*(byte *)(param_1 + 0x286294) & 3) == 3)) {
          *(undefined1 *)(iVar2 + 0x4165) = *(undefined1 *)(local_2c[0] + 0x16);
          *(undefined4 *)(iVar2 + 0x213303) = *puVar8;
          *(undefined2 *)(iVar2 + 0x213307) = *(undefined2 *)(param_2 + 0x51);
        }
        printk("will connect %s (%02x:%02x:%02x:%02x:%02x:%02x) on %d\n",param_2 + 0x2c,
               *(undefined1 *)(param_2 + 0x4d),*(undefined1 *)(param_2 + 0x4e),
               *(undefined1 *)(param_2 + 0x4f),*(undefined1 *)(param_2 + 0x50),
               *(undefined1 *)(param_2 + 0x51),*(undefined1 *)(param_2 + 0x52),
               *(undefined1 *)(local_2c[0] + 0x16));
      }
    }
    if (local_2c[0] != 0) {
      os_free_mem();
    }
    if (0 < DebugLevel) {
      printk("WscPBCBssTableSort : Total %d PBC Registrar Found\n",*(undefined1 *)(param_2 + 0x4c));
    }
  }
  return;
}

