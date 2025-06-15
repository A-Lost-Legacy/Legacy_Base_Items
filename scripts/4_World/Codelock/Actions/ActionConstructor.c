#ifdef CodeLock
modded class ActionConstructor {   
    override void RegisterActions( TTypenameArray actions ) {
        super.RegisterActions( actions );
        actions.Insert(ActionInteractLockOnLegacy);
        actions.Insert(ActionAttachCodeLockToLegacy);
        actions.Insert(ActionManageLockOnLegacy);
        actions.Insert(ActionLockAdminOnLegacy);
    }
}   
#endif