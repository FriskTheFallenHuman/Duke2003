USE [Builder]
GO
/****** Object:  StoredProcedure [dbo].[GetNewID]    Script Date: 03/30/2011 19:36:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[GetNewID]

	@TableName Text

AS
	DECLARE @Count int

	SET @Count = IDENT_CURRENT( @TableName )
	SELECT @Count

RETURN
GO
/****** Object:  Table [dbo].[Variables]    Script Date: 03/30/2011 19:36:24 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Variables](
	[ID] [int] IDENTITY(1,1) NOT NULL,
	[Variable] [varchar](32) NULL,
	[Branch] [varchar](32) NULL,
	[Value] [varchar](max) NULL,
 CONSTRAINT [PK_Variables] PRIMARY KEY CLUSTERED
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  UserDefinedDataType [dbo].[String]    Script Date: 03/30/2011 19:36:24 ******/
CREATE TYPE [dbo].[String] FROM [nvarchar](4000) NOT NULL
GO
/****** Object:  UserDefinedDataType [dbo].[KeyID]    Script Date: 03/30/2011 19:36:24 ******/
CREATE TYPE [dbo].[KeyID] FROM [int] NOT NULL
GO
/****** Object:  Table [dbo].[Jobs]    Script Date: 03/30/2011 19:36:24 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Jobs](
	[ID] [int] IDENTITY(1,1) NOT NULL,
	[Name] [varchar](64) NULL,
	[Command] [varchar](32) NULL,
	[Platform] [varchar](32) NULL,
	[Game] [varchar](16) NULL,
	[Config] [varchar](32) NULL,
	[ScriptConfig] [varchar](32) NULL,
	[Language] [varchar](32) NULL,
	[Define] [varchar](64) NULL,
	[Parameter] [varchar](1024) NULL,
	[LockXDK] [bit] NULL,
	[LockPDK] [bit] NULL,
	[Branch] [varchar](32) NULL,
	[Label] [varchar](96) NULL,
	[Machine] [varchar](16) NULL,
	[BuildLogID] [int] NULL,
	[PrimaryBuild] [bit] NOT NULL,
	[Active] [bit] NOT NULL,
	[Complete] [bit] NOT NULL,
	[Succeeded] [bit] NOT NULL,
	[Copied] [bit] NULL,
	[Killing] [bit] NULL,
	[SpawnTime] [bigint] NULL,
	[Suppressed] [bit] NULL,
 CONSTRAINT [PK_Jobs] PRIMARY KEY CLUSTERED
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  UserDefinedDataType [dbo].[FixedString]    Script Date: 03/30/2011 19:36:24 ******/
CREATE TYPE [dbo].[FixedString] FROM [char](64) NOT NULL
GO
/****** Object:  Table [dbo].[Commands]    Script Date: 03/30/2011 19:36:24 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Commands](
	[ID] [int] IDENTITY(1,1) NOT NULL,
	[Description] [varchar](40) NOT NULL,
	[Command] [varchar](32) NOT NULL,
	[Platform] [varchar](32) NOT NULL,
	[Game] [varchar](32) NOT NULL,
	[Config] [varchar](32) NOT NULL,
	[Language] [varchar](32) NOT NULL,
	[Parameter] [varchar](64) NOT NULL,
	[UserLevel] [smallint] NULL,
	[Hint] [varchar](16) NOT NULL,
	[LockXDK] [bit] NOT NULL,
	[LockPDK] [bit] NOT NULL,
	[Branch] [varchar](32) NOT NULL,
	[Looping] [bit] NOT NULL,
	[Promotable] [int] NOT NULL,
	[MachineLock] [varchar](32) NOT NULL,
	[NextTriggerDelay] [int] NULL,
	[NextTrigger] [datetime] NULL,
	[Access] [int] NOT NULL,
	[Display] [int] NOT NULL,
	[DisplayDetail] [int] NOT NULL,
	[PrimaryBuild] [bit] NOT NULL,
	[LastAttemptedChangeList] [int] NULL,
	[LastAttemptedDateTime] [datetime] NULL,
	[LastFailedChangeList] [int] NULL,
	[LastFailedDateTime] [datetime] NULL,
	[LastGoodChangeList] [int] NULL,
	[LastGoodLabel] [varchar](96) NULL,
	[LastGoodDateTime] [datetime] NULL,
	[Operator] [varchar](32) NOT NULL,
	[Killer] [varchar](32) NOT NULL,
	[Pending] [bit] NULL,
	[Killing] [bit] NULL,
	[Machine] [varchar](16) NOT NULL,
	[BuildLogID] [int] NULL,
	[ConchHolder] [datetime] NULL,
 CONSTRAINT [PK_Commands] PRIMARY KEY CLUSTERED
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[BuildLog]    Script Date: 03/30/2011 19:36:24 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[BuildLog](
	[ID] [int] IDENTITY(1,1) NOT NULL,
	[Command] [varchar](32) NULL,
	[Machine] [varchar](16) NULL,
	[ChangeList] [int] NULL,
	[Promotable] [int] NULL,
	[BuildStarted] [datetime] NULL,
	[BuildEnded] [datetime] NULL,
	[CurrentStatus] [varchar](128) NULL,
	[BuildLabel] [varchar](128) NULL,
	[DetailedLogPath] [varchar](max) NULL,
	[BranchConfigID] [smallint] NULL,
 CONSTRAINT [PK_BuildLog] PRIMARY KEY CLUSTERED
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
EXEC sys.sp_addextendedproperty @name=N'MS_Description', @value=N'ID of the BranchConfig this log refers to' , @level0type=N'SCHEMA',@level0name=N'dbo', @level1type=N'TABLE',@level1name=N'BuildLog', @level2type=N'COLUMN',@level2name=N'BranchConfigID'
GO
/****** Object:  Table [dbo].[Builders]    Script Date: 03/30/2011 19:36:24 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Builders](
	[ID] [int] IDENTITY(1,1) NOT NULL,
	[Machine] [varchar](32) NOT NULL,
	[State] [varchar](16) NOT NULL,
	[StartTime] [datetime] NOT NULL,
	[CurrentTime] [datetime] NULL,
	[EndTime] [datetime] NULL,
	[PS3_SDKVersion] [varchar](32) NOT NULL,
	[X360_SDKVersion] [varchar](32) NOT NULL,
	[DX_SDKVersion] [varchar](32) NOT NULL,
	[Restart] [bit] NULL,
	[CPUBusy] [float] NULL,
	[DiskReadLatency] [float] NULL,
	[DiskWriteLatency] [float] NULL,
	[DiskTransferLatency] [float] NULL,
	[DiskQueueLength] [float] NULL,
	[DiskReadQueueLength] [float] NULL,
	[SystemMemoryAvailable] [float] NULL,
 CONSTRAINT [PK_Builders_1] PRIMARY KEY CLUSTERED
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Branches]    Script Date: 03/30/2011 19:36:24 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Branches](
	[BuilderID] [int] NOT NULL,
	[Branch] [varchar](32) NOT NULL
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[BranchConfig]    Script Date: 03/30/2011 19:36:24 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[BranchConfig](
	[ID] [int] IDENTITY(1,1) NOT NULL,
	[Version] [int] NOT NULL,
	[Branch] [varchar](32) NOT NULL,
	[Server] [varchar](64) NOT NULL,
	[P4User] [varchar](64) NOT NULL,
	[P4Password] [varchar](32) NOT NULL,
	[DirectXVersion] [varchar](32) NOT NULL,
	[XDKVersion] [varchar](32) NOT NULL,
	[PS3SDKVersion] [varchar](32) NOT NULL,
	[PFXSubjectName] [varchar](64) NOT NULL,
	[SigningIdentity] [varchar](64) NOT NULL,
	[HeadChangelist] [int] NOT NULL,
	[LastGoodOverall] [int] NOT NULL,
	[LastFailOverall] [int] NOT NULL,
	[LastAttemptedOverall] [int] NOT NULL,
	[LastGoodXbox360] [int] NOT NULL,
	[LastFailXbox360] [int] NOT NULL,
	[LastGoodPS3] [int] NOT NULL,
	[LastFailPS3] [int] NOT NULL,
	[LastGoodTools] [int] NOT NULL,
	[LastFailTools] [int] NOT NULL,
	[LastGoodMobileDevice] [int] NOT NULL,
	[LastFailMobileDevice] [int] NOT NULL,
	[LastGoodExample] [int] NOT NULL,
	[LastFailExample] [int] NOT NULL,
	[LastGoodNano] [int] NOT NULL,
	[LastFailNano] [int] NOT NULL,
	[LastGoodNanoMobile] [int] NOT NULL,
	[LastFailNanoMobile] [int] NOT NULL,
	[LastGoodGear] [int] NOT NULL,
	[LastFailGear] [int] NOT NULL,
	[LastGoodUDK] [int] NOT NULL,
	[LastFailUDK] [int] NOT NULL,
	[LastGoodMobile] [int] NOT NULL,
	[LastFailMobile] [int] NOT NULL,
	[LastAttemptedXbox360] [int] NOT NULL,
	[LastAttemptedPS3] [int] NOT NULL,
	[LastAttemptedTools] [int] NOT NULL,
	[LastAttemptedMobileDevice] [int] NOT NULL,
	[LastAttemptedExample] [int] NOT NULL,
	[LastAttemptedNano] [int] NOT NULL,
	[LastAttemptedNanoMobile] [int] NOT NULL,
	[LastAttemptedGear] [int] NOT NULL,
	[LastAttemptedUDK] [int] NOT NULL,
	[LastAttemptedMobile] [int] NOT NULL,
	[Xbox360Error] [varchar](max) NULL,
	[SonyPS3Error] [varchar](max) NULL,
	[ToolsError] [varchar](max) NULL,
	[MobileDeviceError] [varchar](max) NULL,
	[PackageError] [varchar](max) NULL,
	[ExampleError] [varchar](max) NULL,
	[NanoError] [varchar](max) NULL,
	[NanoMobileError] [varchar](max) NULL,
	[GearError] [varchar](max) NULL,
	[UDKError] [varchar](max) NULL,
	[MobileError] [varchar](max) NULL,
 CONSTRAINT [PK_BranchConfig] PRIMARY KEY CLUSTERED
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Applications]    Script Date: 03/30/2011 19:36:24 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Applications](
	[ID] [dbo].[KeyID] IDENTITY(1,1) NOT NULL,
	[AppName] [dbo].[FixedString] NOT NULL,
	[Notes] [dbo].[String] NULL,
 CONSTRAINT [PK_Application] PRIMARY KEY CLUSTERED
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY],
 CONSTRAINT [Unique_Application] UNIQUE NONCLUSTERED
(
	[AppName] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  StoredProcedure [dbo].[CheckTriggeredBuild2]    Script Date: 03/30/2011 19:36:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[CheckTriggeredBuild2]
	@MachineName varchar(32),
	@AnyMachine bit,
	@PrimaryBuild bit
AS
	SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;

	BEGIN TRAN
	DECLARE @Trigger INT
	SET @Trigger = 0

	SELECT
		@Trigger = Commands.ID
	FROM Commands, Builders, Branches, BranchConfig
	WHERE   ( Commands.Pending = 1 )
		-- Grab the live builder row
		AND ( ( Builders.Machine = @MachineName ) AND ( Builders.State != 'Dead' ) AND ( Builders.State != 'Zombied' ) )
		-- Make sure the SDK versions match if required
		AND	( Commands.LockXDK = 0 OR ( Builders.X360_SDKVersion = BranchConfig.XDKVersion AND Commands.Branch = BranchConfig.Branch ) )
	    AND ( Commands.LockPDK = 0 OR ( Builders.PS3_SDKVersion = BranchConfig.PS3SDKVersion AND Commands.Branch = BranchConfig.Branch ) )
		-- Make sure the builder has the branch
		AND	( Branches.Branch = Commands.Branch )
		AND ( Branches.BuilderID = Builders.ID )
		-- Make sure no other promotable builds are running
		AND ( Commands.Promotable = 0 OR ( ( SELECT COUNT( ID ) FROM Commands WHERE Promotable <> 0 AND Machine <> '' ) = 0 ) )
		-- Confirm the OS type and primariness
		AND ( @PrimaryBuild = Commands.PrimaryBuild )
		AND ( ( @MachineName LIKE Commands.MachineLock ) OR ( Commands.MachineLock = 'None' AND @AnyMachine = 1 ) )

	if @Trigger != 0 UPDATE Commands SET Pending = 0 WHERE
		( ID = @Trigger )

	SELECT @Trigger
	COMMIT

RETURN
GO
/****** Object:  StoredProcedure [dbo].[CheckTimedBuild2]    Script Date: 03/30/2011 19:36:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[CheckTimedBuild2]
	@MachineName varchar(32),
	@AnyMachine bit,
	@PrimaryBuild bit
AS
	SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;

	BEGIN TRAN
	DECLARE @Trigger INT
	SET @Trigger = 0

	SELECT
		@Trigger = Commands.ID
	FROM Commands, Builders, Branches, BranchConfig
	WHERE	( ( Commands.NextTrigger is not null ) AND ( GETDATE() > Commands.NextTrigger ) )
		-- Grab the live builder row
		AND ( ( Builders.Machine = @MachineName ) AND ( Builders.State != 'Dead' ) AND ( Builders.State != 'Zombied' ) )
		-- Make sure the SDK versions match if required
		AND	( Commands.LockXDK = 0 OR ( Builders.X360_SDKVersion = BranchConfig.XDKVersion AND Commands.Branch = BranchConfig.Branch ) )
	    AND ( Commands.LockPDK = 0 OR ( Builders.PS3_SDKVersion = BranchConfig.PS3SDKVersion AND Commands.Branch = BranchConfig.Branch ) )
		-- Make sure the builder has the branch
		AND	( Branches.Branch = Commands.Branch )
		AND ( Branches.BuilderID = Builders.ID )
		-- Make sure no other promotable builds are running
		AND ( Commands.Promotable = 0 OR ( ( SELECT COUNT( ID ) FROM Commands WHERE Promotable <> 0 AND Machine <> '' ) = 0 ) )
		-- Confirm the OS type and primariness
		AND ( @PrimaryBuild = Commands.PrimaryBuild )
		AND ( ( @MachineName LIKE Commands.MachineLock ) OR ( Commands.MachineLock = 'None' AND @AnyMachine = 1 ) )

	if @Trigger != 0 UPDATE Commands SET Commands.NextTrigger = DATEADD( minute, Commands.NextTriggerDelay, Commands.NextTrigger ) WHERE
		( ID = @Trigger )

	SELECT @Trigger
	COMMIT

RETURN
GO
/****** Object:  StoredProcedure [dbo].[CheckJob2]    Script Date: 03/30/2011 19:36:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[CheckJob2]
	@MachineName varchar(32),
	@PrimaryBuild bit
AS
	SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;

	BEGIN TRAN
	DECLARE @Trigger INT
	SET @Trigger = 0

	SELECT TOP (1)
		@Trigger = Jobs.ID
	FROM Jobs, Builders, Branches, BranchConfig
	    -- Check for pending jobs
	WHERE	( Jobs.Active = 0 )
		AND ( Jobs.Complete = 0 )
		AND ( Jobs.Killing = 0 )
		-- Grab the live builder row
		AND ( ( Builders.Machine = @MachineName ) AND ( Builders.State != 'Dead' ) AND ( Builders.State != 'Zombied' ) )
		-- Make sure the SDK versions match if required
		AND	( Jobs.LockXDK = 0 OR ( Builders.X360_SDKVersion = BranchConfig.XDKVersion AND Jobs.Branch = BranchConfig.Branch ) )
	    AND ( Jobs.LockPDK = 0 OR ( Builders.PS3_SDKVersion = BranchConfig.PS3SDKVersion AND Jobs.Branch = BranchConfig.Branch ) )
		-- Make sure the builder has the branch
		AND	( Branches.Branch = Jobs.Branch )
		AND ( Branches.BuilderID = Builders.ID )
		-- Confirm the OS type and primariness
		AND ( @PrimaryBuild = Jobs.PrimaryBuild )
	ORDER BY Jobs.Label

	IF @Trigger != 0 UPDATE Jobs SET Active = 1 WHERE
		( ID = @Trigger )

	SELECT @Trigger
	COMMIT

RETURN
GO
/****** Object:  StoredProcedure [dbo].[StatCooks]    Script Date: 03/30/2011 19:36:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[StatCooks]

AS

SELECT COUNT( BuildStarted ) AS CommandCount
FROM BuildLog
WHERE ( DATEDIFF( day, BuildStarted, GETDATE() ) < 8 )
AND ( SUBSTRING( Command, 1, 4 ) = 'Cook' )

	RETURN
GO
/****** Object:  StoredProcedure [dbo].[StatCompileJobs]    Script Date: 03/30/2011 19:36:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[StatCompileJobs]

AS

SELECT COUNT( BuildStarted ) AS CommandCount
FROM BuildLog
WHERE ( DATEDIFF( day, BuildStarted, GETDATE() ) < 8 )
AND ( SUBSTRING( Command, 1, 11 ) = 'Jobs/Unreal' )

	RETURN
GO
/****** Object:  StoredProcedure [dbo].[StatCISJobs]    Script Date: 03/30/2011 19:36:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[StatCISJobs]

AS

SELECT COUNT( BuildStarted ) AS CommandCount
FROM BuildLog
WHERE ( DATEDIFF( day, BuildStarted, GETDATE() ) < 8 )
AND ( SUBSTRING( Command, 1, 8 ) = 'Jobs/CIS' )

RETURN
GO
/****** Object:  StoredProcedure [dbo].[StatBuildCount]    Script Date: 03/30/2011 19:36:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[StatBuildCount]

AS

SELECT COUNT( BuildStarted ) AS CommandCount
FROM BuildLog
WHERE ( DATEDIFF( day, BuildStarted, GETDATE() ) < 8 )
AND ( SUBSTRING( Command, 1, 5 ) = 'Build' )

RETURN
GO
/****** Object:  StoredProcedure [dbo].[SetConchTime]    Script Date: 03/30/2011 19:36:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[SetConchTime]

	@CommandID INT

AS

	BEGIN TRAN
	DECLARE @Count INT
	SELECT @Count = COUNT( ID ) FROM Commands WHERE ( ConchHolder is not NULL )
	if @Count = 0 UPDATE Commands SET ConchHolder = GETUTCDATE() WHERE ( ID = @CommandID )
	SELECT @Count
	COMMIT

RETURN
GO
/****** Object:  StoredProcedure [dbo].[SelectVerifyStatus]    Script Date: 03/30/2011 19:36:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[SelectVerifyStatus]

AS

SELECT C.BuildLogID, B.ID, C.Machine, B.ChangeList, B.CurrentStatus, B.BuildStarted, C.Operator, C.Description
FROM Commands C, BuildLog B
WHERE ( C.BuildLogID = B.ID ) AND ( PrimaryBuild = 0 )
ORDER BY B.BuildStarted

	RETURN
GO
/****** Object:  StoredProcedure [dbo].[SelectJobStatus]    Script Date: 03/30/2011 19:36:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[SelectJobStatus]

AS

	SELECT J.BuildLogID, B.ID, J.Machine, B.BuildStarted, B.CurrentStatus FROM Jobs J, BuildLog B WHERE
		( J.BuildLogID = B.ID )
		AND ( Active = 1 )
		AND ( Complete = 0 )
		ORDER BY B.BuildStarted

RETURN
GO
/****** Object:  StoredProcedure [dbo].[SelectBuildStatus]    Script Date: 03/30/2011 19:36:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[SelectBuildStatus]

AS

SELECT DISTINCT
                         Commands.BuildLogID, Commands.Operator, Commands.Description, Commands.Machine, BuildLog.ChangeList, BuildLog.ID, BuildLog.CurrentStatus,
                         BuildLog.BuildStarted, Builders.CurrentTime
FROM            Commands INNER JOIN
                         BuildLog ON Commands.BuildLogID = BuildLog.ID INNER JOIN
                         Builders ON BuildLog.Machine = Builders.Machine
WHERE        (Commands.PrimaryBuild = 1) AND (Builders.State = 'Building')
ORDER BY BuildLog.BuildStarted
RETURN
GO
/****** Object:  StoredProcedure [dbo].[SelectBuilds]    Script Date: 03/30/2011 19:36:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[SelectBuilds]

	@DisplayID int,
	@DisplayDetailID int

AS

	SELECT Description, LastGoodChangeList, DATEADD( MINUTE, DATEDIFF( MINUTE, GETUTCDATE(), GETDATE() ), LastGoodDateTime ) AS LastGoodDateTime,
		CASE Pending WHEN 0 THEN '' WHEN 1 THEN '(Build Pending)' END AS Status,
		CASE WHEN LastGoodLabel is null THEN '' WHEN LastGoodLabel is not null THEN '{' + LastGoodLabel + '}' END AS DisplayLabel
		FROM [Commands] WHERE
			( LastGoodDateTime is not null )
			AND ( ( @DisplayID != 0 AND ( Display = @DisplayID ) )
			OR ( @DisplayDetailID != 0 AND ( DisplayDetail = @DisplayDetailID ) ) )
				ORDER BY LastGoodChangeList DESC, LastGoodDateTime DESC

RETURN
GO
/****** Object:  StoredProcedure [dbo].[SelectActiveBuilders]    Script Date: 03/30/2011 19:36:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[SelectActiveBuilders]

AS

SELECT CurrentTime, Machine FROM Builders
WHERE ( State = 'Connected' ) AND ( CurrentTime is NOT null ) AND ( DATEDIFF( Day, GETUTCDATE(), CurrentTime ) > -1 )
ORDER BY Machine

RETURN
GO
/****** Object:  Table [dbo].[PerformanceData]    Script Date: 03/30/2011 19:36:24 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[PerformanceData](
	[AppID] [dbo].[KeyID] NOT NULL,
	[MachineID] [dbo].[KeyID] NOT NULL,
	[CounterID] [dbo].[KeyID] NOT NULL,
	[IntValue] [bigint] NOT NULL,
	[DateTimeStamp] [datetime] NOT NULL
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[PerformanceCounters]    Script Date: 03/30/2011 19:36:24 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[PerformanceCounters](
	[ID] [dbo].[KeyID] IDENTITY(1,1) NOT NULL,
	[CounterName] [dbo].[FixedString] NOT NULL,
 CONSTRAINT [PK_PerformanceCounters] PRIMARY KEY CLUSTERED
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Machines]    Script Date: 03/30/2011 19:36:24 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Machines](
	[ID] [dbo].[KeyID] IDENTITY(1,1) NOT NULL,
	[MachineName] [dbo].[FixedString] NOT NULL,
	[Notes] [dbo].[String] NULL,
 CONSTRAINT [PK_Machine] PRIMARY KEY CLUSTERED
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY],
 CONSTRAINT [Unique_MachineName] UNIQUE NONCLUSTERED
(
	[MachineName] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  StoredProcedure [dbo].[GetTriggerable2]    Script Date: 03/30/2011 19:36:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[GetTriggerable2]

	@MinAccess int,
	@MaxAccess int,
	@UserDetail int

AS

	SELECT [ID], [Description], [Command], [Hint], [UserLevel], [Machine], [MachineLock]
	FROM [Commands] WHERE
		( Access >= @MinAccess AND Access < @MaxAccess AND UserLevel <= @UserDetail  )
			ORDER BY Access

RETURN
GO
/****** Object:  StoredProcedure [dbo].[GetTriggerable]    Script Date: 03/30/2011 19:36:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[GetTriggerable]

	@MinAccess int,
	@MaxAccess int

AS

	SELECT [ID], [Description], [Command], [Hint], [Machine], [MachineLock]
	FROM [Commands] WHERE
		( Access >= @MinAccess AND Access < @MaxAccess )
			ORDER BY Access

RETURN
GO
/****** Object:  StoredProcedure [dbo].[StatVerifications]    Script Date: 03/30/2011 19:36:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[StatVerifications]

AS

SELECT COUNT( BuildStarted ) AS CommandCount
FROM BuildLog
WHERE ( DATEDIFF( day, BuildStarted, GETDATE() ) < 8 )
AND ( SUBSTRING( Command, 1, 3 ) = 'CIS' )
AND Command <> 'CIS/ProcessP4Changes' AND Command <> 'CIS/UpdateMonitorValues'

	RETURN
GO
/****** Object:  StoredProcedure [dbo].[StatPromotions]    Script Date: 03/30/2011 19:36:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[StatPromotions]

AS
SELECT COUNT( BuildStarted ) AS CommandCount
FROM BuildLog
WHERE ( DATEDIFF( day, BuildStarted, GETDATE() ) < 8 )
AND ( SUBSTRING( Command, 1, 7 ) = 'Promote' )

	RETURN
GO
/****** Object:  StoredProcedure [dbo].[StatPCS]    Script Date: 03/30/2011 19:36:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[StatPCS]

AS
SELECT COUNT( BuildStarted ) AS CommandCount
FROM BuildLog
WHERE ( DATEDIFF( day, BuildStarted, GETDATE() ) < 8 )
AND ( SUBSTRING( Command, 1, 3 ) = 'PCS' )
	RETURN
GO
/****** Object:  StoredProcedure [dbo].[GetActiveBuilderCount]    Script Date: 03/30/2011 19:36:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[GetActiveBuilderCount]

AS
   BEGIN TRAN

   SELECT COUNT( ID ) FROM [Builders] WHERE ( State = 'Connected' ) AND ( DATEDIFF( minute, CurrentTime, GETDATE() ) < 100 )

   COMMIT

   RETURN
GO
/****** Object:  StoredProcedure [dbo].[GetMachineID]    Script Date: 03/30/2011 19:36:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[GetMachineID]
	(
	@MachineName FixedString
	)
AS
	SET NOCOUNT ON

	DECLARE @MachineID KeyID

	SET @MachineID = (SELECT ID FROM dbo.Machines WHERE MachineName = @MachineName)

	IF (@MachineID IS NULL)
	BEGIN
		INSERT INTO dbo.Machines (MachineName) VALUES (@MachineName)
		SET @MachineID = @@IDENTITY
	END

	RETURN @MachineID
GO
/****** Object:  StoredProcedure [dbo].[GetCounterID]    Script Date: 03/30/2011 19:36:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[GetCounterID]
	(
	@CounterName FixedString
	)
AS
	SET NOCOUNT ON

	DECLARE @CounterID KeyID

	SET @CounterID = (SELECT ID FROM dbo.PerformanceCounters WHERE CounterName = @CounterName)

	IF (@CounterID IS NULL)
	BEGIN
		INSERT INTO dbo.PerformanceCounters (CounterName) VALUES (@CounterName)
		SET @CounterID = @@IDENTITY
	END

	RETURN @CounterID
GO
/****** Object:  StoredProcedure [dbo].[GetAppID]    Script Date: 03/30/2011 19:36:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[GetAppID]
	(
	@AppName FixedString
	)
AS
	SET NOCOUNT ON

	DECLARE @AppID KeyID

	SET @AppID = (SELECT ID FROM dbo.Applications WHERE AppName = @AppName)

	IF (@AppID IS NULL)
	BEGIN
		INSERT INTO dbo.Applications (AppName) VALUES (@AppName)
		SET @AppID = @@IDENTITY
	END

	RETURN @AppID
GO
/****** Object:  StoredProcedure [dbo].[StatGBSubmittedToPerforce]    Script Date: 03/30/2011 19:36:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[StatGBSubmittedToPerforce]

AS

SELECT SUM( IntValue ) / ( 1024.0 * 1024.0 * 1024.0 ) FROM PerformanceData
WHERE ( CounterID = 1077 AND DATEDIFF( day, DateTimeStamp, GETDATE() ) < 8 )

RETURN
GO
/****** Object:  StoredProcedure [dbo].[StatGBPublished]    Script Date: 03/30/2011 19:36:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[StatGBPublished]

AS

SELECT SUM( IntValue ) / ( 1024.0 * 1024.0 * 1024.0 ) FROM PerformanceData
WHERE ( CounterID = 1079 OR CounterID = 1080 OR CounterID = 1081 OR CounterID = 1082 )
AND DATEDIFF( day, DateTimeStamp, GETDATE() ) < 8

RETURN
GO
/****** Object:  StoredProcedure [dbo].[StatGBFTPd]    Script Date: 03/30/2011 19:36:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[StatGBFTPd]

AS

SELECT SUM( IntValue ) / ( 1024.0 * 1024.0 * 1024.0 ) FROM PerformanceData
WHERE ( CounterID = 1078 AND DATEDIFF( day, DateTimeStamp, GETDATE() ) < 8 )

RETURN
GO
/****** Object:  StoredProcedure [dbo].[CreatePerformanceData]    Script Date: 03/30/2011 19:36:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[CreatePerformanceData]
	(
		@CounterName FixedString,
		@MachineName FixedString,
		@AppName FixedString,
		@IntValue bigint,
		@DateTimeStamp datetime
	)
AS

	DECLARE @AppID KeyID
	DECLARE @MachineID KeyID
	DECLARE @CounterID KeyID

	EXEC @AppID = dbo.GetAppID @AppName
	EXEC @MachineID = dbo.GetMachineID @MachineName
	EXEC @CounterID = dbo.GetCounterID @CounterName

	INSERT INTO dbo.PerformanceData ( AppID, MachineID, CounterID, IntValue, DateTimeStamp ) VALUES ( @AppID, @MachineID, @CounterID, @IntValue, @DateTimeStamp )

	RETURN
GO
/****** Object:  Default [DF_BranchConfig_Version]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_Version]  DEFAULT ((0)) FOR [Version]
GO
/****** Object:  Default [DF_BranchConfig_HeadChangelist]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_HeadChangelist]  DEFAULT ((0)) FOR [HeadChangelist]
GO
/****** Object:  Default [DF_BranchConfig_LastGoodOverall]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastGoodOverall]  DEFAULT ((-1)) FOR [LastGoodOverall]
GO
/****** Object:  Default [DF_BranchConfig_LastFailedOverall]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastFailedOverall]  DEFAULT ((-1)) FOR [LastFailOverall]
GO
/****** Object:  Default [DF_BranchConfig_LastChangelistProcessed]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastChangelistProcessed]  DEFAULT ((-1)) FOR [LastAttemptedOverall]
GO
/****** Object:  Default [DF_BranchConfig_LastGoodXbox360]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastGoodXbox360]  DEFAULT ((-1)) FOR [LastGoodXbox360]
GO
/****** Object:  Default [DF_BranchConfig_LastFailXbox360]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastFailXbox360]  DEFAULT ((-1)) FOR [LastFailXbox360]
GO
/****** Object:  Default [DF_BranchConfig_LastGoodSonyPS3]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastGoodSonyPS3]  DEFAULT ((-1)) FOR [LastGoodPS3]
GO
/****** Object:  Default [DF_BranchConfig_LastFailSonyPS3]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastFailSonyPS3]  DEFAULT ((-1)) FOR [LastFailPS3]
GO
/****** Object:  Default [DF_BranchConfig_LastGoodTools]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastGoodTools]  DEFAULT ((-1)) FOR [LastGoodTools]
GO
/****** Object:  Default [DF_BranchConfig_LastFailTools]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastFailTools]  DEFAULT ((-1)) FOR [LastFailTools]
GO
/****** Object:  Default [DF_BranchConfig_LastGoodMobile]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastGoodMobile]  DEFAULT ((-1)) FOR [LastGoodMobileDevice]
GO
/****** Object:  Default [DF_BranchConfig_LastFailMobile]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastFailMobile]  DEFAULT ((-1)) FOR [LastFailMobileDevice]
GO
/****** Object:  Default [DF_BranchConfig_LastGoodExample]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastGoodExample]  DEFAULT ((-1)) FOR [LastGoodExample]
GO
/****** Object:  Default [DF_BranchConfig_LastFailExample]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastFailExample]  DEFAULT ((-1)) FOR [LastFailExample]
GO
/****** Object:  Default [DF_BranchConfig_LastGoodNano]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastGoodNano]  DEFAULT ((-1)) FOR [LastGoodNano]
GO
/****** Object:  Default [DF_BranchConfig_LastFailNano]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastFailNano]  DEFAULT ((-1)) FOR [LastFailNano]
GO
/****** Object:  Default [DF_BranchConfig_LastGoodNano1]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastGoodNano1]  DEFAULT ((-1)) FOR [LastGoodNanoMobile]
GO
/****** Object:  Default [DF_BranchConfig_LastFailNano1]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastFailNano1]  DEFAULT ((-1)) FOR [LastFailNanoMobile]
GO
/****** Object:  Default [DF_BranchConfig_LastGoodGear]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastGoodGear]  DEFAULT ((-1)) FOR [LastGoodGear]
GO
/****** Object:  Default [DF_BranchConfig_LastFailGear]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastFailGear]  DEFAULT ((-1)) FOR [LastFailGear]
GO
/****** Object:  Default [DF_BranchConfig_LastGoodUDK]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastGoodUDK]  DEFAULT ((-1)) FOR [LastGoodUDK]
GO
/****** Object:  Default [DF_BranchConfig_LastFailUDK]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastFailUDK]  DEFAULT ((-1)) FOR [LastFailUDK]
GO
/****** Object:  Default [DF_BranchConfig_LastGoodUDK1]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastGoodUDK1]  DEFAULT ((-1)) FOR [LastGoodMobile]
GO
/****** Object:  Default [DF_BranchConfig_LastFailUDK1]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastFailUDK1]  DEFAULT ((-1)) FOR [LastFailMobile]
GO
/****** Object:  Default [DF_BranchConfig_LastAttemptedXbox360]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastAttemptedXbox360]  DEFAULT ((-1)) FOR [LastAttemptedXbox360]
GO
/****** Object:  Default [DF_BranchConfig_LastAttemptedSonyPS3]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastAttemptedSonyPS3]  DEFAULT ((-1)) FOR [LastAttemptedPS3]
GO
/****** Object:  Default [DF_BranchConfig_LastAttemptedTools]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastAttemptedTools]  DEFAULT ((-1)) FOR [LastAttemptedTools]
GO
/****** Object:  Default [DF_BranchConfig_LastAttemptedMobile]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastAttemptedMobile]  DEFAULT ((-1)) FOR [LastAttemptedMobileDevice]
GO
/****** Object:  Default [DF_BranchConfig_LastAttemptedExample]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastAttemptedExample]  DEFAULT ((-1)) FOR [LastAttemptedExample]
GO
/****** Object:  Default [DF_BranchConfig_LastAttemptedNano]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastAttemptedNano]  DEFAULT ((-1)) FOR [LastAttemptedNano]
GO
/****** Object:  Default [DF_BranchConfig_LastAttemptedNano1]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastAttemptedNano1]  DEFAULT ((-1)) FOR [LastAttemptedNanoMobile]
GO
/****** Object:  Default [DF_BranchConfig_LastAttemptedGear]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastAttemptedGear]  DEFAULT ((-1)) FOR [LastAttemptedGear]
GO
/****** Object:  Default [DF_BranchConfig_LastAttemptedUDK]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastAttemptedUDK]  DEFAULT ((-1)) FOR [LastAttemptedUDK]
GO
/****** Object:  Default [DF_BranchConfig_LastAttemptedUDK1]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BranchConfig] ADD  CONSTRAINT [DF_BranchConfig_LastAttemptedUDK1]  DEFAULT ((-1)) FOR [LastAttemptedMobile]
GO
/****** Object:  Default [DF_Builders_PS3_SDKVersion]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[Builders] ADD  CONSTRAINT [DF_Builders_PS3_SDKVersion]  DEFAULT ('None') FOR [PS3_SDKVersion]
GO
/****** Object:  Default [DF_Builders_X360_SDKVersion]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[Builders] ADD  CONSTRAINT [DF_Builders_X360_SDKVersion]  DEFAULT ('None') FOR [X360_SDKVersion]
GO
/****** Object:  Default [DF_Builders_X360_SDKVersion1]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[Builders] ADD  CONSTRAINT [DF_Builders_X360_SDKVersion1]  DEFAULT ('None') FOR [DX_SDKVersion]
GO
/****** Object:  Default [DF_BuildLog_BranchID]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[BuildLog] ADD  CONSTRAINT [DF_BuildLog_BranchID]  DEFAULT ((1)) FOR [BranchConfigID]
GO
/****** Object:  Default [DF_Commands_Hint]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[Commands] ADD  CONSTRAINT [DF_Commands_Hint]  DEFAULT ('Black') FOR [Hint]
GO
/****** Object:  Default [DF_Commands_PrimaryBuild]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[Commands] ADD  CONSTRAINT [DF_Commands_PrimaryBuild]  DEFAULT ((0)) FOR [PrimaryBuild]
GO
/****** Object:  Default [DF_Jobs_Active]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[Jobs] ADD  CONSTRAINT [DF_Jobs_Active]  DEFAULT ((0)) FOR [Active]
GO
/****** Object:  Default [DF_Jobs_Complete]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[Jobs] ADD  CONSTRAINT [DF_Jobs_Complete]  DEFAULT ((0)) FOR [Complete]
GO
/****** Object:  Default [DF_Jobs_Succeeded]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[Jobs] ADD  CONSTRAINT [DF_Jobs_Succeeded]  DEFAULT ((0)) FOR [Succeeded]
GO
/****** Object:  Default [DF_Jobs_Copied]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[Jobs] ADD  CONSTRAINT [DF_Jobs_Copied]  DEFAULT ((0)) FOR [Copied]
GO
/****** Object:  Default [DF_PerformanceData_IntValue]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[PerformanceData] ADD  CONSTRAINT [DF_PerformanceData_IntValue]  DEFAULT ((0)) FOR [IntValue]
GO
/****** Object:  ForeignKey [FK_Commands_Commands]    Script Date: 03/30/2011 19:36:24 ******/
ALTER TABLE [dbo].[Commands]  WITH CHECK ADD  CONSTRAINT [FK_Commands_Commands] FOREIGN KEY([ID])
REFERENCES [dbo].[Commands] ([ID])
GO
ALTER TABLE [dbo].[Commands] CHECK CONSTRAINT [FK_Commands_Commands]
GO
