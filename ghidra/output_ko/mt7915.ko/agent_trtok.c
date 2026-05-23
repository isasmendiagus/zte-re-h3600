// module: mt7915.ko
// function: agent_trtok @ 0x24c844
// size: 136 bytes
//

char * agent_trtok(char *param_1,char *param_2)

{
  size_t sVar1;
  
  if ((param_1 == (char *)0x0) && (param_1 = agnt_rstrtok, agnt_rstrtok == (char *)0x0)) {
    return (char *)0x0;
  }
  sVar1 = strspn(param_1,param_2);
  if ((byte)param_1[sVar1] == 0) {
    agnt_rstrtok = (char *)(uint)(byte)param_1[sVar1];
    return (char *)0x0;
  }
  agnt_rstrtok = strpbrk(param_1 + sVar1,param_2);
  if ((agnt_rstrtok != (char *)0x0) && (*agnt_rstrtok != '\0')) {
    *agnt_rstrtok = '\0';
    agnt_rstrtok = agnt_rstrtok + 1;
  }
  return param_1 + sVar1;
}

