modded class MissionServer extends MissionBase
{
	void ~MissionServer() {
	}

	void MissionServer()
	{
		Print("Legacy_Base_Storage mod has started !");
		GetLegacy_Base_StorageLogger().LogDebug("Legacy_Base_Storage mod has started!");
	}
};
