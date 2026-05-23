// module: mt7915.ko
// function: hw_ctrl_flow_v2_peer_update @ 0xb052c
// size: 220 bytes
//

undefined4
hw_ctrl_flow_v2_peer_update(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  int *piVar4;
  
  uVar1 = param_1[0xb];
  uVar3 = *(undefined4 *)(*param_1 + 8);
  if ((uVar1 & 8) != 0) {
    param_3 = 0;
    if (param_1[0x83] != 0) {
      AsicRaParamStaRecUpdate(uVar3,*(undefined2 *)((int)param_1 + 0x22),param_1[0x83],8);
      if (param_1[0x83] == 0) {
        return 0;
      }
      os_free_mem();
      return 0;
    }
  }
  piVar4 = param_1 + 8;
  uVar2 = uVar1;
  if ((uVar1 & 4) != 0) {
    param_1[0xb] = 4;
    AsicStaRecUpdate(uVar3,piVar4,param_3,4,param_4);
    param_1[0xb] = uVar1 & 0xfffffffb;
    uVar2 = uVar1 & 0xfffffffb;
  }
  if ((uVar1 & 2) != 0) {
    uVar2 = uVar2 & 0xfffffffd;
    param_1[0xb] = 2;
    AsicStaRecUpdate(uVar3,piVar4);
    param_1[0xb] = uVar2;
  }
  if (uVar2 == 0) {
    return 0;
  }
  AsicStaRecUpdate(uVar3,piVar4);
  wifi_sys_update_starec_info(uVar3,piVar4);
  return 0;
}

