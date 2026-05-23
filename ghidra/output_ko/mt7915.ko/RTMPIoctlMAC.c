// module: mt7915.ko
// function: RTMPIoctlMAC @ 0xda9fc
// size: 1268 bytes
//

void RTMPIoctlMAC(int param_1,int param_2)

{
  char *__s;
  char *pcVar1;
  char *pcVar2;
  int iVar3;
  size_t sVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  byte *pbVar8;
  char *__s_00;
  char *pcVar9;
  byte *local_50 [3];
  int local_44;
  int local_40;
  byte *local_3c;
  undefined4 local_38;
  byte *local_34;
  byte *local_30;
  byte *local_2c [2];
  
  local_38 = 0;
  local_30 = (byte *)0x0;
  local_2c[0] = (byte *)0x0;
  local_44 = param_2;
  os_alloc_mem(0,&local_40,0x110c);
  if (local_40 != 0) {
    __s_00 = (char *)(local_40 + 3U & 0xfffffffc);
    pbVar8 = (byte *)(__s_00 + 0x1000);
    __memzero(__s_00);
    __memzero(pbVar8,0x100);
    uVar5 = (uint)*(ushort *)(param_2 + 0x14);
    if (1 < uVar5) {
      if (0xfe < uVar5) {
        uVar5 = 0xff;
      }
      uVar6 = *(uint *)(((uint)local_50 & 0xffffe000) + 8);
      if (!CARRY4(*(uint *)(param_2 + 0x10),uVar5) && *(uint *)(param_2 + 0x10) + uVar5 <= uVar6) {
        uVar6 = 0;
      }
      if (uVar6 == 0) {
        __copy_from_user(pbVar8);
      }
      else {
        __memzero(pbVar8,uVar5);
      }
      __s_00[0x10ff] = '\0';
    }
    local_3c = pbVar8;
    if ((pbVar8 != (byte *)0x0) && (uVar5 = (uint)*pbVar8, uVar5 != 0)) {
      while (uVar5 == 0x20) {
        pbVar8 = pbVar8 + 1;
        uVar5 = (uint)(char)*pbVar8;
      }
      local_3c = pbVar8;
      if (0 < DebugLevel) {
        sVar4 = strlen((char *)pbVar8);
        local_50[0] = pbVar8;
        printk("%s():after trim space, ptr len=%zu, pointer(%p)=%s!\n","RTMPIoctlMAC",sVar4,pbVar8);
      }
    }
    while (__s = strsep((char **)&local_3c,","), __s != (char *)0x0) {
      if (2 < DebugLevel) {
        sVar4 = strlen(__s);
        printk("seg_str[%zu]=%s\n",sVar4,__s);
      }
      pcVar1 = strchr(__s,0x3d);
      if (pcVar1 != (char *)0x0) {
        pcVar9 = pcVar1 + 1;
        *pcVar1 = '\0';
      }
      else {
        pcVar9 = (char *)0x0;
      }
      pcVar2 = strchr(__s,0x2d);
      if (pcVar2 == (char *)0x0) {
        iVar3 = FUN_000d530c(__s,&local_30);
        if (iVar3 == 0) goto LAB_000dae34;
        local_2c[0] = local_30;
      }
      else {
        *pcVar2 = '\0';
        iVar3 = FUN_000d530c(__s,&local_30);
        if (iVar3 == 0) {
LAB_000dae34:
          if (-1 < DebugLevel) {
            printk("Invalid MAC CR Addr, str=%s\n",__s);
          }
          break;
        }
        pcVar2 = pcVar2 + 1;
        iVar3 = FUN_000d530c(pcVar2,local_2c);
        if (iVar3 == 0) {
          if (-1 < DebugLevel) {
            printk("Invalid Range End MAC CR Addr[0x%x], str=%s\n",local_2c[0],pcVar2);
          }
          break;
        }
        if (local_2c[0] < local_30) {
          if (-1 < DebugLevel) {
            local_50[0] = local_2c[0];
            printk("Invalid Range MAC Addr[%s - %s] => [0x%x - 0x%x]\n",__s,pcVar2);
          }
          break;
        }
      }
      if ((pcVar9 != (char *)0x0) &&
         ((*pcVar9 == '\0' || (iVar3 = FUN_000d530c(pcVar9,&local_38), iVar3 == 0)))) {
        if (-1 < DebugLevel) {
          printk("Invalid MAC value[0x%s]\n",pcVar9);
        }
        break;
      }
      if (pcVar1 != (char *)0x0) {
        mac_io_write32(*(undefined4 *)(param_1 + 0xa797a0),local_30,local_38);
        local_34 = local_30;
        iVar3 = mt_mac_cr_range_mapping(param_1,&local_34);
        sVar4 = strlen(__s_00);
        sprintf(__s_00 + sVar4,"[0x%04x]:%08x  ",local_34,local_38);
        if (0 < DebugLevel) {
          printk("MacAddr=0x%x, MacValue=0x%x, IsRemap=%d\n",local_34,local_38,iVar3 == 0);
        }
      }
      else if (local_30 <= local_2c[0]) {
        pbVar8 = local_30;
        do {
          mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),pbVar8,&local_38);
          local_34 = pbVar8;
          iVar3 = mt_mac_cr_range_mapping(param_1,&local_34);
          pbVar8 = pbVar8 + 4;
          sVar4 = strlen(__s_00);
          sprintf(__s_00 + sVar4,"[0x%04x]:%08x  ",local_34,local_38);
          if (0 < DebugLevel) {
            printk("MacAddr=0x%x, MacValue=0x%x, IsRemap=%d\n",local_34,local_38,iVar3 == 0);
          }
        } while (pbVar8 <= local_2c[0]);
      }
      pbVar8 = local_3c;
      if ((local_3c != (byte *)0x0) && (2 < DebugLevel)) {
        sVar4 = strlen((char *)local_3c);
        printk("NextRound: ptr[%zu]=%s\n",sVar4,pbVar8);
      }
    }
    uVar5 = strlen(__s_00);
    if (uVar5 == 1) {
      builtin_strncpy(__s_00 + 1,"===>Error command format!",0x1a);
      uVar5 = strlen(__s_00);
    }
    uVar6 = uVar5 & 0xffff;
    *(short *)(local_44 + 0x14) = (short)uVar5;
    uVar5 = *(uint *)(local_44 + 0x10);
    uVar7 = *(uint *)(((uint)local_50 & 0xffffe000) + 8);
    if (!CARRY4(uVar5,uVar6) && uVar5 + uVar6 <= uVar7) {
      uVar7 = 0;
    }
    if (uVar7 == 0) {
      uVar6 = __copy_to_user(uVar5,__s_00);
    }
    if ((uVar6 != 0) && (2 < DebugLevel)) {
      printk("%s: copy_to_user() fail\n","RTMPIoctlMAC");
    }
    os_free_mem(local_40);
  }
  return;
}

