// module: mt7915.ko
// function: Set_McastMcs @ 0x3318c
// size: 536 bytes
//

undefined4 Set_McastMcs(int *param_1,undefined4 param_2)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined1 *puVar6;
  uint uVar7;
  undefined1 auStack_134 [4];
  undefined4 local_130;
  undefined1 local_127;
  undefined4 local_f8;
  undefined2 local_e0;
  undefined2 local_de;
  
  iVar4 = *param_1;
  uVar7 = *(uint *)(iVar4 + 0x3c);
  bVar2 = os_str_tol(param_2,0,10);
  if ((*(int *)(iVar4 + 0x38) - 0x100U & 0xfffffeff) == 0) {
    uVar7 = uVar7 & 0xff;
    uVar5 = 0;
    if (uVar7 < *(byte *)((int)param_1 + 0x2b7242)) {
      if (bVar2 < 0x10) {
        bVar1 = *(byte *)((int)param_1 + uVar7 * 0x5834 + 0x2b7d55) >> 5;
        if (bVar1 == 0) {
          if (3 < (bVar2 & 0xf7)) {
            if (DebugLevel < 3) {
              return 0;
            }
            printk("MCS must in range of 0 ~ 3 and 8 ~ 11 for CCK Mode.\n");
            return 0;
          }
        }
        else if ((bVar1 == 1) && (7 < bVar2)) {
          if (DebugLevel < 3) {
            return 0;
          }
          printk("MCS must in range from 0 to 7 for OFDM Mode.\n");
          return 0;
        }
        *(byte *)(param_1 + uVar7 * 0x160d + 0xadf55) =
             *(byte *)(param_1 + uVar7 * 0x160d + 0xadf55) & 0xc0 | bVar2 & 0x3f;
        puVar6 = (undefined1 *)((int)param_1 + 0x2b7be1);
        iVar4 = 0;
        do {
          __memzero(auStack_134,0x114);
          local_127 = *puVar6;
          local_e0 = (undefined2)param_1[uVar7 * 0x160d + 0xadf55];
          puVar6 = puVar6 + 0x5834;
          local_130 = 2;
          local_f8 = 0x100;
          local_de = local_e0;
          iVar3 = AsicBssInfoUpdate(param_1,auStack_134);
          if ((iVar3 != 0) && (2 < DebugLevel)) {
            printk("Fail to apply the bssinfo, BSSID=%d!\n",iVar4);
          }
          iVar4 = iVar4 + 1;
        } while (iVar4 < (int)(uint)*(byte *)((int)param_1 + 0x2b7242));
        uVar5 = 1;
      }
      else if (2 < DebugLevel) {
        printk("Mcs must be in range of 0 to 15\n");
      }
    }
    else if (2 < DebugLevel) {
      printk("Invalid device interface!\n");
    }
  }
  else if (DebugLevel < 3) {
    uVar5 = 0;
  }
  else {
    uVar5 = 0;
    printk("Do nothing! This device interface is NOT AP mode!\n");
  }
  return uVar5;
}

