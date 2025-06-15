class LegacyBaseStorageConfig {
    static const string LegacyBaseStorageConfigDIR = "$profile:\\Legacy_Pack\\";
	static const string LegacyBaseStorageConfigPATH = "$profile:\\Legacy_Pack\\Legacy_Base_Storage.json";
    string FileUpdateEnable = "1";
    
    bool EnabledebugLogging = true;                    // enables debug logging for the mod, this will log all actions and events to the logs (please note in the log config it needs to be set to 0 for this to work)
	bool EnableerrorLogging = true;                   // enables error logging for the mod, this will log all errors to the logs (please note in the log config it needs to be set to 0 for this to work)

    bool EnableCraftLogging = true;                 // enables crafting logging for the mod, this will log all crafting actions to the logs (please note in the log config it needs to be set to 0 for this to work)
    bool EnablePlacementLogging = true;            // enables placement logging for the mod, this will log all placement actions to the logs (please note in the log config it needs to be set to 0 for this to work)
    bool EnableDismantleLogging = true;           // enables dismantle logging for the mod, this will log all dismantle actions to the logs (please note in the log config it needs to be set to 0 for this to work)
    bool EnableOpenCloseLogging = true;          // enables open close logging for the mod, this will log all open close actions to the logs (please note in the log config it needs to be set to 0 for this to work)

    bool EnableMLightLogging = true;           // 1 = Enable Main Light Logging, 0 = Disable Main Light Logging
    bool EnableSLightLogging = true;          // 1 = Enable Secondary Light Logging, 0 = Disable Secondary Light Logging

    int ProxyMode = 1;                         // 0 = Hide Proxies | 1 = Hide Proxies when closed | 2 = Don't Hide proxies (please note it will overide settings bellow for the other proxy settings when set to 0 set to 3 for extra settings to take effect)
    int ExtraDetail = 1;                      // 0 = Hide Extra Detials | 1 = Hide Extra Details when closed | 2 = Don't hide Extra Detail  (please note that 1 will only work for lod one as extra details are not pressent in anyother lods)
    int proxyImportant= 1;                   // 0 = Hide Proxies | 1 = Hide Proxies when closed | 2 = Don't Hide proxies (Weapons)
    int proxyimportant2 = 1;                // 0 = Hide Proxies | 1 = Hide Proxies when closed | 2 = Don't Hide proxies (Ammo and Magazines recomended 0 for high pop servers )
    int proxyGeneral = 1;                  // 0 = Hide Proxies | 1 = Hide Proxies when closed | 2 = Don't Hide proxies 
    int proxyMisc = 1;                    // 0 = Hide Proxies | 1 = Hide Proxies when closed | 2 = Don't Hide proxies

    bool AutoCloseOnServerStart = true; // 1 = Enable Automatic Closing of Storages when the server boots up. 0 = disabled
    bool EnableAutoCloseStorageTimer = true; // 1 = Enables Automatic Closing of Storages Timer, after a storage is opened, after AutoCloseMinutes it will close. 0 = disabled
    int AutoCloseMinutes = 5; // Timer for EnableAutoCloseStorageTimer, no decimals allowed, 5 = 5 minutes, 5.5 = broken mod.
    float OpenCloseRange = 2.0; // How many meters away from looking at storage door to receive open / close action. s

    bool CanCraftKits = true; // enables crafting of all kits (please note this will overide the settings below for the other kit crafting settings when set to true)
    int CraftKitToolTime = 20; 
    
    bool CanDeCraftKits = true;
    string DeCraftKitText = "De-Craft Kit";
    string DeCraftKitTool = "Screwdriver";
    int DeCraftKitToolTime = 10;
    int DeCraftKitToolDamage = 10;

    bool CanDismantleStorage = true;
    string DismantleText = "Dismantle";
    string DismantleTool = "Screwdriver";
    int DismantleToolTime = 40;
    int DismantleToolDamage = 20;

    string HologramColor_R = "0.0";
    string HologramColor_G = "1.0";
    string HologramColor_B = "1.0";

    bool EnableAmmoBoxWhitelist = true;
    protected ref array<string> AmmoBoxWhitelist = {};

    bool EnableRefrigeratorWhitelist = true; 
    bool EnableRefrigeratorFoodPreserve = true;
    protected ref array<string> RefrigeratorWhitelist = {};

    bool EnableMedicalCabinetWhitelist = true;
    protected ref array<string> MedicalCabinetWhitelist = {};

    string Temp1 = "";
    string Legacy_Container_01CraftText = "Craft container 1 Kit";
    string Legacy_Container_01RecipeOne = "Nail";
    int Legacy_Container_01RecipeOneQty = 99;
    string Legacy_Container_01RecipeTwo = "MetalPlate";
    int Legacy_Container_01RecipeTwoQty = 2;
    
    string Temp2 = "";
    bool CanCraftcontainer2 = true;
    string Legacy_Container_02CraftText = "Craft container 2 Kit";
    string Legacy_Container_02RecipeOne = "Nail";
    int Legacy_Container_02RecipeOneQty = 99;
    string Legacy_Container_02RecipeTwo = "MetalPlate";
    int Legacy_Container_02RecipeTwoQty = 4;

    void Load() {
		if (GetGame().IsServer()) {
			if (FileExist(LegacyBaseStorageConfigPATH)) { 
				JsonFileLoader<LegacyBaseStorageConfig>.JsonLoadFile(LegacyBaseStorageConfigPATH, this);
				if (FileUpdateEnable == "1") {
					Save();
				}	
			} else { 
				Print("[Legacy Base Storage Mod] Loading default configuration...");
				MakeDirectory(LegacyBaseStorageConfigDIR);
                AmmoBoxWhitelist = {
                    "Box_Base",
                    "Ammunition_Base"
                };
                RefrigeratorWhitelist = {
                    "SodaCan_ColorBase",
                    "Bottle_Base",
                    "Edible_Base"
                };
                MedicalCabinetWhitelist = {
                    "DisinfectantSpray",
                    "DisinfectantAlcohol",
                    "BandageDressing",
                    "Rag",
                    "Heatpack",
                    "PurificationTablets",
                    "CharcoalTablets",
                    "PainkillerTablets",
                    "VitaminBottle",
                    "IodineTincture",
                    "TetracyclineAntibiotics",
                    "Epinephrine",
                    "Morphine",
                    "Syringe",
                    "ClearSyringe",
                    "BloodSyringe",
                    "InjectionVial",
                    "SalineBag",
                    "StartKitIV",
                    "SalineBagIV",
                    "BloodBagEmpty",
                    "BloodBagFull",
                    "BloodBagIV",
                    "BloodTestKit",
                    "Thermometer",
                    "AntiChemInjector",
                    "GasMask_Filter",
                    "ChelatingTablets"
                };
				Save();
			}
		} else {
			Print("[Legacy Base Storage Mod] Trying to load settings before they were received by the server.");
		}
	}
	void Save() {
		JsonFileLoader<LegacyBaseStorageConfig>.JsonSaveFile(LegacyBaseStorageConfigPATH, this);
	}
    array<string> GetAmmoBoxWhitelist() {
		return AmmoBoxWhitelist;
	}
    array<string> GetRefrigeratorWhitelist() {
		return RefrigeratorWhitelist;
	}
    array<string> GetMedicalWhitelist() {
		return MedicalCabinetWhitelist;
	}
}
static ref LegacyBaseStorageConfig m_LegacyBaseStorageConfig
static ref LegacyBaseStorageConfig GetLegacyBaseStorageConfig() {
	if (!m_LegacyBaseStorageConfig) {
		m_LegacyBaseStorageConfig = new LegacyBaseStorageConfig();
		m_LegacyBaseStorageConfig.Load();
	}
	return m_LegacyBaseStorageConfig;
}