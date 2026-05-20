// module: mt7915.ko
// function: Show_IEEE80211H_Proc @ 0xd60ac
// size: 68 bytes
//

undefined4 Show_IEEE80211H_Proc(int param_1,char *param_2,size_t param_3,undefined4 param_4)

{
  char *pcVar1;
  
  pcVar1 = "TRUE";
  if (*(char *)(param_1 + 0x795074) == '\0') {
    pcVar1 = "FALSE";
  }
  snprintf(param_2,param_3,"\t%s",pcVar1,param_4);
  return 0;
}

