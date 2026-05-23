// module: mt7915.ko
// function: SetATEEBFCEInfo @ 0x268684
// size: 104 bytes
//

undefined4 SetATEEBFCEInfo(void)

{
  if ((0 < DebugLevel) &&
     (printk("%s: g_EBF_certification = %d !!!!!\n","SetATEEBFCEInfo",g_EBF_certification),
     0 < DebugLevel)) {
    printk("%s: BF_ON_certification = %d !!!!!\n","SetATEEBFCEInfo",BF_ON_certification);
  }
  return 1;
}

