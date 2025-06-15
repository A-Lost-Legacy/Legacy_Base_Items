
static ref Legacy_Base_StorageLoggingModule GetLegacy_Base_StorageLogger()
{
    return Legacy_Base_StorageLoggingModule.Cast(CF_ModuleCoreManager.Get(Legacy_Base_StorageLoggingModule));
}

[CF_RegisterModule(Legacy_Base_StorageLoggingModule)]
class Legacy_Base_StorageLoggingModule : CF_ModuleGame
{
    private int networkSync_LogLevel;

    ref Legacy_Base_StorageLoggingSettings settings;

    FileHandle fileHandle;

    float dtime = 0;


    override void OnInit()
    {
        super.OnInit();
        
        EnableUpdate();
        EnableMissionStart();
    }

    override void OnMissionStart(Class sender, CF_EventArgs args)
    {
        super.OnMissionStart(sender, args);

        fileHandle = CreateNewLogFile();

        if(GetGame().IsServer())
        {
            settings = Legacy_Base_StorageLoggingSettings.Load();

            networkSync_LogLevel = settings.logLevel;
            SynchLogLevel();       
        }
        else
        {
            AddLegacyRPC("GetLogLevelResponse", SingleplayerExecutionType.Client);
        }
    }

    void GetLogLevelResponse(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		 if (type != CallType.Client)
			 return;

		 Param1<int> data;
		 if (!ctx.Read(data))
            return;

		 networkSync_LogLevel = data.param1;
	}

    void SynchLogLevel()
    {
        GetRPCManager().SendRPC(ClassName(), "GetLogLevelResponse",  new Param1<int>(networkSync_LogLevel), true, NULL);
    }

    override void OnUpdate(Class sender, CF_EventArgs args)
    {
        auto update = CF_EventUpdateArgs.Cast(args);

        if(!GetGame().IsServer())
            return;

        if(!settings)
            return;

        dtime += update.DeltaTime;
        if(dtime >= settings.refreshRateInSeconds)
        {
            dtime = 0;

            settings = Legacy_Base_StorageLoggingSettings.Load();

            networkSync_LogLevel = settings.logLevel;
            SynchLogLevel();
        }
    }


    void MakeDirectoryIfNotExists()
    {
        if(!FileExist(Legacy_Base_Storage_ROOT_FOLDER))
            MakeDirectory(Legacy_Base_Storage_ROOT_FOLDER);

        if(!FileExist(Legacy_Base_Storage_LOG_FOLDER))
            MakeDirectory(Legacy_Base_Storage_LOG_FOLDER);

        if(!FileExist(Legacy_Base_Storage_LOGGER_CONFIG_DIR))
            MakeDirectory(Legacy_Base_Storage_LOGGER_CONFIG_DIR);
        
        if(!FileExist(Legacy_Base_Storage_LOGGER_LOG_DIR))
            MakeDirectory(Legacy_Base_Storage_LOGGER_LOG_DIR);
    }
    
    string GenerateShortDateString()
    {
        int year, month, day;
        GetYearMonthDay(year, month, day);
        return "" + year + "_" + month + "_" + day;
    }

    string GenerateShortTimeString()
    {
        int hour, minute, second;
        GetHourMinuteSecond(hour, minute, second);
        return "" + hour + "_" + minute + "_" + second;
    }

    string GenerateFullTimestamp()
    {
        string dateStr = GenerateShortDateString();
        string timeStr = GenerateShortTimeString();

        return dateStr + "-" + timeStr;
    }

    FileHandle CreateNewLogFile()
    {
        MakeDirectoryIfNotExists();

        string filePath = string.Format(Legacy_Base_Storage_LOGGER_LOG_FILE, GenerateFullTimestamp());

        fileHandle = OpenFile(filePath, FileMode.WRITE);

        if(fileHandle != 0)
        {
            FPrintln(fileHandle, "Creation Time: " + GenerateFullTimestamp());
            return fileHandle;
        }

        return null;
    }

    void Log(string content, Legacy_Base_StorageLogLevel logLevel)
    {
        if(logLevel < networkSync_LogLevel)
            return;
        
        string timestamp = GenerateShortTimeString();
        FPrintln(fileHandle, timestamp + " | " + GetLogLevelString(logLevel) + " | " + content);
    }

    void LogInfo(string content)
    {
        Log(content, Legacy_Base_StorageLogLevel.Info);
    }

    void LogWarning(string content)
    {
        Log(content, Legacy_Base_StorageLogLevel.Warn);
    }

    void LogError(string content)
    {
        Log(content, Legacy_Base_StorageLogLevel.Error);
    }

    void LogDebug(string content)
    {
        Log(content, Legacy_Base_StorageLogLevel.Debug);
    }

    string GetLogLevelString(Legacy_Base_StorageLogLevel logLevel)
    {
        switch(logLevel)
        {
             case Legacy_Base_StorageLogLevel.Debug:
                return "DEBUG";
            case Legacy_Base_StorageLogLevel.Info:
                return "INFO";
            case Legacy_Base_StorageLogLevel.Warn:
                return "WARNING";
            case Legacy_Base_StorageLogLevel.Error:
                return "ERROR";
            default:
                return "";
        }

        return "";
    }

}