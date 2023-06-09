SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[Machines]') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[Machines](
	[MachineID] [int] IDENTITY(1,1) NOT NULL,
	[MachineName] [nvarchar](128) NOT NULL,
 CONSTRAINT [PK_Machines] PRIMARY KEY CLUSTERED 
(
	[MachineID] ASC
)WITH (PAD_INDEX  = OFF, IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
END
GO

IF NOT EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[Machines]') AND name = N'IK_MachineNames')
CREATE UNIQUE NONCLUSTERED INDEX [IK_MachineNames] ON [dbo].[Machines] 
(
	[MachineName] ASC
)WITH (PAD_INDEX  = OFF, IGNORE_DUP_KEY = OFF) ON [PRIMARY]
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[Executables]') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[Executables](
	[ExecutableID] [int] IDENTITY(1,1) NOT NULL,
	[ExecutableName] [nvarchar](128) NOT NULL,
 CONSTRAINT [PK_Executables] PRIMARY KEY CLUSTERED 
(
	[ExecutableID] ASC
)WITH (PAD_INDEX  = OFF, IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
END
GO

IF NOT EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[Executables]') AND name = N'IK_ExecutableNames')
CREATE UNIQUE NONCLUSTERED INDEX [IK_ExecutableNames] ON [dbo].[Executables] 
(
	[ExecutableName] ASC
)WITH (PAD_INDEX  = OFF, IGNORE_DUP_KEY = OFF) ON [PRIMARY]
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[Games]') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[Games](
	[GameID] [int] IDENTITY(1,1) NOT NULL,
	[GameName] [nvarchar](32) NOT NULL,
 CONSTRAINT [PK_Games] PRIMARY KEY CLUSTERED 
(
	[GameID] ASC
)WITH (PAD_INDEX  = OFF, IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
END
GO

IF NOT EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[Games]') AND name = N'IK_GameNames')
CREATE UNIQUE NONCLUSTERED INDEX [IK_GameNames] ON [dbo].[Games] 
(
	[GameName] ASC
)WITH (PAD_INDEX  = OFF, IGNORE_DUP_KEY = OFF) ON [PRIMARY]
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[Groups]') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[Groups](
	[GroupID] [int] IDENTITY(1,1) NOT NULL,
	[GroupName] [nvarchar](128) NOT NULL,
 CONSTRAINT [PK_Groups] PRIMARY KEY CLUSTERED 
(
	[GroupID] ASC
)WITH (PAD_INDEX  = OFF, IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
END
GO

IF NOT EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[Groups]') AND name = N'IK_GroupNames')
CREATE UNIQUE NONCLUSTERED INDEX [IK_GroupNames] ON [dbo].[Groups] 
(
	[GroupName] ASC
)WITH (PAD_INDEX  = OFF, IGNORE_DUP_KEY = OFF) ON [PRIMARY]
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[Maps]') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[Maps](
	[MapID] [int] IDENTITY(1,1) NOT NULL,
	[MapName] [nvarchar](64) NOT NULL,
 CONSTRAINT [PK_Maps] PRIMARY KEY CLUSTERED 
(
	[MapID] ASC
)WITH (PAD_INDEX  = OFF, IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
END
GO

IF NOT EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[Maps]') AND name = N'IK_MapNames')
CREATE UNIQUE NONCLUSTERED INDEX [IK_MapNames] ON [dbo].[Maps] 
(
	[MapName] ASC
)WITH (PAD_INDEX  = OFF, IGNORE_DUP_KEY = OFF) ON [PRIMARY]
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[Quality]') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[Quality](
	[QualityID] [int] IDENTITY(1,1) NOT NULL,
	[QualityName] [nvarchar](32) NOT NULL,
 CONSTRAINT [PK_Quality] PRIMARY KEY CLUSTERED 
(
	[QualityID] ASC
)WITH (PAD_INDEX  = OFF, IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
END
GO

IF NOT EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[Quality]') AND name = N'IK_QualityNames')
CREATE UNIQUE NONCLUSTERED INDEX [IK_QualityNames] ON [dbo].[Quality] 
(
	[QualityName] ASC
)WITH (PAD_INDEX  = OFF, IGNORE_DUP_KEY = OFF) ON [PRIMARY]
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[Jobs]') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[Jobs](
	[JobID] [int] IDENTITY(1,1) NOT NULL,
	[Date] [datetime] NOT NULL,
	[Duration] [float] NOT NULL,
	[UserID] [int] NOT NULL,
	[MachineID] [int] NOT NULL,
	[GroupID] [int] NOT NULL,
	[JobGUID] [nvarchar](64) NOT NULL,
	[Instigator] [bit] NOT NULL,
	[DistributionEnabled] [bit] NOT NULL,
	[RemoteMachineCount] [int] NOT NULL,
	[ExecutableID] [int] NOT NULL,
	[Parameters] [nvarchar](256) NOT NULL,
	[JobWasSuccess] [bit] NOT NULL,
	[TotalTaskCount] [int] NOT NULL,
	[DistributedTaskCount] [int] NOT NULL,
	[RestartedTaskCount] [int] NOT NULL,
	[CacheHitRate] [float] NOT NULL,
	[NetworkBytesSent] [bigint] NOT NULL,
	[NetworkBytesReceived] [bigint] NOT NULL,
	[PeakVirtualMemoryUsed] [bigint] NOT NULL,
	[PeakPhysicalMemoryUsed] [bigint] NOT NULL,
	[TotalProcessorTime] [float] NOT NULL,
	[ExitCode] [int] NOT NULL,
	[QualityID] [int] NOT NULL,
	[GameID] [int] NOT NULL,
	[MapID] [int] NOT NULL,
 CONSTRAINT [PK_Jobs] PRIMARY KEY CLUSTERED 
(
	[JobID] ASC
)WITH (PAD_INDEX  = OFF, IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
END
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[Users]') AND type in (N'U'))
BEGIN
CREATE TABLE [dbo].[Users](
	[UserID] [int] IDENTITY(1,1) NOT NULL,
	[UserName] [nvarchar](32) NOT NULL,
 CONSTRAINT [PK_Users] PRIMARY KEY CLUSTERED 
(
	[UserID] ASC
)WITH (PAD_INDEX  = OFF, IGNORE_DUP_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
END
GO

IF NOT EXISTS (SELECT * FROM sys.indexes WHERE object_id = OBJECT_ID(N'[dbo].[Users]') AND name = N'IK_UserNames')
CREATE UNIQUE NONCLUSTERED INDEX [IK_UserNames] ON [dbo].[Users] 
(
	[UserName] ASC
)WITH (PAD_INDEX  = OFF, IGNORE_DUP_KEY = OFF) ON [PRIMARY]
GO
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
IF NOT EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[AddJob_v1]') AND type in (N'P', N'PC'))
BEGIN
EXEC dbo.sp_executesql @statement = N'
CREATE PROCEDURE [dbo].[AddJob_v1]
	@Duration float,
	@UserName nvarchar(32),
	@MachineName nvarchar(128),
	@GroupName nvarchar(128),
	@JobGUID nvarchar(64),
	@Instigator bit,
	@DistributionEnabled bit,
	@RemoteMachineCount int,
	@ExecutableName nvarchar(128),
	@Parameters nvarchar(256),
	@JobWasSuccess bit,
	@TotalTaskCount int,
	@DistributedTaskCount int,
	@RestartedTaskCount int,
	@CacheHitRate float,
	@NetworkBytesSent bigint,
	@NetworkBytesReceived bigint,
	@PeakVirtualMemoryUsed bigint,
	@PeakPhysicalMemoryUsed bigint,
	@TotalProcessorTime float,
	@ExitCode int,
	@QualityName nvarchar(32),
	@GameName nvarchar(32),
	@MapName nvarchar(64)

AS
BEGIN
	BEGIN TRANSACTION

		-- SET NOCOUNT ON added to prevent extra result sets from
		-- interfering with SELECT statements.
		SET NOCOUNT ON;
	
		-- Get UserID, add if it doesn''t exist yet.
		DECLARE @UserID int
		SET @UserID = (SELECT UserID FROM dbo.Users WHERE UserName = @UserName)
		IF (@UserID IS NULL)
		BEGIN
			INSERT INTO dbo.Users (UserName) VALUES (@UserName)
			SET @UserID = @@IDENTITY
		END

		-- Get MachineID, add if it doesn''t exist yet.
		DECLARE @MachineID int
		SET @MachineID = (SELECT MachineID FROM dbo.Machines WHERE MachineName = @MachineName)
		IF (@MachineID IS NULL)
		BEGIN
			INSERT INTO dbo.Machines (MachineName) VALUES (@MachineName)
			SET @MachineID = @@IDENTITY
		END

		-- Get GroupID, add if it doesn''t exist yet.
		DECLARE @GroupID int
		SET @GroupID = (SELECT GroupID FROM dbo.Groups WHERE GroupName = @GroupName)
		IF (@GroupID IS NULL)
		BEGIN
			INSERT INTO dbo.Groups (GroupName) VALUES (@GroupName)
			SET @GroupID = @@IDENTITY
		END

		-- Get ExecutableID, add if it doesn''t exist yet.
		DECLARE @ExecutableID int
		SET @ExecutableID = (SELECT ExecutableID FROM dbo.Executables WHERE ExecutableName = @ExecutableName)
		IF (@ExecutableID IS NULL)
		BEGIN
			INSERT INTO dbo.Executables (ExecutableName) VALUES (@ExecutableName)
			SET @ExecutableID = @@IDENTITY
		END

		-- Get QualityID, add if it doesn''t exist yet.
		DECLARE @QualityID int
		SET @QualityID = (SELECT QualityID FROM dbo.Quality WHERE QualityName = @QualityName)
		IF (@QualityID IS NULL)
		BEGIN
			INSERT INTO dbo.Quality (QualityName) VALUES (@QualityName)
			SET @QualityID = @@IDENTITY
		END

		-- Get GameID, add if it doesn''t exist yet.
		DECLARE @GameID int
		SET @GameID = (SELECT GameID FROM dbo.Games WHERE GameName = @GameName)
		IF (@GameID IS NULL)
		BEGIN
			INSERT INTO dbo.Games (GameName) VALUES (@GameName)
			SET @GameID = @@IDENTITY
		END

		-- Get MapID, add if it doesn''t exist yet.
		DECLARE @MapID int
		SET @MapID = (SELECT MapID FROM dbo.Maps WHERE MapName = @MapName)
		IF (@MapID IS NULL)
		BEGIN
			INSERT INTO dbo.Maps (MapName) VALUES (@MapName)
			SET @MapID = @@IDENTITY
		END

		-- Set date.
		DECLARE @Date datetime
		SET @Date = GETUTCDATE()
	
		-- Add job to DB.
		INSERT INTO dbo.Jobs (	Date,
								Duration,
								UserID,
								MachineID,
								GroupID,
								JobGUID,
								Instigator,
								DistributionEnabled,
								RemoteMachineCount,
								ExecutableID,
								Parameters,
								JobWasSuccess,
								TotalTaskCount,
								DistributedTaskCount,
								RestartedTaskCount,
								CacheHitRate,
								NetworkBytesSent,
								NetworkBytesReceived,
								PeakVirtualMemoryUsed,
								PeakPhysicalMemoryUsed,
								TotalProcessorTime,
								ExitCode,
								QualityID,
								GameID,
								MapID )
					VALUES (	@Date,
								@Duration,
								@UserID,
								@MachineID,
								@GroupID,
								@JobGUID,
								@Instigator,
								@DistributionEnabled,
								@RemoteMachineCount,
								@ExecutableID,
								@Parameters,
								@JobWasSuccess,
								@TotalTaskCount,
								@DistributedTaskCount,
								@RestartedTaskCount,
								@CacheHitRate,
								@NetworkBytesSent,
								@NetworkBytesReceived,
								@PeakVirtualMemoryUsed,
								@PeakPhysicalMemoryUsed,
								@TotalProcessorTime,
								@ExitCode,
								@QualityID,
								@GameID,
								@MapID )

	COMMIT TRANSACTION
END





' 
END
