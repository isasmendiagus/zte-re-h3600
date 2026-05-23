// module: mt7915.ko
// function: multi_hif_init @ 0x14e64c
// size: 60 bytes
//

void multi_hif_init(void)

{
  DAT_005f3d24 = 0;
  OS_SPIN_LOCK(&DAT_005f3d24);
  _LANCHOR1 = 0;
  DAT_005f3d1c = &DAT_005f3d1c;
  DAT_005f3d20 = &DAT_005f3d1c;
  OS_SPIN_UNLOCK(&DAT_005f3d24);
  return;
}

