// module: mt7915.ko
// function: SetATEReadE2p @ 0x262734
// size: 280 bytes
//

undefined4 SetATEReadE2p(int param_1)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined2 *local_1c;
  
  local_1c = (undefined2 *)0x0;
  if ("cp_support_is_enabled"[param_1 + 4] == '\x02') {
    uVar4 = get_dev_eeprom_size();
    uVar4 = uVar4 & 0xffff;
    iVar2 = os_alloc_mem(param_1,&local_1c,uVar4);
    if (iVar2 == 1) {
      return 1;
    }
    EEReadAll(param_1,local_1c,uVar4);
    uVar4 = uVar4 >> 1;
    if (uVar4 == 0) goto LAB_002627bc;
  }
  else {
    iVar2 = os_alloc_mem(param_1,&local_1c,0x400);
    if (iVar2 == 1) {
      return 1;
    }
    uVar4 = 0x200;
    EEReadAll(param_1,local_1c,0x400);
  }
  uVar3 = 1;
  do {
    if (((0 < DebugLevel) && (printk("%4.4x ",*local_1c), (uVar3 & 0xf) == 0)) && (0 < DebugLevel))
    {
      printk(&_LC74);
    }
    local_1c = local_1c + 1;
    bVar1 = (int)uVar3 < (int)uVar4;
    uVar3 = uVar3 + 1;
  } while (bVar1);
LAB_002627bc:
  os_free_mem(local_1c);
  return 1;
}

