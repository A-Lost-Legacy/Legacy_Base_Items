class Legacy_Container_02 : Legacy_Openable_Base {
    override void SetActions() {
        super.SetActions();
        #ifdef CodeLock
            AddAction(ActionInteractLockOnLegacy);
            AddAction(ActionManageLockOnLegacy);
            AddAction(ActionLockAdminOnALegacy);
        #endif
    }

    override bool HasEnergyManager()
    {
        return true;
    }

    override bool CanBeDismantled() {
        return true;
    }

    override bool DisableVicinityIcon() {
        return true;
    }

    protected bool IsPlayerInBounds(PlayerBase player, float maxX = 1.5, float maxY = 2.0, float maxZ = 1.0) {
        if (!MemoryPointExists("inventory_center")) return false;

        vector center = ModelToWorld(GetMemoryPointPos("inventory_center"));
        vector playerPos = player.GetPosition();
        vector diff = playerPos - center;

        return (
            Math.AbsFloat(diff[0]) < maxX &&Math.AbsFloat(diff[1]) < maxY &&Math.AbsFloat(diff[2]) < maxZ);
    }

    override bool IsPlayerInside(PlayerBase player, string selection) {
        return IsPlayerInBounds(player) || super.IsPlayerInside(player, selection);
    }

    override bool IgnoreOutOfReachCondition() {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        return player && IsPlayerInBounds(player);
    }

    override bool CanDisplayCargo() {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        return player && IsPlayerInBounds(player);
    }

    override bool IsInventoryVisible() {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        return player && IsPlayerInBounds(player);
    }

    override void OnInventoryEnter(Man player) {
        PlayerBase pb = PlayerBase.Cast(player);
        if (pb && !IsPlayerInBounds(pb)) {
            GetGame().GetUIManager().CloseAll();
            return;
        }

        super.OnInventoryEnter(player);

        if (GetInventory()) {
            GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
        }
    }

    override void OnInventoryExit(Man player) {
        super.OnInventoryExit(player);

        if (GetInventory()) {
            GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);
        }
    }

    override bool CanDisplayAttachmentCategory(string category_name) {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player || !IsPlayerInBounds(player, 1.5, 2.0, 5.0)) return false;

        category_name.ToLower();
        bool isCodeLock = category_name.Contains("codelock");
        bool isLock = category_name.Contains("lock");

        #ifdef CodeLock
            return isLock && !isCodeLock;
        #endif
        #ifdef RA_BaseBuilding_Scripts
            return isCodeLock && !isLock;
        #endif
        #ifdef EXPANSIONMODBASEBUILDING
            return isLock && !isCodeLock;
        #endif

        return !(isCodeLock || isLock);
    }

    override bool CanDisplayAttachmentSlot(int slot_id) {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!player || !IsPlayerInBounds(player)) return false;

        int codeLockId = InventorySlots.GetSlotIdFromString("CodeLock");
        int combinationLockId = InventorySlots.GetSlotIdFromString("Att_CombinationLock");

        if (slot_id == codeLockId) {
            #ifdef CodeLock return false; #endif
            #ifdef RA_BaseBuilding_Scripts return true; #endif
            #ifdef EXPANSIONMODBASEBUILDING return false; #endif
        }

        if (slot_id == combinationLockId) {
            #ifdef CodeLock return true; #endif
            #ifdef RA_BaseBuilding_Scripts return false; #endif
            #ifdef EXPANSIONMODBASEBUILDING return true; #endif
        }

        return true;
    }
}
