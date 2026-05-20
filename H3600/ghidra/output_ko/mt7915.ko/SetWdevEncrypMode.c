// module: mt7915.ko
// function: SetWdevEncrypMode @ 0x112d70
// size: 592 bytes
//

void SetWdevEncrypMode(int param_1,char *param_2)

{
  int iVar1;
  size_t sVar2;
  undefined4 uVar3;
  
  iVar1 = rtstrcasecmp(param_2,&_LC1);
  if (iVar1 == 1) {
    uVar3 = 1;
  }
  else {
    iVar1 = rtstrcasecmp(param_2,&_LC25);
    if (iVar1 == 1) {
      uVar3 = 0xe;
    }
    else {
      iVar1 = rtstrcasecmp(param_2,&_LC26);
      if (iVar1 == 1) {
        uVar3 = 0x10;
      }
      else {
        iVar1 = rtstrcasecmp(param_2,&_LC27);
        if ((iVar1 == 1) || (iVar1 = rtstrcasecmp(param_2,"CCMP128"), iVar1 == 1)) {
          uVar3 = 0x20;
        }
        else {
          iVar1 = rtstrcasecmp(param_2,"CCMP256");
          if (iVar1 == 1) {
            uVar3 = 0x40;
          }
          else {
            iVar1 = rtstrcasecmp(param_2,"GCMP128");
            if (iVar1 == 1) {
              uVar3 = 0x80;
            }
            else {
              iVar1 = rtstrcasecmp(param_2,"GCMP256");
              if (iVar1 == 1) {
                uVar3 = 0x100;
              }
              else {
                iVar1 = rtstrcasecmp(param_2,"TKIPAES");
                if ((((((iVar1 != 1) && (iVar1 = rtstrcasecmp(param_2,"TKIPCCMP128"), iVar1 != 1))
                      && (iVar1 = rtstrcasecmp(param_2,"WPA_AES_WPA2_TKIPAES"), iVar1 != 1)) &&
                     ((iVar1 = rtstrcasecmp(param_2,"WPA_AES_WPA2_TKIP"), iVar1 != 1 &&
                      (iVar1 = rtstrcasecmp(param_2,"WPA_TKIP_WPA2_AES"), iVar1 != 1)))) &&
                    ((iVar1 = rtstrcasecmp(param_2,"WPA_TKIP_WPA2_TKIPAES"), iVar1 != 1 &&
                     ((iVar1 = rtstrcasecmp(param_2,"WPA_TKIPAES_WPA2_AES"), iVar1 != 1 &&
                      (iVar1 = rtstrcasecmp(param_2,"WPA_TKIPAES_WPA2_TKIPAES"), iVar1 != 1)))))) &&
                   (iVar1 = rtstrcasecmp(param_2,"WPA_TKIPAES_WPA2_TKIP"), iVar1 != 1)) {
                  if (-1 < DebugLevel) {
                    sVar2 = strlen(param_2);
                    printk("%s:: Not support (EncrypType=%s, len=%d)\n","SetWdevEncrypMode",param_2,
                           sVar2);
                  }
                  goto LAB_00112f64;
                }
                uVar3 = 0x30;
              }
            }
          }
        }
      }
    }
  }
  *(undefined4 *)(param_1 + 0x148) = uVar3;
  *(undefined4 *)(param_1 + 0x228) = 0;
LAB_00112f64:
  if (DebugLevel < 3) {
    return;
  }
  printk("%s::PairwiseCipher=0x%x\n","SetWdevEncrypMode",*(undefined4 *)(param_1 + 0x148));
  return;
}

