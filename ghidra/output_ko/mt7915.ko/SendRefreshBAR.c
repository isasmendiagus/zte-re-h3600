// module: mt7915.ko
// function: SendRefreshBAR @ 0xa3f58
// size: 376 bytes
//

void SendRefreshBAR(int param_1,int param_2)

{
  int iVar1;
  ushort uVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  ushort *puVar6;
  uint uVar7;
  undefined8 uVar8;
  undefined4 local_44;
  undefined4 local_40;
  undefined1 auStack_3c [17];
  byte local_2b;
  short local_2a;
  
  puVar6 = (ushort *)(param_2 + 0xce2);
  local_40 = 0;
  do {
    puVar6 = puVar6 + 1;
    if (*puVar6 != 0) {
      iVar1 = (uint)*puVar6 * 0x48;
      iVar5 = param_1 + iVar1;
      if (*(int *)(iVar5 + 0x1b1cc) == 3) {
        uVar7 = (uint)*(byte *)(iVar5 + 0x1b1c2);
        uVar2 = *(ushort *)(param_1 + iVar1 + 0x1b1c0);
        uVar4 = HcGetMaxStaNum(param_1);
        if (uVar4 <= uVar2) {
          printk(&_LC64,0x638);
          dump_stack();
        }
        uVar8 = os_alloc_mem(param_1,&local_40,0x900);
        if ((int)uVar8 != 0) {
          if (DebugLevel < 0) {
            return;
          }
          printk("BA - MlmeADDBAAction() allocate memory failed\n",(int)((ulonglong)uVar8 >> 0x20),
                 uVar7);
          return;
        }
        sVar3 = chip_get_tid_sn(param_1,*(undefined2 *)(param_2 + 0xe0));
        BarHeaderInit(param_1,auStack_3c,param_2 + 0xec,*(int *)(param_2 + 8) + 0x1b);
        local_2a = sVar3 << 4;
        local_2b = local_2b & 0xf | (byte)((uVar7 & 0xf) << 4);
        MakeOutgoingFrame(local_40,&local_44,0x14,auStack_3c,0xffffffff);
        MiniportMMRequest(param_1,*(byte *)((int)&WMM_UP2AC_MAP + uVar7) | 0x80,local_40,local_44);
        os_free_mem(local_40);
      }
    }
    if (puVar6 == (ushort *)(param_2 + 0xcf2)) {
      return;
    }
  } while( true );
}

