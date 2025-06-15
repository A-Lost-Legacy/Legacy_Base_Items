modded class MissionServer extends MissionBase {
	override void OnInit() {
		super.OnInit();
		Print("[Legacy Base Storage Mod] OnInit");
		GetLegacyBaseStorageConfig();
		GetRPCManager().AddRPC( "LegacyBaseStorageMod", "RPCLegacyBaseStorageMod", this, SingeplayerExecutionType.Both );
	}
	void RPCLegacyBaseStorageMod( CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target ) {
		PlayerIdentity RequestedBy = PlayerIdentity.Cast(sender);
		if (RequestedBy) {
			GetRPCManager().SendRPC("LegacyBaseStorageMod", "RPCLegacyBaseStorageMod", new Param1< LegacyBaseStorageConfig >( GetLegacyBaseStorageConfig() ), true, RequestedBy);
		}
	}
}

