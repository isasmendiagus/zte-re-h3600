// module: mt7915.ko
// function: RguClass_BuildBcnChList @ 0x140730
// size: 216 bytes
//

void RguClass_BuildBcnChList
               (undefined4 param_1,int param_2,int *param_3,undefined4 param_4,char param_5)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  byte local_1e;
  byte local_1d;
  int local_1c;
  
  local_1d = 0xff;
  if (param_5 != '\0') {
    iVar1 = get_channelset_by_reg_class(param_1,param_5,param_4);
    iVar2 = get_channel_set_num();
    local_1e = (byte)iVar2;
    if (iVar2 != 0 && iVar1 != 0) {
      uVar4 = 0;
      do {
        uVar3 = GetRegulatoryMaxTxPwr(param_1,*(undefined1 *)(iVar1 + uVar4));
        uVar4 = uVar4 + 1 & 0xff;
        if (uVar3 < local_1d) {
          local_1d = (byte)uVar3;
        }
      } while (uVar4 < local_1e);
      MakeOutgoingFrame(param_2 + *param_3,&local_1c,1,iVar1,1,&local_1e,1,&local_1d,0xffffffff);
      *param_3 = *param_3 + local_1c;
      return;
    }
  }
  return;
}

