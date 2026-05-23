// module: mt7915.ko
// function: WscGenerateUUID @ 0x1e0810
// size: 868 bytes
//

/* WARNING: Restarted to delay deadcode elimination for space: stack */

undefined4
WscGenerateUUID(int param_1,uint *param_2,char *param_3,int param_4,char param_5,char param_6)

{
  longlong lVar1;
  size_t sVar2;
  int iVar3;
  undefined *puVar4;
  uint *puVar5;
  bool bVar6;
  uint local_60;
  ushort local_5c;
  ushort local_5a;
  byte local_58;
  byte local_57;
  uint local_56;
  undefined2 local_52;
  char acStack_4f [43];
  
  __memzero(&local_60,0x10);
  if (g_stWLANWSCUUID[0] == '\x01') {
    memmove(param_2,g_stWLANWSCUUID + 1,0x10);
    memmove(param_3,g_stWLANWSCUUID + 0x11,0x25);
    return 0;
  }
  if (param_5 == '\0') {
    local_5a = 0x11b2;
    local_60 = 0xbc329e00;
    local_5c = 0x1dd8;
  }
  else {
    lVar1 = (ulonglong)jiffies * 10000000 + 0x1b21dd213814000;
    local_60 = (uint)lVar1;
    local_5a = (ushort)((ulonglong)lVar1 >> 0x30) | 0x1000;
    local_5c = (ushort)((ulonglong)lVar1 >> 0x20);
  }
  local_57 = 1;
  local_58 = 0x86;
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    if (param_6 != '\0') {
      param_1 = param_1 + param_4 * 0x2137b0;
      local_56 = *(uint *)(&DAT_0036db73 + param_1);
      local_52 = *(undefined2 *)(&DAT_0036db77 + param_1);
      goto LAB_001e08a4;
    }
    puVar4 = (undefined *)0x794b5b;
  }
  else {
    if (*(char *)(param_1 + 0x286285) != '\0') goto LAB_001e08a4;
    puVar4 = &DAT_0036db73;
  }
  local_56 = *(uint *)(puVar4 + param_1);
  local_52 = (undefined2)*(uint *)((int)(puVar4 + param_1) + 4);
LAB_001e08a4:
  __memzero(acStack_4f,0x27);
  snprintf(acStack_4f,0x27,"%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",local_60,
           (uint)local_5c,(uint)local_5a,(uint)local_58,(uint)local_57,local_56 & 0xff,
           local_56 >> 8 & 0xff,local_56 >> 0x10 & 0xff,local_56 >> 0x18,(uint)(byte)local_52,
           (uint)local_52._1_1_);
  sVar2 = strlen(acStack_4f);
  if ((0x25 < sVar2) && (-1 < DebugLevel)) {
    printk("ERROR:UUID String size too large!\n");
  }
  strncpy(param_3,acStack_4f,0x25);
  local_60 = local_60 << 0x18 | (local_60 >> 8 & 0xff) << 0x10 | (local_60 >> 0x10 & 0xff) << 8 |
             local_60 >> 0x18;
  local_5c = local_5c << 8 | local_5c >> 8;
  local_5a = local_5a << 8 | local_5a >> 8;
  *(ushort *)(param_2 + 1) = local_5c;
  *(ushort *)((int)param_2 + 6) = local_5a;
  *param_2 = local_60;
  *(uint *)((int)param_2 + 10) = local_56;
  bVar6 = g_stWLANWSCUUID[0] == '\0';
  *(undefined2 *)((int)param_2 + 0xe) = local_52;
  *(byte *)(param_2 + 2) = local_58;
  *(byte *)((int)param_2 + 9) = local_57;
  if (bVar6) {
    memmove(g_stWLANWSCUUID + 1,param_2,0x10);
    memmove(g_stWLANWSCUUID + 0x11,param_3,0x25);
    g_stWLANWSCUUID[0] = '\x01';
  }
  if (2 < DebugLevel) {
    printk("The UUID Hex string is:");
  }
  puVar5 = param_2 + 4;
  iVar3 = DebugLevel;
  do {
    if (2 < iVar3) {
      printk(&_LC12,(char)*param_2);
      iVar3 = DebugLevel;
    }
    param_2 = (uint *)((int)param_2 + 1);
  } while (param_2 != puVar5);
  if ((2 < iVar3) && (printk(&_LC13), 2 < DebugLevel)) {
    printk("The UUID ASCII string is:%s!\n",param_3);
  }
  return 0;
}

