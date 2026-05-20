// module: mt7915.ko
// function: mtf_write_tmac_info_beacon @ 0x19eb50
// size: 304 bytes
//

void mtf_write_tmac_info_beacon
               (int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  int iVar1;
  undefined2 local_54;
  undefined1 local_52;
  undefined1 local_51;
  undefined1 local_50;
  undefined1 local_4f;
  undefined1 local_4e;
  undefined1 local_4d;
  undefined1 local_4c;
  undefined1 local_49;
  undefined1 local_47;
  undefined1 local_44;
  undefined1 local_43;
  undefined4 local_40;
  undefined1 local_3c;
  undefined1 local_39;
  undefined1 local_38;
  undefined1 local_36;
  undefined1 local_35;
  undefined1 local_34;
  undefined1 local_33;
  undefined1 local_32;
  uint local_30;
  undefined1 local_2b;
  undefined1 local_28;
  undefined1 local_24;
  undefined1 local_23;
  
  __memzero(&local_54,0x34);
  local_39 = *(undefined1 *)(param_2 + 0xe);
  local_40 = param_5;
  local_33 = 0;
  local_32 = 8;
  local_52 = 0;
  local_4d = 0;
  local_4c = 0;
  local_4f = 0;
  local_49 = 0;
  local_54 = 0;
  local_47 = 0;
  local_44 = 0;
  local_43 = 0;
  local_51 = 1;
  local_4e = 1;
  local_50 = 1;
  local_35 = 1;
  local_3c = 0x18;
  local_38 = HcGetBcnQueueIdx(param_1,param_2);
  local_30 = (uint)*(byte *)(param_2 + 0xe);
  local_2b = *(undefined1 *)(param_2 + 0x29);
  local_24 = *(undefined1 *)(param_2 + 0x93c);
  local_28 = *(char *)(param_2 + 0x988) == '\x02';
  local_34 = 1;
  local_23 = 0;
  if (*(char *)(param_1 + 0x795943) != '\x01') {
    iVar1 = HcGetBandByWdev(param_2);
    if (iVar1 == 0) {
      local_36 = 0x18;
    }
    else {
      iVar1 = HcGetBandByWdev(param_2);
      if (iVar1 == 1) {
        local_36 = 0x19;
      }
    }
  }
  __memzero(param_3,0x20);
  mtf_write_tmac_info_fixed_rate(param_1,param_3,&local_54,param_4);
  return;
}

