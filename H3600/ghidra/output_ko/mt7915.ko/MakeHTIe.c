// module: mt7915.ko
// function: MakeHTIe @ 0xb3950
// size: 460 bytes
//

void MakeHTIe(int param_1,int param_2,int *param_3,int param_4)

{
  byte bVar1;
  undefined4 uVar2;
  byte *__src;
  uint uVar3;
  uint __n;
  int iVar4;
  undefined1 *puVar5;
  undefined4 uVar6;
  byte *pbVar7;
  undefined4 uVar8;
  byte local_5c;
  byte local_5b [3];
  int local_58;
  int local_54;
  undefined2 local_50;
  undefined2 local_4e;
  undefined2 local_4c;
  undefined2 local_4a;
  undefined2 local_48;
  undefined2 local_46;
  undefined2 local_44;
  byte local_42 [30];
  
  iVar4 = *param_3;
  uVar2 = wlan_operate_get_addht(param_2);
  bVar1 = wlan_operate_get_ht_bw(param_2);
  local_5b[0] = 0x16;
  local_5c = 0x1a;
  __src = (byte *)wlan_operate_get_ht_cap(param_2);
  __n = (uint)local_5c;
  memmove(local_42,__src,__n);
  pbVar7 = local_5b;
  uVar3 = (uint)local_5b[0];
  local_42[0] = local_42[0] & 0xfd | (bVar1 & 1) << 1;
  puVar5 = &AddHtInfoIe;
  uVar6 = 1;
  uVar8 = 0xffffffff;
  MakeOutgoingFrame(param_4 + iVar4,&local_58,1,&HtCapIe,1,&local_5c,__n,local_42,1,&AddHtInfoIe,1,
                    pbVar7,uVar3,uVar2,0xffffffff);
  iVar4 = iVar4 + local_58;
  if ((*(byte *)(param_2 + 0x1a) < 0xf) && ((*__src & 2) != 0)) {
    local_4a = *(undefined2 *)(param_1 + 0x7956a4);
    local_50 = *(undefined2 *)(param_1 + 0x79569e);
    local_4c = *(undefined2 *)(param_1 + 0x7956a2);
    local_48 = *(undefined2 *)(param_1 + 0x7956a6);
    local_46 = *(undefined2 *)(param_1 + 0x7956a8);
    local_44 = *(undefined2 *)(param_1 + 0x7956aa);
    local_4e = *(undefined2 *)(param_1 + 0x7956a0);
    local_5b[2] = 0xe;
    local_5b[1] = 0x4a;
    MakeOutgoingFrame(param_4 + iVar4,&local_54,1,local_5b + 1,1,local_5b + 2,0xe,&local_50,
                      0xffffffff,puVar5,uVar6,pbVar7,uVar3,uVar2,uVar8);
    *param_3 = iVar4 + local_54;
    return;
  }
  *param_3 = iVar4;
  return;
}

