USE [EngineTaskPerf]
GO
/****** Object:  Table [dbo].[Tasks]    Script Date: 12/21/2010 14:21:57 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Tasks](
	[TaskID] [int] IDENTITY(1,1) NOT NULL,
	[Duration] [float] NOT NULL,
	[PlatformName] [varchar](64) NOT NULL,
	[ConfigName] [varchar](64) NOT NULL,
	[MachineName] [char](32) NOT NULL,
	[UserName] [varchar](64) NOT NULL,
	[GameName] [char](32) NOT NULL,
	[TaskDescription] [varchar](255) NOT NULL,
	[TaskParameter] [varchar](255) NOT NULL,
	[Changelist] [int] NOT NULL,
	[CmdLine] [varchar](max) NOT NULL,
	[Date] [datetime] NOT NULL
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  StoredProcedure [dbo].[AddTask]    Script Date: 12/21/2010 14:21:57 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE PROCEDURE [dbo].[AddTask]
	@Duration float,
	@PlatformName varchar(64),
	@ConfigName varchar(64),
	@Changelist int,
	@MachineName varchar(32),
	@UserName varchar(64),
	@GameName varchar(32),
	@TaskDescription varchar(255),
	@TaskParameter varchar(255),
	@CmdLine varchar(MAX),
	@Date datetime = NULL
AS
BEGIN
	BEGIN TRANSACTION
		-- SET NOCOUNT ON added to prevent extra result sets from
		-- interfering with SELECT statements.
		SET NOCOUNT ON;

		-- Set date if it wasn't passed in.
		IF (@Date IS NULL)
		BEGIN
			SET @Date = GETDATE()
		END

		-- Add run to DB and return its ID.
		DECLARE @RunID int
		INSERT INTO dbo.Tasks	(Duration,PlatformName,ConfigName,Changelist,MachineName,UserName,GameName,TaskDescription,TaskParameter,CmdLine,Date)
					VALUES		(@Duration,@PlatformName,@ConfigName,@Changelist,@MachineName,@UserName,@GameName,@TaskDescription,@TaskParameter,@CmdLine,@Date)
		SET @RunID = @@IDENTITY

	COMMIT TRANSACTION
END
GO
