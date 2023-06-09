USE [UnrealProp]
GO
/****** Object:  Table [dbo].[UserNames]    Script Date: 04/05/2011 18:04:58 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[UserNames](
	[ID] [int] IDENTITY(1,1) NOT NULL,
	[Email] [varchar](64) NOT NULL,
 CONSTRAINT [PK_UserNames] PRIMARY KEY CLUSTERED
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[UPDSNames]    Script Date: 04/05/2011 18:04:58 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[UPDSNames](
	[ID] [int] IDENTITY(1,1) NOT NULL,
	[UPDSName] [varchar](32) NOT NULL,
 CONSTRAINT [PK_UPDSNames] PRIMARY KEY CLUSTERED
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[TaskStatuses]    Script Date: 04/05/2011 18:04:58 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[TaskStatuses](
	[ID] [smallint] IDENTITY(4,1) NOT NULL,
	[Description] [varchar](16) NOT NULL,
 CONSTRAINT [PK_JobStatus] PRIMARY KEY CLUSTERED
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[ClientGroups]    Script Date: 04/05/2011 18:04:58 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[ClientGroups](
	[ID] [int] IDENTITY(1,1) NOT NULL,
	[GroupName] [varchar](32) NOT NULL,
 CONSTRAINT [PK_ClientGroups] PRIMARY KEY CLUSTERED
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[CachedFileInfo]    Script Date: 04/05/2011 18:04:58 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[CachedFileInfo](
	[ID] [bigint] IDENTITY(1,1) NOT NULL,
	[Size] [bigint] NOT NULL,
	[DateAndTime] [datetime] NOT NULL,
	[Hash] [varchar](48) NOT NULL,
 CONSTRAINT [PK_CachedFileInfo] PRIMARY KEY CLUSTERED
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Stats]    Script Date: 04/05/2011 18:04:58 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Stats](
	[ID] [bigint] IDENTITY(1,1) NOT NULL,
	[ProjectID] [smallint] NOT NULL,
	[PlatformID] [smallint] NOT NULL,
	[Count] [bigint] NOT NULL,
	[Scheduled] [datetime] NOT NULL,
	[Completed] [datetime] NOT NULL,
 CONSTRAINT [PK_Stats] PRIMARY KEY CLUSTERED
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Projects]    Script Date: 04/05/2011 18:04:58 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Projects](
	[ID] [smallint] IDENTITY(1,1) NOT NULL,
	[Title] [varchar](32) NOT NULL,
 CONSTRAINT [PK_Projects] PRIMARY KEY CLUSTERED
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Platforms]    Script Date: 04/05/2011 18:04:58 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Platforms](
	[ID] [smallint] IDENTITY(1,1) NOT NULL,
	[Name] [varchar](16) NOT NULL,
 CONSTRAINT [PK_Platforms] PRIMARY KEY CLUSTERED
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[PlatformBuildStatuses]    Script Date: 04/05/2011 18:04:58 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[PlatformBuildStatuses](
	[ID] [smallint] IDENTITY(1,1) NOT NULL,
	[Description] [varchar](64) NOT NULL,
 CONSTRAINT [PK_BuildStatus] PRIMARY KEY CLUSTERED
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Paths]    Script Date: 04/05/2011 18:04:58 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Paths](
	[ID] [bigint] IDENTITY(1,1) NOT NULL,
	[Path] [varchar](256) NOT NULL,
 CONSTRAINT [PK_Paths] PRIMARY KEY CLUSTERED
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Errors]    Script Date: 04/05/2011 18:04:58 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Errors](
	[ID] [int] IDENTITY(1,1) NOT NULL,
	[Error] [varchar](4096) NOT NULL,
 CONSTRAINT [PK_Errors] PRIMARY KEY CLUSTERED
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Defines]    Script Date: 04/05/2011 18:04:58 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Defines](
	[ID] [int] IDENTITY(1,1) NOT NULL,
	[Define] [varchar](16) NOT NULL,
 CONSTRAINT [PK_Defines] PRIMARY KEY CLUSTERED
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[CommandLines]    Script Date: 04/05/2011 18:04:58 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[CommandLines](
	[ID] [int] IDENTITY(1,1) NOT NULL,
	[CommandLine] [varchar](256) NOT NULL,
 CONSTRAINT [PK_CommandLines] PRIMARY KEY CLUSTERED
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[ClientMachines]    Script Date: 04/05/2011 18:04:58 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[ClientMachines](
	[ID] [int] IDENTITY(1,1) NOT NULL,
	[PlatformID] [smallint] NOT NULL,
	[Path] [varchar](256) NOT NULL,
	[Name] [varchar](32) NOT NULL,
	[UserNameID] [int] NOT NULL,
	[UserEmailID] [int] NULL,
	[ClientGroupID] [int] NOT NULL,
	[Reboot] [bit] NOT NULL,
	[UPDSNameID] [int] NOT NULL,
 CONSTRAINT [PK_ClientMachines] PRIMARY KEY CLUSTERED
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[PlatformBuilds]    Script Date: 04/05/2011 18:04:58 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[PlatformBuilds](
	[ID] [bigint] IDENTITY(1,1) NOT NULL,
	[Special] [bit] NOT NULL,
	[PlatformID] [smallint] NOT NULL,
	[ProjectID] [smallint] NOT NULL,
	[DefineAID] [int] NOT NULL,
	[DefineBID] [int] NOT NULL,
	[UserNameID] [int] NOT NULL,
	[Title] [varchar](40) NOT NULL,
	[Path] [varchar](256) NOT NULL,
	[Size] [bigint] NOT NULL,
	[StatusID] [smallint] NOT NULL,
	[DiscoveryTime] [datetime] NOT NULL,
	[BuildTime] [datetime] NULL,
 CONSTRAINT [PK_BuildForPlatform] PRIMARY KEY CLUSTERED
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[BuildConfigs]    Script Date: 04/05/2011 18:04:57 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[BuildConfigs](
	[ID] [smallint] IDENTITY(1,1) NOT NULL,
	[PlatformID] [smallint] NOT NULL,
	[BuildConfig] [varchar](32) NOT NULL,
 CONSTRAINT [PK_BuildConfigs] PRIMARY KEY CLUSTERED
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Tasks]    Script Date: 04/05/2011 18:04:58 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Tasks](
	[ID] [bigint] IDENTITY(1,1) NOT NULL,
	[StatusID] [smallint] NOT NULL,
	[AssignedUPDSID] [int] NOT NULL,
	[ClientMachineID] [int] NOT NULL,
	[UserNameID] [int] NOT NULL,
	[PlatformBuildID] [bigint] NOT NULL,
	[SubmissionTime] [datetime] NOT NULL,
	[ScheduleTime] [datetime] NOT NULL,
	[CompletionTime] [datetime] NULL,
	[ErrorID] [int] NOT NULL,
	[Recurring] [bit] NOT NULL,
	[RunAfterProp] [bit] NOT NULL,
	[BuildConfigID] [smallint] NOT NULL,
	[CommandLineID] [int] NOT NULL,
	[Progress] [smallint] NOT NULL,
	[Priority] [smallint] NOT NULL,
 CONSTRAINT [PK_Tasks] PRIMARY KEY CLUSTERED
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[PlatformBuildFiles]    Script Date: 04/05/2011 18:04:58 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[PlatformBuildFiles](
	[ID] [bigint] IDENTITY(1,1) NOT NULL,
	[PlatformBuildID] [bigint] NOT NULL,
	[PathID] [bigint] NOT NULL,
	[CachedFileInfoID] [bigint] NOT NULL,
 CONSTRAINT [PK_BuildFiles] PRIMARY KEY CLUSTERED
(
	[ID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Default [DF_ClientMachines_UserNameID]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[ClientMachines] ADD  CONSTRAINT [DF_ClientMachines_UserNameID]  DEFAULT ((1)) FOR [UserNameID]
GO
/****** Object:  Default [DF_ClientMachines_Reboot]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[ClientMachines] ADD  CONSTRAINT [DF_ClientMachines_Reboot]  DEFAULT ((1)) FOR [Reboot]
GO
/****** Object:  Default [DF_ClientMachines_UPDSNameID]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[ClientMachines] ADD  CONSTRAINT [DF_ClientMachines_UPDSNameID]  DEFAULT ((1)) FOR [UPDSNameID]
GO
/****** Object:  Default [DF_PlatformBuildFiles_PathID]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[PlatformBuildFiles] ADD  CONSTRAINT [DF_PlatformBuildFiles_PathID]  DEFAULT ((0)) FOR [PathID]
GO
/****** Object:  Default [DF_PlatformBuildFiles_CachedFileInfoID]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[PlatformBuildFiles] ADD  CONSTRAINT [DF_PlatformBuildFiles_CachedFileInfoID]  DEFAULT ((0)) FOR [CachedFileInfoID]
GO
/****** Object:  Default [DF_PlatformBuilds_Special]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[PlatformBuilds] ADD  CONSTRAINT [DF_PlatformBuilds_Special]  DEFAULT ((0)) FOR [Special]
GO
/****** Object:  Default [DF_PlatformBuilds_DefineAID]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[PlatformBuilds] ADD  CONSTRAINT [DF_PlatformBuilds_DefineAID]  DEFAULT ((1)) FOR [DefineAID]
GO
/****** Object:  Default [DF_PlatformBuilds_DefineBID]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[PlatformBuilds] ADD  CONSTRAINT [DF_PlatformBuilds_DefineBID]  DEFAULT ((1)) FOR [DefineBID]
GO
/****** Object:  Default [DF_PlatformBuilds_UserNameID]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[PlatformBuilds] ADD  CONSTRAINT [DF_PlatformBuilds_UserNameID]  DEFAULT ((1)) FOR [UserNameID]
GO
/****** Object:  Default [DF_PlatformBuilds_Date]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[PlatformBuilds] ADD  CONSTRAINT [DF_PlatformBuilds_Date]  DEFAULT ('2007-01-01 10:00:00') FOR [DiscoveryTime]
GO
/****** Object:  Default [DF_Tasks_UserNameID]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[Tasks] ADD  CONSTRAINT [DF_Tasks_UserNameID]  DEFAULT ((1)) FOR [UserNameID]
GO
/****** Object:  Default [DF_Tasks_ErrorID]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[Tasks] ADD  CONSTRAINT [DF_Tasks_ErrorID]  DEFAULT ((1)) FOR [ErrorID]
GO
/****** Object:  Default [DF_Tasks_Recurring]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[Tasks] ADD  CONSTRAINT [DF_Tasks_Recurring]  DEFAULT ((0)) FOR [Recurring]
GO
/****** Object:  Default [DF_Tasks_CommandLineID]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[Tasks] ADD  CONSTRAINT [DF_Tasks_CommandLineID]  DEFAULT ((1)) FOR [CommandLineID]
GO
/****** Object:  Default [DF_Tasks_Progress]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[Tasks] ADD  CONSTRAINT [DF_Tasks_Progress]  DEFAULT ((0)) FOR [Progress]
GO
/****** Object:  Default [DF_Tasks_Priority]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[Tasks] ADD  CONSTRAINT [DF_Tasks_Priority]  DEFAULT ((0)) FOR [Priority]
GO
/****** Object:  ForeignKey [FK_BuildConfigs_Platforms]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[BuildConfigs]  WITH CHECK ADD  CONSTRAINT [FK_BuildConfigs_Platforms] FOREIGN KEY([PlatformID])
REFERENCES [dbo].[Platforms] ([ID])
GO
ALTER TABLE [dbo].[BuildConfigs] CHECK CONSTRAINT [FK_BuildConfigs_Platforms]
GO
/****** Object:  ForeignKey [FK_ClientMachines_ClientGroups]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[ClientMachines]  WITH CHECK ADD  CONSTRAINT [FK_ClientMachines_ClientGroups] FOREIGN KEY([ClientGroupID])
REFERENCES [dbo].[ClientGroups] ([ID])
GO
ALTER TABLE [dbo].[ClientMachines] CHECK CONSTRAINT [FK_ClientMachines_ClientGroups]
GO
/****** Object:  ForeignKey [FK_ClientMachines_Platforms]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[ClientMachines]  WITH CHECK ADD  CONSTRAINT [FK_ClientMachines_Platforms] FOREIGN KEY([PlatformID])
REFERENCES [dbo].[Platforms] ([ID])
GO
ALTER TABLE [dbo].[ClientMachines] CHECK CONSTRAINT [FK_ClientMachines_Platforms]
GO
/****** Object:  ForeignKey [FK_Paths_Paths]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[Paths]  WITH CHECK ADD  CONSTRAINT [FK_Paths_Paths] FOREIGN KEY([ID])
REFERENCES [dbo].[Paths] ([ID])
GO
ALTER TABLE [dbo].[Paths] CHECK CONSTRAINT [FK_Paths_Paths]
GO
/****** Object:  ForeignKey [FK_PlatformBuildFiles_Paths]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[PlatformBuildFiles]  WITH CHECK ADD  CONSTRAINT [FK_PlatformBuildFiles_Paths] FOREIGN KEY([PathID])
REFERENCES [dbo].[Paths] ([ID])
GO
ALTER TABLE [dbo].[PlatformBuildFiles] CHECK CONSTRAINT [FK_PlatformBuildFiles_Paths]
GO
/****** Object:  ForeignKey [FK_PlatformBuildFiles_PlatformBuilds]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[PlatformBuildFiles]  WITH CHECK ADD  CONSTRAINT [FK_PlatformBuildFiles_PlatformBuilds] FOREIGN KEY([PlatformBuildID])
REFERENCES [dbo].[PlatformBuilds] ([ID])
GO
ALTER TABLE [dbo].[PlatformBuildFiles] CHECK CONSTRAINT [FK_PlatformBuildFiles_PlatformBuilds]
GO
/****** Object:  ForeignKey [FK_PlatformBuilds_DefinesA]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[PlatformBuilds]  WITH CHECK ADD  CONSTRAINT [FK_PlatformBuilds_DefinesA] FOREIGN KEY([DefineAID])
REFERENCES [dbo].[Defines] ([ID])
GO
ALTER TABLE [dbo].[PlatformBuilds] CHECK CONSTRAINT [FK_PlatformBuilds_DefinesA]
GO
/****** Object:  ForeignKey [FK_PlatformBuilds_DefinesB]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[PlatformBuilds]  WITH CHECK ADD  CONSTRAINT [FK_PlatformBuilds_DefinesB] FOREIGN KEY([DefineBID])
REFERENCES [dbo].[Defines] ([ID])
GO
ALTER TABLE [dbo].[PlatformBuilds] CHECK CONSTRAINT [FK_PlatformBuilds_DefinesB]
GO
/****** Object:  ForeignKey [FK_PlatformBuilds_PlatformBuildStatuses]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[PlatformBuilds]  WITH CHECK ADD  CONSTRAINT [FK_PlatformBuilds_PlatformBuildStatuses] FOREIGN KEY([StatusID])
REFERENCES [dbo].[PlatformBuildStatuses] ([ID])
GO
ALTER TABLE [dbo].[PlatformBuilds] CHECK CONSTRAINT [FK_PlatformBuilds_PlatformBuildStatuses]
GO
/****** Object:  ForeignKey [FK_PlatformBuilds_Platforms]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[PlatformBuilds]  WITH CHECK ADD  CONSTRAINT [FK_PlatformBuilds_Platforms] FOREIGN KEY([PlatformID])
REFERENCES [dbo].[Platforms] ([ID])
GO
ALTER TABLE [dbo].[PlatformBuilds] CHECK CONSTRAINT [FK_PlatformBuilds_Platforms]
GO
/****** Object:  ForeignKey [FK_PlatformBuilds_Projects]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[PlatformBuilds]  WITH CHECK ADD  CONSTRAINT [FK_PlatformBuilds_Projects] FOREIGN KEY([ProjectID])
REFERENCES [dbo].[Projects] ([ID])
GO
ALTER TABLE [dbo].[PlatformBuilds] CHECK CONSTRAINT [FK_PlatformBuilds_Projects]
GO
/****** Object:  ForeignKey [FK_Jobs_ClientMachines]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[Tasks]  WITH CHECK ADD  CONSTRAINT [FK_Jobs_ClientMachines] FOREIGN KEY([ClientMachineID])
REFERENCES [dbo].[ClientMachines] ([ID])
GO
ALTER TABLE [dbo].[Tasks] CHECK CONSTRAINT [FK_Jobs_ClientMachines]
GO
/****** Object:  ForeignKey [FK_Jobs_JobStatus]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[Tasks]  WITH CHECK ADD  CONSTRAINT [FK_Jobs_JobStatus] FOREIGN KEY([StatusID])
REFERENCES [dbo].[TaskStatuses] ([ID])
GO
ALTER TABLE [dbo].[Tasks] CHECK CONSTRAINT [FK_Jobs_JobStatus]
GO
/****** Object:  ForeignKey [FK_Tasks_BuildConfigs]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[Tasks]  WITH CHECK ADD  CONSTRAINT [FK_Tasks_BuildConfigs] FOREIGN KEY([BuildConfigID])
REFERENCES [dbo].[BuildConfigs] ([ID])
GO
ALTER TABLE [dbo].[Tasks] CHECK CONSTRAINT [FK_Tasks_BuildConfigs]
GO
/****** Object:  ForeignKey [FK_Tasks_PlatformBuilds]    Script Date: 04/05/2011 18:04:58 ******/
ALTER TABLE [dbo].[Tasks]  WITH CHECK ADD  CONSTRAINT [FK_Tasks_PlatformBuilds] FOREIGN KEY([PlatformBuildID])
REFERENCES [dbo].[PlatformBuilds] ([ID])
GO
ALTER TABLE [dbo].[Tasks] CHECK CONSTRAINT [FK_Tasks_PlatformBuilds]
GO
