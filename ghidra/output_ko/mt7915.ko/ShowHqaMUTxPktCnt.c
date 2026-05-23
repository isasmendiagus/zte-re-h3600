// module: mt7915.ko
// function: ShowHqaMUTxPktCnt @ 0x8f6dc
// size: 160 bytes
//

undefined4 ShowHqaMUTxPktCnt(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int local_c;
  
  local_c = 0;
  if (param_1 != 0) {
    if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7626) {
      uVar2 = 0xd290;
    }
    else {
      uVar2 = 0xd090;
    }
    mac_io_read32(*(undefined4 *)(param_1 + 0xa797a0),uVar2 | 0x820f0000,&local_c);
    iVar1 = DebugLevel;
    iVar3 = *(int *)(param_1 + 0xa789dc);
    if (iVar3 == -1) {
      iVar3 = 0;
    }
    *(int *)(param_1 + 0xa789dc) = iVar3 + local_c;
    if (0 < iVar1) {
      printk("%s:(MuTxCnt=%d\n","ShowHqaMUTxPktCnt");
    }
  }
  return 1;
}

