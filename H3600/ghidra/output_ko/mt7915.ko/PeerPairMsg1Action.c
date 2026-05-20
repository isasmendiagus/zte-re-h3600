// module: mt7915.ko
// function: PeerPairMsg1Action @ 0x1203f0
// size: 792 bytes
//

void PeerPairMsg1Action(undefined4 param_1,int param_2,uint *param_3,int param_4)

{
  undefined4 uVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  uint *puVar5;
  uint *puVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  uint *__dest;
  int iVar11;
  undefined4 *__dest_00;
  size_t __n;
  undefined4 *puVar12;
  undefined4 *puVar13;
  size_t sVar14;
  undefined1 auStack_b4 [20];
  undefined4 local_a0 [12];
  undefined4 auStack_70 [4];
  undefined4 auStack_60 [15];
  
  log_time_begin(1,auStack_b4);
  if (2 < DebugLevel) {
    printk("===> %s\n","PeerPairMsg1Action");
  }
  if ((*(byte *)(param_4 + 1) & 3) == 3) {
    iVar8 = 0x1e;
    uVar2 = 0x89;
  }
  else {
    iVar8 = 0x18;
    uVar2 = 0x83;
  }
  if (*(uint *)(param_4 + 0x908) < uVar2) {
    return;
  }
  iVar9 = param_4 + iVar8 + 8;
  __dest_00 = (undefined4 *)((int)param_3 + 0x1ce);
  iVar8 = WpaMessageSanity(param_1,iVar9,(*(uint *)(param_4 + 0x908) - 8) - iVar8,1,param_3,param_2,
                           __dest_00);
  if (iVar8 == 0) {
    return;
  }
  __dest = param_3 + 0xcc;
  puVar5 = param_3 + 0xc9;
  iVar11 = (int)param_3 + 0x32a;
  puVar6 = param_3 + 0xd4;
  memmove(param_3 + 0xe4,(void *)(iVar9 + 9),8);
  memmove(__dest,(void *)(iVar9 + 0x11),0x20);
  GenRandom(param_1,iVar11,puVar6);
  *(undefined1 *)((int)param_3 + 0x3d9) = 1;
  *(undefined1 *)(param_2 + 0x1464) = 0;
  *(undefined1 *)(param_2 + 0x91e) = 0;
  __memzero(param_2 + 0x91f,0x20);
  iVar8 = is_pmkid_cache_in_sec_config(param_3);
  if (iVar8 != 0) {
    memmove((void *)((int)param_3 + 0x18e),(void *)param_3[0x164],0x20);
  }
  iVar8 = (int)param_3 + 0x18e;
  if ((*param_3 & 0x30000) == 0) {
    if ((char)param_3[0xa1] != '\x02') {
      if ((*param_3 & 0x6000) == 0) {
        if ((char)param_3[0xa1] == '\x01') {
          sVar14 = 0x30;
          puVar13 = local_a0;
          WpaDerivePTK_KDF_256(iVar8,__dest,puVar5,puVar6,iVar11,local_a0,0x30);
          puVar10 = local_a0;
          do {
            uVar1 = *puVar10;
            uVar3 = puVar10[1];
            uVar4 = puVar10[2];
            uVar7 = puVar10[3];
            puVar12 = puVar10 + 4;
            puVar10 = puVar10 + 4;
            *__dest_00 = uVar1;
            __dest_00[1] = uVar3;
            __dest_00[2] = uVar4;
            __dest_00[3] = uVar7;
            __dest_00 = __dest_00 + 4;
          } while (puVar12 != auStack_70);
          hex_dump(&_LC175,local_a0,0x30);
        }
        else {
          puVar10 = local_a0;
          sVar14 = 0x40;
          puVar13 = puVar10;
          WpaDerivePTK();
          do {
            uVar1 = *puVar10;
            uVar3 = puVar10[1];
            uVar4 = puVar10[2];
            uVar7 = puVar10[3];
            puVar12 = puVar10 + 4;
            puVar10 = puVar10 + 4;
            *__dest_00 = uVar1;
            __dest_00[1] = uVar3;
            __dest_00[2] = uVar4;
            __dest_00[3] = uVar7;
            __dest_00 = __dest_00 + 4;
          } while (puVar12 != auStack_60);
        }
      }
      else {
        puVar10 = local_a0;
        sVar14 = 0x30;
        puVar13 = puVar10;
        WpaDerivePTK_KDF_256(iVar8,__dest,puVar5,puVar6,iVar11,puVar10,0x30);
        do {
          uVar1 = *puVar10;
          uVar3 = puVar10[1];
          uVar4 = puVar10[2];
          uVar7 = puVar10[3];
          puVar12 = puVar10 + 4;
          puVar10 = puVar10 + 4;
          *__dest_00 = uVar1;
          __dest_00[1] = uVar3;
          __dest_00[2] = uVar4;
          __dest_00[3] = uVar7;
          __dest_00 = __dest_00 + 4;
        } while (puVar12 != auStack_70);
      }
      goto LAB_001205e4;
    }
    __n = 0x30;
  }
  else {
    __n = 0x58;
  }
  puVar13 = local_a0;
  sVar14 = __n;
  WpaDerivePTK_KDF_384(iVar8,__dest,puVar5,puVar6,iVar11,local_a0,__n);
  memcpy(__dest_00,local_a0,__n);
LAB_001205e4:
  *(undefined1 *)(param_3 + 0xe6) = 9;
  uVar2 = (uint)*(byte *)(param_4 + 1) << 0x19;
  *(byte *)((int)param_3 + 0x595) = (byte)(uVar2 >> 0x1f);
  WPABuildPairMsg2(param_1,param_3,param_2,uVar2 >> 0x1f,iVar11,puVar13,sVar14);
  log_time_end(2,"peer_msg1",1,auStack_b4);
  return;
}

