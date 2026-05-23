// module: wlan_debug_module.ko
// function: printPINGv6 @ 0x136d8
// size: 1488 bytes
//

void printPINGv6(int param_1,undefined4 param_2,int param_3,byte *param_4,byte *param_5,int param_6,
                int param_7)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  char *pcVar4;
  int local_220;
  uint local_21c;
  uint local_218;
  uint local_214;
  uint local_210;
  uint local_20c;
  uint local_208;
  uint local_204;
  uint local_200;
  uint local_1fc;
  uint local_1f8;
  uint local_1f4;
  uint local_1f0;
  undefined4 *local_1ec;
  undefined1 *local_1e8;
  char *local_1e4;
  undefined1 *local_1e0;
  char *local_1dc;
  uint local_1d8;
  int local_1d4;
  char *local_1d0;
  int local_1cc;
  uint local_1c8;
  uint local_1c4;
  uint local_1c0;
  uint local_1bc;
  uint local_1b8;
  uint local_1b4;
  uint local_1b0;
  uint local_1ac;
  undefined4 local_1a4;
  undefined4 local_1a0;
  undefined4 local_19c;
  undefined4 local_198;
  undefined4 local_194;
  undefined4 local_190;
  undefined4 local_18c;
  undefined4 local_188;
  undefined4 local_184;
  undefined4 local_180;
  undefined4 local_17c;
  undefined4 local_178;
  undefined4 local_174;
  undefined4 local_170;
  undefined4 local_16c;
  undefined4 local_168;
  undefined4 local_164;
  undefined4 local_160;
  undefined4 local_15c;
  undefined2 local_158;
  undefined1 auStack_156 [46];
  char acStack_128 [260];
  
  pcVar4 = (char *)(uint)*(byte *)(param_1 + 0x36);
  local_184 = 0;
  uVar2 = (*(ushort *)(param_1 + 0x3c) & 0xff) << 8 | (uint)(*(ushort *)(param_1 + 0x3c) >> 8);
  local_180 = 0;
  local_17c = 0;
  local_178 = 0;
  local_174 = 0;
  local_170 = 0;
  local_16c = 0;
  local_168 = 0;
  local_164 = 0;
  local_160 = 0;
  local_15c = 0;
  local_158 = 0;
  memset(auStack_156,0,0x2e);
  local_1a0 = *(undefined4 *)(param_1 + 0x1a);
  local_19c = *(undefined4 *)(param_1 + 0x1e);
  local_1a4 = *(undefined4 *)(param_1 + 0x16);
  local_190 = *(undefined4 *)(param_1 + 0x2a);
  local_198 = *(undefined4 *)(param_1 + 0x22);
  local_194 = *(undefined4 *)(param_1 + 0x26);
  local_18c = *(undefined4 *)(param_1 + 0x2e);
  local_188 = *(undefined4 *)(param_1 + 0x32);
  IPv6ToStr(&local_1a4,&local_184,0x2e);
  IPv6ToStr(&local_194,auStack_156,0x2e);
  if ((((uint)pcVar4 ^ 0x80) < 2) && (param_6 != 0 && param_3 != 0)) {
    local_220 = param_3;
    local_21c = param_2;
    local_218 = param_3;
    local_1e0 = (undefined1 *)uVar2;
    local_1d8 = uVar2;
    if (param_7 == -1) {
      if (g_pktcnt_dbgredirect == 0) {
        local_1e4 = "request";
        if (pcVar4 != (char *)0x80) {
          local_1e4 = "reply";
        }
        local_21c = (uint)*param_4;
        local_218 = (uint)param_4[1];
        local_1ec = &local_184;
        local_1e8 = auStack_156;
        local_214 = (uint)param_4[2];
        local_210 = (uint)param_4[3];
        local_20c = (uint)param_4[4];
        local_208 = (uint)param_4[5];
        local_204 = (uint)*param_5;
        local_200 = (uint)param_5[1];
        local_1fc = (uint)param_5[2];
        local_1f8 = (uint)param_5[3];
        local_1f4 = (uint)param_5[4];
        local_1f0 = (uint)param_5[5];
        local_1d0 = (char *)local_1f8;
        printk("[%s]%8ld [%u][%s] %02X:%02X:%02X:%02X:%02X:%02X->%02X:%02X:%02X:%02X:%02X:%02X,  %s->%s, ping %s, seq=%d\n"
               ,param_6,jiffies,param_2);
      }
      else {
        uVar2 = filp_open("/var/tmp/pingv6_record",0x442,0);
        if (uVar2 < 0xfffff001) {
          memset(acStack_128,0,0x100);
          local_210 = (uint)param_4[1];
          local_208 = (uint)param_4[3];
          local_204 = (uint)param_4[4];
          local_214 = (uint)*param_4;
          local_20c = (uint)param_4[2];
          local_200 = (uint)param_4[5];
          local_1cc = jiffies;
          local_1dc = "request";
          if (pcVar4 != (char *)0x80) {
            local_1dc = "reply";
          }
          local_1fc = (uint)*param_5;
          local_1f8 = (uint)param_5[1];
          local_1e8 = (undefined1 *)(uint)param_5[5];
          local_1f4 = (uint)param_5[2];
          local_1f0 = (uint)param_5[3];
          local_1ec = (undefined4 *)(uint)param_5[4];
          local_1e4 = (char *)&local_184;
          local_1e0 = auStack_156;
          local_220 = jiffies;
          local_1d0 = local_1dc;
          local_1c8 = local_214;
          local_1c4 = local_210;
          local_1c0 = local_20c;
          local_1bc = local_208;
          local_1b8 = local_204;
          local_1b4 = local_200;
          local_1b0 = local_1fc;
          local_1ac = local_1f8;
          iVar1 = snprintf(acStack_128,0x100,
                           "[%s]%8ld [%u][%s] %02X:%02X:%02X:%02X:%02X:%02X->%02X:%02X:%02X:%02X:%02X:%02X,  %s->%s, ping %s, seq=%d\n"
                           ,param_6);
          goto LAB_00013944;
        }
      }
    }
    else if (g_pktcnt_dbgredirect == 0) {
      local_21c = (uint)*param_4;
      local_1e4 = pcVar4;
      if (pcVar4 == (char *)0x80) {
        local_1e4 = "request";
      }
      local_218 = (uint)param_4[1];
      local_214 = (uint)param_4[2];
      local_210 = (uint)param_4[3];
      local_20c = (uint)param_4[4];
      local_208 = (uint)param_4[5];
      local_1e8 = auStack_156;
      local_1ec = &local_184;
      local_1dc = (char *)param_7;
      local_204 = (uint)*param_5;
      if (pcVar4 != (char *)0x80) {
        local_1e4 = "reply";
      }
      local_200 = (uint)param_5[1];
      local_1fc = (uint)param_5[2];
      local_1f8 = (uint)param_5[3];
      local_1f4 = (uint)param_5[4];
      local_1f0 = (uint)param_5[5];
      local_1d0 = (char *)local_1f8;
      printk("[%s]%8ld [%u][%s] %02X:%02X:%02X:%02X:%02X:%02X->%02X:%02X:%02X:%02X:%02X:%02X,  %s->%s, ping %s, seq=%d, VID=%d\n"
             ,param_6,jiffies,param_2);
    }
    else {
      uVar2 = filp_open("/var/tmp/pingv6_record",0x442,0);
      if (uVar2 < 0xfffff001) {
        memset(acStack_128,0,0x100);
        local_210 = (uint)param_4[1];
        local_208 = (uint)param_4[3];
        local_204 = (uint)param_4[4];
        local_214 = (uint)*param_4;
        local_20c = (uint)param_4[2];
        local_200 = (uint)param_4[5];
        local_1cc = jiffies;
        local_1dc = "request";
        if (pcVar4 != (char *)0x80) {
          local_1dc = "reply";
        }
        local_1fc = (uint)*param_5;
        local_1f8 = (uint)param_5[1];
        local_1e8 = (undefined1 *)(uint)param_5[5];
        local_1f4 = (uint)param_5[2];
        local_1f0 = (uint)param_5[3];
        local_1ec = (undefined4 *)(uint)param_5[4];
        local_1e4 = (char *)&local_184;
        local_1e0 = auStack_156;
        local_1d4 = param_7;
        local_220 = jiffies;
        local_1d0 = local_1dc;
        local_1c8 = local_214;
        local_1c4 = local_210;
        local_1c0 = local_20c;
        local_1bc = local_208;
        local_1b8 = local_204;
        local_1b4 = local_200;
        local_1b0 = local_1fc;
        local_1ac = local_1f8;
        iVar1 = snprintf(acStack_128,0x100,
                         "[%s]%8ld [%u][%s] %02X:%02X:%02X:%02X:%02X:%02X->%02X:%02X:%02X:%02X:%02X:%02X,  %s->%s, ping %s, seq=%d, VID=%d\n"
                         ,param_6);
LAB_00013944:
        uVar3 = *(undefined4 *)(((uint)&local_220 & 0xffffe000) + 8);
        *(undefined4 *)(((uint)&local_220 & 0xffffe000) + 8) = 0;
        vfs_write(uVar2,acStack_128,iVar1,uVar2 + 0x40);
        *(undefined4 *)(((uint)&local_220 & 0xffffe000) + 8) = uVar3;
        filp_close(uVar2,0);
        return;
      }
    }
  }
  return;
}

