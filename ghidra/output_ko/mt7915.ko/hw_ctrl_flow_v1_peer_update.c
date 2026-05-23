// module: mt7915.ko
// function: hw_ctrl_flow_v1_peer_update @ 0xafedc
// size: 260 bytes
//

undefined4
hw_ctrl_flow_v1_peer_update(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  int *piVar5;
  
  uVar2 = param_1[0xb];
  uVar4 = *(undefined4 *)(*param_1 + 8);
  if ((uVar2 & 8) != 0) {
    param_3 = 0;
    if (param_1[0x83] != 0) {
      AsicRaParamStaRecUpdate(uVar4,*(undefined2 *)((int)param_1 + 0x22),param_1[0x83],8);
      if (param_1[0x83] == 0) {
        return 0;
      }
      os_free_mem();
      return 0;
    }
  }
  piVar5 = param_1 + 8;
  uVar1 = uVar2;
  if ((uVar2 & 4) != 0) {
    param_1[0xb] = 4;
    AsicStaRecUpdate(uVar4,piVar5,param_3,4,param_4);
    param_1[0xb] = uVar2 & 0xfffffffb;
    uVar1 = uVar2 & 0xfffffffb;
  }
  uVar3 = uVar1;
  if ((uVar2 & 2) != 0) {
    param_1[0xb] = 2;
    AsicStaRecUpdate(uVar4,piVar5);
    param_1[0xb] = uVar1 & 0xfffffffd;
    uVar3 = uVar1 & 0xfffffffd;
  }
  if ((uVar1 & 0x1000) != 0) {
    AsicAddRemoveKeyTab(uVar4,param_1 + 0xd);
    uVar3 = param_1[0xb] & 0xffffefff;
    param_1[0xb] = uVar3;
  }
  if (uVar3 == 0) {
    return 0;
  }
  AsicStaRecUpdate(uVar4,piVar5);
  wifi_sys_update_starec_info(uVar4,piVar5);
  return 0;
}

