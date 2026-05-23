// module: mt7915.ko
// function: MLDSnooping @ 0x2426d4
// size: 996 bytes
//

void MLDSnooping(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                int param_5,undefined2 param_6)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  byte *pbVar6;
  undefined4 *puVar7;
  uint uVar8;
  bool bVar9;
  undefined4 local_48;
  char local_35;
  int local_34;
  undefined1 local_2e;
  undefined1 local_2d;
  byte local_2c;
  byte local_2b;
  byte local_2a;
  byte local_29;
  
  if (((param_5 != 0) && (puVar7 = *(undefined4 **)(param_5 + 8), puVar7 != (undefined4 *)0x0)) &&
     (iVar3 = isMldPkt(param_2,param_4,&local_35,&local_34), iVar3 == 1)) {
    if (2 < DebugLevel) {
      printk("MLD type=%0x\n",local_35);
    }
    iVar3 = puVar7[5];
    if (iVar3 == 1) {
      if (*(char *)(param_5 + 0xe8) == '\0') {
        local_48 = 1;
      }
      else {
        local_48 = 0x81;
      }
    }
    else {
      local_48 = 1;
    }
    if (local_35 == -0x7c) {
      if (local_34 != -8) {
        local_2c = *(byte *)(local_34 + 0x14);
        local_2b = *(byte *)(local_34 + 0x15);
        local_2a = *(byte *)(local_34 + 0x16);
        local_29 = *(byte *)(local_34 + 0x17);
        local_2e = 0x33;
        local_2d = 0x33;
      }
      if (2 < DebugLevel) {
        printk("EntryInsert Group Id=%02x:%02x:%02x:%02x:%02x:%02x\n",local_2e,local_2d,local_2c,
               local_2b,local_2a,local_29);
        iVar3 = puVar7[5];
      }
      if ((iVar3 != 1) || (*(char *)(param_5 + 0xe8) == '\0')) {
        AsicMcastEntryDelete
                  (param_1,&local_2e,*(undefined1 *)((int)puVar7 + 0x999),param_3,*puVar7,param_6);
      }
    }
    else if (local_35 == -0x71) {
      pbVar6 = (byte *)(local_34 + 8);
      uVar4 = (*(ushort *)(local_34 + 6) & 0xff) << 8 | (uint)(*(ushort *)(local_34 + 6) >> 8);
      if (uVar4 != 0) {
        uVar8 = 0;
        do {
          uVar5 = (*(ushort *)(pbVar6 + 2) & 0xff) << 8 | (uint)(*(ushort *)(pbVar6 + 2) >> 8);
          bVar1 = *pbVar6;
          bVar2 = pbVar6[1];
          if (DebugLevel < 3) {
            if (pbVar6 != (byte *)0xfffffffc) {
LAB_00242810:
              local_2b = pbVar6[0x11];
              local_2c = pbVar6[0x10];
              local_2a = pbVar6[0x12];
              local_29 = pbVar6[0x13];
              local_2e = 0x33;
              local_2d = 0x33;
              goto LAB_0024283c;
            }
          }
          else {
            printk("MLDv2 Type=%d, ADL=%d, numOfSource=%d\n",bVar1,(uint)bVar2,uVar5);
            if (pbVar6 != (byte *)0xfffffffc) goto LAB_00242810;
LAB_0024283c:
            if (2 < DebugLevel) {
              printk("MLD Group=%02x:%02x:%02x:%02x:%02x:%02x\n",local_2e,local_2d,local_2c,local_2b
                     ,local_2a,local_29);
            }
          }
          bVar9 = 1 < bVar1;
          if (bVar1 != 2) {
            bVar9 = bVar1 != 4;
          }
          if (bVar9 && (bVar1 != 2 && bVar1 != 5)) {
            if (bVar1 == 6 || (bVar1 & 0xfd) == 1) {
              if (uVar5 != 0) goto LAB_00242854;
              if ((puVar7[5] != 1) || (*(char *)(param_5 + 0xe8) == '\0')) {
                AsicMcastEntryDelete
                          (param_1,&local_2e,*(undefined1 *)((int)puVar7 + 0x999),param_3,*puVar7,
                           param_6);
              }
            }
          }
          else {
LAB_00242854:
            AsicMcastEntryInsert
                      (param_1,&local_2e,*(undefined1 *)((int)puVar7 + 0x999),local_48,param_3,
                       *puVar7,param_6);
          }
          uVar8 = uVar8 + 1;
          pbVar6 = pbVar6 + (uint)bVar2 + uVar5 * 0x10 + 0x14;
        } while (uVar8 != uVar4);
      }
    }
    else if (local_35 == -0x7d) {
      if (local_34 != -8) {
        local_2c = *(byte *)(local_34 + 0x14);
        local_2b = *(byte *)(local_34 + 0x15);
        local_2a = *(byte *)(local_34 + 0x16);
        local_29 = *(byte *)(local_34 + 0x17);
        local_2e = 0x33;
        local_2d = 0x33;
      }
      if (2 < DebugLevel) {
        printk("EntryInsert Group Id=%02x:%02x:%02x:%02x:%02x:%02x\n",local_2e,local_2d,local_2c,
               local_2b,local_2a,local_29);
      }
      AsicMcastEntryInsert
                (param_1,&local_2e,*(undefined1 *)((int)puVar7 + 0x999),local_48,param_3,*puVar7,
                 param_6);
    }
    else if (2 < DebugLevel) {
      printk("unknow MLD Type=%d\n");
    }
  }
  return;
}

