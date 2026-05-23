// module: mt7915.ko
// function: ZTE_WLAN_Temperature_Protection_Enable @ 0x15fda4
// size: 44 bytes
//

bool ZTE_WLAN_Temperature_Protection_Enable(void)

{
  if (_LANCHOR0 == '\0') {
    return DAT_0034d536 != '\0';
  }
  return true;
}

