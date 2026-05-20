// module: mt7915.ko
// function: RTMP_GetTxPwr @ 0x13e3e8
// size: 468 bytes
//

int RTMP_GetTxPwr(int param_1,uint param_2,uint param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  undefined1 *puVar3;
  byte bVar4;
  char cVar5;
  uint uVar6;
  uint local_34 [4];
  undefined4 local_24;
  
  uVar1 = wlan_operate_get_cen_ch_1(param_4);
  iVar2 = wlan_operate_get_bw(param_4);
  uVar6 = (param_2 << 0x10) >> 0x1d;
  bVar4 = *(byte *)(param_1 + 0x794cd8);
  if (bVar4 < 0x5b) {
    if (bVar4 < 0x3d) {
      if (bVar4 < 0x1f) {
        if (bVar4 < 0x10) {
          if (bVar4 < 10) {
            cVar5 = '\a';
          }
          else {
            cVar5 = '\n';
          }
        }
        else {
          cVar5 = '\r';
        }
      }
      else {
        cVar5 = '\x10';
      }
    }
    else {
      cVar5 = '\x12';
    }
  }
  else {
    cVar5 = '\x13';
  }
  if (iVar2 == 1) {
    if (uVar1 < 0xf) {
      local_34[0] = *(uint *)("auth_fsm_peer_auth_req_action" + param_1 + 0x18);
      local_34[1] = *(uint *)("auth_fsm_peer_auth_req_action" + param_1 + 0x1c);
      local_34[2] = *(uint *)("auth_fsm_msg_invalid_state" + param_1);
      local_34[3] = *(uint *)("auth_fsm_msg_invalid_state" + param_1 + 4);
      local_24 = *(undefined4 *)("auth_fsm_msg_invalid_state" + param_1 + 8);
    }
    else {
      local_34[0] = *(uint *)("auth_fsm_peer_auth_req_action" + param_1 + 4);
      local_34[1] = *(uint *)("auth_fsm_peer_auth_req_action" + param_1 + 8);
      local_34[2] = *(uint *)("auth_fsm_peer_auth_req_action" + param_1 + 0xc);
      local_34[3] = *(uint *)("auth_fsm_peer_auth_req_action" + param_1 + 0x10);
      local_24 = *(undefined4 *)("auth_fsm_peer_auth_req_action" + param_1 + 0x14);
    }
  }
  else if (param_3 < 0xf) {
    local_34[0] = *(uint *)("auth_fsm_peer_auth_rsp_at_seq2_action" + param_1 + 0x18);
    local_34[1] = *(uint *)("auth_fsm_peer_auth_rsp_at_seq2_action" + param_1 + 0x1c);
    local_34[2] = *(uint *)("auth_fsm_peer_auth_rsp_at_seq2_action" + param_1 + 0x20);
    local_34[3] = *(uint *)("auth_fsm_peer_auth_rsp_at_seq2_action" + param_1 + 0x24);
    local_24 = *(undefined4 *)("auth_fsm_peer_auth_req_action" + param_1);
  }
  else {
    local_34[0] = *(uint *)("auth_fsm_peer_auth_rsp_at_seq2_action" + param_1 + 4);
    local_34[1] = *(uint *)("auth_fsm_peer_auth_rsp_at_seq2_action" + param_1 + 8);
    local_34[2] = *(uint *)("auth_fsm_peer_auth_rsp_at_seq2_action" + param_1 + 0xc);
    local_34[3] = *(uint *)("auth_fsm_peer_auth_rsp_at_seq2_action" + param_1 + 0x10);
    local_24 = *(undefined4 *)("auth_fsm_peer_auth_rsp_at_seq2_action" + param_1 + 0x14);
  }
  switch(uVar6) {
  case 0:
  case 1:
    bVar4 = (byte)((local_34[1] << 0x14) >> 0x1c);
    break;
  case 2:
  case 3:
    if (("SetPartProfileParameters"[param_1 + 0x18] & 0xf0U) == 0x10) {
      bVar4 = (byte)((local_34[2] << 0x14) >> 0x1c);
      break;
    }
    if (("SetPartProfileParameters"[param_1 + 0x18] & 0xf0U) == 0x20) {
      bVar4 = (byte)((local_34[3] << 0x14) >> 0x1c);
      break;
    }
  default:
    bVar4 = 0;
  }
  puVar3 = TxPwrCfg;
  iVar2 = 0;
  if (uVar6 == 3) {
    uVar6 = 2;
  }
  while (((byte)*puVar3 != uVar6 || ((uint)(byte)puVar3[1] != (param_2 & 0x3f)))) {
    puVar3 = puVar3 + 0xc;
    iVar2 = iVar2 + 1;
    if (puVar3 == ChRegion) {
LAB_0013e55c:
      return (int)cVar5;
    }
  }
  iVar2 = iVar2 * 0xc;
  cVar5 = cVar5 - (bVar4 - (char)((*(uint *)(TxPwrCfg + iVar2 + 8) &
                                  local_34[*(ushort *)(TxPwrCfg + iVar2 + 2)]) >>
                                 TxPwrCfg[iVar2 + 4]));
  goto LAB_0013e55c;
}

