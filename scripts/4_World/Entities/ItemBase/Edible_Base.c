// modded class Edible_Base : ItemBase {
//     bool isRefrigPreserveOn() {
//         return GetLegacyBaseStorageConfig().EnableRefrigeratorFoodPreserve;
//     }
//     bool isInFridge() {
//     	Legacy_Refrigerator refrigerator;
//     	EntityAI obj = GetHierarchyParent();
//     	return Class.CastTo(refrigerator, obj);
// 	}
// 	override bool CanProcessDecay() {
//         bool preserveInFridge = isRefrigPreserveOn() && isInFridge();
//         return !GetIsFrozen() && (GetFoodStageType() != FoodStageType.ROTTEN) && !preserveInFridge;
//     }
// } 