// module: mt7915.ko
// function: build_vht_oper_ie @ 0x202f0c
// size: 312 bytes
//

undefined4
build_vht_oper_ie(int param_1,undefined4 param_2,uint param_3,int param_4,undefined4 *param_5)

{
  char cVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  uint uVar4;
  char cVar5;
  int iVar6;
  undefined4 local_25;
  
  if (param_4 != 0) {
    uVar2 = wlan_operate_get_cen_ch_2(param_4);
    __memzero(&local_25,5);
    iVar6 = *(int *)(param_4 + 0x3fe4);
    uVar3 = wlan_config_get_ch_band(param_4);
    if (iVar6 != 0) {
      if (((param_3 < 0xf) || (*(char *)(param_1 + 0x795074) != '\x01')) ||
         (*(char *)(iVar6 + 4) != '\x01')) {
        uVar4 = vht_cent_ch_freq(param_3,param_2,uVar3);
      }
      else {
        uVar4 = vht_cent_ch_freq(*(undefined1 *)(iVar6 + 5),param_2,uVar3);
      }
      cVar1 = (char)uVar4;
      switch(param_2) {
      case 0:
        local_25 = 0;
        break;
      case 1:
        local_25 = CONCAT31((uint3)uVar4 & 0xff,1);
        break;
      case 2:
        if (uVar4 < param_3) {
          cVar5 = cVar1 + '\b';
        }
        else {
          cVar5 = cVar1 + -8;
        }
        local_25._0_2_ = CONCAT11(cVar5,1);
        local_25 = (uint)CONCAT12(cVar1,(undefined2)local_25);
        break;
      case 3:
        local_25 = (uVar4 & 0xff) << 8;
        local_25._0_3_ = CONCAT12(uVar2,(undefined2)local_25);
        local_25 = CONCAT31((uint3)local_25 >> 8,1);
      }
      local_25 = CONCAT13(0xfc,(uint3)local_25);
      *(undefined1 *)(param_5 + 1) = 0xff;
      *param_5 = local_25;
      return 5;
    }
  }
  return 0;
}

