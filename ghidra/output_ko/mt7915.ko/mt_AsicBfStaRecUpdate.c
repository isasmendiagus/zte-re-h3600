// module: mt7915.ko
// function: mt_AsicBfStaRecUpdate @ 0x85540
// size: 3956 bytes
//

undefined4 mt_AsicBfStaRecUpdate(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined1 uVar4;
  byte bVar5;
  char *pcVar6;
  uint uVar7;
  undefined1 uVar8;
  byte bVar9;
  char cVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  char cVar14;
  byte bVar15;
  char local_40;
  undefined1 auStack_38 [2];
  byte local_36;
  undefined1 auStack_34 [6];
  byte local_2e;
  byte local_2d;
  
  bVar9 = (byte)"SetPartProfileParameters"[param_1 + 0x18] >> 4;
  if (*(char *)(param_1 + 0x79504d) != '\0') {
    iVar3 = HcGetBandByWdev(*(undefined4 *)(param_4 * 0x14c0 + param_1 + 0xa1d28));
    if (iVar3 == 0) {
      bVar9 = "SetPartProfileParameters"[param_1 + 0x1a];
    }
    else {
      bVar9 = "rtmp_read_vow_parms_from_file"[param_1];
    }
  }
  uVar12 = (uint)bVar9;
  switch(*(byte *)(param_4 * 0x14c0 + param_1 + 0xa1ddf) >> 5) {
  case 0:
  case 1:
    iVar3 = param_4 * 0x14c0 + param_1;
    *(undefined1 *)(iVar3 + 0xa295d) = 0;
    *(undefined1 *)(iVar3 + 0xa2962) = 1;
    *(undefined1 *)(iVar3 + 0xa2963) = 0;
    *(byte *)(iVar3 + 0xa2964) = bVar9 - 1;
    *(undefined1 *)(iVar3 + 0xa2974) = 0x18;
    *(byte *)(iVar3 + 0xa2965) = (byte)(((uint)*(ushort *)(iVar3 + 0xa1dde) << 0x17) >> 0x1e);
    *(undefined1 *)(iVar3 + 0xa2976) = 0;
    *(byte *)(iVar3 + 0xa2977) = bVar9 - 1;
    *(byte *)(iVar3 + 0xa2975) = (byte)(((uint)*(ushort *)(iVar3 + 0xa1dde) << 0x17) >> 0x1e);
    uVar1 = *(uint *)(param_1 + 0xa787b8);
    goto LAB_00085ac0;
  case 2:
  case 3:
    iVar13 = param_4 * 0x14c0 + param_1;
    iVar3 = wlan_config_get_etxbf(*(undefined4 *)(iVar13 + 0xa1d28));
    if ((iVar3 == 1) ||
       (iVar3 = wlan_config_get_etxbf(*(undefined4 *)(iVar13 + 0xa1d28)), iVar3 == 2)) {
      iVar3 = mt_WrapClientSupportsETxBF(param_1,param_1 + param_4 * 0x14c0 + 0xa29d9);
      if (iVar3 != 0) {
        iVar13 = param_1 + param_4 * 0x14c0;
        *(undefined1 *)(iVar13 + 0xa295d) = 1;
        iVar3 = wlan_config_get_itxbf(*(undefined4 *)(iVar13 + 0xa1d28));
        if (iVar3 == 0) {
          *(undefined1 *)(iVar13 + 0xa2962) = 2;
          *(byte *)(iVar13 + 0xa2965) =
               (byte)(((uint)*(ushort *)(iVar13 + 0xa1dde) << 0x17) >> 0x1e);
        }
        else {
          *(byte *)(iVar13 + 0xa295d) = *(byte *)(iVar13 + 0xa295d) | 2;
          *(undefined1 *)(iVar13 + 0xa2962) = 2;
          *(byte *)(iVar13 + 0xa2965) =
               (byte)(((uint)*(ushort *)(iVar13 + 0xa1dde) << 0x17) >> 0x1e);
        }
        iVar13 = param_4 * 0x14c0 + param_1;
        *(undefined1 *)(iVar13 + 0xa295c) = 0;
        iVar3 = wlan_operate_get_ht_cap(*(undefined4 *)(iVar13 + 0xa1d28));
        uVar7 = uVar12 - 1 & 0xff;
        uVar1 = (*(byte *)(iVar13 + 0xa29dc) & 1) << 1 | (uint)(*(byte *)(iVar13 + 0xa29db) >> 7);
        uVar2 = ((uint)*(byte *)(iVar3 + 0x18) << 0x1b) >> 0x1e;
        if (uVar2 <= uVar1) {
          uVar1 = uVar2;
        }
        if (uVar7 <= uVar1) {
          uVar1 = uVar7;
        }
        *(char *)(iVar13 + 0xa2964) = (char)uVar1;
        *(char *)(iVar13 + 0xa2960) = (char)(uVar1 << 3);
        if (*(char *)(iVar13 + 0xa29c9) == '\0') {
          bVar9 = 0;
          if (*(char *)(iVar13 + 0xa29c8) != '\0') {
            bVar9 = 1;
          }
        }
        else {
          bVar9 = 2;
        }
        iVar3 = param_4 * 0x14c0 + param_1;
        if (*(char *)(iVar3 + 0xa29ca) != '\0') {
          bVar9 = 3;
        }
        if (*(byte *)(iVar3 + 0xa2964) <= bVar9) {
          bVar9 = *(byte *)(iVar3 + 0xa2964);
        }
        *(byte *)(iVar3 + 0xa2963) = bVar9;
        *(byte *)(iVar3 + 0xa2976) = bVar9;
        *(char *)(iVar3 + 0xa2977) = (char)(uVar12 - 1);
        *(undefined1 *)(iVar3 + 0xa2974) = 0x18;
        *(byte *)(iVar3 + 0xa2975) = (byte)(((uint)*(ushort *)(iVar3 + 0xa1dde) << 0x17) >> 0x1e);
        uVar1 = *(uint *)(param_1 + 0xa787b8);
        goto LAB_00085ac0;
      }
    }
    iVar13 = param_4 * 0x14c0 + param_1;
    *(undefined1 *)(iVar13 + 0xa295d) = 0;
    iVar3 = wlan_config_get_itxbf(*(undefined4 *)(iVar13 + 0xa1d28));
    if (iVar3 == 0) {
      *(undefined1 *)(iVar13 + 0xa2962) = 2;
      *(byte *)(iVar13 + 0xa2965) = (byte)(((uint)*(ushort *)(iVar13 + 0xa1dde) << 0x17) >> 0x1e);
    }
    else {
      *(byte *)(iVar13 + 0xa295d) = *(byte *)(iVar13 + 0xa295d) | 2;
      *(undefined1 *)(iVar13 + 0xa2962) = 2;
      *(byte *)(iVar13 + 0xa2965) = (byte)(((uint)*(ushort *)(iVar13 + 0xa1dde) << 0x17) >> 0x1e);
    }
    iVar3 = param_4 * 0x14c0 + param_1;
    *(byte *)(iVar3 + 0xa2964) = bVar9 - 1;
    *(byte *)(iVar3 + 0xa2977) = bVar9 - 1;
    *(byte *)(iVar3 + 0xa2975) = (byte)(((uint)*(ushort *)(iVar3 + 0xa1dde) << 0x17) >> 0x1e);
    uVar1 = (uint)*(byte *)(iVar3 + 0xa29d3);
    if (*(char *)(iVar3 + 0xa29c9) == '\0') {
      uVar2 = 0;
      if (*(char *)(iVar3 + 0xa29c8) != '\0') {
        uVar2 = 1;
      }
    }
    else {
      uVar2 = 2;
    }
    iVar3 = param_4 * 0x14c0 + param_1;
    if (*(char *)(param_4 * 0x14c0 + param_1 + 0xa29ca) != '\0') {
      uVar2 = 3;
    }
    if (((uVar1 << 0x1e) >> 0x1f & uVar1) != 0) {
      uVar2 = (uVar1 << 0x1c) >> 0x1e;
    }
    *(byte *)(iVar3 + 0xa2976) = (byte)uVar2;
    bVar9 = (byte)uVar2;
    if (*(byte *)(iVar3 + 0xa2964) <= uVar2) {
      bVar9 = *(byte *)(iVar3 + 0xa2964);
    }
    *(byte *)(iVar3 + 0xa2963) = bVar9;
    if ((((uint)*(ushort *)(iVar3 + 0xa1dde) << 0x17) >> 0x1e < 2) &&
       (*(char *)(iVar3 + 0xa2963) == '\0')) {
      *(undefined1 *)(iVar3 + 0xa2974) = 0x48;
      uVar1 = *(uint *)(param_1 + 0xa787b8);
    }
    else {
      *(undefined1 *)(param_4 * 0x14c0 + param_1 + 0xa2974) = 0x18;
      uVar1 = *(uint *)(param_1 + 0xa787b8);
    }
    goto LAB_00085ac0;
  case 4:
    iVar13 = param_4 * 0x14c0 + param_1;
    iVar3 = wlan_config_get_etxbf(*(undefined4 *)(iVar13 + 0xa1d28));
    if ((iVar3 == 1) ||
       (iVar3 = wlan_config_get_etxbf(*(undefined4 *)(iVar13 + 0xa1d28)), iVar3 == 2)) {
      iVar3 = mt_WrapClientSupportsVhtETxBF(param_1,param_1 + param_4 * 0x14c0 + 0xa2a34);
      if (iVar3 != 0) {
        iVar13 = param_1 + param_4 * 0x14c0;
        *(undefined1 *)(iVar13 + 0xa295d) = 1;
        iVar3 = wlan_config_get_itxbf(*(undefined4 *)(iVar13 + 0xa1d28));
        if (iVar3 == 0) {
          *(undefined1 *)(iVar13 + 0xa295c) = 0;
          *(undefined1 *)(iVar13 + 0xa2962) = 4;
          *(byte *)(iVar13 + 0xa2965) =
               (byte)(((uint)*(ushort *)(iVar13 + 0xa1dde) << 0x17) >> 0x1e);
        }
        else {
          *(byte *)(iVar13 + 0xa295d) = *(byte *)(iVar13 + 0xa295d) | 2;
          *(undefined1 *)(iVar13 + 0xa295c) = 0;
          *(undefined1 *)(iVar13 + 0xa2962) = 4;
          *(byte *)(iVar13 + 0xa2965) =
               (byte)(((uint)*(ushort *)(iVar13 + 0xa1dde) << 0x17) >> 0x1e);
        }
        iVar3 = param_4 * 0x14c0 + param_1;
        mt_WrapSetVHTETxBFCap(param_1,*(undefined4 *)(iVar3 + 0xa1d28),auStack_38);
        *(undefined1 *)(iVar3 + 0xa295e) = 1;
        *(undefined1 *)(iVar3 + 0xa2960) = 0;
        *(undefined1 *)(iVar3 + 0xa295f) = 0x49;
        uVar4 = (undefined1)(uVar12 - 1);
        *(undefined1 *)(iVar3 + 0xa2961) = 0x49;
        uVar1 = (uint)(*(byte *)(iVar3 + 0xa2a35) >> 5);
        if ((local_36 & 7) <= uVar1) {
          uVar1 = local_36 & 7;
        }
        uVar8 = (char)uVar1;
        if ((uVar12 - 1 & 0xff) <= uVar1) {
          uVar8 = uVar4;
        }
        *(undefined1 *)(iVar3 + 0xa2964) = uVar8;
        bVar9 = *(byte *)(iVar3 + 0xa2a38);
        if ((bVar9 & 0x30) == 0x30) {
          bVar15 = (bVar9 & 0xc) != 0xc;
        }
        else {
          bVar15 = 2;
        }
        iVar3 = param_4 * 0x14c0 + param_1;
        if ((bVar9 & 0xc0) != 0xc0) {
          bVar15 = 3;
        }
        if (*(byte *)(iVar3 + 0xa2964) <= bVar15) {
          bVar15 = *(byte *)(iVar3 + 0xa2964);
        }
        *(byte *)(iVar3 + 0xa2963) = bVar15;
        *(byte *)(iVar3 + 0xa2976) = bVar15;
        *(undefined1 *)(iVar3 + 0xa2977) = uVar4;
        *(undefined1 *)(iVar3 + 0xa2974) = 0x18;
        *(byte *)(iVar3 + 0xa2975) = (byte)(((uint)*(ushort *)(iVar3 + 0xa1dde) << 0x17) >> 0x1e);
        if ((*(ushort *)(iVar3 + 0xa1dde) & 0x180) == 0x180) {
          *(undefined1 *)(iVar3 + 0xa2964) = 1;
          uVar1 = *(uint *)(param_1 + 0xa787b8);
          goto LAB_00085ac0;
        }
        break;
      }
    }
    iVar13 = param_4 * 0x14c0 + param_1;
    *(undefined1 *)(iVar13 + 0xa295d) = 0;
    iVar3 = wlan_config_get_itxbf(*(undefined4 *)(iVar13 + 0xa1d28));
    if (iVar3 == 0) {
      *(undefined1 *)(iVar13 + 0xa295c) = 0;
      *(undefined1 *)(iVar13 + 0xa2962) = 4;
      *(byte *)(iVar13 + 0xa2965) = (byte)(((uint)*(ushort *)(iVar13 + 0xa1dde) << 0x17) >> 0x1e);
    }
    else {
      *(undefined1 *)(iVar13 + 0xa295c) = 0;
      *(byte *)(iVar13 + 0xa295d) = *(byte *)(iVar13 + 0xa295d) | 2;
      *(undefined1 *)(iVar13 + 0xa2962) = 4;
      *(byte *)(iVar13 + 0xa2965) = (byte)(((uint)*(ushort *)(iVar13 + 0xa1dde) << 0x17) >> 0x1e);
    }
    iVar3 = param_4 * 0x14c0 + param_1;
    *(byte *)(iVar3 + 0xa2964) = bVar9 - 1;
    *(byte *)(iVar3 + 0xa2977) = bVar9 - 1;
    *(byte *)(iVar3 + 0xa2975) = (byte)(((uint)*(ushort *)(iVar3 + 0xa1dde) << 0x17) >> 0x1e);
    bVar9 = *(byte *)(iVar3 + 0xa2a3c);
    if ((bVar9 & 0x30) == 0x30) {
      bVar15 = (bVar9 & 0xc) != 0xc;
    }
    else {
      bVar15 = 2;
    }
    iVar3 = param_4 * 0x14c0 + param_1;
    if ((bVar9 & 0xc0) != 0xc0) {
      bVar15 = 3;
    }
    *(byte *)(iVar3 + 0xa2976) = bVar15;
    if (*(byte *)(iVar3 + 0xa2964) <= bVar15) {
      bVar15 = *(byte *)(iVar3 + 0xa2964);
    }
    *(byte *)(iVar3 + 0xa2963) = bVar15;
    if ((((uint)*(ushort *)(iVar3 + 0xa1dde) << 0x17) >> 0x1e < 2) &&
       (*(char *)(iVar3 + 0xa2963) == '\0')) {
      *(undefined1 *)(iVar3 + 0xa2974) = 0x48;
    }
    else {
      *(undefined1 *)(param_4 * 0x14c0 + param_1 + 0xa2974) = 0x18;
    }
    iVar3 = param_4 * 0x14c0 + param_1;
    if ((*(ushort *)(iVar3 + 0xa1dde) & 0x180) == 0x180) {
      *(undefined1 *)(iVar3 + 0xa2977) = 1;
      uVar1 = *(uint *)(param_1 + 0xa787b8);
      goto LAB_00085ac0;
    }
    break;
  case 5:
    __memzero(auStack_34);
    iVar13 = param_4 * 0x14c0 + param_1;
    mt_wrap_get_he_bf_cap(*(undefined4 *)(iVar13 + 0xa1d28),auStack_34);
    iVar3 = wlan_config_get_mcs_nss_caps(*(undefined4 *)(iVar13 + 0xa1d28));
    uVar1 = wlan_config_get_he_bw(*(undefined4 *)(iVar13 + 0xa1d28));
    uVar2 = wlan_config_get_tx_stream(*(undefined4 *)(iVar13 + 0xa1d28));
    if (2 < uVar1) {
      uVar11 = *(byte *)(iVar3 + 3) + 1 & 0xff;
      uVar7 = uVar2;
      if (uVar11 <= uVar2) {
        uVar7 = uVar11;
      }
      local_40 = (char)uVar7;
    }
    iVar13 = param_4 * 0x14c0 + param_1;
    iVar3 = wlan_config_get_etxbf(*(undefined4 *)(iVar13 + 0xa1d28));
    if ((iVar3 == 1) ||
       (iVar3 = wlan_config_get_etxbf(*(undefined4 *)(iVar13 + 0xa1d28)), iVar3 == 2)) {
      iVar3 = param_1 + param_4 * 0x14c0;
      if ((*(uint *)(iVar3 + 0xa1da8) & 2) != 0) {
        *(undefined1 *)(iVar3 + 0xa295c) = 0;
        *(undefined1 *)(iVar3 + 0xa295d) = 1;
        *(undefined1 *)(iVar3 + 0xa2962) = 8;
        local_40 = (char)uVar2 + -1;
        *(byte *)(iVar3 + 0xa2965) = (byte)(((uint)*(ushort *)(iVar3 + 0xa1dde) << 0x17) >> 0x1e);
        *(undefined1 *)(iVar3 + 0xa2960) = 0;
        *(undefined1 *)(iVar3 + 0xa295e) = 1;
        *(undefined1 *)(iVar3 + 0xa295f) = 0x49;
        *(undefined1 *)(iVar3 + 0xa2961) = 0x49;
        bVar9 = *(byte *)(iVar3 + 0xa1dac);
        if (local_2e <= *(byte *)(iVar3 + 0xa1dac)) {
          bVar9 = local_2e;
        }
        *(byte *)(iVar3 + 0xa2964) = bVar9;
        if (*(byte *)(iVar3 + 0xa1db0) <= bVar9) {
          bVar9 = *(byte *)(iVar3 + 0xa1db0);
        }
        *(byte *)(iVar3 + 0xa2963) = bVar9;
        *(char *)(iVar3 + 0xa2977) = local_40;
        *(byte *)(iVar3 + 0xa2976) = bVar9;
        *(byte *)(iVar3 + 0xa2975) = (byte)(((uint)*(ushort *)(iVar3 + 0xa1dde) << 0x17) >> 0x1e);
        *(undefined1 *)(iVar3 + 0xa2974) = 0x18;
        if ((2 < uVar1) && ((*(ushort *)(iVar3 + 0xa1dde) & 0x180) == 0x180)) {
          if (*(byte *)(iVar3 + 0xa1dad) <= local_2d) {
            local_2d = *(byte *)(iVar3 + 0xa1dad);
          }
          *(byte *)(iVar3 + 0xa2978) = local_2d;
          bVar9 = *(byte *)(iVar3 + 0xa1d4b);
          if ((bVar9 & 4) != 0) {
            pcVar6 = (char *)(param_1 + param_4 * 0x14c0 + 0xa1d69);
            cVar10 = '\x01';
            do {
              pcVar6 = pcVar6 + 1;
              cVar14 = cVar10 + '\x01';
              if (*pcVar6 == '\x03') {
                cVar10 = cVar10 + -1;
                goto LAB_00086298;
              }
              cVar10 = cVar14;
            } while (cVar14 != '\b');
            cVar10 = '\a';
LAB_00086298:
            iVar3 = param_4 * 0x14c0 + param_1;
            *(char *)(iVar3 + 0xa2979) = cVar10;
            bVar9 = *(byte *)(iVar3 + 0xa1d4b);
          }
          if ((bVar9 & 8) != 0) {
            pcVar6 = (char *)(param_4 * 0x14c0 + param_1 + 0xa1d79);
            cVar10 = '\x01';
            do {
              pcVar6 = pcVar6 + 1;
              cVar14 = cVar10 + '\x01';
              if (*pcVar6 == '\x03') {
                bVar9 = cVar10 - 1;
                goto LAB_000862f8;
              }
              cVar10 = cVar14;
            } while (cVar14 != '\b');
            bVar9 = 7;
LAB_000862f8:
            iVar3 = param_4 * 0x14c0 + param_1;
            bVar15 = *(byte *)(iVar3 + 0xa2979);
            if (bVar15 == 0) {
              *(byte *)(iVar3 + 0xa2979) = bVar9;
            }
            else {
              if (bVar9 <= bVar15) {
                bVar15 = bVar9;
              }
              *(byte *)(iVar3 + 0xa2979) = bVar15;
            }
          }
        }
        iVar3 = param_4 * 0x14c0 + param_1;
        *(byte *)(iVar3 + 0xa297c) = (byte)*(undefined4 *)(iVar3 + 0xa1da8) >> 7;
        *(byte *)(iVar3 + 0xa297d) = (byte)((uint)(*(int *)(iVar3 + 0xa1da8) << 0x17) >> 0x1f);
        *(undefined1 *)(iVar3 + 0xa2982) = 0;
        uVar1 = *(uint *)(param_1 + 0xa787b8);
        if ((uVar1 & 2) != 0) {
          *(undefined1 *)(iVar3 + 0xa297a) = *(undefined1 *)(param_1 + 0xa787bd);
          *(undefined1 *)(iVar3 + 0xa297b) = *(undefined1 *)(param_1 + 0xa787be);
        }
        if ((uVar1 & 4) != 0) {
          iVar3 = param_4 * 0x14c0 + param_1;
          *(undefined1 *)(iVar3 + 0xa297c) = *(undefined1 *)(param_1 + 0xa787bf);
          *(undefined1 *)(iVar3 + 0xa297d) = *(undefined1 *)(param_1 + 0xa787c0);
        }
        if ((uVar1 & 8) != 0) {
          iVar3 = param_4 * 0x14c0 + param_1;
          *(undefined1 *)(iVar3 + 0xa297e) = *(undefined1 *)(param_1 + 0xa787c1);
          *(undefined1 *)(iVar3 + 0xa297f) = *(undefined1 *)(param_1 + 0xa787c2);
        }
        if ((uVar1 & 0x10) != 0) {
          iVar3 = param_4 * 0x14c0 + param_1;
          *(undefined1 *)(iVar3 + 0xa2980) = *(undefined1 *)(param_1 + 0xa787c3);
          *(undefined1 *)(iVar3 + 0xa2981) = *(undefined1 *)(param_1 + 0xa787c4);
        }
        goto LAB_00085ac0;
      }
    }
    iVar3 = param_4 * 0x14c0;
    cVar10 = (char)uVar2 + -1;
    iVar13 = param_1 + iVar3;
    *(undefined1 *)(iVar13 + 0xa295d) = 0;
    *(undefined1 *)(iVar13 + 0xa295c) = 0;
    *(undefined1 *)(iVar13 + 0xa2962) = 8;
    pcVar6 = (char *)(param_1 + iVar3 + 0xa1d51);
    *(char *)(iVar13 + 0xa2964) = cVar10;
    *(byte *)(iVar13 + 0xa2965) = (byte)(((uint)*(ushort *)(iVar13 + 0xa1dde) << 0x17) >> 0x1e);
    *(char *)(iVar13 + 0xa2977) = cVar10;
    *(byte *)(iVar13 + 0xa2975) = (byte)(((uint)*(ushort *)(iVar13 + 0xa1dde) << 0x17) >> 0x1e);
    cVar10 = '\x01';
    do {
      pcVar6 = pcVar6 + 1;
      cVar14 = cVar10 + '\x01';
      if (*pcVar6 == '\x03') {
        bVar9 = cVar10 - 1;
        goto LAB_000856f0;
      }
      cVar10 = cVar14;
    } while (cVar14 != '\b');
    bVar9 = 7;
LAB_000856f0:
    iVar13 = param_4 * 0x14c0 + param_1;
    *(byte *)(iVar13 + 0xa2976) = bVar9;
    *(undefined1 *)(iVar13 + 0xa2974) = 0x18;
    if (*(byte *)(iVar13 + 0xa2964) <= bVar9) {
      bVar9 = *(byte *)(iVar13 + 0xa2964);
    }
    *(byte *)(iVar13 + 0xa2963) = bVar9;
    if ((2 < uVar1) && ((*(ushort *)(iVar13 + 0xa1dde) & 0x180) == 0x180)) {
      *(char *)(iVar13 + 0xa2978) = local_40 + -1;
      bVar9 = *(byte *)(iVar13 + 0xa1d4b);
      if ((bVar9 & 4) == 0) {
        bVar15 = *(byte *)(iVar13 + 0xa2979);
      }
      else {
        pcVar6 = (char *)(param_1 + iVar3 + 0xa1d69);
        cVar10 = '\x01';
        do {
          pcVar6 = pcVar6 + 1;
          cVar14 = cVar10 + '\x01';
          if (*pcVar6 == '\x03') {
            bVar15 = cVar10 - 1;
            goto LAB_00086464;
          }
          cVar10 = cVar14;
        } while (cVar14 != '\b');
        bVar15 = 7;
LAB_00086464:
        iVar13 = param_4 * 0x14c0 + param_1;
        *(byte *)(iVar13 + 0xa2979) = bVar15;
        bVar9 = *(byte *)(iVar13 + 0xa1d4b);
      }
      bVar5 = bVar15;
      if ((bVar9 & 8) != 0) {
        pcVar6 = (char *)(param_1 + iVar3 + 0xa1d79);
        cVar10 = '\x01';
        do {
          pcVar6 = pcVar6 + 1;
          cVar14 = cVar10 + '\x01';
          if (*pcVar6 == '\x03') {
            bVar5 = cVar10 - 1;
            goto LAB_000863d4;
          }
          cVar10 = cVar14;
        } while (cVar14 != '\b');
        bVar5 = 7;
LAB_000863d4:
        if (bVar15 == 0) {
          *(byte *)(param_4 * 0x14c0 + param_1 + 0xa2979) = bVar5;
        }
        else {
          if (bVar15 < bVar5) {
            bVar5 = bVar15;
          }
          *(byte *)(param_4 * 0x14c0 + param_1 + 0xa2979) = bVar5;
        }
      }
      iVar3 = param_4 * 0x14c0 + param_1;
      bVar9 = *(byte *)(iVar3 + 0xa2978);
      if (bVar9 <= bVar5) {
        bVar5 = bVar9;
      }
      *(byte *)(iVar3 + 0xa2979) = bVar5;
      uVar1 = *(uint *)(param_1 + 0xa787b8);
      goto LAB_00085ac0;
    }
    break;
  default:
    if ((*(uint *)(param_1 + 0xa787b8) & 1) != 0) {
      *(undefined1 *)(param_4 * 0x14c0 + param_1 + 0xa295c) = *(undefined1 *)(param_1 + 0xa787bc);
    }
    return 0;
  }
  uVar1 = *(uint *)(param_1 + 0xa787b8);
LAB_00085ac0:
  if ((uVar1 & 1) != 0) {
    *(undefined1 *)(param_4 * 0x14c0 + param_1 + 0xa295c) = *(undefined1 *)(param_1 + 0xa787bc);
  }
  iVar3 = param_4 * 0x14c0 + param_1;
  if ((*(byte *)(iVar3 + 0xa295d) & 1) == 0) {
    cVar10 = g_ru2PfmuMemReq
             [(uint)*(byte *)(iVar3 + 0xa2963) + (uint)*(byte *)(iVar3 + 0xa2964) * 4];
    *(char *)(iVar3 + 0xa2967) = cVar10;
  }
  else {
    if ((uint)*(byte *)(iVar3 + 0xa2964) == uVar12 - 1) {
      cVar10 = g_ru2PfmuMemReq
               [(uint)*(byte *)(iVar3 + 0xa2963) + (uint)*(byte *)(iVar3 + 0xa2964) * 4];
    }
    else {
      cVar10 = g_ru2PfmuMemReq[(uint)*(byte *)(iVar3 + 0xa2963) + (uVar12 - 1) * 4];
    }
    *(char *)(iVar3 + 0xa2967) = cVar10;
  }
  iVar3 = param_4 * 0x14c0 + param_1;
  *(undefined1 *)(iVar3 + 0xa2968) = 0;
  *(byte *)(iVar3 + 0xa2969) = *(byte *)(iVar3 + 0xa2969) & 0xc0;
  *(char *)(iVar3 + 0xa2966) =
       cVar10 * *(char *)((int)&g_aPfmuTimeOfMem20M + (uint)*(byte *)(iVar3 + 0xa2965));
  *(undefined1 *)(iVar3 + 0xa296a) = 0;
  *(undefined1 *)(iVar3 + 0xa296c) = 0;
  *(undefined1 *)(iVar3 + 0xa296e) = 0;
  *(undefined2 *)(iVar3 + 0xa2970) = 0;
  *(byte *)(iVar3 + 0xa296b) = *(byte *)(iVar3 + 0xa296b) & 0xc0;
  *(byte *)(iVar3 + 0xa296d) = *(byte *)(iVar3 + 0xa296d) & 0xc0;
  *(byte *)(iVar3 + 0xa296f) = *(byte *)(iVar3 + 0xa296f) & 0xc0;
  *(undefined1 *)(iVar3 + 0xa2973) = *(undefined1 *)(param_1 + 0x7959a6);
  return 1;
}

