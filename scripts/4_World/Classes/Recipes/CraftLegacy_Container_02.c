class CraftLegacy_Container_02 extends CraftLegacyKitBase {
	override bool CanDo( ItemBase ingredients[], PlayerBase player ) {
		return (GetLegacyBaseStorageConfig().CanCraftcontainer2); 
    }
	override void Init() {
		m_Name = GetLegacyBaseStorageConfig().Legacy_Container_02CraftText;
		m_IsInstaRecipe = false;
		m_AnimationLength = GetLegacyBaseStorageConfig().CraftKitToolTime;
		int recipeMakeCost = GetLegacyBaseStorageConfig().Legacy_Container_02RecipeOneQty;
		int recipeResourceCost = GetLegacyBaseStorageConfig().Legacy_Container_02RecipeTwoQty;
		m_recipeitemone = GetLegacyBaseStorageConfig().Legacy_Container_02RecipeOne;
		m_recipeitemtwo = GetLegacyBaseStorageConfig().Legacy_Container_02RecipeTwo;
		//conditions
		m_MinDamageIngredient[0] = -1;
		m_MaxDamageIngredient[0] = 3;
		m_MinQuantityIngredient[0] = recipeMakeCost;
		m_MaxQuantityIngredient[0] = -1;
		m_MinDamageIngredient[1] = -1;
		m_MaxDamageIngredient[1] = 3;
		m_MinQuantityIngredient[1] = recipeResourceCost;
		m_MaxQuantityIngredient[1] = -1;
		//ingredient 1  
		InsertIngredient(0, m_recipeitemone);
		m_IngredientAddHealth[0] = -1;
		m_IngredientSetHealth[0] = -1;
		m_IngredientAddQuantity[0] = -recipeMakeCost;
		m_IngredientDestroy[0] = false;
		m_IngredientUseSoftSkills[0] = false;
		//ingredient 2	
		InsertIngredient(1, m_recipeitemtwo);
		m_IngredientAddHealth[1] = -1;
		m_IngredientSetHealth[1] = -1;
		m_IngredientAddQuantity[1] = -recipeResourceCost;
		m_IngredientDestroy[1] = false;
		m_IngredientUseSoftSkills[1] = false;
		//result
		AddResult("Legacy_Container_02_Kit");	// recipe result
		m_ResultSetFullQuantity[0] = false;
		m_ResultSetQuantity[0] = -1;
		m_ResultSetHealth[0] = -1;	
		m_ResultInheritsHealth[0] = 0;
		m_ResultInheritsColor[0] = -1;
		m_ResultToInventory[0] = -2;
		m_ResultUseSoftSkills[0] = false;
		m_ResultReplacesIngredient[0] = -1;
	}
}