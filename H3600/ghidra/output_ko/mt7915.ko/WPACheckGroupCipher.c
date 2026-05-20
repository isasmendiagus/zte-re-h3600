// module: mt7915.ko
// function: WPACheckGroupCipher @ 0x11b394
// size: 372 bytes
//

undefined4 WPACheckGroupCipher(int param_1,int param_2,char *param_3)

{
  int iVar1;
  undefined4 *puVar2;
  uint uVar3;
  
  if ((byte)param_3[1] < 6) goto LAB_0011b3bc;
  if (*param_3 == -0x23) {
    if ((*(uint *)(param_1 + 0x228) & 0x10) == 0) {
      if ((*(uint *)(param_1 + 0x228) & 0x20) == 0) goto LAB_0011b3bc;
      puVar2 = &OUI_WPA_CCMP;
      *(uint *)(param_2 + 0x228) = *(uint *)(param_2 + 0x228) | 0x20;
    }
    else {
      puVar2 = &OUI_WPA_TKIP;
      *(uint *)(param_2 + 0x228) = *(uint *)(param_2 + 0x228) | 0x10;
    }
    if (puVar2 == (undefined4 *)0x0) goto LAB_0011b3bc;
    iVar1 = memcmp(param_3 + 8,puVar2,4);
  }
  else {
    if (*param_3 != '0') goto LAB_0011b3bc;
    uVar3 = *(uint *)(param_1 + 0x228);
    if ((uVar3 & 2) == 0) {
      if ((uVar3 & 4) == 0) {
        if ((uVar3 & 0x10) == 0) {
          if ((uVar3 & 0x20) == 0) {
            if ((uVar3 & 0x40) == 0) {
              if ((uVar3 & 0x80) == 0) {
                if ((uVar3 & 0x100) == 0) goto LAB_0011b3bc;
                puVar2 = &OUI_WPA2_CIPHER_GCMP256;
                *(uint *)(param_2 + 0x228) = *(uint *)(param_2 + 0x228) | 0x100;
              }
              else {
                puVar2 = &OUI_WPA2_CIPHER_GCMP128;
                *(uint *)(param_2 + 0x228) = *(uint *)(param_2 + 0x228) | 0x80;
              }
            }
            else {
              puVar2 = &OUI_WPA2_CIPHER_CCMP256;
              *(uint *)(param_2 + 0x228) = *(uint *)(param_2 + 0x228) | 0x40;
            }
          }
          else {
            puVar2 = &OUI_WPA2_CIPHER_CCMP128;
            *(uint *)(param_2 + 0x228) = *(uint *)(param_2 + 0x228) | 0x20;
          }
        }
        else {
          puVar2 = &OUI_WPA2_CIPHER_TKIP;
          *(uint *)(param_2 + 0x228) = *(uint *)(param_2 + 0x228) | 0x10;
        }
      }
      else {
        puVar2 = &OUI_WPA2_CIPHER_WEP104;
        *(uint *)(param_2 + 0x228) = *(uint *)(param_2 + 0x228) | 4;
      }
    }
    else {
      puVar2 = &OUI_WPA2_CIPHER_WEP40;
      *(uint *)(param_2 + 0x228) = *(uint *)(param_2 + 0x228) | 2;
    }
    if (puVar2 == (undefined4 *)0x0) goto LAB_0011b3bc;
    iVar1 = memcmp(param_3 + 4,puVar2,4);
  }
  if (iVar1 == 0) {
    return 1;
  }
LAB_0011b3bc:
  *(undefined4 *)(param_2 + 0x228) = 0;
  return 0;
}

