class Legacy_Wooden_Table_Base : Legacy_Storage_Base {
    override bool CanBeDismantled() {
		return true;
	}
}
class Legacy_Wooden_Table extends Legacy_Wooden_Table_Base {}