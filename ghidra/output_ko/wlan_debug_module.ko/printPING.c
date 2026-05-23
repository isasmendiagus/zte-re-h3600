// module: wlan_debug_module.ko
// function: printPING @ 0x11e34
// size: 1632 bytes
//

void printPING(int param_1,undefined4 param_2,int param_3,byte *param_4,byte *param_5,int param_6,
              int param_7)

{
  byte bVar1;
  ushort uVar2;
  bool bVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  int local_1d8;
  uint local_1d4;
  uint local_1d0;
  uint local_1cc;
  uint local_1c8;
  uint local_1c4;
  uint local_1c0;
  uint local_1bc;
  uint local_1b8;
  uint local_1b4;
  uint local_1b0;
  uint local_1ac;
  uint local_1a8;
  uint local_1a4;
  uint local_1a0;
  uint local_19c;
  uint local_198;
  uint local_194;
  uint local_190;
  uint local_18c;
  uint local_188;
  char *local_184;
  uint local_180;
  char *local_17c;
  uint local_178;
  int local_174;
  char *local_170;
  uint local_16c;
  char *local_168;
  int local_164;
  uint local_160;
  uint local_15c;
  uint local_158;
  uint local_154;
  uint local_150;
  uint local_14c;
  uint local_148;
  uint local_144;
  uint local_140;
  uint local_13c;
  uint local_138;
  uint local_134;
  uint local_130;
  uint local_12c;
  char acStack_128 [260];
  
  uVar6 = *(byte *)(param_1 + 0xe) & 0xf;
  uVar7 = uVar6 * 4;
  if (uVar6 == 5) {
    bVar1 = *(byte *)(param_1 + 0x22);
    uVar2 = *(ushort *)(param_1 + 0x28);
  }
  else {
    if (0x14 < uVar7) {
      uVar7 = uVar7 + 0xe;
    }
    bVar1 = *(byte *)(param_1 + uVar7);
    uVar2 = *(ushort *)((byte *)(param_1 + uVar7) + 6);
  }
  local_180 = (uVar2 & 0xff) << 8 | (uint)(uVar2 >> 8);
  uVar7 = bVar1 & 0xf7;
  if ((bVar1 & 0xf7) != 0) {
    return;
  }
  if (param_6 == 0 || param_3 == 0) {
    return;
  }
  bVar3 = bVar1 != 8;
  local_1d8 = param_3;
  local_178 = local_180;
  local_170 = (char *)param_2;
  local_16c = param_3;
  if (param_7 == -1) {
    if (g_pktcnt_dbgredirect == 0) {
      local_1d4 = (uint)*param_4;
      local_1d0 = (uint)param_4[1];
      local_1cc = (uint)param_4[2];
      local_1c8 = (uint)param_4[3];
      local_1c4 = (uint)param_4[4];
      local_1c0 = (uint)param_4[5];
      local_1bc = (uint)*param_5;
      local_1b8 = (uint)param_5[1];
      local_1b4 = (uint)param_5[2];
      local_1b0 = (uint)param_5[3];
      local_1ac = (uint)param_5[4];
      local_184 = "request";
      if (bVar3) {
        local_184 = "reply";
      }
      local_1a8 = (uint)param_5[5];
      local_1a4 = (uint)*(byte *)(param_1 + 0x1a);
      local_1a0 = (uint)*(byte *)(param_1 + 0x1b);
      local_19c = (uint)*(byte *)(param_1 + 0x1c);
      local_198 = (uint)*(byte *)(param_1 + 0x1d);
      local_194 = (uint)*(byte *)(param_1 + 0x1e);
      local_190 = (uint)*(byte *)(param_1 + 0x1f);
      local_18c = (uint)*(byte *)(param_1 + 0x20);
      local_188 = (uint)*(byte *)(param_1 + 0x21);
      local_170 = local_184;
      local_16c = local_1ac;
      local_168 = (char *)local_1c0;
      printk("[%s]%8ld [%u][%s] %02X:%02X:%02X:%02X:%02X:%02X->%02X:%02X:%02X:%02X:%02X:%02X, %d.%d.%d.%d->%d.%d.%d.%d, ping %s, seq=%d\n"
             ,param_6,jiffies,param_2);
      return;
    }
    uVar6 = filp_open("/var/tmp/ping_record",0x442,uVar7);
    if (0xfffff000 < uVar6) {
      return;
    }
    memset(acStack_128,uVar7,0x100);
    local_1cc = (uint)*param_4;
    local_1c8 = (uint)param_4[1];
    local_1c4 = (uint)param_4[2];
    local_1bc = (uint)param_4[4];
    local_1b0 = (uint)param_5[1];
    local_1c0 = (uint)param_4[3];
    local_1b8 = (uint)param_4[5];
    local_164 = jiffies;
    local_1b4 = (uint)*param_5;
    local_17c = "request";
    if (bVar3) {
      local_17c = "reply";
    }
    local_1ac = (uint)param_5[2];
    local_1a8 = (uint)param_5[3];
    local_1a4 = (uint)param_5[4];
    local_1a0 = (uint)param_5[5];
    local_198 = (uint)*(byte *)(param_1 + 0x1b);
    local_19c = (uint)*(byte *)(param_1 + 0x1a);
    local_194 = (uint)*(byte *)(param_1 + 0x1c);
    local_190 = (uint)*(byte *)(param_1 + 0x1d);
    local_18c = (uint)*(byte *)(param_1 + 0x1e);
    local_188 = (uint)*(byte *)(param_1 + 0x1f);
    local_184 = (char *)(uint)*(byte *)(param_1 + 0x20);
    local_180 = (uint)*(byte *)(param_1 + 0x21);
    local_1d4 = (uint)local_170;
    local_1d0 = local_16c;
    local_1d8 = jiffies;
    local_168 = local_17c;
    local_160 = local_1cc;
    local_15c = local_1c8;
    local_158 = local_1c4;
    local_154 = local_1c0;
    local_150 = local_1bc;
    local_14c = local_1b8;
    local_148 = local_1b4;
    local_144 = local_1b0;
    local_140 = local_1ac;
    local_13c = local_1a8;
    local_138 = local_1a4;
    local_134 = local_1a0;
    local_130 = local_19c;
    local_12c = local_198;
    iVar4 = snprintf(acStack_128,0x100,
                     "[%s]%8ld [%u][%s] %02X:%02X:%02X:%02X:%02X:%02X->%02X:%02X:%02X:%02X:%02X:%02X, %d.%d.%d.%d->%d.%d.%d.%d, ping %s, seq=%d\n"
                     ,param_6);
  }
  else {
    if (g_pktcnt_dbgredirect == 0) {
      local_1d4 = (uint)*param_4;
      local_1d0 = (uint)param_4[1];
      local_1cc = (uint)param_4[2];
      local_1c8 = (uint)param_4[3];
      local_1c4 = (uint)param_4[4];
      local_1c0 = (uint)param_4[5];
      local_184 = "request";
      if (bVar3) {
        local_184 = "reply";
      }
      local_1bc = (uint)*param_5;
      local_1b8 = (uint)param_5[1];
      local_1b4 = (uint)param_5[2];
      local_1b0 = (uint)param_5[3];
      local_1ac = (uint)param_5[4];
      local_1a8 = (uint)param_5[5];
      local_1a4 = (uint)*(byte *)(param_1 + 0x1a);
      local_1a0 = (uint)*(byte *)(param_1 + 0x1b);
      local_19c = (uint)*(byte *)(param_1 + 0x1c);
      local_198 = (uint)*(byte *)(param_1 + 0x1d);
      local_194 = (uint)*(byte *)(param_1 + 0x1e);
      local_190 = (uint)*(byte *)(param_1 + 0x1f);
      local_18c = (uint)*(byte *)(param_1 + 0x20);
      local_188 = (uint)*(byte *)(param_1 + 0x21);
      local_17c = (char *)param_7;
      local_170 = local_184;
      local_16c = local_1ac;
      local_168 = (char *)local_1c0;
      printk("[%s]%8ld [%u][%s] %02X:%02X:%02X:%02X:%02X:%02X->%02X:%02X:%02X:%02X:%02X:%02X, %d.%d.%d.%d->%d.%d.%d.%d, ping %s, seq=%d, VID=%d\n"
             ,param_6,jiffies,param_2);
      return;
    }
    uVar6 = filp_open("/var/tmp/ping_record",0x442,uVar7);
    if (0xfffff000 < uVar6) {
      return;
    }
    memset(acStack_128,uVar7,0x100);
    local_1cc = (uint)*param_4;
    local_1c8 = (uint)param_4[1];
    local_1c4 = (uint)param_4[2];
    local_1bc = (uint)param_4[4];
    local_1b0 = (uint)param_5[1];
    local_1c0 = (uint)param_4[3];
    local_1b8 = (uint)param_4[5];
    local_164 = jiffies;
    local_1b4 = (uint)*param_5;
    local_17c = "request";
    if (bVar3) {
      local_17c = "reply";
    }
    local_1ac = (uint)param_5[2];
    local_1a8 = (uint)param_5[3];
    local_1a4 = (uint)param_5[4];
    local_1a0 = (uint)param_5[5];
    local_198 = (uint)*(byte *)(param_1 + 0x1b);
    local_19c = (uint)*(byte *)(param_1 + 0x1a);
    local_194 = (uint)*(byte *)(param_1 + 0x1c);
    local_190 = (uint)*(byte *)(param_1 + 0x1d);
    local_188 = (uint)*(byte *)(param_1 + 0x1f);
    local_184 = (char *)(uint)*(byte *)(param_1 + 0x20);
    local_18c = (uint)*(byte *)(param_1 + 0x1e);
    local_180 = (uint)*(byte *)(param_1 + 0x21);
    local_1d4 = (uint)local_170;
    local_1d0 = local_16c;
    local_1d8 = jiffies;
    local_174 = param_7;
    local_168 = local_17c;
    local_160 = local_1cc;
    local_15c = local_1c8;
    local_158 = local_1c4;
    local_154 = local_1c0;
    local_150 = local_1bc;
    local_14c = local_1b8;
    local_148 = local_1b4;
    local_144 = local_1b0;
    local_140 = local_1ac;
    local_13c = local_1a8;
    local_138 = local_1a4;
    local_134 = local_1a0;
    local_130 = local_19c;
    local_12c = local_198;
    iVar4 = snprintf(acStack_128,0x100,
                     "[%s]%8ld [%u][%s] %02X:%02X:%02X:%02X:%02X:%02X->%02X:%02X:%02X:%02X:%02X:%02X, %d.%d.%d.%d->%d.%d.%d.%d, ping %s, seq=%d, VID=%d\n"
                     ,param_6);
  }
  uVar5 = *(undefined4 *)(((uint)&local_1d8 & 0xffffe000) + 8);
  *(uint *)(((uint)&local_1d8 & 0xffffe000) + 8) = uVar7;
  vfs_write(uVar6,acStack_128,iVar4,uVar6 + 0x40);
  *(undefined4 *)(((uint)&local_1d8 & 0xffffe000) + 8) = uVar5;
  filp_close(uVar6,uVar7);
  return;
}

