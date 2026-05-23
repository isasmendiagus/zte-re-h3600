// module: mt7915.ko
// function: Set_LoadEepromBufferFromEfuse_Proc @ 0x1d38ac
// size: 16 bytes
//

undefined4 Set_LoadEepromBufferFromEfuse_Proc(void)

{
  rtmp_ee_load_from_efuse();
  return 1;
}

