// module: mt7915.ko
// function: WscPINBssTableSort @ 0x1e8670
// size: 792 bytes
//

void WscPINBssTableSort(undefined4 param_1,int param_2)

{
  int iVar1;
  uint *puVar2;
  int iVar3;
  undefined4 uVar4;
  uint *puVar5;
  uint uVar6;
  int local_2c [2];
  
  local_2c[0] = 0;
  if (param_2 == 0) {
    return;
  }
  uVar4 = *(undefined4 *)(param_2 + 0x29ec);
  iVar1 = GetStaCfgByWdev(param_1,uVar4);
  if (iVar1 == 0) {
    printk(&_LC163,0x28e0);
    dump_stack();
  }
  puVar2 = (uint *)get_scan_tab_by_wdev(param_1,uVar4);
  *(char *)(param_2 + 0x6c) = *(char *)(param_2 + 0x6c) + '\x01';
  os_alloc_mem(0,local_2c,0x1f8);
  if (local_2c[0] == 0) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: Allocate memory fail!!!\n","WscPINBssTableSort");
    return;
  }
  __memzero(local_2c[0],0x3f);
  iVar3 = DebugLevel;
  *(undefined1 *)(param_2 + 99) = 0;
  if (iVar3 < 3) {
    if (*puVar2 == 0) goto LAB_001e879c;
LAB_001e8710:
    puVar5 = puVar2 + 2;
    uVar6 = 0;
    do {
      uVar6 = uVar6 + 1;
      iVar3 = RTMPCompareMemory(param_2 + 0x4d,(int)puVar5 + 6,6);
      if (iVar3 == 0) {
        if ((2 < DebugLevel) &&
           (printk("#  wsc Bssid %02x:%02x:%02x:%02x:%02x:%02x\n",*(undefined1 *)(param_2 + 0x4d),
                   *(undefined1 *)(param_2 + 0x4e),*(undefined1 *)(param_2 + 0x4f),
                   *(undefined1 *)(param_2 + 0x50),*(undefined1 *)(param_2 + 0x51),
                   *(undefined1 *)(param_2 + 0x52)), 2 < DebugLevel)) {
          printk("# pIn Bssid %02x:%02x:%02x:%02x:%02x:%02x\n",*(undefined1 *)((int)puVar5 + 6),
                 *(undefined1 *)((int)puVar5 + 7),(char)puVar5[2],*(undefined1 *)((int)puVar5 + 9),
                 *(undefined1 *)((int)puVar5 + 10),*(undefined1 *)((int)puVar5 + 0xb));
        }
        if (((short)puVar5[0x3b] != 0) &&
           (((iVar1 == 0 || ((char)puVar5[5] == *(char *)(iVar1 + 0x4060))) &&
            (iVar3 = WscBssWpsIESearchForPIN
                               (param_1,param_2,puVar5,local_2c[0],(short)puVar5[0x3b],
                                (int)puVar5 + 0xee), iVar3 == 0)))) {
          WscBssWpsIESearchForPIN
                    (param_1,param_2,puVar5,local_2c[0],*(undefined2 *)((int)puVar5 + 0x4ee),
                     puVar5[0x13c]);
        }
      }
      puVar5 = puVar5 + 0x2bd;
    } while (uVar6 < *puVar2);
  }
  else {
    printk("%s: scan result AP Count:%u\n","WscPINBssTableSort",*puVar2);
    if (*puVar2 != 0) goto LAB_001e8710;
  }
  if (*(char *)(param_2 + 99) == '\x01') {
    RTMPZeroMemory(param_2 + 0x28,0x24);
    RTMPMoveMemory(param_2 + 0x2c,local_2c[0] + 0x18,*(undefined1 *)(local_2c[0] + 0x38));
    *(uint *)(param_2 + 0x28) = (uint)*(byte *)(local_2c[0] + 0x38);
    RTMPZeroMemory(param_2 + 0x4d,6);
    RTMPMoveMemory(param_2 + 0x4d,local_2c[0] + 0x10,6);
    RTMPZeroMemory(param_2 + 0x66,6);
    RTMPMoveMemory(param_2 + 0x66,local_2c[0] + 0x39,6);
    if (iVar1 != 0) {
      *(undefined1 *)(iVar1 + 0x4165) = *(undefined1 *)(local_2c[0] + 0x16);
    }
  }
LAB_001e879c:
  if (local_2c[0] != 0) {
    os_free_mem();
  }
  if (0 < DebugLevel) {
    printk("WscPINBssTableSort : Total %d PIN Registrar Found\n",*(undefined1 *)(param_2 + 99));
  }
  return;
}

