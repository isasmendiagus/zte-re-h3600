// module: mt7915.ko
// function: ra_mtd_read_nm @ 0x1569a0
// size: 236 bytes
//

undefined4
ra_mtd_read_nm(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
              undefined4 param_5)

{
  uint uVar1;
  char *pcVar2;
  undefined1 auStack_24 [16];
  
  uVar1 = RtmpOSFileOpen("/wlan/caldata",0,0);
  if ((uVar1 == 0) || (0xfffff000 < uVar1)) {
    pcVar2 = "/etc/wireless/mt7915/MT7915_EEPROM.bin";
    printk("%s(%d):read cal(%s) err, Try Default(%s)\n","ra_mtd_read_nm",0x50,"/wlan/caldata",
           "/etc/wireless/mt7915/MT7915_EEPROM.bin");
    uVar1 = RtmpOSFileOpen("/etc/wireless/mt7915/MT7915_EEPROM.bin",0,0);
    if ((uVar1 == 0) || (0xfffff000 < uVar1)) {
      printk("%s(%d):read Default(%s) err\n","ra_mtd_read_nm",0x54,
             "/etc/wireless/mt7915/MT7915_EEPROM.bin",pcVar2);
      return 0xffffffff;
    }
  }
  RtmpOSFSInfoChange(auStack_24,1);
  RtmpOSFileSeek(uVar1,param_3);
  RtmpOSFileRead(uVar1,param_1,param_5);
  RtmpOSFileClose(uVar1);
  RtmpOSFSInfoChange(auStack_24,0);
  return param_5;
}

