// module: mt7915.ko
// function: mt_engine_stop_tx @ 0x256a04
// size: 440 bytes
//

int mt_engine_stop_tx(undefined4 param_1,uint *param_2,undefined4 *param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  undefined1 local_21;
  
  uVar4 = *param_2;
  uVar2 = param_2[0x305];
  uVar3 = param_2[0x304];
  if (10 < *(byte *)((int)param_2 + 0xc55)) {
    if (((code *)param_3[0x37] != (code *)0x0) &&
       (iVar1 = (*(code *)param_3[0x37])(param_1,param_2[0xaf],0), iVar1 != 0)) {
      return iVar1;
    }
    if (((code *)param_3[0x36] != (code *)0x0) &&
       (iVar1 = (*(code *)param_3[0x36])(param_1,param_2[0xaf],0), iVar1 != 0)) {
      return iVar1;
    }
  }
  uVar5 = (uVar4 << 0x1e) >> 0x1f;
  if (uVar4 == 0x100) {
    uVar5 = 1;
  }
  param_2[0x310] = 0;
  if (uVar5 != 0) {
    *param_2 = uVar4 & 0xfffffffd;
    iVar1 = (*(code *)*param_3)(param_1,1,0,param_4);
    if (iVar1 != 0) {
      return iVar1;
    }
    if (uVar3 != 0 || uVar2 != 0) {
      local_21 = 0;
      iVar1 = net_ad_clean_sta_q(param_1,0xff);
      if (iVar1 != 0) {
        return iVar1;
      }
      iVar1 = net_ad_get_omac_idx(param_1,param_2[0xaf],&local_21);
      if (iVar1 != 0) {
        return iVar1;
      }
      if (*(char *)((int)param_2 + 0x215) != '\0') {
        uVar2 = 0;
        do {
          iVar1 = (*(code *)param_3[5])(param_1,0,param_2[uVar2 + 0x9f],local_21,param_4);
          uVar2 = uVar2 + 1 & 0xff;
          if (iVar1 != 0) {
            return iVar1;
          }
        } while (uVar2 < *(byte *)((int)param_2 + 0x215));
      }
      iVar1 = (*(code *)param_3[0x5c])(param_1,0,param_4,2);
      if (iVar1 != 0) {
        return iVar1;
      }
    }
  }
  if (*(char *)((int)param_2 + 0xc55) == '\n') {
    (*(code *)param_3[0x52])(param_1,param_4,2,1,0,0,0,0,0);
  }
  return 0;
}

