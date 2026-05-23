// module: mt7915.ko
// function: rtmp_ee_write_to_efuse @ 0x1d3044
// size: 728 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 rtmp_ee_write_to_efuse(int param_1)

{
  ushort uVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  char *extraout_r1;
  char *extraout_r1_00;
  char *extraout_r1_01;
  char *extraout_r1_02;
  char cVar6;
  char *pcVar7;
  char *pcVar8;
  ushort uVar9;
  void *__s1;
  undefined4 local_50;
  undefined4 local_4c;
  char local_48 [36];
  
  local_48[0] = '\0';
  local_48[1] = '\0';
  local_48[2] = '\0';
  local_48[3] = '\0';
  local_48[4] = '\0';
  local_48[5] = '\0';
  local_48[6] = '\0';
  local_48[7] = '\0';
  local_48[8] = '\0';
  local_48[9] = '\0';
  local_48[10] = '\0';
  local_48[0xb] = '\0';
  local_48[0xc] = '\0';
  local_48[0xd] = '\0';
  local_48[0xe] = '\0';
  local_48[0xf] = '\0';
  iVar3 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  __s1 = *(void **)("Set_IRR_TTGOnOff" + param_1 + 4);
  uVar1 = *(ushort *)(iVar3 + 0xf4);
  local_50 = 0;
  local_4c = (void *)0x0;
  local_48[0x10] = -1;
  local_48[0x11] = -1;
  local_48[0x12] = -1;
  local_48[0x13] = -1;
  local_48[0x14] = -1;
  local_48[0x15] = -1;
  local_48[0x16] = -1;
  local_48[0x17] = -1;
  local_48[0x18] = -1;
  local_48[0x19] = -1;
  local_48[0x1a] = -1;
  local_48[0x1b] = -1;
  local_48[0x1c] = -1;
  local_48[0x1d] = -1;
  local_48[0x1e] = -1;
  local_48[0x1f] = -1;
  iVar3 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(int *)(iVar3 + 0xd8) == 0) {
    if (uVar1 == 0) {
      return 1;
    }
  }
  else {
    os_alloc_mem(param_1,&local_4c,uVar1);
    if (local_4c == (void *)0x0) {
      if (-1 < DebugLevel) {
        printk("%s: os_alloc_mem fail\n","rtmp_ee_write_to_efuse");
        return 0;
      }
      return 0;
    }
    if (uVar1 != 0) {
      __memzero(local_4c,uVar1);
    }
    (**(code **)(iVar3 + 0xd8))(param_1,local_4c);
    __s1 = local_4c;
    if (uVar1 == 0) goto LAB_001d3208;
  }
  uVar9 = 0;
  do {
    iVar4 = memcmp(__s1,local_48 + 0x10,0x10);
    if (iVar4 != 0) {
      if (2 < DebugLevel) {
        printk("offset 0x%04x:\n",uVar9);
      }
      pcVar7 = (char *)((int)&local_4c + 3);
      MtCmdEfuseAccessRead(param_1,uVar9,local_48,&local_50);
      pcVar8 = (char *)((int)__s1 + -1);
      bVar2 = false;
      do {
        pcVar8 = pcVar8 + 1;
        cVar6 = *pcVar8;
        pcVar5 = pcVar7 + (1 - (int)local_48);
        pcVar7 = pcVar7 + 1;
        if (*pcVar7 != cVar6) {
          if (3 < DebugLevel) {
            printk("index 0x%04x: ",pcVar5);
            if (DebugLevel < 4) {
              cVar6 = *pcVar8;
              pcVar5 = extraout_r1;
            }
            else {
              printk("orignal block value=0x%04x, write value=0x%04x\n",*pcVar7,*pcVar8);
              cVar6 = *pcVar8;
              pcVar5 = extraout_r1_00;
            }
          }
          bVar2 = true;
          *pcVar7 = cVar6;
        }
      } while (pcVar7 != local_48 + 0xf);
      if (bVar2) {
        iVar4 = DebugLevel;
        pcVar7 = local_48;
        if (2 < DebugLevel) {
          printk("write block content: ",pcVar5);
          pcVar5 = extraout_r1_02;
          iVar4 = DebugLevel;
        }
        do {
          if (2 < iVar4) {
            printk(&_LC26,*pcVar7);
            pcVar5 = extraout_r1_01;
            iVar4 = DebugLevel;
          }
          pcVar7 = pcVar7 + 1;
        } while (pcVar7 != local_48 + 0x10);
        if (2 < iVar4) {
          printk(&_LC19,pcVar5);
        }
        MtCmdEfuseAccessWrite(param_1,uVar9,local_48);
      }
    }
    uVar9 = uVar9 + 0x10;
    __s1 = (void *)((int)__s1 + 0x10);
  } while (uVar9 < uVar1);
LAB_001d3208:
  if (*(int *)(iVar3 + 0xd8) != 0) {
    os_free_mem(local_4c);
  }
  return 1;
}

