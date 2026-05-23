// module: mt7915.ko
// function: HwCtrlSetBcnOffload @ 0xaf108
// size: 244 bytes
//

undefined4 HwCtrlSetBcnOffload(int param_1,int param_2)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  undefined1 local_228;
  byte local_227;
  undefined1 local_226;
  undefined1 local_225;
  byte local_224;
  undefined2 local_222;
  undefined2 local_220;
  undefined2 local_21e;
  undefined1 auStack_21c [512];
  undefined1 local_1c;
  
  pbVar1 = *(byte **)(param_2 + 8);
  iVar2 = *(int *)(param_1 + (uint)*pbVar1 * 4 + 0xc);
  __memzero(&local_228,0x210);
  if (pbVar1[9] == 0) {
    if (iVar2 == -0x948) {
      if (-1 < DebugLevel) {
        printk("%s(): bcn_buf is NULL!\n","HwCtrlSetBcnOffload");
        return 1;
      }
      return 1;
    }
    iVar3 = *(int *)(iVar2 + 0x954);
  }
  else {
    iVar3 = 0;
  }
  local_227 = pbVar1[8];
  local_228 = *(undefined1 *)(iVar2 + 0x29);
  local_226 = 0;
  local_225 = HcGetBandByWdev(iVar2);
  local_1c = *(undefined1 *)(iVar2 + 0x944);
  local_220 = (undefined2)*(undefined4 *)(pbVar1 + 4);
  local_224 = pbVar1[9];
  local_21e = (undefined2)*(undefined4 *)(pbVar1 + 0xc);
  local_222 = (undefined2)*(undefined4 *)(pbVar1 + 0x10);
  memcpy(auStack_21c,*(void **)(iVar3 + 0xcc),*(size_t *)(pbVar1 + 4));
  MtCmdBcnOffloadSet(param_1,&local_228);
  return 0;
}

