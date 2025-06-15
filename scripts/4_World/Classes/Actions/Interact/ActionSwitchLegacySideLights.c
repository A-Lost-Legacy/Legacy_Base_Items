class ActionSwitchLegacySideLights: ActionInteractBase
{
	void ActionSwitchLegacySideLights()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_HUDCursorIcon = CursorIcons.CloseDoors;
	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNone;
	}

	override string GetText()
	{
		return m_Text;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( !target )
			return false;

		Legacy_Storage_Base storage = Legacy_Storage_Base.Cast(target.GetObject());
		
		if ( !storage )
			return false;

		string selection = storage.GetActionComponentName(target.GetComponentIndex());
		
		if (!selection.Contains("lightswitch") && !selection.Contains("light_switch_3_button"))
			return false;
		
		if ( storage.IssideLightOn() )
		{
			m_Text = "Side Lights Off";
			return true;
		}
		
		else
		{
			m_Text = "Side Lights On";
			return true;
		}
			
		return false;
	}

	override void OnStartServer(ActionData action_data) {
		Legacy_Storage_Base storage = Legacy_Storage_Base.Cast(action_data.m_Target.GetObject());
		PlayerBase player = PlayerBase.Cast(action_data.m_Player);
	
		if (storage && player) {
			bool turnOff = storage.IssideLightOn();
	
			if (turnOff) {
				storage.SwitchsideLigthOff();
			} else {
				storage.SwitchsideLigthOn();
			}
	

			if (GetLegacyBaseStorageConfig().EnableSLightLogging) {
				string stateText;
				if (turnOff) {
					stateText = "Light Off";
				} else {
					stateText = "Light On";
				}
	
				GetLegacy_Base_StorageLogger().LogInfo("[Legacy_Base_Storage][Side Light Switch]: " +player.GetIdentity().GetName() + " (" +player.GetIdentity().GetPlainId() + ") " +stateText + " " +storage.GetType() + " at " +storage.GetPosition().ToString());
			}
		}
	}
};