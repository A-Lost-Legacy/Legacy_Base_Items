class ActionLegacyCustomCloseOpen: ActionInteractBase {
	protected string opencloseState;

	void ActionLegacyCustomCloseOpen() {
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_HUDCursorIcon = CursorIcons.CloseDoors;
	}

	override void CreateConditionComponents() {
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNone;
	}

	override string GetText() {
		return opencloseState;
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
		Legacy_Storage_Base storage = Legacy_Storage_Base.Cast(target.GetObject());
		if (!storage) return false;

		string selection = target.GetObject().GetActionComponentName(target.GetComponentIndex(), "view");
		bool isInRange = IsInReach(player, target, GetLegacyBaseStorageConfig().OpenCloseRange);
		bool validSelection = selection.Contains("doors") || selection.Contains("coveraction") || selection.Contains("lid");

		if (!isInRange || !validSelection) return false;

		// Set open/close state based on type
		if (storage.IsOpen()) {
			opencloseState = "#close";
			if (storage.IsKindOf("Legacy_Coverable_Base")) opencloseState = "Cover";
			if (storage.IsKindOf("Legacy_Slidable_Base")) opencloseState = "Slide Shut";
		} else {
			opencloseState = "#open";
			if (storage.IsKindOf("Legacy_Coverable_Base")) opencloseState = "Uncover";
			if (storage.IsKindOf("Legacy_Slidable_Base")) opencloseState = "Slide Open";
		}

		// CodeLock Compatibility
		#ifdef CodeLock
		if (storage.IsCodeLocked() && !storage.IsOpen()) return false;
		#endif

		// RA_BaseBuilding Compatibility
		#ifdef RA_BaseBuilding_Scripts
		if (storage.IsCodeLocked(player.GetIdentity()) && !storage.IsOpen()) return false;
		#endif

		return true;
	}

	override void OnStartServer(ActionData action_data) {
		Legacy_Storage_Base storage = Legacy_Storage_Base.Cast(action_data.m_Target.GetObject());
		if (!storage) return;

		#ifdef RA_BaseBuilding_Scripts	
		PlayerBase player = PlayerBase.Cast(action_data.m_Player);
		if (storage.IsCodeLocked(player.GetIdentity())) return;
		#endif

		if (storage.IsOpen()) {
			storage.Close();
		} else {
			storage.Open();
		}
	}

	override void OnEndServer(ActionData action_data) {
		if (GetLegacyBaseStorageConfig().EnableOpenCloseLogging) {
			PlayerBase player = PlayerBase.Cast(action_data.m_Player);
			LogOpenAction(PlayerBase.Cast(action_data.m_Player), Legacy_Storage_Base.Cast(action_data.m_Target.GetObject()));
		}
	}
;
	void LogOpenAction(PlayerBase player, Legacy_Storage_Base storage) {
		if (!player || !storage) return;
		vector playerPos = player.GetPosition();
		GetLegacy_Base_StorageLogger().LogInfo("[Legacy_Base_Storage][Open/Close]: " + player.GetIdentity().GetName() +" (" + player.GetIdentity().GetPlainId() + ") " + opencloseState + " " + storage.GetType() + " at " + storage.GetPosition() + " | Player Position: " + playerPos.ToString());
	}
}
