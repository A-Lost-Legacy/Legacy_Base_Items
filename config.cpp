
class CfgPatches
{
	class LegacyBuilding_Scripts
	{
        requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Scripts","DZ_Sounds_Effects","DZ_Characters","DZ_Gear_Tools"};
	};
};

class CfgAddons
{
	class PreloadBanks{};
	class PreloadAddons
	{
		class DayZ
		{
			list[] = {"DZ_Data","DZ_Scripts","DZ_UI","DZ_UIFonts","DZ_Sounds_Effects"};
		};
	};
};

class CfgMods 
{
	class LegacyBuilding
	{
		name = "Legacy_Base_Storage";
		dir = "Legacy_Base_Storage";
		creditsJson = "Legacy_Base_Storage/Scripts/Credits.json";
		inputs = "Legacy_Base_Storage/Scripts/Inputs.xml";
		type = "mod";

		dependencies[] =
		{
			"Game", "World", "Mission"
		};
		class defs
		{
			// class imageSets			  {files[]= {"LegacyPack/GUI/imagesets/CUI.imageset"};};
			// class engineScriptModule  {files[]= {"Modular-Building/scripts/1_Core"};};
			class gameScriptModule 	  {files[]= {"Legacy_Base_Storage/scripts/Common","Legacy_Base_Storage/scripts/3_Game"};};
			class worldScriptModule	  {files[]= {"Legacy_Base_Storage/scripts/Common","Legacy_Base_Storage/scripts/4_World"};};
			class missionScriptModule {files[]= {"Legacy_Base_Storage/scripts/Common","Legacy_Base_Storage/scripts/5_Mission"};};
		};
	};	
};
