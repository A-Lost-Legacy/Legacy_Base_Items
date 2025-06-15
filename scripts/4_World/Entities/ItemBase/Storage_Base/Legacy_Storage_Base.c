class Legacy_Storage_Base: Container_Base {
    protected string m_OpenSoundSet = "";
    protected string m_CloseSoundSet = "";

    protected bool m_IsLightOnServer;
	protected bool m_IsLightOnClient;

	protected bool m_IssideLightOnServer;
	protected bool m_IssideLightOnClient;
    protected EffectSound m_SoundLight;

    ref array<ScriptedLightBase> m_AreaLights;
    ref array<ScriptedLightBase> m_AreaSLights;

	ContainerMLight				m_ContainerMLight;
	ContainerSLight				m_ContainerSLight;

	protected const string LAMP_TEXTURE_ON	= "Legacy_Base_Storage\\BaseObjects\\Shared\\Lighting\\ceiling_on.rvmat";
	protected const string LAMP_TEXTURE_OFF	= "Legacy_Base_Storage\\BaseObjects\\Shared\\Lighting\\ceiling_off.rvmat";

	protected const string Side_LAMP_TEXTURE_ON	= "Legacy_Base_Storage\\BaseObjects\\Shared\\Lighting\\Side_on.rvmat";
	protected const string Side_LAMP_TEXTURE_OFF	= "Legacy_Base_Storage\\BaseObjects\\Shared\\Lighting\\Side_off.rvmat";

    // Solar not yet implimented 

    static const string LOOP_SOUND = "BLElectricLoop_SoundSet";
	static const string BATTERY_ATTACH_SOUND = "sparkplug_attach_SoundSet";
	static const string BATTERY_DETACH_SOUND = "sparkplug_detach_SoundSet";
	// static const string LEVER_ON_SOUND = "LegacyActivateSolarpanel_SoundSet";
	// static const string LEVER_OFF_SOUND = "LegacyDeactivateSolarpanel_SoundSet";

	// protected EffectSound m_PanelWorkingSound;
	protected EffectSound m_SoundTurnOn;
	protected EffectSound m_SoundTurnOff;

	ref Timer m_SoundLoopStartTimer;

	ItemBase m_BufferBattery; 
	bool m_IsWorking_Legacy;
	int m_BatteryEnergy0To100;
	protected float m_ChargeEnergyPerSecond;


    override void SetActions() {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] SetActions called");
        }
        super.SetActions();
		AddAction(ActionSwitchLegacyLight);
		AddAction(ActionSwitchLegacySideLights);
        
    }
    void ApplyAnimationFromConfig(string animName, int configValue)
    {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] ApplyAnimationFromConfig called. animName=" + animName + ", configValue=" + configValue);
        }
        int openPhase;
        int closedPhase;
    
        switch (configValue)
        {
            case 0:
                openPhase = 1;
                closedPhase = 1;
                break;
            case 1:
                openPhase = 0;
                closedPhase = 1;
                break;
            case 2:
                openPhase = 0;
                closedPhase = 0;
                break;
            default:
                openPhase = 1;
                closedPhase = 1;
                break;
        }
    
        if (IsOpen())
            SetAnimationPhase(animName, openPhase);
        else
            SetAnimationPhase(animName, closedPhase);
    }
    void ApplyProxyModeAnimation(string animName, int hideproxy)
    {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] ApplyProxyModeAnimation called. animName=" + animName + ", hideproxy=" + hideproxy);
        }
        int phase;

        switch (hideproxy)
        {
            case 0: // Always hide
                phase = 1;
                break;
            case 1: // Hide only when closed
                if (IsOpen())
                    phase = 0;
                else
                    phase = 1;
                break;
            case 2: // Never hide
                phase = 0;
                break;
            default:
                phase = 1;
                break;
        }

    SetAnimationPhase(animName, phase);
    }
    #ifndef SERVER
    BaseLight m_Light;
    #endif 
    override void DeferredInit() 
    {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] DeferredInit called");
        }		
		super.DeferredInit();
        #ifndef SERVER
        if (HasBaseLights()) {
            m_Light = BaseLight.Cast(ScriptedLightBase.CreateLight(BaseLight, "0 0 0"));
            if (m_Light)
                m_Light.AttachOnMemoryPoint(this, "light");
        }
        #endif        
    }
    void Legacy_Storage_Base() 
    {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] Legacy_Storage_Base constructor called");
        }
        RegisterNetSyncVariableBool( "m_IsLightOnServer" );
		RegisterNetSyncVariableBool( "m_IssideLightOnServer" );
        m_AreaLights = new array<ScriptedLightBase>();
        m_AreaSLights = new array<ScriptedLightBase>();
    }
    override void EEDelete(EntityAI parent) {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] EEDelete called");
        }
        super.EEDelete(parent);
        if ( !GetGame().IsDedicatedServer() )
		{
			if ( m_ContainerMLight )
				m_ContainerMLight.Destroy();

			if ( m_ContainerSLight )
				m_ContainerSLight.Destroy();
		}
		#ifndef SERVER
		if (m_Light)
			m_Light.Destroy();   
		#endif
	}
    void InitializeSoundSets() {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] InitializeSoundSets called");
        }
        if (ConfigIsExisting("openSoundSet")) {
            m_OpenSoundSet = ConfigGetString("openSoundSet");
        }
        if (ConfigIsExisting("closeSoundSet")) {
            m_CloseSoundSet = ConfigGetString("closeSoundSet");
        }
    }
    void SoundOpenPlay() {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] SoundOpenPlay called");
        }
        EffectSound sound;
        if (MemoryPointExists("Doors1")) {
            sound = SEffectManager.PlaySound(m_OpenSoundSet, ModelToWorld(GetMemoryPointPos("Doors1")));
        } else {
            sound = SEffectManager.PlaySound(m_OpenSoundSet, GetPosition());
        }
        if (sound) {
            sound.SetSoundAutodestroy(true);
        }
    }
	void SoundClosePlay() {		
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] SoundClosePlay called");
        }
        EffectSound sound;
        if (MemoryPointExists("Doors1")) {
            sound = SEffectManager.PlaySound(m_CloseSoundSet, ModelToWorld(GetMemoryPointPos("Doors1")));
        } else {
            sound = SEffectManager.PlaySound(m_CloseSoundSet, GetPosition());
        }
        if (sound) {
            sound.SetSoundAutodestroy(true);
        }
	}
    bool HasBaseLights() {
        bool has = MemoryPointExists("light");
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] HasBaseLights called: " + has);
        }
        return has;
    }
    bool CanBeDismantled() {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] CanBeDismantled called");
        }
        return false;
    }
    bool AcceptsCodeLocks() {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] AcceptsCodeLocks called");
        }
        return true;
    }

    override bool IsPlayerInside(PlayerBase player, string selection) {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] IsPlayerInside called: player=" + player + ", selection=" + selection);
        }
        if (MemoryPointExists("inventory_center")) {
            return vector.Distance(player.GetPosition(), ModelToWorld(GetMemoryPointPos("inventory_center"))) < 1.75;
        }
        return super.IsPlayerInside(player, selection);
    }

    override bool CanObstruct()
    {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] CanObstruct called");
        }
        return true;
    }
    override bool CanPutInCargo(EntityAI parent) {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] CanPutInCargo called");
        }
		return false;
	}
	override bool CanPutIntoHands(EntityAI parent) {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] CanPutIntoHands called");
        }
		return false;
	}
    override void OnInventoryEnter(Man player) {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] OnInventoryEnter called: player=" + player);
        }
        super.OnInventoryEnter(player);
        if(GetInventory()) {
            GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);       
        }
    }
    override void OnInventoryExit(Man player) {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] OnInventoryExit called: player=" + player);
        }
        super.OnInventoryExit(player);
        if(GetInventory()) {
            GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);
        }        
    }
    override bool CanDisplayAttachmentCategory(string category_name) {	
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] CanDisplayAttachmentCategory called: category_name=" + category_name);
        }
        if (!super.CanDisplayAttachmentCategory(category_name))
            return false;
        category_name.ToLower();
        bool isCodeLock = category_name.Contains("codelock");
        bool isLock = category_name.Contains("lock");
        #ifdef CodeLock
            if (isCodeLock) return false;
            if (isLock) return true;
        #endif
        #ifdef RA_BaseBuilding_Scripts
            if (isCodeLock) return true;
            if (isLock) return false;
        #endif
        #ifdef EXPANSIONMODBASEBUILDING
            if (isCodeLock) return false;
            if (isLock) return true;
        #endif
        return !(isCodeLock || isLock);
    }
    override bool CanDisplayAttachmentSlot(int slot_id) {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] CanDisplayAttachmentSlot called: slot_id=" + slot_id);
        }
        int codeLockId = InventorySlots.GetSlotIdFromString("CodeLock");
        int combinationLockId = InventorySlots.GetSlotIdFromString("Att_CombinationLock");
        if (slot_id == codeLockId) {
            #ifdef CodeLock
                return false; 
            #endif
            #ifdef RA_BaseBuilding_Scripts
                return true;
            #endif
            #ifdef EXPANSIONMODBASEBUILDING
                return false;
            #endif
            return false;
        }
        if (slot_id == combinationLockId) {
            #ifdef CodeLock
                return true;
            #endif
            #ifdef RA_BaseBuilding_Scripts
                return false;
            #endif
            #ifdef EXPANSIONMODBASEBUILDING
                return true;
            #endif
            return false;
        }
        return super.CanDisplayAttachmentSlot(slot_id);
    }
    override bool CanReceiveAttachment(EntityAI attachment, int slotId) {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] CanReceiveAttachment called: attachment=" + attachment + ", slotId=" + slotId);
        }
        #ifdef CodeLock 
            CodeLock c_Lock;
            if (Class.CastTo(c_Lock, attachment))
                return true;
        #endif
        #ifdef RA_BaseBuilding_Scripts
            int codelock = InventorySlots.GetSlotIdFromString("Att_CombinationLock");
            switch(slotId) {
                case codelock:
                {   
                    if ( FindAttachmentBySlotName("Att_CombinationLock") == NULL) {
                        return false;
                    }
                    break;
                }
            }    
        #endif
        return super.CanReceiveAttachment(attachment, slotId);
    }
    void UpdateVisualState()
    {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] UpdateVisualState called");
        }
        // Door animations
        if (IsOpen())
        {
            SetAnimationPhase("Doors1", 1);
            SetAnimationPhase("Doors2", 1);
            SetAnimationPhase("Doors3", 1);
            SetAnimationPhase("Doors4", 1);
            SetAnimationPhase("cover", 1);
        }
        else
        {
            SetAnimationPhase("Doors1", 0);
            SetAnimationPhase("Doors2", 0);
            SetAnimationPhase("Doors3", 0);
            SetAnimationPhase("Doors4", 0);
            SetAnimationPhase("cover", 0);
        }
    
        int proxyMode = GetLegacyBaseStorageConfig().ProxyMode;
    
        if (proxyMode == 3)
        {
            // ProxyMode disabled — use individual config flags
            ApplyAnimationFromConfig("ExtraDetail", GetLegacyBaseStorageConfig().ExtraDetail);
            ApplyAnimationFromConfig("proxyImportant", GetLegacyBaseStorageConfig().proxyImportant);
            ApplyAnimationFromConfig("proxyimportant2", GetLegacyBaseStorageConfig().proxyimportant2);
            ApplyAnimationFromConfig("proxyGeneral", GetLegacyBaseStorageConfig().proxyGeneral);
            ApplyAnimationFromConfig("proxyMisc", GetLegacyBaseStorageConfig().proxyMisc);
        }
        else
        {
            // ProxyMode overrides everything
            ApplyProxyModeAnimation("hideproxy", proxyMode);
            ApplyProxyModeAnimation("ExtraDetail", proxyMode);
            ApplyProxyModeAnimation("proxyImportant", proxyMode);
            ApplyProxyModeAnimation("proxyimportant2", proxyMode);
            ApplyProxyModeAnimation("proxyGeneral", proxyMode);
            ApplyProxyModeAnimation("proxyMisc", proxyMode);
        }
    } 

    #ifdef EXPANSIONMODBASEBUILDING
    override bool ExpansionCanOpen(PlayerBase player, string selection) {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] ExpansionCanOpen called: player=" + player + ", selection=" + selection);
        }
        if (!super.ExpansionCanOpen(player, selection))
            return false;
        return selection.Contains("doors") || selection.Contains("coveraction") || selection.Contains("lid");
    }
    #endif
    #ifdef RA_BaseBuilding_Scripts
    override float GetCostToUpkeep() {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] GetCostToUpkeep called");
        }
        return 0.00001;
    }
    override float GetTimeToDecay() {       
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] GetTimeToDecay called");
        }
        return 72.0 * 60.0 * 60.0;
    }
    #endif

    override void AfterStoreLoad()
	{	
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] AfterStoreLoad called");
        }
		super.AfterStoreLoad();

		UpdateLight();
		UpdatesideLight();
	}

    override void OnVariablesSynchronized()
	{
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] OnVariablesSynchronized called. m_IsLightOnServer=" + m_IsLightOnServer + ", m_IsLightOnClient=" + m_IsLightOnClient + ", m_IssideLightOnServer=" + m_IssideLightOnServer + ", m_IssideLightOnClient=" + m_IssideLightOnClient);
        }
		if ( m_IsLightOnServer && !m_IsLightOnClient )
		{
			LightOn();
		}
        else if ( !m_IsLightOnServer && m_IsLightOnClient )
		{
			LightOff();
		}

		if ( m_IssideLightOnServer && !m_IssideLightOnClient )
		{
			sideLightOn();
		}
        else if ( !m_IssideLightOnServer && m_IssideLightOnClient )
		{
			sideLightOff();
		}
		
	}
    bool IsLightOn()
	{
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] IsLightOn called");
        }
		if (GetGame().IsServer())
            return m_IsLightOnServer;
        else
            return m_IsLightOnClient;
	}

	bool IssideLightOn()
	{
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] IssideLightOn called");
        }
		if (GetGame().IsServer())
            return m_IssideLightOnServer;
        else
            return m_IssideLightOnClient;
	}
	
    void LightOn()
    {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] LightOn called");
        }
        m_IsLightOnClient = true;
    
        // List of memory point names for main lighting
        string lightPoints[] = {
            "light01",
            "light02",
            "light03",
            "light04"
        };
    
        foreach (string pointName : lightPoints)
        {
            if (MemoryPointExists(pointName))
            {
                ScriptedLightBase light = ContainerMLight.Cast(ScriptedLightBase.CreateLight(ContainerMLight, "0 0 0"));
                if (light)
                {
                    light.AttachOnMemoryPoint(this, pointName);
                    m_AreaLights.Insert(light);
                }
            }
            else

            if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
				GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] LightOn: MemoryPoint '" + pointName + "' does not exist. ");
			}
        }
    
        SoundLightOn();
    }
	
	void sideLightOn()
	{
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] sideLightOn called");
        }
		m_IssideLightOnClient = true;

		 // List of memory point names for side lighting/ Secondery lighting
         string lightPoints[] = {
            "side",
            "side2"
        };
    
        foreach (string pointName : lightPoints)
        {
            if (MemoryPointExists(pointName))
            {
                ScriptedLightBase light = ContainerSLight.Cast(ScriptedLightBase.CreateLight(ContainerSLight, "0 0 0"));
                if (light)
                {
                    light.AttachOnMemoryPoint(this, pointName);
                    m_AreaSLights.Insert(light);
                }
            }
            else

            if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
				GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] LightOn: MemoryPoint '" + pointName + "' does not exist. ");
			}
        }
    
        SoundLightOn();
	}

    void LightOff()
    {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] LightOff called");
        }
        m_IsLightOnClient = false;

        foreach (ScriptedLightBase light : m_AreaLights)
        {
            if (light)
                light.Destroy();
        }

        m_AreaLights.Clear();

        SoundLightOff();
    }

    void sideLightOff()
	{
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] sideLightOff called");
        }
		m_IssideLightOnClient = false;
		
		foreach (ScriptedLightBase light : m_AreaSLights)
	{
		if (light)
			light.Destroy();
	}

	m_AreaSLights.Clear();
		
		SoundLightOff();
	}

    void SwitchLigthOn()
    {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] SwitchLigthOn called, setting m_IsLightOnServer = true");
        }   
        m_IsLightOnServer = true;

        int index = GetHiddenSelectionIndex("ceiling_lamp");

        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] Hidden selection index for 'ceiling_lamp': " + index);
        }

        SetObjectMaterial(index, LAMP_TEXTURE_ON);
        SetSynchDirty();
        UpdateLight();
    }
	
	void SwitchsideLigthOn()
	{
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] SwitchsideLigthOn called");
        }
		m_IssideLightOnServer = true;
		
		SetObjectMaterial(GetHiddenSelectionIndex("side_lamp"), Side_LAMP_TEXTURE_ON);
		
		SetSynchDirty();
		
		UpdatesideLight();
	}

	void SwitchLigthOff()
	{
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] SwitchLigthOff called, setting m_IsLightOnServer = false");
        }
		m_IsLightOnServer = false;
		
		SetObjectMaterial(GetHiddenSelectionIndex("ceiling_lamp"), LAMP_TEXTURE_OFF);
		
		SetSynchDirty();
		
		UpdateLight();
	}

	void SwitchsideLigthOff()
	{
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] SwitchsideLigthOff called");
        }
		m_IssideLightOnServer = false;
		
		SetObjectMaterial(GetHiddenSelectionIndex("side_lamp"), Side_LAMP_TEXTURE_OFF);
		
		SetSynchDirty();
		
		UpdatesideLight();
	}
	
	void UpdateLight()
	{
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] UpdateLight called. IsLightOn()=" + IsLightOn());
        }
		if ( IsLightOn() )
		{
			SetAnimationPhase("light_on", 0);
			SetAnimationPhase("light_off", 1);
		}
		else
		{
			SetAnimationPhase("light_on", 1);
			SetAnimationPhase("light_off", 0);
		}
	}

	void UpdatesideLight()
	{
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] UpdatesideLight called. IssideLightOn()=" + IssideLightOn());
        }
		if ( IssideLightOn() )
		{
			SetAnimationPhase("sidelight_on", 0);
			SetAnimationPhase("sidelight_off", 1);
		}
		else
		{
			SetAnimationPhase("sidelight_on", 1);
			SetAnimationPhase("sidelight_off", 0);
		}
	}

    protected void SoundLightOn()
	{
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] SoundLightOn called");
        }
		vector selection_pos = ModelToWorld( GetMemoryPointPos( "lightswitch" ) );
		
        m_SoundLight = SEffectManager.PlaySound( "Flashlight_TurnOn_SoundSet" , selection_pos );
		m_SoundLight.SetSoundAutodestroy( true );
	}
	
	protected void SoundLightOff()
	{
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] SoundLightOff called");
        }
		vector selection_pos = ModelToWorld( GetMemoryPointPos( "lightswitch" ) );
		
        m_SoundLight = SEffectManager.PlaySound( "Flashlight_TurnOff_SoundSet" , selection_pos );
		m_SoundLight.SetSoundAutodestroy( true );
	}

    	override void EEItemAttached(EntityAI item, string slot_name)
	{
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] EEItemAttached called: item=" + item + ", slot_name=" + slot_name);
        }
		super.EEItemAttached(item, slot_name);

		ItemBase item_IB = ItemBase.Cast(item);

		if (item_IB.IsKindOf("TruckBattery"))
		{
			#ifndef SERVER
			EffectSound sound = SEffectManager.PlaySound(BATTERY_ATTACH_SOUND, GetPosition());
			sound.SetAutodestroy(true);
			#endif

			m_BufferBattery = item_IB;

			if (GetGame().IsServer())
			{
				this.SetQuantity(m_BufferBattery.GetQuantity());
				this.GetCompEM().SetEnergy(m_BufferBattery.GetCompEM().GetEnergy());
			}
		}
	}

    override bool IsElectricAppliance()
	{
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] IsElectricAppliance called");
        }
		return true;
	}

    override void EEItemDetached(EntityAI item, string slot_name)
    {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] EEItemDetached called: item=" + item + ", slot_name=" + slot_name);
        }
        super.EEItemDetached(item, slot_name);

        if (item.IsKindOf("TruckBattery"))
        {
            m_BufferBattery = NULL;

            if (GetGame().IsServer())
            {
                this.SetQuantity(0);
            }

            #ifndef SERVER
            EffectSound sound = SEffectManager.PlaySound(BATTERY_DETACH_SOUND, GetPosition());
            sound.SetAutodestroy(true);
            #endif
        }
    }

	// bool IsCargoEmpty()
	// {
	// 	if (HasPluggedInDevice())
	// 	{
	// 		return false;
	// 	}

	// 	if (GetNumberOfItems() < 1 && GetInventory().AttachmentCount() < 1)
	// 	{
	// 		return true;
	// 	}
	// 	return false;
	// }
}
