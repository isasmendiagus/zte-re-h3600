// module: mt7915.ko
// function: RTMPIoctlAddPMKIDCache @ 0x378a4
// size: 808 bytes
//

void RTMPIoctlAddPMKIDCache(int *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  byte *local_b8;
  uint local_b4;
  uint local_b0;
  uint local_ac;
  uint local_a8;
  uint local_a4;
  uint local_a0;
  uint local_9c;
  uint local_98;
  int local_90;
  undefined1 auStack_8a [6];
  char local_84 [8];
  undefined4 local_7c;
  undefined2 local_78;
  undefined1 auStack_76 [6];
  byte local_70;
  byte local_6f;
  byte local_6e;
  byte local_6d;
  byte local_6c;
  byte local_6b;
  
  uVar4 = *(uint *)(*param_1 + 0x3c);
  os_alloc_mem(param_1,&local_90,*(undefined2 *)(param_2 + 0x14));
  if (local_90 != 0) {
    uVar2 = (uint)*(ushort *)(param_2 + 0x14);
    uVar3 = *(uint *)(((uint)&local_b8 & 0xffffe000) + 8);
    if (!CARRY4(*(uint *)(param_2 + 0x10),uVar2) && *(uint *)(param_2 + 0x10) + uVar2 <= uVar3) {
      uVar3 = 0;
    }
    if (uVar3 == 0) {
      iVar1 = __copy_from_user(local_90);
      if (iVar1 != 0) goto LAB_0003798c;
    }
    else if (uVar2 != 0) {
      __memzero(local_90,uVar2);
LAB_0003798c:
      if (2 < DebugLevel) {
        printk("%s: copy from user failed\n","RTMPIoctlAddPMKIDCache");
      }
      os_free_mem(local_90);
      return;
    }
    uVar4 = uVar4 & 0xff;
    uVar2 = param_1[uVar4 * 0x160d + 0xadc9d];
    if ((uVar2 & 0x10040) != 0) {
      if (*(int *)(local_90 + 0x10) == 0x20) {
        if (1 < DebugLevel) {
          printk("%s: pKey->KeyLength = %d\n","RTMPIoctlAddPMKIDCache");
          uVar2 = param_1[uVar4 * 0x160d + 0xadc9d];
        }
        iVar1 = local_90;
        builtin_strncpy(local_84,"PMK Name",8);
        local_7c = *(undefined4 *)((int)param_1 + uVar4 * 0x5834 + 0x2b7269);
        local_78 = *(undefined2 *)((int)param_1 + uVar4 * 0x5834 + 0x2b726d);
        memmove(auStack_76,(void *)(local_90 + 4),6);
        if ((uVar2 & 0x30000) == 0) {
          local_b8 = &local_70;
          local_b4 = 0x14;
          RT_HMAC_SHA1(iVar1 + 0x14,0x20,local_84);
        }
        else {
          local_b8 = &local_70;
          local_b4 = 0x10;
          RT_HMAC_SHA384(iVar1 + 0x14,0x30,local_84,0x14);
        }
        iVar1 = local_90;
        memmove(auStack_8a,(void *)(local_90 + 4),6);
        local_b8 = (byte *)(iVar1 + 0x14);
        local_b4 = (uint)*(byte *)(iVar1 + 0x10);
        RTMPAddPMKIDCache(param_1 + 0xda1ff,uVar4,auStack_8a,&local_70);
        if (2 < DebugLevel) {
          local_ac = (uint)local_70;
          local_a8 = (uint)local_6f;
          local_b8 = (byte *)(uint)*(byte *)(local_90 + 7);
          local_b4 = (uint)*(byte *)(local_90 + 8);
          local_a4 = (uint)local_6e;
          local_a0 = (uint)local_6d;
          local_9c = (uint)local_6c;
          local_b0 = (uint)*(byte *)(local_90 + 9);
          local_98 = (uint)local_6b;
          printk("WPA2(pre-auth):(%02x:%02x:%02x:%02x:%02x:%02x)Calc PMKID=%02x:%02x:%02x:%02x:%02x:%02x\n"
                 ,*(undefined1 *)(local_90 + 4),*(undefined1 *)(local_90 + 5),
                 *(undefined1 *)(local_90 + 6));
          if (2 < DebugLevel) {
            local_b8 = (byte *)(uint)*(byte *)(local_90 + 0x17);
            local_b4 = (uint)*(byte *)(local_90 + 0x18);
            local_b0 = (uint)*(byte *)(local_90 + 0x19);
            local_ac = (uint)*(byte *)(local_90 + 0x1a);
            local_a8 = (uint)*(byte *)(local_90 + 0x1b);
            printk("PMK =%02x:%02x:%02x:%02x-%02x:%02x:%02x:%02x\n",*(undefined1 *)(local_90 + 0x14)
                   ,*(undefined1 *)(local_90 + 0x15),*(undefined1 *)(local_90 + 0x16));
          }
        }
      }
      else if (-1 < DebugLevel) {
        printk("Set::RT_OID_802_11_WPA2_ADD_PMKID_CACHE ERROR or is wep key\n");
      }
    }
    os_free_mem(local_90);
    if (2 < DebugLevel) {
      printk("<== RTMPIoctlAddPMKIDCache\n");
    }
  }
  return;
}

