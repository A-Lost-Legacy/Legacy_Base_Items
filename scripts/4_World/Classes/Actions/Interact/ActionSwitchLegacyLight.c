class ActionSwitchLegacyLight: ActionInteractBase
{

	void ActionSwitchLegacyLight()
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

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (!target)
			return false;

		Legacy_Storage_Base storage = Legacy_Storage_Base.Cast(target.GetObject());
		if (!storage)
			return false;

		string selection = storage.GetActionComponentName(target.GetComponentIndex());
		if (!selection.Contains("lightswitch") && !selection.Contains("light_switch_3_button"))
			return false;

		//! Check energy system
		if (!storage.HasEnergyManager() || !storage.GetCompEM().CanSwitchOn())
			return false;

		if ( storage.IsLightOn() )
		{
			m_Text = "Light Off";
			return true;
		}
		
		else
		{
			m_Text = "Light On";
			return true;
		}
		
		return true;
	}

	override void OnStartServer(ActionData action_data)
	{
		Legacy_Storage_Base storage = Legacy_Storage_Base.Cast(action_data.m_Target.GetObject());
		PlayerBase player = PlayerBase.Cast(action_data.m_Player);

		if (!storage || !player)
			return;

		//! Final safety: check EM capability again
		if (!storage.HasEnergyManager() || !storage.GetCompEM().CanSwitchOn())
			return;

		bool turnOff = storage.IsLightOn();

		if (turnOff)
			storage.SwitchLigthOff();
		else
			storage.SwitchLigthOn();

		//! Optional logging
		
		if (GetLegacyBaseStorageConfig().EnableMLightLogging) {
			string stateText;
			if (turnOff) {
				stateText = "Light Off";
			} else {
				stateText = "Light On";
			}
			GetLegacy_Base_StorageLogger().LogInfo("[Legacy_Base_Storage][Main Light Switch]: " +player.GetIdentity().GetName() + " (" +player.GetIdentity().GetPlainId() + ") " +stateText + " " +storage.GetType() + " at " +storage.GetPosition().ToString());
		}
	}	
};

// class ActionSwitchLegacyLight: ActionInteractBase
// {

// 	void ActionSwitchLegacyLight()
// 	{
// 		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
// 		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
// 		m_HUDCursorIcon = CursorIcons.CloseDoors;
// 	}

// 	override void CreateConditionComponents()  
// 	{
// 		m_ConditionItem = new CCINone;
// 		m_ConditionTarget = new CCTNone;
// 	}

// 	override string GetText()
// 	{
// 		return m_Text;
// 	}

// 	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
// 	{
// 		if ( !target )
// 			return false;

// 		Legacy_Storage_Base storage = Legacy_Storage_Base.Cast(target.GetObject());
		
// 		if ( !storage )
// 			return false;

// 		string selection = storage.GetActionComponentName(target.GetComponentIndex());
		
// 		if (!selection.Contains("lightswitch") && !selection.Contains("light_switch_3_button"))
// 			return false;
		
// 		if ( storage.IsLightOn() )
// 		{
// 			m_Text = "Light Off";
// 			return true;
// 		}
		
// 		else
// 		{
// 			m_Text = "Light On";
// 			return true;
// 		}
			
// 		return false;
// 	}

// 	override void OnStartServer(ActionData action_data) {
// 		Legacy_Storage_Base storage = Legacy_Storage_Base.Cast(action_data.m_Target.GetObject());
// 		PlayerBase player = PlayerBase.Cast(action_data.m_Player);
	
// 		if (storage && player) {
// 			bool turnOff = storage.IsLightOn();
	
// 			if (turnOff) {
// 				storage.SwitchLigthOff();
// 			} else {
// 				storage.SwitchLigthOn();
// 			}
	

// 			if (GetLegacyBaseStorageConfig().EnableMLightLogging) {
// 				string stateText;
// 				if (turnOff) {
// 					stateText = "Light Off";
// 				} else {
// 					stateText = "Light On";
// 				}
	
// 				GetLegacy_Base_StorageLogger().LogInfo("[Legacy_Base_Storage][Main Light Switch]: " +player.GetIdentity().GetName() + " (" +player.GetIdentity().GetPlainId() + ") " +stateText + " " +storage.GetType() + " at " +storage.GetPosition().ToString());
// 			}
// 		}
// 	}
	
// };