// Patrol 1 = Hrabice Airport South
ref array<vector> patrol_1  = {"2123.32 268.742 11326.2", "2123.32 268.742 11326.2", "2015.13 268.742 11532.4", "2019.83 268.742 11621.1", "2140.48 268.742 11603.5"};

// If you add another patrol array, add it to this list
ref array<array<vector>> patrol_list = {patrol_1};

// IMPORTANT: If you add an entry to the above list, pick the loadout for it by adding the loadout filename to this list
ref array<string> patrol_loadouts = {"FSCLoadout.json"};

/// Array for ammount of ai per patrol, IMPORTANT: same as patrol_loadoats if you add an entry to the patrol_list add an entry to this array too!
/// You can either either use MIN_NUMBER_PER_PATROL, a fixed value "8" or RandomAIAmmount()
/// Alternitively if you give RandomAIAmmount() a min and max value it will use those instead of the values set below,
/// this is useful when you wish to choose per mission/area EG: RandomAIAmmount(10,20)
ref array<int> patrol_aiAmmount = {RandomAIAmmount(5, 10)};

// you may change these quantities
const int MIN_NUMBER_PER_PATROL = 2;// Min Number of AI per patrol
const int MAX_NUMBER_PER_PATROL = 8;// Max Number of AI per patrol
const int MAXR = 800;				// This is the main spawn radius- how close a player needs to be to spawn them in.
const int MINR = 250;				// If a player is this close to the patrol start point, it is too close for them to spawn
const int DESPAWNR = 1000;			// If all players are this far away, they despawn.
const int RESPAWN_SECONDS = 300;	// The amount of seconds before a new patrol will spawn, after they both die

class CustomPatrol : eAIDynamicPatrol {
	override void OnPatrolSpawn(eAIGroup patrol) {
		// Uncomment this line to change the faction of the patrol from Raiders (default)
		// eAIFactionGuards for example is a faction which only kills players who have their weapons out
		// patrol.SetFaction(new eAIFactionGuards());
		
		// Uncomment this line to slow down or speed up the patrol (1.0 to 3.0)
		// patrol.SetSpeedLimit(1.0);
	}
	override void OnUnitSpawn(eAIBase unit) {
		// Uncomment this to give the AI unlimited magazines (new one is added on reload)
		// unit.SetUnlimitedMags(true);
		
		// You can also do anything you would do in the StartingEquipSetup() for players here
		
		// These lines will add attachments the same way you would for a player. However, the AI must have the M4A1 class in the Loadout.json file already for it to work.
		//Weapon_Base weapon = Weapon_Base.Cast(unit.GetItemInHands());
		//weapon.GetInventory().CreateAttachment("M4_PlasticHndgrd");
		//weapon.GetInventory().CreateAttachment("M4_OEBttstck");
		//weapon.GetInventory().CreateAttachment("M4_CarryHandleOptic");
	}
};

autoptr array<autoptr eAIDynamicPatrol> patrols = {};

void InitDynamicPatrols() {
	for (int i = 0; i < patrol_list.Count(); i++) {
		string loadout = "SoldierLoadout.json"; // default
		if (i < patrol_loadouts.Count()) loadout = patrol_loadouts[i];
		autoptr eAIDynamicPatrol pat = new eAIDynamicPatrol(patrol_list[i][0], patrol_list[i], loadout, patrol_aiAmmount[i], MINR, MAXR, DESPAWNR, RESPAWN_SECONDS);
		patrols.Insert(pat);
		pat.UpdateTriggers();
	}
}

void SpawnSentry(vector pos, string loadout = "SoldierLoadout.json") {
	eAIGame game = MissionServer.Cast(GetGame().GetMission()).GetEAIGame();
	eAIBase ai = game.SpawnAI_Sentry(pos, loadout);
}

int RandomAIAmmount() 
{
	return Math.RandomInt(MIN_NUMBER_PER_PATROL, MAX_NUMBER_PER_PATROL + 1);
}

int RandomAIAmmount(int a, int b) 
{
	return Math.RandomInt(a, b + 1);
}

modded class CustomMission
{
	void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		m_eaiGame.GetGroupByLeader(player);
		super.StartingEquipSetup(player, clothesChosen);
	}
};