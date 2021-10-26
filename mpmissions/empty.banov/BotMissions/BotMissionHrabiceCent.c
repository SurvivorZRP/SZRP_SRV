class BotMissionHrabiceCent: MissionBase
{
	
	void BotMissionHrabiceCent() { StartMissionAI(); }
	
	AIWorld world = GetGame().GetWorld().GetAIWorld();
	
	// Êîíôèãè áîòîâ
	vector BotSpawnPoint = "2026.72 268.742 11746.1";				// çàäàåì òî÷êó ñïàâíà áîòà	
	
	int m_botAcuracy = 3;											// Íàñòðîéêà ìåòêîñòè áîòà (÷åì âûøå ÷èñëî, òåì ÷àùå áîò ïðîìàçûâàåò)
	
	int BotSolderCountMin = 4;  										// íàçíà÷àåì ìèíèìàëüíîå êîëè÷åññòâî áîòîâ
	int BotSolderCountMax = 6;										// íàçíà÷àåì ìàêñèìàëüíîå êîëè÷åññòâî áîòîâ
	
	int botLootCountMin = 5; 											// íàçíà÷àåì ìèíèìàëüíîå êîëè÷åñòâî ëóòà ó áîòà
	int botLootCountMax = 15; 										// íàçíà÷àåì ìàêñèìàëüíîå êîëè÷åñòâî ëóòà ó áîòà
	
	float Zone_Radius = 1100;											// Ðàäèóñ òðèããåðà íà èãðîêà äëÿ ïîÿâëåíèÿ áîòîâ
	
	bool isUseCheckPoints = true;										// çàäàåì èñïîëüçóþòñÿ ëè ÷åêïîíèíòû true - èñïîëüçóþòñÿ, fslse - íå èñïîëüçóþòñÿ
	bool isBotKaratist = false;										// Çàäàåì áóäóò ëè áîòû ñ îðóæèåì èëè áóäóò äðàòñÿ êóëàêàìè, ïî óìîë÷àíèþ îíè ñ îðóæèåì, åñëè íóæíû áåç îãíåñòðåëà ïðîïèøè true
	bool onRespawnBot = true;											// Âêëþ÷åíèå èëè îòêëþ÷åíèå ðåñïàâíà áîòà (true - âêëþ÷åíî, fslse - âûêëþ÷åíî)
	bool canUseTrigger = true;										// Èñïîëüçîâàòü òðèããåð (true - âêëþ÷åíî, fslse - âûêëþ÷åíî), åñëè íå èñïîëüçóåòñÿ òðèããåð áîòû ñïàâíÿòñÿ ñðàçó ïîñëå çàïóñêà ñåðâåðà
	bool useKilFeed = true;											// Âêëþ÷åíèå èëè îòêëþ÷åíèå îïîâåùåíèÿ ïðè óáèéñòâå áîòà
	bool m_Frendly = false;											// Äðóæåëþáèå :) âêëþ÷åíèå èëè îòêëþ÷åíèå. Åñëè âêëþ÷åíî òî áîòû âàñ íå áóäóò àòàêîâàòü ïîêà âû íà íåãî íå íàïàäåòå, åñëè àòàêóåòå áîòà òî ñòàíåòå äëÿ âñåõ áîòîâ âðàãîì. 
	bool onVoice = false;												// Âêëþ÷åíèå èëè îòêëþ÷åíèå ãîëîñà áîòà (âêëþ÷åíèå ýòîãî ïàðàìåòðà âûçûâàåò áîëüøå íàãðóçêè íà ñåðâåð)
	int m_spawnBotRadius = 10;										// Ðàäèóñ ñïàâíà áîòîâ íà òåðèòîðèå, öåíòðîì òåðèòîðèè ÿâëÿåòñÿ êîîðäèíàòà óêàçàííàÿ â BotSpawnPoint
	int m_SpeedPatrol = 1;											// Óñòàíîâêà ñêîðîñòè ïåðåäâèæåíèÿ ïðè ïàòðóëèðîâàíèè (min = 1 max = 3)
	
	int m_TargetDist = 150;											// Çàäàåì ðàñòîÿíèå â ìåòðàõ íà êîòîðîì áîò âèäèò öåëü.
	
	bool canBotSpawned = true;										// Íå èçìåíÿòü!!!!!!!
	
	// ------------------------------- êîíåö êîíôèãà  ------------------------------------------ //
	
	
	//Version 1.0 090321
	ref TStringArray Shirt = {"MSFC_EMR_JacketTwo", "MSFC_EMR_PCU5Jacket", "MSFC_EMR_GorkaJacketFlag"};
	ref TStringArray Jeans = {"MSFC_EMR_CargoPants", "MSFC_EMR_GorkaPants", "MSFC_G3Pants_EMR"};
	ref TStringArray Shoes = {"MSFC_EMR_Boots", "CombatBoots_Beige", "CombatBoots_Black", "CombatBoots_Brown"};
	ref TStringArray BackPack = {"MSFC_EMR_AssaultBag", "MSFC_EMR_Tortila", "MSFC_EMR_Mountain"};
	ref TStringArray Vest = {"HighCapacityVest_Black", "HighCapacityVest_Olive", "MSFC_SmershVestEMR", "MSFC_EMR_PlateVest", "MSFC_6B45_Vest_EMR"};
	ref TStringArray Helm = {"MSFC_6B47_Cover_EMR", "MSFC_EMR_Cap", "MSFC_OPS_Core_EMR"};
	ref TStringArray Gloves = {"MSFC_EMR_Gloves", "OMNOGloves_Brown", "SurgicalGloves_Blue"};
	ref TStringArray OtherEquip = {};
	
	ref TStringArray RandomLoot = {"Apple", "Banana", "PeachesCan", "SardinesCan", "TacticalBaconCan", "Crackers", "SodaCan_Cola", "SodaCan_Kvass", "Canteen", "Vodka", "CigarettePack_Chernamorka", "BandageDressing", "BloodTestKit", "TetracyclineAntibiotics", "PainkillerTablets", "Morphine", "Rice", "Rope", "Screwdriver", "AmmoBox_545x39_20Rnd", "AmmoBox_9x19_25rnd", "AmmoBox_45ACP_25rnd", "AmmoBox_556x45_20Rnd", "MassAmmoBox_556x45_10Rnd", "AmmoBox_762x39_20Rnd", "AmmoBox_308Win_20Rnd", "TTC_AmmoBox_300blk_20rnd", "TraderPlus_Money_Dollar1", "TraderPlus_Money_Dollar2", "TraderPlus_Money_Ruble5000", "TraderPlus_Money_Ruble2000", "TraderPlus_Money_Ruble1000", "CP_CannabisSeedsPackBlue", "CP_CannabisSeedsPackSkunk", "CP_JointSkunk", "CP_JointKush", "CP_RollingPapers", "CP_Cigarette"};  //Äîáàâëÿåì â ìàñèâ ëþáîé ëóò, êîëè÷åñòâî íå îãðàíè÷åíî
	ref TStringArray MeleeWeap = {"WoodAxe", "FirefighterAxe", "Shovel", "Pickaxe"}; 														//Äîáàâëÿåì õîëîäíîå îðóæèå
	
	// -------------------------------- êîíåö ìàññèâîâ ëóòà  -------------------------------------------------------//

	EntityAI itemEnt;				// Íå èçìåíÿòü!!!!

	// Ôóíêöèÿ ñîçäàíèÿ ÷åêïîèíòîâ (ïðîïèñûâàåì ÷åêïîèíòû òóò)
	void AddCeckPoint(SurvivorBotBase m_BotSolder)
	{
		m_BotSolder.SetUseCheckpoint(); // Ýòó ñòðîêó íå òðîãàåì!
		
		m_BotSolder.AddCheckpoint("2026.72 268.742 11746.1");
		m_BotSolder.AddCheckpoint("2032.46 268.742 11886.6");
		m_BotSolder.AddCheckpoint("2151.49 268.742 11879.0");
		m_BotSolder.AddCheckpoint("2134.39 268.742 11742.6");
	
	}
	// ---------------------------------- Êîíåö ôóíêöèè ñîçäàíèÿ ÷åêïîèíòîâ  -------------------------------------- /	
	

	ref array<SurvivorBotBase> m_BotMass = new array<SurvivorBotBase>;
	ref array<SurvivorBotBase> m_PlaersZoneArray = new array<SurvivorBotBase>;
	
	// Ôóíêöèÿ ñîçäàíèÿ îðóæèÿ äëÿ áîòà (òóò ìîæíî äîáàâèòü 7 âìäîâ îðóæèÿ, âïèñûâàåì ïî ñâîåìó óñìîòðåíèþ)
	void createWeapFromBot(SurvivorBotBase m_BotSolder)
	{
		int randomWeapon = Math.RandomInt(1, 7);
			
		switch( randomWeapon )
		{	
			//Version 1.0 090321
			case 1: 
			{
				m_BotSolder.AddWeapon("M4A1"); 				
				m_BotSolder.AddWeaponAtt("M4_RISHndgrd");
				m_BotSolder.AddWeaponAtt("M4_MPBttstck");
				m_BotSolder.AddWeaponAtt("ACOGOptic");
				m_BotSolder.AddMagazine("Mag_STANAG_60Rnd");
				break;
			}
				
			case 2: 
			{
				m_BotSolder.AddWeapon("AKM");
				m_BotSolder.AddWeaponAtt("AK_WoodBttstck");
				m_BotSolder.AddWeaponAtt("AK_WoodHndgrd");
				m_BotSolder.AddMagazine("Mag_AKM_Drum75Rnd");
				break;
			}
				
			case 3: 
			{
				m_BotSolder.AddWeapon("TTC_MPX");
				m_BotSolder.AddWeaponAtt("TTC_MPXMCX1_Bttstck2");
				m_BotSolder.AddMagazine("TTC_MPX_Mag_60rnd");
				break;
			}
				
			case 4: 
			{
				m_BotSolder.AddWeapon("TTC_AKMod_Multi");
				m_BotSolder.AddWeaponAtt("TTC_AKMod_Multi_Hndguard");
				m_BotSolder.AddWeaponAtt("TTC_AKMod_Multi_bttstk");
				m_BotSolder.AddWeaponAtt("ACOGOptic");
				m_BotSolder.AddWeaponAtt("AK_Suppressor");
				m_BotSolder.AddMagazine("Mag_AKM_Drum75Rnd");
				break;
			}
				
			case 5: 
			{
				m_BotSolder.AddWeapon("ASVAL"); 		
				m_BotSolder.AddWeaponAtt("TTC_Razor");	
				m_BotSolder.AddMagazine("Mag_VAL_20Rnd");
				break;
			}
				
			case 6: 
			{
				m_BotSolder.AddWeapon("TTC_MP7A1");
				m_BotSolder.AddWeaponAtt("TTC_PistolSuppressor");
				m_BotSolder.AddMagazine("TTC_MP7A1_Mag_40rnd");
				break;
			}
				
			case 7: 
			{
				m_BotSolder.AddWeapon("TTC_KAC");
				m_BotSolder.AddWeaponAtt("TTC_HAMR");
				m_BotSolder.AddMagazine("Mag_STANAG_60Rnd");
				break;
			}
			// End Version 1.0
		}		
	}
	// ----------------------------- Êîíåö ôóíêöèè ñîçäàíèÿ îðóæèÿ ------------------------------------- //
	
	// Ôóíêöèÿ ñïàâíà áîòà (òóò íè÷åãî íå ìåíÿåì!!!)
	void createBotUnit()
	{
		vector Navmesh;
		vector botSpPos;
		private SurvivorBotBase m_BotSolder;
		
		ref TStringArray m_BotBody = { "BotM_Mirek", "BotM_Rolf", "BotM_Quinn", "BotM_Peter", "BotM_Oliver" };
		
		PGFilter m_pgFilterNav = new PGFilter();
		m_pgFilterNav.SetFlags(PGPolyFlags.WALK, PGPolyFlags.INSIDE, 0);
		
		float bspX = BotSpawnPoint[0];
		float bspY = BotSpawnPoint[2];
				
		if (isUseCheckPoints)
			botSpPos = Vector(bspX + Math.RandomInt(-7, 7), BotSpawnPoint[1], bspY + Math.RandomInt(-7, 7));
		else
			botSpPos = Vector(bspX + Math.RandomInt(-m_spawnBotRadius, m_spawnBotRadius), BotSpawnPoint[1], bspY + Math.RandomInt(-m_spawnBotRadius, m_spawnBotRadius));
		
		bool IsNavmesh = world.SampleNavmeshPosition( botSpPos, 2, m_pgFilterNav, Navmesh );
		
		if (IsNavmesh)
			m_BotSolder = SurvivorBotBase.Cast(GetGame().CreatePlayer(null, m_BotBody.GetRandomElement(), Navmesh,  0, "NONE"));
		else
			m_BotSolder = SurvivorBotBase.Cast(GetGame().CreatePlayer(null, m_BotBody.GetRandomElement(), botSpPos,  0, "NONE"));
		

		m_BotSolder.GetInventory().CreateInInventory(Shirt.GetRandomElement());
		m_BotSolder.GetInventory().CreateInInventory(Jeans.GetRandomElement());
		m_BotSolder.GetInventory().CreateInInventory(Shoes.GetRandomElement());
		m_BotSolder.GetInventory().CreateInInventory(BackPack.GetRandomElement());
		m_BotSolder.GetInventory().CreateInInventory(Vest.GetRandomElement());
		m_BotSolder.GetInventory().CreateInInventory(Helm.GetRandomElement());
		m_BotSolder.GetInventory().CreateInInventory(Gloves.GetRandomElement());			
		m_BotSolder.GetInventory().CreateInInventory(OtherEquip.GetRandomElement());
		
		if (isBotKaratist)
			m_BotSolder.GetHumanInventory().CreateInHands(MeleeWeap.GetRandomElement());
		else
			createWeapFromBot(m_BotSolder);
			
		int rndLootCnt = Math.RandomInt(botLootCountMin, botLootCountMax);
			
		for (int i = 0; i < rndLootCnt; i++)
		{
			itemEnt = m_BotSolder.GetInventory().CreateInInventory(RandomLoot.GetRandomElement());
			if (itemEnt)
			{
				int rndHlt = Math.RandomInt(55,100);
				itemEnt.SetHealth("","",rndHlt);
			}
		}

		m_BotSolder.SetAcuracy(m_botAcuracy);
		m_BotSolder.SetDistance(m_TargetDist);
		m_BotSolder.SetUseVoice(onVoice);
		m_BotSolder.SetUseKillFeed(useKilFeed);
		m_BotSolder.SetFrendly(m_Frendly);
		m_BotSolder.SetSpeedPatrol(m_SpeedPatrol);
		
		
		if (isUseCheckPoints) 
			AddCeckPoint(m_BotSolder);
	
		
		m_BotMass.Insert(m_BotSolder);
	}
	// ----------------------------- Êîíåö ôóíêöèè ñïàâíà áîòà ------------------------------------- //
	
	// ----------------------------- Ôóíêöèÿ ðåñïàâíà áîòîâ ----------------------------------------//
	private void respawnBotUnit()
	{
		ref array<Man> players = new array<Man>;
		GetGame().GetPlayers( players );
		SurvivorBotBase Bot_Ar;
		vector posB;
		bool m_botRemoved = false;
		float distB;
		int m_countBot = m_BotMass.Count();
		int plaersZoneCount = -1;
		m_PlaersZoneArray.Clear();
		if (canBotSpawned)
		{	
			for ( int u = 0; u < players.Count(); u++ )
			{
					
				PlayerBase player;
				Class.CastTo(player, players.Get(u));
				vector pos = player.GetPosition();
				float dist = vector.Distance( pos, BotSpawnPoint );
				
				if ( dist < Zone_Radius && player.IsAlive() )
				{
					m_PlaersZoneArray.Insert(player);
				//	return;
				}
			}	
			Print("Players count in zone bots Tisy = " + m_PlaersZoneArray.Count());
			if (m_PlaersZoneArray.Count() == 0)
			{
					
				for ( int a = 0; a < m_countBot; a++ )
				{
					Bot_Ar = m_BotMass.Get(a);
					if (Bot_Ar)
					{
						if (!Bot_Ar.IsAlive())
						{
							posB = Bot_Ar.GetPosition();
							distB = vector.Distance( posB, BotSpawnPoint );
							if (distB < Zone_Radius) 
							{
								m_BotMass.Remove( a );	
							}
							
							if (m_BotMass.Count() == 0)
								m_botRemoved = true;
						}
						else
						{
							if (distB < Zone_Radius) 
							{
								m_BotMass.Remove( a );	
								GetGame().ObjectDelete( Bot_Ar );
							}
							
							if (m_BotMass.Count() == 0)
								m_botRemoved = true;
						}
					}
				}
					
				if (m_botRemoved && m_PlaersZoneArray.Count() == 0)	
				{
					StartMissionAI();
					GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(respawnBotUnit);
					m_botRemoved = false;
				}
			}			
		}			
	}
	// ----------------------------- Êîíåö ôóíêöèè ----------------------------------------//
	

	
	
	// Ôóíêöèÿ ñïàâíà ãðóïïû áîòîâ
	int delaySpawn = 0;
	void spawnBotGroup()
	{
		int rndBotGrpCnt = Math.RandomInt(BotSolderCountMin, BotSolderCountMax);
		Print("Bots spawned! Count " + rndBotGrpCnt);
		for (int a = 0; a < rndBotGrpCnt; a++)
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(createBotUnit, 500 + delaySpawn);
			delaySpawn +=1000;
		}	
	}
	// --------------------------------------- Êîíåö ôóíêöèè ñïàâíà ãðóïïû  --------------------------------------- //
	
	// Ôóíêöèÿ òðèããåðà íà èãðîêà
	void TriggerPlayers()
	{  
		ref array<Man> players = new array<Man>;
		GetGame().GetPlayers( players );
		delaySpawn = 0;		
		if (canBotSpawned && IsGoodSrvFps())
		{	
			for ( int u = 0; u < players.Count(); u++ )
			{
					
				PlayerBase player;
				Class.CastTo(player, players.Get(u));
				vector pos = player.GetPosition();
				float dist = vector.Distance( pos, BotSpawnPoint );
				
				if ( dist < Zone_Radius && !player.IsBot() ) 
				{
					spawnBotGroup();
					GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(TriggerPlayers);	

					if (onRespawnBot)
						GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(respawnBotUnit, 60000, true);					
				} 
			}
		}
	} 
	// --------------------------------------- Êîíåö ôóíêöèè òðèããåðà  --------------------------------------- //
	
	// Ýòó ôóíêöèþ âûçûâàåì â initBotMissions.c	
	void StartMissionAI()
	{
		Print("Start mission bot");
		if (canUseTrigger)
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(TriggerPlayers, 5000, true);			
		}
		else if (IsGoodSrvFps())
		{
			spawnBotGroup();
		}
	}
	
	bool IsGoodSrvFps()
	{
		float TestFpsSrv = GetGame().GetFps();
		
		if (TestFpsSrv < 2)
		{
			return true;
		}
		else
		{
			Print("Server FPS low! FPS = " + TestFpsSrv + " Bots not respawned!");
			return false;
		}			
	}	
}