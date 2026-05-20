// module: mt7915.ko
// function: MlmeAssocReqSanity @ 0x11230c
// size: 64 bytes
//

undefined4
MlmeAssocReqSanity(undefined4 param_1,undefined4 *param_2,undefined4 param_3,undefined4 *param_4,
                  undefined2 *param_5,undefined4 *param_6,undefined2 *param_7)

{
  *param_6 = param_2[3];
  *param_4 = *param_2;
  *(undefined2 *)(param_4 + 1) = *(undefined2 *)(param_2 + 1);
  *param_5 = *(undefined2 *)((int)param_2 + 6);
  *param_7 = *(undefined2 *)(param_2 + 2);
  return 1;
}

