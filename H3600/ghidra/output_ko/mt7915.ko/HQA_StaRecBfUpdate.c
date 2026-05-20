// module: mt7915.ko
// function: HQA_StaRecBfUpdate @ 0x27a970
// size: 836 bytes
//

undefined4 HQA_StaRecBfUpdate(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  uint __n;
  int iVar4;
  char *local_88;
  uint local_84 [4];
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  if (param_3 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: HqaCmdFrame is NULL\n","HQA_StaRecBfUpdate");
    }
  }
  else {
    os_alloc_mem(param_1,&local_88,0x200);
    if (local_88 == (char *)0x0) {
      FUN_0026cdd0(param_3,param_2,2,3);
      return 3;
    }
    __n = (*(ushort *)(param_3 + 8) & 0xff) << 8 | (uint)(*(ushort *)(param_3 + 8) >> 8);
    if (__n < 0x5d) {
      memcpy(local_84,(void *)(param_3 + 0xc),__n);
      if (__n >> 2 != 0) {
        puVar2 = local_84;
        do {
          uVar1 = *puVar2;
          puVar3 = puVar2 + 1;
          *puVar2 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
                    uVar1 >> 0x18;
          puVar2 = puVar3;
        } while (puVar3 != local_84 + (__n >> 2));
      }
      puVar2 = local_84;
      iVar4 = 0;
      do {
        if (0 < DebugLevel) {
          printk("DWORD%d:%08x\n",iVar4,*puVar2);
        }
        iVar4 = iVar4 + 1;
        puVar2 = puVar2 + 1;
      } while (iVar4 != 0x17);
      __memzero(local_88,0x200);
      sprintf(local_88,
              "%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x"
              ,local_84[0],local_84[1],local_84[2],local_84[3],local_74,local_70,local_6c,local_68,
              local_64,local_60,local_5c,local_58,local_54,local_50,local_4c,local_48,local_44,
              local_40,local_3c,local_38,local_34,local_30,local_2c);
      Set_StaRecBfUpdate(param_1,local_88);
      if (local_88 == (char *)0x0) {
        FUN_0026cdd0(param_3,param_2,2);
      }
      else {
        os_free_mem(local_88);
        FUN_0026cdd0(param_3,param_2,2,0);
      }
      if ((0 < DebugLevel) &&
         (printk("%s: %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n"
                 ,"HQA_StaRecBfUpdate",local_84[0],local_84[1],local_84[2],local_84[3],local_74,
                 local_70,local_6c,local_68,local_64,local_60,local_5c,local_58,local_50,local_4c,
                 local_48,local_44,local_40,local_3c,local_38,local_34,local_30,local_2c),
         0 < DebugLevel)) {
        printk("%s: wlan_idx:%x, bss_idx:%x\n","HQA_StaRecBfUpdate",local_84[0],local_84[1],
               local_84[2],local_84[3],local_74,local_70,local_6c,local_68,local_64,local_60,
               local_5c,local_58,local_50,local_4c,local_48,local_44,local_40,local_3c,local_38,
               local_34,local_30,local_2c);
      }
      return 0;
    }
    os_free_mem();
    FUN_0026cdd0(param_3,param_2,2,2);
  }
  return 2;
}

