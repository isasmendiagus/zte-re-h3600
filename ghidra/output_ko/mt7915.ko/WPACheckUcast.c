// module: mt7915.ko
// function: WPACheckUcast @ 0x11b52c
// size: 440 bytes
//

bool WPACheckUcast(int param_1,int param_2,char *param_3)

{
  short sVar1;
  int iVar2;
  char cVar3;
  ushort uVar4;
  ushort uVar5;
  uint uVar6;
  short *psVar7;
  short *__s1;
  short sVar8;
  bool bVar9;
  
  cVar3 = *param_3;
  if (cVar3 == '0') {
    psVar7 = (short *)(param_3 + 8);
  }
  else {
    if (cVar3 != -0x23) {
      if (-1 < DebugLevel) {
        printk("[ERROR]%s : invalid IE=%d\n","WPACheckUcast");
      }
      return false;
    }
    psVar7 = (short *)(param_3 + 0xc);
  }
  __s1 = psVar7 + 1;
  sVar1 = *psVar7;
  uVar6 = *(uint *)(param_2 + 0x148);
  if (sVar1 != 0) {
    sVar8 = 0;
    do {
      if (cVar3 == -0x23) {
        iVar2 = memcmp(__s1,&OUI_WPA_TKIP,4);
        if (iVar2 == 0) {
LAB_0011b618:
          uVar6 = uVar6 | 0x10;
          *(uint *)(param_2 + 0x148) = uVar6;
        }
        else {
          iVar2 = memcmp(__s1,&OUI_WPA_CCMP,4);
          if (iVar2 == 0) {
LAB_0011b60c:
            uVar6 = uVar6 | 0x20;
            *(uint *)(param_2 + 0x148) = uVar6;
          }
        }
      }
      else if (cVar3 == '0') {
        iVar2 = memcmp(__s1,&OUI_WPA2_CIPHER_TKIP,4);
        if (iVar2 == 0) goto LAB_0011b618;
        iVar2 = memcmp(__s1,&OUI_WPA2_CIPHER_CCMP128,4);
        if (iVar2 == 0) goto LAB_0011b60c;
        iVar2 = memcmp(__s1,&OUI_WPA2_CIPHER_CCMP256,4);
        if (iVar2 == 0) {
          uVar6 = uVar6 | 0x40;
          *(uint *)(param_2 + 0x148) = uVar6;
        }
        else {
          iVar2 = memcmp(__s1,&OUI_WPA2_CIPHER_GCMP128,4);
          if (iVar2 == 0) {
            uVar6 = uVar6 | 0x80;
            *(uint *)(param_2 + 0x148) = uVar6;
          }
          else {
            iVar2 = memcmp(__s1,&OUI_WPA2_CIPHER_GCMP256,4);
            if (iVar2 == 0) {
              uVar6 = uVar6 | 0x100;
              *(uint *)(param_2 + 0x148) = uVar6;
            }
          }
        }
      }
      __s1 = __s1 + 2;
      uVar4 = (sVar1 + -1) - sVar8;
      uVar5 = sVar8 + 1;
      sVar8 = sVar8 + 1;
      if (uVar4 <= uVar5) break;
      cVar3 = *param_3;
    } while( true );
  }
  bVar9 = (uVar6 & *(uint *)(param_1 + 0x148)) == 0;
  if (bVar9) {
    *(undefined4 *)(param_2 + 0x148) = 0;
  }
  return !bVar9;
}

