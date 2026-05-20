// module: mt7915.ko
// function: os_module_init @ 0x245c34
// size: 4 bytes
//

void os_module_init(void)

{
  DAT_005f3d24 = 0;
  OS_SPIN_LOCK(&DAT_005f3d24);
  _LANCHOR1 = 0;
  DAT_005f3d1c = &DAT_005f3d1c;
  DAT_005f3d20 = &DAT_005f3d1c;
  OS_SPIN_UNLOCK(&DAT_005f3d24);
  return;
}

