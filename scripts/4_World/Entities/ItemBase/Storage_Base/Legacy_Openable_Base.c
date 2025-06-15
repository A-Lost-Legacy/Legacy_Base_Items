class Legacy_Openable_Base : Legacy_Storage_Base {
	protected bool m_IsOpened;
	protected bool m_IsOpenedLocal;
	private bool m_IsOpenable;
	protected bool m_AutoCloseStart = false;
	protected bool m_AutoCloseTimer = false;
	static const int AUTO_CLOSE_TIMER = 60 * GetLegacyBaseStorageConfig().AutoCloseMinutes * 1000; 

	void Legacy_Openable_Base() {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] Legacy_Openable_Base constructor called");
        }
		RegisterNetSyncVariableBool("m_IsOpened");	
        InitializeSoundSets();
		m_AutoCloseStart = GetLegacyBaseStorageConfig().AutoCloseOnServerStart;
		m_AutoCloseTimer = GetLegacyBaseStorageConfig().EnableAutoCloseStorageTimer;
		UpdateVisualState();
	}

	override void EEInit() {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] EEInit called");
        }
		super.EEInit();		
        if(IsOpen()) {
            if(GetInventory()) {
                GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);
                if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
                    GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] EEInit: Inventory unlocked because open");
                }
            }    
		} else {
            if(GetInventory()) {
			    GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);	
                if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
                    GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] EEInit: Inventory locked because closed");
                }
            }    
		}		
	}

	override void Open() {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] Open called");
        }
		m_IsOpened = true;
		UpdateVisualState();
        if(GetInventory()) {
		    GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);
            if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
                GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] Open: Inventory unlocked");
            }
        }     
		if(m_AutoCloseTimer) {
            if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
                GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] Open: Scheduling autoclose in " + AUTO_CLOSE_TIMER + " ms");
            }
			g_Game.GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(Close);
			g_Game.GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(Close, AUTO_CLOSE_TIMER);
		}	
        SetSynchDirty();	
	}

	override void Close() {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] Close called");
        }
		m_IsOpened = false;
		UpdateVisualState();
        if(GetInventory()) {
            GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
            if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
                GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] Close: Inventory locked");
            }
        }    
        SetSynchDirty();
	}

	override bool IsOpen() {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] IsOpen called: " + m_IsOpened);
        }
		return m_IsOpened;
	}

	override void OnVariablesSynchronized() {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] OnVariablesSynchronized called: m_IsOpened=" + m_IsOpened + ", m_IsOpenedLocal=" + m_IsOpenedLocal);
        }
		super.OnVariablesSynchronized();
		if ( m_IsOpened != m_IsOpenedLocal ) {		
			if ( IsOpen() && !IsBeingPlaced() ) {
                if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
                    GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] OnVariablesSynchronized: Play SoundOpenPlay()");
                }
				SoundOpenPlay();
			}
			if ( !IsOpen() && !IsBeingPlaced() ) {
                if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
                    GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] OnVariablesSynchronized: Play SoundClosePlay()");
                }
				SoundClosePlay();
			}		
			m_IsOpenedLocal = m_IsOpened;
		}
		UpdateVisualState();
	}

	override void OnStoreSave( ParamsWriteContext ctx ) {   
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] OnStoreSave called");
        }
		super.OnStoreSave( ctx );		
		ctx.Write( m_IsOpened );	
	}

	override bool OnStoreLoad( ParamsReadContext ctx, int version ) {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] OnStoreLoad called. version=" + version);
        }
		if ( !super.OnStoreLoad( ctx, version ) )
			return false;
		if (!ctx.Read( m_IsOpened ) )
			return false;
		if ( m_IsOpened ) {
            if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
                GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] OnStoreLoad: Open()");
            }
            Open();
		} else {
            if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
                GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] OnStoreLoad: Close()");
            }
            Close();
		}	
		return true;
	}

	override void AfterStoreLoad() {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] AfterStoreLoad called");
        }
		super.AfterStoreLoad();
		if(IsOpen() && m_AutoCloseStart) {
            if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
                GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] AfterStoreLoad: Closing because m_AutoCloseStart");
            }
			Close();
		}	
	}

	override bool CanReceiveItemIntoCargo(EntityAI item) {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] CanReceiveItemIntoCargo called: item=" + item + ", IsOpen=" + IsOpen());
        }
		return IsOpen();
	}

	override bool CanReleaseCargo (EntityAI cargo) {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] CanReleaseCargo called: cargo=" + cargo + ", IsOpen=" + IsOpen());
        }
		return IsOpen();
	}

	override bool CanDisplayCargo() {
        if (GetLegacyBaseStorageConfig().EnabledebugLogging) {
            GetLegacy_Base_StorageLogger().LogDebug("[DEBUG] CanDisplayCargo called. IsOpen=" + IsOpen());
        }
		return IsOpen();
	}

	override void SetActions() {
        super.SetActions();
        AddAction(ActionLegacyCustomCloseOpen);
    }
}
