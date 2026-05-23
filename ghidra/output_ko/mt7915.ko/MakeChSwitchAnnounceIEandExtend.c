// module: mt7915.ko
// function: MakeChSwitchAnnounceIEandExtend @ 0xb36d4
// size: 620 bytes
//

void MakeChSwitchAnnounceIEandExtend(int param_1,int param_2,int *param_3,int param_4)

{
  ushort uVar1;
  undefined1 uVar2;
  char cVar3;
  undefined4 uVar4;
  size_t __n;
  undefined4 uVar5;
  char *pcVar6;
  int iVar7;
  int iVar8;
  undefined1 *puVar9;
  undefined1 *puVar10;
  undefined1 local_2e;
  undefined1 auStack_2d [3];
  undefined2 local_2a;
  
  iVar7 = *param_3;
  if (param_2 != 0) {
    wlan_operate_get_ht_bw(param_2);
    pcVar6 = *(char **)(param_2 + 0x3fe4);
    if (pcVar6 != (char *)0x0) {
      iVar8 = param_4 + iVar7;
      *(short *)(param_2 + 0x982) = (short)iVar7;
      *(undefined1 *)(param_4 + iVar7) = 0x25;
      *(undefined1 *)(iVar8 + 1) = 3;
      *(undefined1 *)(iVar8 + 2) = 1;
      puVar10 = (undefined1 *)(iVar8 + 5);
      *(undefined1 *)(iVar8 + 3) = *(undefined1 *)(param_2 + 0x1a);
      *(char *)(iVar8 + 4) = (pcVar6[1] + -1) - *pcVar6;
      if (*(char *)(param_1 + 0x795948) == '\0') {
        iVar7 = iVar7 + 5;
      }
      else {
        build_ext_channel_switch_ie
                  (param_1,&local_2e,*(undefined1 *)(param_2 + 0x1a),*(undefined2 *)(param_2 + 0x18)
                   ,param_2);
        iVar7 = iVar7 + 0xb;
        *(int *)(iVar8 + 5) = _local_2e;
        *(undefined2 *)(iVar8 + 9) = local_2a;
        puVar10 = (undefined1 *)(iVar8 + 0xb);
      }
      uVar1 = *(ushort *)(param_2 + 0x18);
      iVar8 = wlan_operate_get_ht_bw(param_2);
      if ((uVar1 & 0x20) != 0) {
        uVar4 = wlan_config_get_ch_band(param_2);
        puVar9 = puVar10 + 2;
        *puVar10 = 0xc4;
        if (iVar8 == 1) {
          puVar10[3] = 3;
          puVar10[2] = 0xc2;
          __memzero(&local_2e,3);
          uVar5 = wlan_config_get_vht_bw(param_2);
          switch(uVar5) {
          case 0:
            _local_2e = (uint)(uint3)auStack_2d << 8;
            break;
          case 1:
            _local_2e = CONCAT31(auStack_2d,1);
            uVar2 = vht_cent_ch_freq(*(undefined1 *)(param_2 + 0x1a),1,uVar4);
            uVar4 = _local_2e;
            _local_2e = CONCAT11(uVar2,local_2e);
            auStack_2d[2] = SUB41(uVar4,3);
            _local_2e = (uint3)_local_2e;
            break;
          case 2:
            _local_2e = CONCAT31(auStack_2d,1);
            cVar3 = vht_cent_ch_freq(*(undefined1 *)(param_2 + 0x1a),2,uVar4);
            _local_2e = CONCAT11(cVar3 + -8,local_2e);
            uVar2 = vht_cent_ch_freq(*(undefined1 *)(param_2 + 0x1a),2,uVar4);
            _local_2e = CONCAT12(uVar2,_local_2e);
            break;
          case 3:
            _local_2e = CONCAT31(auStack_2d,1);
            uVar2 = vht_cent_ch_freq(*(undefined1 *)(param_2 + 0x1a),3,uVar4);
            _local_2e = CONCAT11(uVar2,local_2e);
            uVar2 = wlan_operate_get_cen_ch_2(param_2);
            _local_2e = CONCAT12(uVar2,_local_2e);
          }
          puVar9 = puVar10 + 7;
          iVar8 = 7;
          cVar3 = '\x05';
          *(ushort *)(puVar10 + 4) = _local_2e;
          puVar10[6] = auStack_2d[1];
        }
        else {
          iVar8 = 2;
          cVar3 = '\0';
        }
        *puVar9 = 0xc3;
        __memzero(&local_2e,5);
        __n = build_vht_txpwr_envelope(param_1,param_2,&local_2e);
        puVar9[1] = (char)__n;
        memcpy(puVar9 + 2,&local_2e,__n);
        iVar7 = iVar7 + __n + 2 + iVar8;
        puVar10[1] = cVar3 + (char)(__n + 2);
      }
      *param_3 = iVar7;
    }
  }
  return;
}

