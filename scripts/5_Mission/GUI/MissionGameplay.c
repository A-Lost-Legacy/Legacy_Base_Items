modded class MissionGameplay extends MissionBase {
	void MissionGameplay() {
		GetRPCManager().AddRPC( "LegacyBaseStorageMod", "RPCLegacyBaseStorageMod", this, SingeplayerExecutionType.Both );
	}
	override void OnMissionStart() {
		super.OnMissionStart();
		Print("[Legacy Base Storage Mod] [Client] Requesting Settings From Server");
		GetRPCManager().SendRPC("LegacyBaseStorageMod", "RPCLegacyBaseStorageMod", new Param1< LegacyBaseStorageConfig >( NULL ), true, NULL);
	}
	void RPCLegacyBaseStorageMod( CallType type,  ParamsReadContext ctx, PlayerIdentity sender, Object target ) {
		Param1< LegacyBaseStorageConfig > data  
		if ( !ctx.Read( data ) ) return;
		m_LegacyBaseStorageConfig = data.param1;
		Print("[Legacy Base Storage Mod] [Client] Settings Received");
	}
}