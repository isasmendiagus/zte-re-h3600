// module: mt7915.ko
// function: MakeCountryIe @ 0xb3fb4
// size: 892 bytes
//

void MakeCountryIe(int param_1,int param_2,int *param_3,int param_4)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  char *pcVar4;
  uint uVar5;
  int iVar6;
  undefined1 local_37;
  undefined1 local_36;
  char local_35;
  int local_34;
  int local_30;
  undefined4 local_2c;
  
  iVar6 = *param_3;
  local_30 = 0;
  local_2c = 0;
  local_37 = 7;
  local_36 = 0x20;
  if ((*(char *)(param_1 + 0x794c30) == '\0') &&
     (((*(byte *)(param_2 + 0x1a) < 0xf || (*(char *)(param_1 + 0x795074) != '\x01')) &&
      (*(char *)(param_2 + 0xb21) != '\x01')))) goto LAB_000b402c;
  os_alloc_mem(0,&local_30,0x100);
  if (local_30 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: Allocate memory fail!!!\n","MakeCountryIe");
    }
    goto LAB_000b402c;
  }
  __memzero(local_30,0x100);
  uVar1 = wlan_operate_get_ht_bw(param_2);
  GetCuntryMaxTxPwr(param_1,*(undefined2 *)(param_2 + 0x18),param_2,uVar1);
  local_35 = '\x1e';
  if ((*(ushort *)(param_2 + 0x18) & 0x4e) == 0) {
    if ((*(ushort *)(param_2 + 0x18) & 0x1b1) != 0) {
      pcVar4 = *(char **)(param_1 + 0x794c40);
      if (pcVar4 != (char *)0x0) {
        if (*pcVar4 != '\0') goto LAB_000b40c4;
        uVar2 = 0;
        uVar5 = 0;
        local_35 = '\0';
LAB_000b4130:
        if (*(char *)(param_1 + 0x794c35) == '\0') goto LAB_000b4144;
        uVar3 = 0x4c36;
        goto LAB_000b4148;
      }
      if (DebugLevel < 0) goto LAB_000b42d4;
      printk("%s: pChDesc5G is NULL !!!\n","MakeCountryIe");
    }
  }
  else {
    pcVar4 = *(char **)(param_1 + 0x794c3c);
    if (pcVar4 != (char *)0x0) {
      if (*pcVar4 == '\0') {
        uVar2 = 0;
        uVar5 = 0;
        local_35 = '\0';
      }
      else {
LAB_000b40c4:
        uVar5 = 0;
        do {
          MakeOutgoingFrame(local_30 + uVar5,&local_34,1,pcVar4,1,pcVar4 + 1,1,&local_35,0xffffffff)
          ;
          pcVar4 = pcVar4 + 3;
          uVar5 = uVar5 + local_34;
        } while (*pcVar4 != '\0');
        local_35 = (char)uVar5;
        uVar2 = uVar5 & 1;
        if ((*(ushort *)(param_2 + 0x18) & 0x4e) == 0) goto LAB_000b4130;
      }
LAB_000b4144:
      uVar3 = 0x4c31;
LAB_000b4148:
      local_2c = CONCAT13(local_2c._3_1_,*(undefined3 *)(param_1 + (uVar3 | 0x790000)));
      if (uVar2 == 0) {
        local_35 = local_35 + '\x04';
        MakeOutgoingFrame(param_4 + iVar6,&local_34,1,&local_37,1,&local_35,1,&local_2c,1,
                          (int)&local_2c + 1,1,&local_36,uVar5 + 1,local_30,0xffffffff);
      }
      else {
        local_35 = local_35 + '\x03';
        MakeOutgoingFrame(param_4 + iVar6,&local_34,1,&local_37,1,&local_35,1,&local_2c,1,
                          (int)&local_2c + 1,1,&local_36,uVar5,local_30,0xffffffff);
      }
      iVar6 = iVar6 + local_34;
      os_free_mem(local_30);
LAB_000b402c:
      *param_3 = iVar6;
      return;
    }
    if (DebugLevel < 0) goto LAB_000b42d4;
    printk("%s: pChDesc2G is NULL !!!\n","MakeCountryIe");
  }
  if (-1 < DebugLevel) {
    printk("%s: pChDesc is NULL !!!\n","MakeCountryIe");
  }
LAB_000b42d4:
  os_free_mem(local_30);
  return;
}

