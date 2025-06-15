class CraftLegacyKitBase extends RecipeBase {
    string m_recipeitemone;
	string m_recipeitemtwo;
	override float GetLengthInSecs() {
		return m_AnimationLength;
	}
	override bool CanDo( ItemBase ingredients[], PlayerBase player ) {
		return (GetLegacyBaseStorageConfig().CanCraftKits); 
    }
	override void Do(ItemBase ingredients[], PlayerBase player,array<ItemBase> results, float specialty_weight) {
		ItemBase result;
		Class.CastTo(result, results.Get(0));
		if ( GetLegacyBaseStorageConfig().EnableCraftLogging ) {
			GetLegacy_Base_StorageLogger().LogInfo("[Legacy_Base_Storage][Crafting]: " + player.GetIdentity().GetName() + " (" + player.GetIdentity().GetPlainId() + ") crafted " + result.GetType() + " at " + player.GetPosition());
		}	
	}
}