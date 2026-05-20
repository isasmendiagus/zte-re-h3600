// module: mt7915.ko
// function: map_check_cap_ie @ 0x1602bc
// size: 120 bytes
//

undefined4 map_check_cap_ie(int param_1,undefined1 *param_2)

{
  int iVar1;
  
  iVar1 = memcmp((void *)(param_1 + 2),&MAP_OUI,3);
  if ((((iVar1 == 0) && (6 < *(byte *)(param_1 + 1))) && (*(char *)(param_1 + 5) == MAP_OUI_TYPE))
     && ((*(char *)(param_1 + 6) == MAP_EXT_ATTRI && (*(char *)(param_1 + 7) == '\x01')))) {
    *param_2 = *(undefined1 *)(param_1 + 8);
    return 1;
  }
  return 0;
}

