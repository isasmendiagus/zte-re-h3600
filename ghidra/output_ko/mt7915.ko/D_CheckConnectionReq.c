// module: mt7915.ko
// function: D_CheckConnectionReq @ 0x9de7c
// size: 680 bytes
//

bool D_CheckConnectionReq
               (undefined4 param_1,undefined4 *param_2,undefined4 *param_3,int param_4,
               undefined4 param_5)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  undefined1 uVar6;
  uint uVar7;
  char *pcVar8;
  int iVar9;
  bool bVar10;
  uint local_78 [4];
  undefined1 local_68 [4];
  undefined1 local_64;
  undefined1 local_61;
  undefined4 local_5c;
  undefined2 local_58;
  undefined1 local_55;
  
  local_78[0] = 1;
  local_78[1] = 0;
  local_78[2] = 4;
  local_78[3] = 2;
  uVar7 = BandSteerAvgRssi(param_1,param_5);
  local_61 = (undefined1)uVar7;
  if (param_4 == 4) {
    iVar9 = 0;
LAB_0009decc:
    local_5c = *param_3;
    local_64 = *(undefined1 *)((int)param_2 + 0x106e);
    local_58 = *(undefined2 *)(param_3 + 1);
    local_55 = (undefined1)iVar9;
    local_68[0] = 1;
    RtmpOSWrielessEventSend(*param_2,1,0x950,0,local_68,0x40);
  }
  else {
    if (param_4 != 6) {
      iVar9 = 1;
      goto LAB_0009decc;
    }
    local_5c = *param_3;
    local_58 = *(undefined2 *)(param_3 + 1);
    local_64 = *(undefined1 *)((int)param_2 + 0x106e);
    iVar9 = 3;
    local_68[0] = 1;
    local_55 = 3;
    RtmpOSWrielessEventSend(*param_2,1,0x950,0,local_68,0x40);
  }
  if ((*(char *)((int)param_2 + 5) != '\x01') || ((local_78[iVar9] & param_2[3]) == 0)) {
    return true;
  }
  if ((param_2[0x406] == 0) ||
     (iVar9 = (**(code **)(param_2[0x406] + 0x14))(param_2,param_3), iVar9 == 0)) {
    return *(char *)((int)param_2 + 0x106e) == '\x01';
  }
  if (*(char *)((int)param_2 + 0x106e) == '\x01') {
    if ((*(uint *)(iVar9 + 4) & 1) == 0) {
      return true;
    }
    if ((param_2[4] & 8) == 0) {
      return true;
    }
    if ((int)*(char *)((int)param_2 + 0x1023) <= (int)uVar7) {
      return true;
    }
    if (DebugLevel < 3) {
      return false;
    }
    uVar1 = *(undefined1 *)param_3;
    uVar2 = *(undefined1 *)((int)param_3 + 1);
    uVar3 = *(undefined1 *)((int)param_3 + 2);
    pcVar8 = "\n 5G rssi is low =%d abandon.(%02x:%02x:%02x:%02x:%02x:%02x)\n";
  }
  else {
    if ((*(uint *)(iVar9 + 4) & 2) == 0) {
      return true;
    }
    if ((((param_2[4] & 8) != 0) && (*(char *)(iVar9 + 0xf) != '\0')) &&
       (uVar7 = (uint)*(char *)(iVar9 + 0xf), (int)uVar7 < (int)*(char *)((int)param_2 + 0x1023))) {
      if (DebugLevel < 3) {
        return true;
      }
      uVar1 = *(undefined1 *)param_3;
      uVar2 = *(undefined1 *)((int)param_3 + 1);
      pcVar8 = "\nsupport 5G but 5G RSSI is low=%d pass.(%02x:%02x:%02x:%02x:%02x:%02x)\n";
      uVar3 = *(undefined1 *)((int)param_3 + 2);
      uVar4 = *(undefined1 *)((int)param_3 + 3);
      uVar5 = *(undefined1 *)(param_3 + 1);
      uVar6 = *(undefined1 *)((int)param_3 + 5);
      bVar10 = true;
      goto LAB_0009dfe8;
    }
    uVar7 = *(int *)(iVar9 + 0x10) + 1;
    *(uint *)(iVar9 + 0x10) = uVar7;
    if (*(byte *)((int)param_2 + 0x108e) <= uVar7) {
      return true;
    }
    if (DebugLevel < 3) {
      return false;
    }
    uVar1 = *(undefined1 *)param_3;
    uVar2 = *(undefined1 *)((int)param_3 + 1);
    pcVar8 = "\nsupport 5G ulInSilenceNum=%d abandon.(%02x:%02x:%02x:%02x:%02x:%02x)\n";
    uVar3 = *(undefined1 *)((int)param_3 + 2);
  }
  uVar4 = *(undefined1 *)((int)param_3 + 3);
  bVar10 = false;
  uVar5 = *(undefined1 *)(param_3 + 1);
  uVar6 = *(undefined1 *)((int)param_3 + 5);
LAB_0009dfe8:
  printk(pcVar8,uVar7,uVar1,uVar2,uVar3,uVar4,uVar5,uVar6);
  return bVar10;
}

