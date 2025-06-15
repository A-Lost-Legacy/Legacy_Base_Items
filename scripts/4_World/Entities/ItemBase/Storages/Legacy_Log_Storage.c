class Legacy_Log_Storage_Base : Legacy_Storage_Base {
    override bool CanBeDismantled() {
		return true;
	}
}
class Legacy_Log_Storage extends Legacy_Log_Storage_Base {}