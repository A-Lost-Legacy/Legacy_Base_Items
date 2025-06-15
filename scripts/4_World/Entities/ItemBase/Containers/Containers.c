modded class AmmoBox : Container_Base {
    bool IsItemWhitelisted(EntityAI item) {
        if(GetLegacyBaseStorageConfig().EnableAmmoBoxWhitelist) {
            array<string> itemWhitelist = GetLegacyBaseStorageConfig().GetAmmoBoxWhitelist();
            foreach (string whitelist : itemWhitelist) {
		    	if(item.IsKindOf(whitelist)) {
                    return true;
                }        
		    }
            return false;
        }
        return true;
    } 
    override bool CanReceiveItemIntoCargo(EntityAI item) {
        return IsItemWhitelisted(item) && super.CanReceiveItemIntoCargo(item);
    }
    override bool CanSwapItemInCargo(EntityAI child_entity, EntityAI new_entity) {
        return IsItemWhitelisted(new_entity) && super.CanSwapItemInCargo(child_entity, new_entity);
    }
}	