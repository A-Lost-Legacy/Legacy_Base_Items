class Legacy_Container : Legacy_Openable_Base {
	override void SetActions() {
        super.SetActions();
		#ifdef CodeLock
			AddAction(ActionInteractLockOnLegacy);
			AddAction(ActionManageLockOnLegacy);
			AddAction(ActionLockAdminOnALegacy);
		#endif
    }
    override bool CanBeDismantled() {
		return true;
	}
}