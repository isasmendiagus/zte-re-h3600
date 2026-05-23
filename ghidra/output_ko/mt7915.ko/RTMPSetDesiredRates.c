// module: mt7915.ko
// function: RTMPSetDesiredRates @ 0xdb6e0
// size: 1088 bytes
//

void RTMPSetDesiredRates(undefined4 param_1,int param_2,undefined *param_3)

{
  int iVar1;
  undefined4 local_20;
  undefined4 local_1c;
  
  __memzero(&local_20,8);
  if (*(short *)(param_2 + 0x18) == 1) {
    if (param_3 != (undefined *)0x112a880) {
      if ((int)param_3 < 0x112a881) {
        if (param_3 == (undefined *)0x895440) {
          local_20 = CONCAT31(local_20._1_3_,0x12);
          *(byte *)(param_2 + 0x8ae) = *(byte *)(param_2 + 0x8ae) & 0x80 | 1;
          goto LAB_000db76c;
        }
        if (param_3 == (undefined *)0xb71b00) {
LAB_000db918:
          local_20 = CONCAT31(local_20._1_3_,0x18);
          *(byte *)(param_2 + 0x8ae) = *(byte *)(param_2 + 0x8ae) & 0x80 | 2;
          goto LAB_000db76c;
        }
        if (param_3 == (undefined *)0x5b8d80) {
LAB_000db9c8:
          local_20 = CONCAT31(local_20._1_3_,0xc);
          *(byte *)(param_2 + 0x8ae) = *(byte *)(param_2 + 0x8ae) & 0x80;
          goto LAB_000db76c;
        }
      }
      else {
        if (param_3 == (undefined *)0x2255100) {
LAB_000db814:
          local_20 = CONCAT31(local_20._1_3_,0x48);
          *(byte *)(param_2 + 0x8ae) = *(byte *)(param_2 + 0x8ae) & 0x80 | 5;
          goto LAB_000db76c;
        }
        if ((int)param_3 < 0x2255101) {
          if (param_3 == (undefined *)0x16e3600) goto LAB_000db9f0;
        }
        else {
          if (param_3 == (undefined *)0x2dc6c00) {
LAB_000dba0c:
            local_20 = CONCAT31(local_20._1_3_,0x60);
            *(byte *)(param_2 + 0x8ae) = *(byte *)(param_2 + 0x8ae) & 0x80 | 6;
            goto LAB_000db76c;
          }
          if (param_3 == (undefined *)0x337f980) {
LAB_000db754:
            local_20 = CONCAT31(local_20._1_3_,0x6c);
            *(byte *)(param_2 + 0x8ae) = *(byte *)(param_2 + 0x8ae) & 0x80 | 7;
            goto LAB_000db76c;
          }
        }
      }
      *(byte *)(param_2 + 0x8ae) = *(byte *)(param_2 + 0x8ae) & 0x80 | 0x21;
      local_20 = 0x3048606c;
      local_1c = 0xc121824;
      goto LAB_000db76c;
    }
LAB_000db8fc:
    local_20 = CONCAT31(local_20._1_3_,0x24);
    *(byte *)(param_2 + 0x8ae) = *(byte *)(param_2 + 0x8ae) & 0x80 | 3;
  }
  else {
    if (param_3 == (undefined *)0xa7d8c0) {
      local_20 = CONCAT31(local_20._1_3_,0x16);
      *(byte *)(param_2 + 0x8ae) = *(byte *)(param_2 + 0x8ae) & 0x80 | 3;
      goto LAB_000db76c;
    }
    if ((int)param_3 < 0xa7d8c1) {
      if (param_3 == &DAT_004c4b40) {
        local_20 = CONCAT31(local_20._1_3_,0xb);
        *(byte *)(param_2 + 0x8ae) = *(byte *)(param_2 + 0x8ae) & 0x80 | 2;
        goto LAB_000db76c;
      }
      if ((int)param_3 < 0x4c4b41) {
        if (param_3 == (undefined *)0xf4240) {
          local_20 = CONCAT31(local_20._1_3_,2);
          *(byte *)(param_2 + 0x8ae) = *(byte *)(param_2 + 0x8ae) & 0x80;
          goto LAB_000db76c;
        }
        if (param_3 == (undefined *)0x1e8480) {
          local_20 = CONCAT31(local_20._1_3_,4);
          *(byte *)(param_2 + 0x8ae) = *(byte *)(param_2 + 0x8ae) & 0x80 | 1;
          goto LAB_000db76c;
        }
      }
      else {
        if (param_3 == (undefined *)0x5b8d80) goto LAB_000db9c8;
        if (param_3 == (undefined *)0x895440) {
          local_20 = CONCAT31(local_20._1_3_,0x12);
          *(byte *)(param_2 + 0x8ae) = *(byte *)(param_2 + 0x8ae) & 0x80 | 1;
          goto LAB_000db76c;
        }
      }
    }
    else {
      if (param_3 == (undefined *)0x16e3600) {
LAB_000db9f0:
        local_20 = CONCAT31(local_20._1_3_,0x30);
        *(byte *)(param_2 + 0x8ae) = *(byte *)(param_2 + 0x8ae) & 0x80 | 4;
        goto LAB_000db76c;
      }
      if ((int)param_3 < 0x16e3601) {
        if (param_3 == (undefined *)0xb71b00) goto LAB_000db918;
        if (param_3 == (undefined *)0x112a880) goto LAB_000db8fc;
      }
      else {
        if (param_3 == (undefined *)0x2dc6c00) goto LAB_000dba0c;
        if (param_3 == (undefined *)0x337f980) goto LAB_000db754;
        if (param_3 == (undefined *)0x2255100) goto LAB_000db814;
      }
    }
    if (*(short *)(param_2 + 0x18) == 2) {
      local_20 = 0x2040b16;
    }
    else {
      local_20 = 0x3048606c;
      local_1c = 0x2040b16;
    }
    *(byte *)(param_2 + 0x8ae) = *(byte *)(param_2 + 0x8ae) & 0x80 | 0x21;
  }
LAB_000db76c:
  __memzero(param_2 + 0xaf8,0xc);
  iVar1 = DebugLevel;
  *(undefined4 *)(param_2 + 0xaf8) = local_20;
  *(undefined4 *)(param_2 + 0xafc) = local_1c;
  if (2 < iVar1) {
    printk(" RTMPSetDesiredRates (%02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x)\n",
           *(undefined1 *)(param_2 + 0xaf8),*(undefined1 *)(param_2 + 0xaf9),
           *(undefined1 *)(param_2 + 0xafa),*(undefined1 *)(param_2 + 0xafb),
           *(undefined1 *)(param_2 + 0xafc),*(undefined1 *)(param_2 + 0xafd),
           *(undefined1 *)(param_2 + 0xafe),*(undefined1 *)(param_2 + 0xaff));
  }
  MlmeUpdateTxRates(param_1,0,0);
  return;
}

