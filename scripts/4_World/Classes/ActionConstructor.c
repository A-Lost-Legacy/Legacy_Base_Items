modded class ActionConstructor {
    override void RegisterActions( TTypenameArray actions ) {
        super.RegisterActions( actions );
        actions.Insert(ActionLegacyCustomCloseOpen);
        // actions.Insert(ActionLegacyGreenHouseDismantle);
        actions.Insert(ActionSwitchLegacyLight);
        actions.Insert(ActionSwitchLegacySideLights);
    }
}     