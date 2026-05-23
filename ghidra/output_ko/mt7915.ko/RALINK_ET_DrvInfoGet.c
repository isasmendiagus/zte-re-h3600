// module: mt7915.ko
// function: RALINK_ET_DrvInfoGet @ 0x243104
// size: 60 bytes
//

void RALINK_ET_DrvInfoGet(int param_1,int param_2)

{
  builtin_strncpy((char *)(param_2 + 4),"RALI",4);
  builtin_strncpy((char *)(param_2 + 8),"NK W",4);
  builtin_strncpy((char *)(param_2 + 0xc),"LAN",4);
  sprintf((char *)(param_2 + 100),"CSR 0x%lx",*(undefined4 *)(param_1 + 0x24),"CSR 0x%lx");
  return;
}

