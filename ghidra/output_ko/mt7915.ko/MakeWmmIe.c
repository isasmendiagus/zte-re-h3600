// module: mt7915.ko
// function: MakeWmmIe @ 0xb3e68
// size: 332 bytes
//

void MakeWmmIe(undefined4 param_1,int param_2,int *param_3,int param_4)

{
  int iVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  undefined2 *puVar5;
  byte *pbVar6;
  undefined1 *puVar7;
  int local_44;
  undefined4 local_3e;
  undefined1 local_3a;
  undefined1 local_39;
  undefined2 local_38;
  undefined1 local_36;
  undefined1 local_35;
  undefined1 local_34;
  undefined1 local_33;
  undefined2 local_32;
  char local_30 [20];
  
  iVar4 = *(int *)(param_2 + 4);
  local_44 = 0;
  local_32 = 0;
  local_30[0] = '\0';
  local_30[1] = '\0';
  local_30[2] = '\0';
  local_30[3] = '\0';
  local_30[4] = '\0';
  local_30[5] = '\0';
  local_30[6] = '\0';
  local_30[7] = '\0';
  local_30[8] = '\0';
  local_30[9] = '\0';
  local_30[10] = '\0';
  local_30[0xb] = '\0';
  local_30[0xc] = '\0';
  local_30[0xd] = '\0';
  local_30[0xe] = '\0';
  local_30[0xf] = '\0';
  iVar3 = *param_3;
  local_3a = 0xdd;
  local_39 = 0x18;
  local_38 = 0x5000;
  local_36 = 0xf2;
  local_35 = 2;
  local_34 = 1;
  local_33 = 1;
  iVar1 = wlan_config_get_ht_edca(param_2);
  if (iVar1 != 0) {
    if (*(char *)(iVar4 + 0x8d8) == '\0') {
      bVar2 = 0;
    }
    else {
      bVar2 = 0x80;
    }
    local_32 = CONCAT11(local_32._1_1_,bVar2 | *(byte *)(iVar1 + 6) & 0xf);
    iVar4 = 0;
    local_3e = *(undefined4 *)(iVar1 + 7);
    puVar5 = (undefined2 *)(iVar1 + 0x14);
    pbVar6 = (byte *)&local_3e;
    puVar7 = &local_3a;
    do {
      puVar7[10] = (*pbVar6 & 0xf) + *(char *)(iVar1 + 0x1c) * '\x10' + (char)iVar4 * ' ';
      iVar4 = iVar4 + 1;
      puVar7[0xb] = (*(byte *)(iVar1 + 0xb) & 0xf) + *(char *)(iVar1 + 0xf) * '\x10';
      puVar7[0xc] = (char)*puVar5;
      puVar7[0xd] = (char)((ushort)*puVar5 >> 8);
      iVar1 = iVar1 + 1;
      puVar5 = puVar5 + 1;
      pbVar6 = pbVar6 + 1;
      puVar7 = puVar7 + 4;
    } while (iVar4 != 4);
    MakeOutgoingFrame(param_4 + iVar3,&local_44,0x1a,&local_3a,0xffffffff);
    iVar3 = iVar3 + local_44;
  }
  *param_3 = iVar3;
  return;
}

