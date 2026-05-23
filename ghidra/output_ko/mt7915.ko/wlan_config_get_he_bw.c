// module: mt7915.ko
// function: wlan_config_get_he_bw @ 0x206430
// size: 136 bytes
//

byte wlan_config_get_he_bw(int param_1)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0xb10);
  bVar1 = 0;
  if (*(char *)(iVar2 + 0x15) == '\0') goto LAB_0020646c;
  if (*(char *)(iVar2 + 0x15) == '\x01') {
    switch(*(undefined1 *)(iVar2 + 0x5c)) {
    case 0:
      *(undefined1 *)(iVar2 + 100) = 1;
      return 1;
    case 1:
      *(undefined1 *)(iVar2 + 100) = 2;
      break;
    case 2:
      *(undefined1 *)(iVar2 + 100) = 3;
      break;
    case 3:
      *(undefined1 *)(iVar2 + 100) = 4;
      break;
    default:
      goto switchD_00206454_default;
    }
  }
  else {
switchD_00206454_default:
    if (*(byte *)(iVar2 + 100) < 2) {
      return *(byte *)(iVar2 + 100);
    }
  }
  if ((*(ushort *)(param_1 + 0x18) & 0x40) == 0) {
    return *(byte *)(iVar2 + 100);
  }
  bVar1 = 1;
LAB_0020646c:
  *(byte *)(iVar2 + 100) = bVar1;
  return bVar1;
}

