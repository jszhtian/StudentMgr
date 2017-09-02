USE [ZZU-DB]
GO
CREATE TABLE [MajorinUDE](
	[MajorUUID] [uniqueidentifier] NOT NULL Default(newsequentialid()),
	[MajorName] [nvarchar](50) NOT NULL Unique,
	[Supervisor] [nvarchar](50) NOT NULL,
	Primary Key([MajorUUID]),
)
Go
