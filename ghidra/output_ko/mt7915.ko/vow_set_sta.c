// module: mt7915.ko
// function: vow_set_sta @ 0x40628
// size: 792 bytes
//

undefined4 vow_set_sta(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  int local_34;
  undefined1 local_30;
  byte local_2e;
  undefined1 uStack_29;
  uint local_28 [2];
  
  __memzero(&local_34,0x14);
  local_30 = (undefined1)param_2;
  local_2e = (byte)((uint)(param_2 << 0x16) >> 0x1e);
  local_34 = param_3;
  switch(param_3) {
  case 0:
    iVar3 = param_1 + param_2 * 8;
    local_28[0] = (uint)*(byte *)(iVar3 + 0xa799e8) << (*(uint *)(param_1 + 0xa797c8) & 0xff) |
                  (uint)*(byte *)(iVar3 + 0xa799ee) << (*(uint *)(param_1 + 0xa797c4) & 0xff) |
                  (uint)*(byte *)(iVar3 + 0xa799ec) |
                  (uint)*(byte *)(iVar3 + 0xa799e9) << (*(uint *)(param_1 + 0xa797cc) & 0xff) |
                  (uint)*(byte *)(iVar3 + 0xa799ea) << (*(uint *)(param_1 + 0xa797d0) & 0xff) |
                  (uint)*(byte *)(iVar3 + 0xa799eb) << (*(uint *)(param_1 + 0xa797d4) & 0xff);
    if (3 < DebugLevel) {
      printk("%s:(SubCmd %x, Value = 0x%x)\n","vow_set_sta",0);
    }
    break;
  case 1:
    local_28[0] = (uint)*(byte *)(param_1 + (param_2 + 0x14f33d) * 8 + 4);
    break;
  case 2:
    local_28[0] = (uint)*(byte *)(param_1 + (param_2 + 0x14f33d) * 8 + 6);
    break;
  case 3:
    local_28[0] = (uint)*(byte *)(param_1 + (param_2 + 0x14f33d) * 8);
    break;
  case 4:
    iVar3 = param_1 + param_2 * 8;
    uVar2 = 0x99e9;
    goto LAB_0004088c;
  case 5:
    iVar3 = param_1 + param_2 * 8;
    uVar2 = 0x99ea;
    goto LAB_0004088c;
  case 6:
    iVar3 = param_1 + param_2 * 8;
    uVar2 = 0x99eb;
LAB_0004088c:
    local_28[0] = (uint)*(byte *)(iVar3 + (uVar2 | 0xa70000));
    break;
  case 7:
    local_28[0] = (uint)*(byte *)(param_1 + (param_2 + 0x14f33d) * 8 + 5);
    break;
  default:
    if (3 < DebugLevel) {
      printk("%s:(No such command = 0x%x)\n","vow_set_sta",param_3);
    }
    break;
  case 0x20:
  case 0x21:
  case 0x22:
  case 0x23:
  case 0x24:
  case 0x25:
  case 0x26:
  case 0x27:
    local_28[0] = (uint)*(byte *)(param_1 + param_3 + 0xa7a2d4);
    if (3 < DebugLevel) {
      printk("%s:(SubCmd %x, Value = 0x%x)\n","vow_set_sta",param_3);
    }
    break;
  case 0x28:
    puVar6 = &uStack_29;
    iVar4 = 0;
    iVar3 = DebugLevel;
    puVar5 = (undefined1 *)(param_1 + 0xa7a2f4);
    do {
      if (3 < iVar3) {
        printk("%s:(vow_sta_dwrr_quantum[%d] = 0x%x)\n","vow_set_sta",iVar4,*puVar5);
        iVar3 = DebugLevel;
      }
      iVar4 = iVar4 + 1;
      puVar6 = puVar6 + 1;
      *puVar6 = *puVar5;
      puVar5 = puVar5 + 1;
    } while (iVar4 != 8);
    if (3 < iVar3) {
      printk("%s:(SubCmd %x, Value = 0x%x)\n","vow_set_sta",0x28,0);
    }
    break;
  case 0x30:
    local_28[0] = (uint)*(byte *)(param_1 + (param_2 + 0x14f33d) * 8 + 7);
    if (3 < DebugLevel) {
      printk("%s:(SubCmd %x, Value = 0x%x)\n","vow_set_sta",0x30);
    }
  }
  uVar1 = MtCmdSetVoWDRRCtrl(param_1,&local_34);
  if (3 < DebugLevel) {
    printk("%s:(ret = %d), sizeof %zu\n","vow_set_sta",uVar1,0x14);
  }
  return uVar1;
}

