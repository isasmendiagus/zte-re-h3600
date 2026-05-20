// module: mt7915.ko
// function: WscBuildProbeReqIE @ 0x1e4bb4
// size: 1152 bytes
//

void WscBuildProbeReqIE(undefined4 param_1,int param_2,int param_3,char *param_4)

{
  int iVar1;
  size_t sVar2;
  int iVar3;
  uint extraout_r12;
  uint uVar4;
  bool bVar5;
  ushort local_3e;
  int local_3c;
  int local_38;
  int local_34;
  undefined1 local_2e;
  char local_2d;
  undefined1 local_2c;
  undefined1 local_2b;
  undefined1 local_2a;
  undefined1 local_29;
  
  local_3c = 0;
  local_38 = 0;
  local_3e = 0;
  if (3 < DebugLevel) {
    printk("-----> WscBuildProbeReqIE\n");
  }
  os_alloc_mem(0,&local_3c,0x200);
  if (local_3c == 0) {
    if (-1 < DebugLevel) {
      printk("%s: Allocate memory fail!!!\n","WscBuildProbeReqIE");
    }
  }
  else {
    GetStaCfgByWdev(param_1,param_2);
    local_2c = 0;
    local_38 = 0;
    local_34 = local_3c;
    local_2e = 0xdd;
    local_2b = 0x50;
    local_2d = '\x04';
    local_29 = 4;
    local_2a = 0xf2;
    iVar1 = AppendWSCTLV(0x104a,local_3c,param_2 + 0x1354,0);
    iVar3 = *(int *)(param_2 + 0x12e4);
    bVar5 = iVar3 == 4;
    if (bVar5) {
      iVar3 = 2;
    }
    local_34 = local_34 + iVar1;
    if (bVar5) {
      local_3e = (ushort)iVar3;
    }
    local_38 = local_38 + iVar1;
    if (!bVar5) {
      local_3e = (ushort)(iVar3 == 1);
    }
    iVar1 = AppendWSCTLV(0x103a,local_34,&local_3e,0);
    bVar5 = *(char *)(param_2 + 0x3e15) == '\0';
    uVar4 = extraout_r12;
    if (bVar5) {
      uVar4 = (uint)*(byte *)(param_2 + 0x12ee);
    }
    local_34 = local_34 + iVar1;
    local_38 = local_38 + iVar1;
    if (!bVar5) {
      uVar4 = (uint)*(ushort *)(param_2 + 0x12ee);
    }
    local_3e = (ushort)((uVar4 & 0xff) << 8) | (ushort)(uVar4 >> 8) & 0xff;
    iVar1 = AppendWSCTLV(0x1008,local_34,&local_3e,0);
    local_34 = local_34 + iVar1;
    local_38 = local_38 + iVar1;
    iVar1 = AppendWSCTLV(0x1047,local_34,param_2 + 0x1356,0);
    local_34 = local_34 + iVar1;
    local_38 = local_38 + iVar1;
    iVar1 = AppendWSCTLV(0x1054,local_34,param_2 + 0x138c,0);
    local_34 = local_34 + iVar1;
    local_38 = local_38 + iVar1;
    iVar1 = AppendWSCTLV(0x103c,local_34,param_2 + 0x144f,0);
    local_3e = *(ushort *)(param_2 + 0x1458);
    local_34 = local_34 + iVar1;
    local_38 = local_38 + iVar1;
    iVar1 = AppendWSCTLV(0x1002,local_34,&local_3e,0);
    local_3e = *(ushort *)(param_2 + 0x145c);
    local_34 = local_34 + iVar1;
    local_38 = local_38 + iVar1;
    iVar1 = AppendWSCTLV(0x1009,local_34,&local_3e,0);
    local_3e = *(ushort *)(param_2 + 0x145a);
    local_34 = local_34 + iVar1;
    local_38 = local_38 + iVar1;
    iVar1 = AppendWSCTLV(0x1012,local_34,&local_3e,0);
    local_34 = local_34 + iVar1;
    local_38 = iVar1 + local_38;
    if (*(char *)(param_2 + 0x3e15) != '\0') {
      __memzero(local_34,0x44);
      sVar2 = strlen((char *)(param_2 + 0x13af));
      iVar1 = AppendWSCTLV(0x1021,local_34,(char *)(param_2 + 0x13af),sVar2 & 0xffff);
      local_34 = local_34 + iVar1;
      local_38 = local_38 + iVar1;
      __memzero(local_34,0x24);
      sVar2 = strlen((char *)(param_2 + 0x13ef));
      iVar1 = AppendWSCTLV(0x1023,local_34,(char *)(param_2 + 0x13ef),sVar2 & 0xffff);
      local_34 = local_34 + iVar1;
      local_38 = local_38 + iVar1;
      __memzero(local_34,0x24);
      sVar2 = strlen((char *)(param_2 + 0x140f));
      iVar1 = AppendWSCTLV(0x1024,local_34,(char *)(param_2 + 0x140f),sVar2 & 0xffff);
      local_34 = local_34 + iVar1;
      local_38 = local_38 + iVar1;
      __memzero(local_34,0x24);
      sVar2 = strlen((char *)(param_2 + 0x136c));
      iVar1 = AppendWSCTLV(0x1011,local_34,(char *)(param_2 + 0x136c),sVar2 & 0xffff);
      local_38 = local_38 + iVar1;
      local_34 = local_34 + iVar1;
      WscGenV2Msg(param_2 + 0x12e4,0,0,0,&local_34,&local_38);
    }
    local_2d = (char)local_38 + local_2d;
    RTMPMoveMemory(param_3,&local_2e,6);
    RTMPMoveMemory(param_3 + 6,local_3c,local_38);
    *param_4 = (char)local_38 + '\x06';
    if (local_3c != 0) {
      os_free_mem();
    }
    if (3 < DebugLevel) {
      printk("<----- WscBuildProbeReqIE\n");
    }
  }
  return;
}

