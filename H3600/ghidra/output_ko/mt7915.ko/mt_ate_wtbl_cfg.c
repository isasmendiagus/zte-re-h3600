// module: mt7915.ko
// function: mt_ate_wtbl_cfg @ 0x285904
// size: 848 bytes
//

void mt_ate_wtbl_cfg(int param_1,int param_2)

{
  char cVar1;
  undefined1 uVar2;
  char cVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  int iVar6;
  undefined4 uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  undefined1 local_7c [4];
  undefined4 local_78;
  undefined4 local_74;
  undefined1 local_70;
  undefined4 local_6c;
  uint local_68;
  undefined1 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined1 local_58;
  undefined4 local_54;
  uint local_50;
  undefined1 local_4c;
  undefined4 local_48;
  uint local_44;
  undefined1 local_40;
  undefined4 local_3c;
  uint local_38;
  undefined1 local_34;
  undefined4 local_30;
  uint local_2c;
  
  iVar6 = net_ad_wrap_service();
  param_2 = param_2 * 0xd18;
  cVar1 = *(char *)(iVar6 + param_2 + 0x1106);
  iVar6 = net_ad_wrap_service(param_1);
  uVar11 = (uint)*(byte *)(iVar6 + param_2 + 0x1135);
  iVar6 = net_ad_wrap_service(param_1);
  uVar2 = *(undefined1 *)(iVar6 + param_2 + 0x1138);
  iVar6 = net_ad_wrap_service(param_1);
  cVar3 = *(char *)(iVar6 + param_2 + 0x1139);
  iVar6 = net_ad_wrap_service(param_1);
  uVar4 = *(undefined1 *)(iVar6 + param_2 + 0x1136);
  iVar6 = net_ad_wrap_service(param_1);
  uVar10 = (uint)*(byte *)(iVar6 + param_2 + 0x113c);
  iVar6 = net_ad_wrap_service(param_1);
  uVar5 = *(undefined1 *)(iVar6 + param_2 + 0x113a);
  iVar6 = net_ad_wrap_service(param_1);
  uVar9 = *(uint *)(iVar6 + param_2 + 0x1128);
  __memzero(local_7c,0x54);
  local_7c[0] = 2;
  local_78 = 0x9fffffff;
  if (uVar11 < 2) {
LAB_00285be4:
    local_74 = 0;
  }
  else if (uVar11 < 4) {
    local_74 = 0x20000000;
  }
  else {
    if (uVar11 != 4) goto LAB_00285be4;
    local_74 = 0x60000000;
  }
  local_6c = 0xd8e0f000;
  local_70 = 3;
  if (cVar1 == '\0') {
    local_68 = 0;
    local_5c = 0;
  }
  else {
    uVar8 = uVar9 & 7;
    local_68 = uVar8 | 0x27000000 | (uVar9 & 0x1f) << 0x10 | uVar8 << 9 | uVar8 << 6 | uVar8 << 3;
    local_5c = 0xffffffff;
  }
  local_60 = 0;
  local_64 = 4;
  local_54 = 0xfff7c0ff;
  local_58 = 5;
  switch(uVar4) {
  case 0:
    local_50 = uVar10 << 8;
    break;
  case 1:
    local_50 = uVar10 << 9 | 0x1000;
    break;
  case 2:
    local_50 = uVar10 << 10 | 0x2000;
    break;
  case 3:
    local_50 = uVar10 << 0xb | 0x3000;
    break;
  default:
    if (0 < DebugLevel) {
      printk("%s: Can\'t find such bw, use default\n","mt_ate_wtbl_cfg");
    }
    local_50 = uVar10 << 8;
  }
  if (uVar11 - 2 < 3) {
    local_50 = local_50 | 0x80000;
  }
  else if (uVar11 == 0) {
    uVar7 = 1;
    goto LAB_00285ac4;
  }
  uVar7 = 0;
LAB_00285ac4:
  uVar9 = asic_tx_rate_to_tmi_rate(param_1,uVar11,uVar2,cVar3 + '\x01',uVar5,uVar7);
  uVar10 = uVar9 & 0xfff;
  local_38 = (uVar9 & 0xfff) << 4 | uVar10 << 0x10 | uVar9 << 0x1c | (uVar9 << 0x14) >> 0x1c;
  local_44 = uVar10 | uVar9 << 0x18 | uVar10 << 0xc;
  local_2c = (uVar9 << 0x14) >> 0x18 | uVar10 << 8 | uVar9 << 0x14;
  local_4c = 6;
  local_48 = 0;
  local_3c = 0;
  local_30 = 0;
  local_40 = 7;
  local_34 = 8;
  if (2 < DebugLevel) {
    printk("%s: phy_mode=%d, mcs=%d, nss=%d, stbc=%d, wtbl_rate=0x%x\n","mt_ate_wtbl_cfg",uVar11,
           uVar2,cVar3,uVar5,uVar9);
  }
  WtblResetAndDWsSet(param_1,*(undefined2 *)(param_1 + 0xa3b008),1,7,local_7c);
  return;
}

