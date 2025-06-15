modded class PluginRecipesManagerBase {
	override void RegisterRecipies() {
		super.RegisterRecipies();
		RegisterRecipe(new DismantleLegacyBaseStorage);		
		RegisterRecipe(new DeCraftLegacyKitBase);
		RegisterRecipe(new CraftLegacyKitBase);
		RegisterRecipe(new CraftLegacy_Container_02);
	}
}