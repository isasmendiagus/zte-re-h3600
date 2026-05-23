// module: mt7915.ko
// function: printOthers @ 0x155360
// size: 72 bytes
//

undefined4 printOthers(undefined4 param_1,char *param_2)

{
  size_t sVar1;
  
  sVar1 = strlen(param_2);
  sprintf(param_2 + sVar1,"%s%-16s%s\n","===================="," OTHERS ","====================");
  return 1;
}

