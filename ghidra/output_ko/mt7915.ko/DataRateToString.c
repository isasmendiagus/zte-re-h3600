// module: mt7915.ko
// function: DataRateToString @ 0x156c44
// size: 1172 bytes
//

uint DataRateToString(int param_1,char *param_2,size_t param_3,int param_4,int param_5)

{
  size_t sVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 *puVar5;
  int iVar6;
  byte bVar7;
  char cVar8;
  char cVar9;
  undefined1 uVar10;
  int iVar11;
  char *pcVar12;
  undefined *apuStack_b0 [2];
  undefined4 local_a8;
  int local_a4;
  undefined1 local_a0;
  
  apuStack_b0[0] = &DAT_002efba8;
  apuStack_b0[1] = &DAT_002efbac;
  iVar11 = *(int *)(param_5 + 0x134);
  iVar6 = *(int *)(param_5 + 0x138);
  if (param_4 == 0) {
    bVar7 = *(byte *)(param_5 + 0x13c);
    uVar3 = (uint)*(byte *)(param_5 + 0x148);
    uVar10 = *(undefined1 *)(param_5 + 0x14c);
    cVar9 = *(char *)(param_5 + 0x150);
    uVar4 = *(uint *)(param_5 + 0x144);
    cVar8 = *(char *)(param_5 + 0x154);
    if (bVar7 != 0) {
      if (bVar7 != 1) {
LAB_00156e64:
        if (bVar7 < 4) {
          snprintf((char *)&local_a8,0x80,"MCS%d, ",uVar3);
        }
        else {
          snprintf((char *)&local_a8,0x80,"NSS%d_MCS%d, ",uVar4 & 0xff,uVar3);
        }
        goto LAB_00156d0c;
      }
LAB_00156ef4:
      if (uVar3 == 0xb) {
        bVar7 = 1;
        local_a8 = 0x202c4d36;
        local_a4 = (uint)local_a4._1_3_ << 8;
      }
      else if (uVar3 == 0xf) {
        bVar7 = 1;
        local_a8 = 0x202c4d39;
        local_a4 = (uint)local_a4._1_3_ << 8;
      }
      else if (uVar3 == 10) {
        bVar7 = 1;
        local_a8 = 0x2c4d3231;
        local_a4 = CONCAT22(local_a4._2_2_,0x20);
      }
      else if (uVar3 == 0xe) {
        bVar7 = 1;
        local_a8 = 0x2c4d3831;
        local_a4 = CONCAT22(local_a4._2_2_,0x20);
      }
      else if (uVar3 == 9) {
        bVar7 = 1;
        local_a8 = 0x2c4d3432;
        local_a4 = CONCAT22(local_a4._2_2_,0x20);
      }
      else if (uVar3 == 0xd) {
        bVar7 = 1;
        local_a8 = 0x2c4d3633;
        local_a4 = CONCAT22(local_a4._2_2_,0x20);
      }
      else if (uVar3 == 8) {
        bVar7 = 1;
        local_a8 = 0x2c4d3834;
        local_a4 = CONCAT22(local_a4._2_2_,0x20);
      }
      else if (uVar3 == 0xc) {
        bVar7 = 1;
        local_a8 = 0x2c4d3435;
        local_a4 = CONCAT22(local_a4._2_2_,0x20);
      }
      else {
        bVar7 = 1;
        local_a8 = 0x6f6b6e75;
        local_a4 = 0x202c776e;
        local_a0 = 0;
      }
      goto LAB_00156d0c;
    }
  }
  else {
    bVar7 = *(byte *)(param_5 + 0x158);
    uVar3 = (uint)*(byte *)(param_5 + 0x164);
    uVar10 = *(undefined1 *)(param_5 + 0x168);
    cVar9 = *(char *)(param_5 + 0x16c);
    uVar4 = *(uint *)(param_5 + 0x160);
    cVar8 = *(char *)(param_5 + 0x170);
    iVar11 = iVar6;
    if (bVar7 != 0) {
      if (bVar7 != 1) goto LAB_00156e64;
      if (param_4 == 1) {
        uVar3 = (uint)*(byte *)((int)&tmi_rate_map_ofdm + uVar3);
      }
      goto LAB_00156ef4;
    }
    if (param_4 == 1) {
      if ((*(uint *)(param_1 + 0x795124) & 0x10) == 0) {
        puVar5 = &tmi_rate_map_cck_lp;
      }
      else {
        puVar5 = (undefined4 *)&tmi_rate_map_cck_sp;
      }
      uVar3 = (uint)*(byte *)((int)puVar5 + uVar3);
    }
  }
  if (uVar3 == 0) {
    bVar7 = 0;
    local_a8 = 0x4c204d31;
    local_a4 = 0x202c50;
  }
  else if (uVar3 == 1) {
    bVar7 = 0;
    local_a8 = 0x4c204d32;
    local_a4 = 0x202c50;
  }
  else if (uVar3 == 2) {
    bVar7 = 0;
    local_a8 = 0x4c204d35;
    local_a4 = 0x202c50;
  }
  else {
    if (uVar3 == 3) {
      puVar5 = &_LC60;
    }
    else {
      if (uVar3 == 5) {
        bVar7 = 0;
        local_a8 = 0x53204d32;
        local_a4 = 0x202c50;
        goto LAB_00156d0c;
      }
      if (uVar3 == 6) {
        bVar7 = 0;
        local_a8 = 0x53204d35;
        local_a4 = 0x202c50;
        goto LAB_00156d0c;
      }
      if (uVar3 == 7) {
        puVar5 = &_LC63;
      }
      else {
        puVar5 = &_LC64;
      }
    }
    local_a8 = *puVar5;
    local_a4 = puVar5[1];
    bVar7 = 0;
    local_a0 = (undefined1)puVar5[2];
  }
LAB_00156d0c:
  sVar1 = strlen((char *)&local_a8);
  uVar2 = get_bw_str(uVar10);
  snprintf((char *)((int)&local_a8 + sVar1),0x80 - sVar1,"%s, ",uVar2);
  sVar1 = strlen((char *)&local_a8);
  if (cVar9 == '\0') {
    uVar2 = 0x4c;
  }
  else {
    uVar2 = 0x53;
  }
  snprintf((char *)((int)&local_a8 + sVar1),0x80 - sVar1,"%cGI, ",uVar2);
  sVar1 = strlen((char *)&local_a8);
  uVar2 = get_phymode_str(bVar7);
  pcVar12 = ", STBC";
  if (cVar8 == '\0') {
    pcVar12 = " ";
  }
  snprintf((char *)((int)&local_a8 + sVar1),0x80 - sVar1,"%s%s %s",uVar2,pcVar12,
           apuStack_b0[-((iVar11 << 0x19) >> 0x1f)]);
  uVar4 = snprintf(param_2,param_3,"%s",&local_a8);
  if (param_3 - uVar4 <= uVar4) {
    uVar4 = 0xffffffff;
  }
  return uVar4;
}

