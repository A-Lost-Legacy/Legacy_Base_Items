class Legacy_Mesh_stroage_unit_Base : Legacy_Openable_Base {
	override void SetActions() {
        super.SetActions();
		#ifdef CodeLock
			AddAction(ActionInteractLockOnLegacy);
			AddAction(ActionManageLockOnLegacy);
			AddAction(ActionLockAdminOnLegacy);
		#endif
    }
    override bool CanBeDismantled() {
		return true;
	}
}
class Legacy_Mesh_stroage_unit extends Legacy_Mesh_stroage_unit_Base {}