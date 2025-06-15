modded class ActionRepairPart
{
	override protected bool RepairCondition( PlayerBase player, ActionTarget target, ItemBase item, bool camera_check )
	{
		Object target_object = target.GetObject();
		
		if ( target_object && target_object.CanUseConstruction() && target_object.GetType().Contains("Legacy_Container_") )
		{
			return false;
		}
		else
		{
			return super.RepairCondition(player, target, item, camera_check);
		}
	}
};