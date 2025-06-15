class DeCraftLegacyKitBase extends RecipeBase {
    string m_recipeitemone;
	string m_recipeitemtwo;
	string m_DeCraftKitTool;
	override float GetLengthInSecs() {
		return m_AnimationLength;
	}
    override bool CanDo( ItemBase ingredients[], PlayerBase player ) {
		return (GetLegacyBaseStorageConfig().CanDeCraftKits); 
	}
	override void Do(ItemBase ingredients[], PlayerBase player,array<ItemBase> results, float specialty_weight) {
		string name = "";
		name = ingredients[0].Get_KitName();  
		if ( GetLegacyBaseStorageConfig().EnableCraftLogging ) {
			GetLegacy_Base_StorageLogger().LogInfo("[Legacy_Base_Storage][Crafting]: " + player.GetIdentity().GetName() + " (" + player.GetIdentity().GetPlainId() + ") decrafted " + ingredients[0].GetType() + " at " + player.GetPosition());
		}	
		MiscGameplayFunctions.TurnItemIntoItemEx(player, new TurnItemIntoItemLambda(ingredients[0], name, player));
	}
}