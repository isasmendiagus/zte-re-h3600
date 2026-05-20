// module: mt7915.ko
// function: dfs_rddidx_to_dbdc @ 0x238120
// size: 112 bytes
//

int dfs_rddidx_to_dbdc(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  uVar2 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  iVar1 = param_2;
  if (uVar2 == 0x7915 || uVar2 == 0x7615) {
    iVar3 = param_2;
    if (*(char *)(param_1 + 0x795134) == '\x06' || *(char *)(param_1 + 0x795134) == '\x03') {
      iVar3 = 0;
    }
    iVar1 = iVar3;
    if ((uVar2 == 0x7915) && (iVar1 = param_2, param_2 != 2)) {
      iVar1 = iVar3;
    }
  }
  return iVar1;
}

