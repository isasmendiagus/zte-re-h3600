// module: mt7915.ko
// function: MtCmdGetCfgStatRsp @ 0x1abf64
// size: 224 bytes
//

void MtCmdGetCfgStatRsp(int param_1,char *param_2)

{
  char cVar1;
  
  cVar1 = *param_2;
  if (cVar1 == '\r') {
    os_move_mem(*(void **)(param_1 + 0xc),param_2 + 4,1);
    if (DebugLevel < 3) {
      return;
    }
    printk("%s, DPD Enable:%d Band:%d\n","MtCmdGetCfgStatRsp",param_2[4],param_2[5]);
    return;
  }
  if (cVar1 == '\x0e') {
    os_move_mem(*(void **)(param_1 + 0xc),param_2 + 4,1);
    if (DebugLevel < 3) {
      return;
    }
    printk("%s, THER Enable:%d\n","MtCmdGetCfgStatRsp",param_2[4]);
    return;
  }
  if (cVar1 != '\f') {
    return;
  }
  os_move_mem(*(void **)(param_1 + 0xc),param_2 + 4,1);
  if (DebugLevel < 3) {
    return;
  }
  printk("%s, TSSI Enable:%d Band:%d\n","MtCmdGetCfgStatRsp",param_2[4],param_2[5]);
  return;
}

