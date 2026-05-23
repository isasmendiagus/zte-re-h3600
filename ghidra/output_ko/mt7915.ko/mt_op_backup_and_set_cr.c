// module: mt7915.ko
// function: mt_op_backup_and_set_cr @ 0x257874
// size: 28 bytes
//

undefined4 mt_op_backup_and_set_cr(void)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = mt_test_mac_backup_and_set_cr();
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = 0x502;
  }
  return uVar2;
}

