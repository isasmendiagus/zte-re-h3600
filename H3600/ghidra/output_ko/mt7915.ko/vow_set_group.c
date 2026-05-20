// module: mt7915.ko
// function: vow_set_group @ 0x40df0
// size: 1124 bytes
//

undefined4 vow_set_group(int param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  undefined1 *puVar4;
  int iVar5;
  undefined1 *puVar6;
  undefined4 local_138;
  undefined1 local_134;
  uint local_12c;
  undefined1 uStack_29;
  undefined1 local_28 [16];
  
  __memzero(&local_138,0x120);
  local_134 = (undefined1)param_2;
  local_138 = param_3;
  switch(param_3) {
  case 0:
    vow_fill_group_all(param_1,param_2,&local_138);
    break;
  case 1:
    local_12c = (uint)*(ushort *)(param_1 + param_2 * 0x1c + 0xa79838);
    if (2 < DebugLevel) {
      printk("%s:(SubCmd %x, Value = 0x%x)\n","vow_set_group",1);
    }
    break;
  case 2:
    local_12c = (uint)*(ushort *)(param_1 + param_2 * 0x1c + 0xa7983a);
    if (2 < DebugLevel) {
      printk("%s:(SubCmd %x, Value = 0x%x)\n","vow_set_group",2);
    }
    break;
  case 3:
    local_12c = (uint)*(byte *)(param_1 + param_2 * 0x1c + 0xa79834);
    if (2 < DebugLevel) {
      printk("%s:(SubCmd %x, Value = 0x%x)\n","vow_set_group",3);
    }
    break;
  case 4:
    local_12c = (uint)*(ushort *)(param_1 + param_2 * 0x1c + 0xa7983c);
    if (2 < DebugLevel) {
      printk("%s:(SubCmd %x, Value = 0x%x)\n","vow_set_group",4);
    }
    break;
  case 5:
    local_12c = (uint)*(ushort *)(param_1 + param_2 * 0x1c + 0xa7982e);
    if (2 < DebugLevel) {
      printk("%s:(SubCmd %x, Value = 0x%x)\n","vow_set_group",5);
    }
    break;
  case 6:
    local_12c = (uint)*(byte *)(param_1 + param_2 * 0x1c + 0xa79835);
    if (2 < DebugLevel) {
      printk("%s:(SubCmd %x, Value = 0x%x)\n","vow_set_group",6);
    }
    break;
  case 7:
    local_12c = (uint)*(ushort *)(param_1 + param_2 * 0x1c + 0xa7983e);
    if (2 < DebugLevel) {
      printk("%s:(SubCmd %x, Value = 0x%x)\n","vow_set_group",7);
    }
    break;
  case 8:
    local_12c = (uint)*(ushort *)(param_1 + param_2 * 0x1c + 0xa79830);
    if (2 < DebugLevel) {
      printk("%s:(SubCmd %x, Value = 0x%x)\n","vow_set_group",8);
    }
    break;
  case 9:
    local_12c = (uint)*(byte *)(param_1 + param_2 * 0x1c + 0xa79836);
    if (2 < DebugLevel) {
      printk("%s:(SubCmd %x, Value = 0x%x)\n","vow_set_group",9);
    }
    break;
  case 10:
    local_12c = (uint)*(ushort *)(param_1 + param_2 * 0x1c + 0xa79832);
    if (2 < DebugLevel) {
      printk("%s:(SubCmd %x, Value = 0x%x)\n","vow_set_group",10);
    }
    break;
  default:
    if (2 < DebugLevel) {
      printk("%s:(No such command = 0x%x)\n","vow_set_group",param_3);
    }
    break;
  case 0x10:
    uVar3 = 0;
    do {
      uVar2 = uVar3 & 0xff;
      uVar3 = uVar3 + 1;
      vow_fill_group_all(param_1,uVar2,&local_138);
    } while (uVar3 != 0x10);
    break;
  case 0x20:
  case 0x21:
  case 0x22:
  case 0x23:
  case 0x24:
  case 0x25:
  case 0x26:
  case 0x27:
  case 0x28:
  case 0x29:
  case 0x2a:
  case 0x2b:
  case 0x2c:
  case 0x2d:
  case 0x2e:
  case 0x2f:
    local_28[param_2] = *(undefined1 *)(param_1 + param_2 * 0x1c + 0xa79837);
    if (2 < DebugLevel) {
      printk("%s:(group %d DWRR quantum = 0x%x)\n","vow_set_group",param_2);
    }
    break;
  case 0x30:
    puVar6 = &uStack_29;
    iVar5 = 0;
    puVar4 = (undefined1 *)(param_1 + 0xa79837);
    do {
      puVar6 = puVar6 + 1;
      *puVar6 = *puVar4;
      if (2 < DebugLevel) {
        printk("%s:(group %d DWRR quantum = 0x%x)\n","vow_set_group",iVar5);
      }
      iVar5 = iVar5 + 1;
      puVar4 = puVar4 + 0x1c;
    } while (iVar5 != 0x10);
  }
  uVar1 = MtCmdSetVoWGroupCtrl(param_1,&local_138);
  if (2 < DebugLevel) {
    printk("%s:(ret = %d), sizeof %zu\n","vow_set_group",uVar1,0x120);
  }
  return uVar1;
}

