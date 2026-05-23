// module: wlan_debug_module.ko
// function: printDHCPv6 @ 0x13410
// size: 708 bytes
//

void printDHCPv6(int param_1,undefined4 param_2,int param_3,undefined1 *param_4,undefined1 *param_5,
                int param_6,int param_7)

{
  byte bVar1;
  ushort uVar2;
  ushort uVar3;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined2 local_90;
  undefined1 auStack_8e [46];
  char *apcStack_60 [15];
  
  uVar2 = *(ushort *)(param_1 + 0x36) << 8 | *(ushort *)(param_1 + 0x36) >> 8;
  uVar3 = *(ushort *)(param_1 + 0x38) << 8 | *(ushort *)(param_1 + 0x38) >> 8;
  if ((uVar3 == 0x223 && uVar2 == 0x222) || (uVar3 == 0x222 && uVar2 == 0x223)) {
    apcStack_60[0] = "unknown";
    apcStack_60[1] = "solicit";
    apcStack_60[2] = "advertise";
    apcStack_60[3] = "request";
    bVar1 = *(byte *)(param_1 + 0x3e);
    local_bc = 0;
    local_b8 = 0;
    apcStack_60[4] = "confirm";
    apcStack_60[5] = "renew";
    apcStack_60[6] = "rebind";
    apcStack_60[7] = "reply";
    local_b4 = 0;
    local_b0 = 0;
    apcStack_60[8] = "release";
    apcStack_60[9] = "decline";
    apcStack_60[10] = "reconfigure";
    apcStack_60[0xb] = "information-request";
    apcStack_60[0xc] = "relay-forw";
    apcStack_60[0xd] = "relay-repl";
    local_ac = 0;
    local_a8 = 0;
    local_a4 = 0;
    local_a0 = 0;
    local_9c = 0;
    local_98 = 0;
    local_94 = 0;
    local_90 = 0;
    memset(auStack_8e,0,0x2e);
    local_dc = *(undefined4 *)(param_1 + 0x16);
    local_d8 = *(undefined4 *)(param_1 + 0x1a);
    local_d4 = *(undefined4 *)(param_1 + 0x1e);
    local_d0 = *(undefined4 *)(param_1 + 0x22);
    local_cc = *(undefined4 *)(param_1 + 0x26);
    local_c8 = *(undefined4 *)(param_1 + 0x2a);
    local_c4 = *(undefined4 *)(param_1 + 0x2e);
    local_c0 = *(undefined4 *)(param_1 + 0x32);
    IPv6ToStr(&local_dc,&local_bc,0x2e);
    IPv6ToStr(&local_cc,auStack_8e,0x2e);
    if ((bVar1 - 1 < 0xd) && (param_6 != 0 && param_3 != 0)) {
      if (param_7 == -1) {
        printk("[%s]%8ld [%u][%s] %02X:%02X:%02X:%02X:%02X:%02X->%02X:%02X:%02X:%02X:%02X:%02X, %s->%s, dhcp %s\n"
               ,param_6,jiffies,param_2,param_3,*param_4,param_4[1],param_4[2],param_4[3],param_4[4]
               ,param_4[5],*param_5,param_5[1],param_5[2],param_5[3],param_5[4],param_5[5],&local_bc
               ,auStack_8e,apcStack_60[bVar1]);
      }
      else {
        printk("[%s]%8ld [%u][%s] %02X:%02X:%02X:%02X:%02X:%02X->%02X:%02X:%02X:%02X:%02X:%02X, %s->%s, dhcp %s, VID=%d\n"
               ,param_6,jiffies,param_2,param_3,*param_4,param_4[1],param_4[2],param_4[3],param_4[4]
               ,param_4[5],*param_5,param_5[1],param_5[2],param_5[3],param_5[4],param_5[5],&local_bc
               ,auStack_8e,apcStack_60[bVar1],param_7);
      }
    }
  }
  return;
}

