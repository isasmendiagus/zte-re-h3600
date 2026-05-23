// module: mt7915.ko
// function: sae_build_token_req @ 0x209624
// size: 220 bytes
//

undefined4 sae_build_token_req(undefined4 param_1,int param_2,void *param_3,undefined4 *param_4)

{
  undefined1 uVar1;
  undefined1 *puVar2;
  int iVar3;
  
  if (param_2 != 0) {
    iVar3 = *(int *)(param_2 + 0x180);
    memmove(param_3,(void *)(param_2 + 0x2c),2);
    if ((*(uint *)(iVar3 + 0x1b90c) + 100000 < jiffies) &&
       (*(uint *)(iVar3 + 0x1b90c) < jiffies - 100000)) {
      puVar2 = (undefined1 *)(iVar3 + 0x1b90f);
      *(uint *)(iVar3 + 0x1b90c) = jiffies;
      do {
        uVar1 = RandomByte(*(undefined4 *)(iVar3 + 0x1b924));
        puVar2 = puVar2 + 1;
        *puVar2 = uVar1;
      } while (puVar2 != (undefined1 *)(iVar3 + 0x1b915));
    }
    RT_HMAC_SHA256(iVar3 + 0x1b910,6,param_2 + 0x166,6,(int)param_3 + 2,0x20);
    *param_4 = 0x22;
    return 1;
  }
  return 0;
}

