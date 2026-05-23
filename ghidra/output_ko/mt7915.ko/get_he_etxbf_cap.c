// module: mt7915.ko
// function: get_he_etxbf_cap @ 0x177918
// size: 384 bytes
//

void get_he_etxbf_cap(int param_1,int param_2)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint *puVar7;
  
  puVar7 = *(uint **)(param_2 + 0x1c);
  iVar3 = wlan_config_get_mcs_nss_caps();
  iVar5 = *(int *)(param_2 + 0x28);
  if (iVar5 == 0) {
    return;
  }
  if (iVar5 == 2) {
    if (*(int *)(param_1 + 0x14) == 1) {
      uVar6 = *puVar7;
      if (1 < *(byte *)(param_2 + 4)) {
        uVar6 = uVar6 | 1;
      }
      *puVar7 = uVar6;
      if (*(byte *)(param_2 + 4) < 2) {
        uVar4 = 0;
      }
      else {
        uVar4 = 4;
      }
      uVar4 = uVar4 | uVar6;
      *puVar7 = uVar4;
    }
    else {
      uVar4 = *puVar7;
    }
    if ((uVar4 & 1) == 0) {
      return;
    }
  }
  else {
    if (iVar5 == 3) {
      uVar6 = *puVar7;
      *(undefined1 *)((int)puVar7 + 5) = 3;
      *(undefined1 *)(puVar7 + 1) = 3;
      *puVar7 = uVar6 | 0x62;
      bVar1 = *(byte *)(param_2 + 4);
      *puVar7 = uVar6 | 0x1e2;
      iVar3 = bVar1 - 1;
      if (1 < iVar3) {
        iVar3 = 2;
      }
      *(char *)(puVar7 + 2) = (char)iVar3;
      return;
    }
    if (iVar5 != 1) {
      if (-1 < DebugLevel) {
        printk("%s: set wrong parameters\n","get_he_etxbf_cap");
        return;
      }
      return;
    }
    if (*(int *)(param_1 + 0x14) == 1) {
      uVar6 = *puVar7;
      if (1 < *(byte *)(param_2 + 4)) {
        uVar6 = uVar6 | 1;
      }
      *puVar7 = uVar6;
      if (*(byte *)(param_2 + 4) < 2) {
        uVar4 = 0;
      }
      else {
        uVar4 = 4;
      }
      uVar4 = uVar4 | uVar6;
    }
    else {
      uVar4 = *puVar7;
    }
    *(undefined1 *)((int)puVar7 + 5) = 3;
    *puVar7 = uVar4 | 0x62;
    *(undefined1 *)(puVar7 + 1) = 3;
    iVar5 = *(byte *)(param_2 + 4) - 1;
    if (1 < iVar5) {
      iVar5 = 2;
    }
    *(char *)(puVar7 + 2) = (char)iVar5;
    if ((uVar4 & 1) == 0) {
      return;
    }
  }
  cVar2 = *(char *)(iVar3 + 3);
  if (cVar2 == '\0') {
    cVar2 = '\x01';
  }
  *(char *)((int)puVar7 + 7) = cVar2;
  cVar2 = wlan_config_get_tx_stream(param_1);
  *puVar7 = *puVar7 | 0x180;
  *(char *)((int)puVar7 + 6) = cVar2 + -1;
  return;
}

