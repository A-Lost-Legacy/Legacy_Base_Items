class Legacy_Base_StorageLoggingSettings 
{
    int logLevel = 0;
    int refreshRateInSeconds = 60;

    void MakeDirectoryIfNotExists()
    {
        if(!FileExist( Legacy_Base_Storage_ROOT_FOLDER))
            MakeDirectory( Legacy_Base_Storage_ROOT_FOLDER);

        if(!FileExist( Legacy_Base_Storage_LOG_FOLDER))
            MakeDirectory( Legacy_Base_Storage_LOG_FOLDER);

        if(!FileExist( Legacy_Base_Storage_LOGGER_CONFIG_DIR))
            MakeDirectory( Legacy_Base_Storage_LOGGER_CONFIG_DIR);
        
        if(!FileExist( Legacy_Base_Storage_LOGGER_LOG_DIR))
            MakeDirectory( Legacy_Base_Storage_LOGGER_LOG_DIR);
    }

    void Save()
    {
        JsonFileLoader<Legacy_Base_StorageLoggingSettings>.JsonSaveFile( Legacy_Base_Storage_LOGGER_CONFIG_FILE, this);
    }

    static ref Legacy_Base_StorageLoggingSettings Load()
    {
        Legacy_Base_StorageLoggingSettings settings = new Legacy_Base_StorageLoggingSettings();

        settings.MakeDirectoryIfNotExists();

        if(FileExist( Legacy_Base_Storage_LOGGER_CONFIG_FILE))
        {
            JsonFileLoader<Legacy_Base_StorageLoggingSettings>.JsonLoadFile( Legacy_Base_Storage_LOGGER_CONFIG_FILE, settings);
            return settings;
        }

        settings.Save();
        return settings;
    }

}