// module: mt7915.ko
// function: WpaMicFailureReportFrame @ 0x5741c
// size: 816 bytes
//

void WpaMicFailureReportFrame(int param_1,char *param_2)

{
  char cVar1;
  undefined1 *puVar2;
  int iVar3;
  undefined4 uVar4;
  byte bVar5;
  int iVar6;
  char *pcVar7;
  int local_68;
  undefined4 local_64;
  undefined1 *local_60;
  undefined4 local_5a;
  undefined2 local_56;
  undefined4 local_54;
  undefined2 local_50;
  undefined2 local_4e;
  undefined4 local_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  iVar6 = *(int *)(param_2 + 0x92c);
  local_68 = 0;
  local_64 = 0;
  iVar3 = GetStaCfgByWdev(param_1,iVar6);
  if (iVar3 == 0) {
    printk(&_LC0,0x8f);
    dump_stack();
    return;
  }
  uVar4 = GetAssociatedAPByWdev(param_1,iVar6);
  if (2 < DebugLevel) {
    printk("WpaMicFailureReportFrame ----->\n");
  }
  cVar1 = *param_2;
  *(ushort *)(param_1 + 0xa39f90) = *(ushort *)(param_1 + 0xa39f90) + 1 & 0xfff;
  local_54 = *(undefined4 *)(iVar6 + 0x1b);
  local_5a = *(undefined4 *)(iVar3 + 0x212428);
  local_56 = *(undefined2 *)(iVar3 + 0x21242c);
  local_50 = *(undefined2 *)(iVar6 + 0x1f);
  local_4e = EAPOL;
  os_alloc_mem(0,&local_60,0x5dc);
  puVar2 = local_60;
  if (local_60 == (undefined1 *)0x0) {
    if (-1 < DebugLevel) {
      printk("!!!%s : no memory!!!\n","WpaMicFailureReportFrame");
    }
  }
  else {
    __memzero(local_60,0x5dc);
    bVar5 = 1;
    *puVar2 = 1;
    puVar2[1] = 3;
    puVar2[5] = puVar2[5] | 8;
    puVar2[4] = 0xfe;
    if ((*(uint *)(iVar3 + 0x174) & 0x20) != 0) {
      bVar5 = 2;
    }
    puVar2[6] = puVar2[6] & 0xf8 | bVar5;
    puVar2[6] = puVar2[6] & 0xf7 | (cVar1 == '\x01') << 3;
    puVar2[5] = puVar2[5] | 5;
    puVar2[2] = 0;
    puVar2[3] = 0x5f;
    memmove(puVar2 + 9,(char *)(iVar3 + 0x2127ba),8);
    pcVar7 = (char *)(iVar3 + 0x2127c2);
    do {
      pcVar7 = pcVar7 + -1;
      cVar1 = *pcVar7;
      *pcVar7 = cVar1 + '\x01';
      if ((char)(cVar1 + '\x01') != '\0') break;
    } while (pcVar7 != (char *)(iVar3 + 0x2127ba));
    os_alloc_mem(param_1,&local_68,0x900);
    if (local_68 == 0) {
      os_free_mem(local_60);
    }
    else {
      MakeOutgoingFrame(local_68,&local_64,CONCAT11(puVar2[2],puVar2[3]) + 4,puVar2,0xffffffff);
      __memzero(&local_4c,0x10);
      if ((*(uint *)(iVar3 + 0x174) & 0x20) == 0) {
        RT_HMAC_MD5(iVar3 + 0x212560,0x10,local_68,local_64,&local_4c,0x10);
      }
      else {
        local_3c = 0;
        local_38 = 0;
        local_34 = 0;
        local_30 = 0;
        local_2c = 0;
        RT_HMAC_SHA1(iVar3 + 0x212560,0x10,local_68,local_64,&local_3c,0x14);
        local_4c = local_3c;
        uStack_48 = local_38;
        uStack_44 = local_34;
        uStack_40 = local_30;
      }
      *(undefined4 *)(puVar2 + 0x51) = local_4c;
      *(undefined4 *)(puVar2 + 0x55) = uStack_48;
      *(undefined4 *)(puVar2 + 0x59) = uStack_44;
      *(undefined4 *)(puVar2 + 0x5d) = uStack_40;
      RTMPToWirelessSta(param_1,uVar4,&local_5a,0xe,puVar2,CONCAT11(puVar2[2],puVar2[3]) + 4,0);
      os_free_mem(local_68);
      os_free_mem(local_60);
      if (2 < DebugLevel) {
        printk("WpaMicFailureReportFrame <-----\n");
      }
    }
  }
  return;
}

