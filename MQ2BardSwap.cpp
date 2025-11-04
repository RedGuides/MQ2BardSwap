// MQ2BardSwap.cpp - v1.1 (by Cr4zyb4rd)
//
// changes
//  9/25/04 - Use spell structs instead of parsing MQ2Data
//            complete rewrite of swapping logic, melee swapping should work in all situations
//
//   11/09/2009 - Change CastingSpellID to CastingData.SpellID
//

#include <mq/Plugin.h>

PreSetup("MQ2BardSwap");
PLUGIN_VERSION(2009.1109);

typedef struct _EXCLUDED {
	CHAR Song[MAX_STRING];
	struct _EXCLUDED *pNext;
} EXCLUDED, *PEXCLUDED;

PEXCLUDED pExcluded = 0;

const char* SongSkills[] = {
	"Brass Instruments",
	"Percussion Instruments",
	"Stringed Instruments",
	"Wind Instruments",
	"Sing",
	nullptr
};

const char* InstrumentList[] = {
	"Horn",
	"Drum",
	"Lute",
	"Wind",
	"Singing",
	"Weapons",
	nullptr
};

struct _data {
	char Command[MAX_STRING];
	bool Enabled;
} InstrumentSettings[6];

bool bMeleeSwap = false;
bool bSwapEnabled = false;
bool bExcluded = false;
int MeleeDelay = 0;
int iCurrentSwap = 5;
int SwapTo = 5;
int ExcludeCount = 0;
ULONGLONG DelayCounter = 0;
PSPELL pOldSong = 0;

VOID ClearExcluded()
{
	while(pExcluded)
	{
		PEXCLUDED pNext=pExcluded->pNext;
		delete pExcluded;
		pExcluded=pNext;
	}
}

VOID AddElement(PCHAR szLine)
{
	PEXCLUDED pElement=new EXCLUDED;
	pElement->pNext=pExcluded;
	pExcluded=pElement;
	strcpy_s(pElement->Song,szLine);
	DebugSpew("New element '%s'",pElement->Song);
}

VOID LoadINI()
{
   char ElementList[MAX_STRING*10] = {0};
   char szTemp[MAX_STRING];
   ClearExcluded();
   for (int i=0;InstrumentList[i]!=NULL;i++) {
      GetPrivateProfileString("SETTINGS",InstrumentList[i],"DISABLED",szTemp,MAX_STRING,INIFileName);
      if(!strcmp(szTemp,"DISABLED")){
         WriteChatf("%s %s",InstrumentList[i],szTemp);
         InstrumentSettings[i].Enabled=false;
      } else {
         strcpy_s(InstrumentSettings[i].Command,szTemp);
         InstrumentSettings[i].Enabled=true;
      }
      WritePrivateProfileString("Settings",InstrumentList[i],szTemp,INIFileName);
   }
   MeleeDelay = GetPrivateProfileInt("SETTINGS","DELAY",21,INIFileName);
   sprintf_s(szTemp, "%d", MeleeDelay);
   WritePrivateProfileString("Settings","Delay",szTemp,INIFileName);

   CHAR szBuffer[MAX_STRING] = {0};
   ExcludeCount=0;

   if (GetPrivateProfileString("Exclude",NULL,"",ElementList,MAX_STRING*10,INIFileName)) {
      PCHAR pElementList = ElementList;
      while (pElementList[0]!=0) {
         GetPrivateProfileString("Exclude",pElementList,"",szBuffer,MAX_STRING,INIFileName);
         if (szBuffer[0]!=0) {
            AddElement(szBuffer);
            ExcludeCount++;
         }
         pElementList+=strlen(pElementList)+1;
      }
   }
}

VOID BardSwapCommand(PSPAWNINFO pChar, PCHAR szLine)
{
	char szTemp[MAX_STRING];
	GetArg(szTemp,szLine,1);
	if (!strlen(szTemp)) {
		if (bSwapEnabled) {
			WriteChatColor("MQ2BardSwap::Swapping OFF");
			bSwapEnabled=false;
			return;
		}
		if (GetCharInfo()) {
			sprintf_s(INIFileName,"%s\\MQ2BardSwap_%s_%s.ini", gPathConfig, pLocalPC->Name, GetServerShortName());
			LoadINI();
		}
		WriteChatColor("MQ2BardSwap::Swapping ON");
		bSwapEnabled=true;
	}
	if(!_strnicmp(szTemp,"melee",5)) {
		if (bMeleeSwap) {
			WriteChatColor("MQ2BardSwap::Melee-Swapping OFF");
			bMeleeSwap=false;
			return;
		}
		WriteChatColor("MQ2BardSwap::Melee-Swapping ON");
		bMeleeSwap=true;
	}
}

class MQ2BardSwapType *pBardSwapType=0;

class MQ2BardSwapType : public MQ2Type
{
public:
	enum BardSwapMembers
	{
		Swapping,
		Excluded,
		MeleeSwap,
		Delay,
		CurrentSwap,
	};

   MQ2BardSwapType():MQ2Type("swap")
   {
      TypeMember(Swapping);
      TypeMember(Excluded);
      TypeMember(MeleeSwap);
      TypeMember(Delay);
      TypeMember(CurrentSwap);
   }

   virtual bool GetMember(MQVarPtr VarPtr, const char* Member, char* Index, MQTypeVar &Dest) override
   {
      MQTypeMember* pMember=MQ2BardSwapType::FindMember(Member);
      if (!pMember)
         return false;
      switch((BardSwapMembers)pMember->ID) {
         case Swapping:
            Dest.DWord=bSwapEnabled;
            Dest.Type=mq::datatypes::pBoolType;
            return true;
         case Excluded:
            Dest.DWord=bExcluded;
            Dest.Type=mq::datatypes::pBoolType;
            return true;
         case MeleeSwap:
            Dest.DWord=bMeleeSwap;
            Dest.Type=mq::datatypes::pBoolType;
            return true;
         case Delay:
            Dest.Int=MeleeDelay;
            Dest.Type=mq::datatypes::pIntType;
            return true;
         case CurrentSwap:
            strcpy_s(DataTypeTemp, InstrumentList[iCurrentSwap]);
            Dest.Ptr=DataTypeTemp;
            Dest.Type=mq::datatypes::pStringType;
            return true;
      }
      return false;
   }

   bool ToString(MQVarPtr VarPtr, PCHAR Destination) override
   {
      if (bSwapEnabled)
         strcpy_s(Destination, MAX_STRING, "TRUE");
      else
         strcpy_s(Destination, MAX_STRING, "FALSE");
      return true;
   }
};

bool dataBardSwap(const char* szName, MQTypeVar &Dest)
{
   Dest.DWord=1;
   Dest.Type=pBardSwapType;
   return true;
}

PLUGIN_API void InitializePlugin()
{
   DebugSpewAlways("Initializing MQ2BardSwap");
   AddCommand("/bardswap",BardSwapCommand);
   AddMQ2Data("BardSwap",dataBardSwap);

   pBardSwapType = new MQ2BardSwapType;

}

PLUGIN_API void ShutdownPlugin()
{
   DebugSpewAlways("Shutting down MQ2BardSwap");
   RemoveCommand("/bardswap");
   RemoveMQ2Data("BardSwap");
   ClearExcluded();
   delete pBardSwapType;
}

PLUGIN_API void OnPulse()
{
	if (!bSwapEnabled || GetGameState() !=GAMESTATE_INGAME || GetCharInfo()->standstate != STANDSTATE_STAND)
		return;

	PSPELL pCurrentSong;
	PCHARINFO pCharInfo = GetCharInfo();

	pCurrentSong=GetSpellByID(pCharInfo->pSpawn->CastingData.SpellID);
	if (pCurrentSong!=pOldSong) {
		// Swap in weapons if not already held
		if (bMeleeSwap && iCurrentSwap!=5) {
			EzCommand(InstrumentSettings[5].Command);
			iCurrentSwap=SwapTo=5;
		}
		bExcluded=false;
		pOldSong=pCurrentSong;
		for (int i=0;SongSkills[i]!=NULL;i++) {
			if (!pCurrentSong)
				break;
			if (!strcmp(szSkills[pCurrentSong->Skill],SongSkills[i])) {
				if (ExcludeCount){
					PEXCLUDED pElement=pExcluded;
					for (int j=0;j<ExcludeCount;j++) {
						if (!strcmp(pCurrentSong->Name,pElement->Song)) {
							bExcluded=true;
							break;
						}
						pElement=pElement->pNext;
					}
				}
				if (InstrumentSettings[i].Enabled && !bExcluded) {
					SwapTo=i;
					DelayCounter=GetTickCount64()+((bMeleeSwap?MeleeDelay:0)*100);
				} else if (bMeleeSwap) SwapTo=5;
				break;
			}
		}
	}

	if (DelayCounter<=::GetTickCount64() && SwapTo!=iCurrentSwap) {
		EzCommand(InstrumentSettings[SwapTo].Command);
		DelayCounter=0;
		iCurrentSwap=SwapTo;
	}
}
